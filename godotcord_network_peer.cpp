#include "godotcord_network_peer.h"
#include "discord-files/discord.h"
#include "core/io/marshalls.h"
#include "core/os/os.h"
#include "inttypes.h"

uint64_t NetworkedMultiplayerDiscord::unique_peer_id;
int64_t NetworkedMultiplayerDiscord::local_user_id;
String NetworkedMultiplayerDiscord::route;

Error NetworkedMultiplayerDiscord::init_discord(Ref<Godotcord> godotcord) {
	lobby_manager = &(godotcord->get_core()->LobbyManager());
	network_manager = &(godotcord->get_core()->NetworkManager());

	NetworkedMultiplayerDiscord::route = godotcord->get_route();
	godotcord->removeRouteEvent();

	discord::User user{};
	discord::Result result = godotcord->get_core()->UserManager().GetCurrentUser(&user);
	ERR_FAIL_COND_V(result != discord::Result::Ok, ERR_SKIP);
	NetworkedMultiplayerDiscord::local_user_id = user.GetId();

	network_manager->GetPeerId(&NetworkedMultiplayerDiscord::unique_peer_id);
	print_line(vformat("Peer id is %d", NetworkedMultiplayerDiscord::unique_peer_id));

	//LOBBY EVENTS
	lobby_manager->OnMemberConnect.Connect([this](int64_t p_lobby_id, int64_t p_user_id) {
		if (p_lobby_id != lobby_id)
			return;

		int target = _gen_unique_id();
		GodotcordPeer p;
		p.discord_id = p_user_id;
		p.target_id = target;

		peers.push_back(p);
	});

	lobby_manager->OnMemberDisconnect.Connect([this](int64_t p_lobby_id, int64_t p_user_id) {
		if (p_lobby_id != lobby_id)
			return;
		peers.erase(*_get_peer_by_discord_id(p_user_id));

		emit_signal("peer_disconnected", p_user_id);
	});

	lobby_manager->OnLobbyDelete.Connect([this](int64_t p_lobby_id, uint32_t p_reason) {
		if (lobby_id == p_lobby_id) {
			lobby_manager->DisconnectNetwork(p_lobby_id); //try if it has to be called
			lobby_manager->DisconnectLobby(p_lobby_id, [](discord::Result result) {
				if (result != discord::Result::Ok) {
					//error
				}
			});
			lobby_id = 0;
			connection_status = CONNECTION_DISCONNECTED;
			active = false;
			server = false;

			emit_signal("server_disconnected");
		}
	});

	lobby_manager->OnMemberUpdate.Connect([this](int64_t p_lobby_id, int64_t p_user_id) {
		if (p_user_id == NetworkedMultiplayerDiscord::local_user_id) {
			char peer_id[4096];
			lobby_manager->GetMemberMetadataValue(lobby_id, p_user_id, "peer_id", peer_id);

			String s(peer_id);
			Variant v(s);
			uint64_t t = static_cast<uint64_t>((int64_t)v);
			return;
		}

		GodotcordPeer peer = *_get_peer_by_discord_id(p_user_id);
		if (peer.discord_peer_id != 0) {
			char route[4096];
			lobby_manager->GetMemberMetadataValue(lobby_id, p_user_id, "route", route);

			network_manager->UpdatePeer(peer.discord_peer_id, route);

		} else {
			_setup_peer(p_user_id, true);
			emit_signal("peer_connected", peer.target_id);
		}
	});

	lobby_manager->OnLobbyMessage.Connect([this](int64_t p_lobby_id, int64_t p_user_id, uint8_t *data, uint32_t p_length) {
		print_line("Received lobby message");
		if (data[0] == 'c' && p_length == 17) {
			uint64_t l_p_id = decode_uint64(&data[9]);
			if (l_p_id == NetworkedMultiplayerDiscord::unique_peer_id) {
				uint64_t p_id = decode_uint64(&data[1]);
				_get_peer_by_discord_peer_id(p_id)->confirmed = true;
				_resend_messages();
			}
		}
	});

	//NETWORK EVENTS
	network_manager->OnMessage.Connect([this](uint64_t p_peer_id, int p_channel, uint8_t *data, uint32_t discord_size) {
		print_line("Message arrived");
		if (data[0] == 'c') {
			//custom event
		} else if (data[0] == 'i') {
			Packet p;
			p.channel = p_channel;
			p.from = _get_peer_by_discord_peer_id(p_peer_id)->target_id;
			p.size = decode_uint32(&data[1]);
			p.data = (uint8_t *)memalloc(p.size);
			memcpy(&p.data[0], &data[5], p.size);
			//&p.data[0] = &data[5];
			

			incomming_packets.push_back(p);
		}

		return 0;
	});

	network_manager->OnRouteUpdate.Connect([this](const char *p_route) {
		NetworkedMultiplayerDiscord::route = String(p_route);
		print_line(vformat("Route is %s", NetworkedMultiplayerDiscord::route));
		if (!active)
			return;
		discord::LobbyMemberTransaction txn{};
		discord::Result result = lobby_manager->GetMemberUpdateTransaction(lobby_id, NetworkedMultiplayerDiscord::local_user_id, &txn);
		ERR_FAIL_COND(result != discord::Result::Ok)
		txn.SetMetadata("route", NetworkedMultiplayerDiscord::route.utf8());

		lobby_manager->UpdateMember(lobby_id, NetworkedMultiplayerDiscord::local_user_id, txn, [](discord::Result result) {
			if (result != discord::Result::Ok) {
				//error
			}
		});
	});

	return OK;
}

void NetworkedMultiplayerDiscord::set_transfer_mode(TransferMode p_mode) {
    transfer_mode = p_mode;
}

NetworkedMultiplayerPeer::TransferMode NetworkedMultiplayerDiscord::get_transfer_mode() const {
    return transfer_mode;
}

void NetworkedMultiplayerDiscord::set_target_peer(int p_peer) {
	target_peer = p_peer;
}

int NetworkedMultiplayerDiscord::get_packet_peer() const {
	ERR_FAIL_COND_V_MSG(!active, -1, "The multiplayer instance isn't currently active.");
	ERR_FAIL_COND_V(incomming_packets.size() == 0, 1);

	return incomming_packets.front()->get().from;
}

Error NetworkedMultiplayerDiscord::create_lobby(int size, bool pub) {
	ERR_FAIL_COND_V_MSG(active, ERR_ALREADY_IN_USE, "The multiplayer instance is already active.");
	ERR_FAIL_COND_V_MSG(size < 1, ERR_INVALID_PARAMETER, "Size must be >= 1.");

	discord::LobbyTransaction txn{};
	lobby_manager->GetLobbyCreateTransaction(&txn);

	txn.SetCapacity(size);

	if (pub) {
		txn.SetType(discord::LobbyType::Public);
	} else {
		txn.SetType(discord::LobbyType::Private);
	}
	connection_status = CONNECTION_CONNECTING;

	lobby_manager->CreateLobby(txn, [this](discord::Result result, discord::Lobby lobby) {
		if (result == discord::Result::Ok) {
			lobby_id = lobby.GetId();
			server = true;
			active = true;
			connection_status = CONNECTION_CONNECTED;

			_store_connection_details();

			GodotcordPeer p;
			p.discord_id = NetworkedMultiplayerDiscord::local_user_id;
			p.target_id = 1;
			peers.push_back(p);

			unique_id = 1;


			emit_signal("peer_connected", unique_id);
			emit_signal("created_lobby");
		} else {
			connection_status = CONNECTION_DISCONNECTED;
		}
	});

	return Error::OK;
}

Error NetworkedMultiplayerDiscord::join_lobby(int id, String secret) {
	ERR_FAIL_COND_V_MSG(active, ERR_ALREADY_IN_USE, "The multiplayer instance is already active.");

	connection_status = CONNECTION_CONNECTING;
	lobby_manager->ConnectLobby(id, secret.utf8(), [this](discord::Result result, discord::Lobby lobby) {
		if (result == discord::Result::Ok) {
			lobby_id = lobby.GetId();
			server = false;
			active = true;
			connection_status = CONNECTION_CONNECTED;

			_store_connection_details();

			//add all already connected peers to peers list
			int32_t count;
			discord::Result result;
			result = lobby_manager->MemberCount(lobby_id, &count);
			ERR_FAIL_COND(result != discord::Result::Ok);
			discord::UserId user_id;
			char *value = (char *)memalloc(sizeof(char) * 5);

			for (int i = 0; i < count; i++) {
				result = lobby_manager->GetMemberUserId(lobby_id, i, &user_id);
				ERR_CONTINUE(result != discord::Result::Ok);

				int peer_id;
				if (lobby.GetOwnerId() == user_id) {
					peer_id = 1;
				} else {
					peer_id = _gen_unique_id();
				}

				GodotcordPeer p;
				p.discord_id = user_id;
				p.target_id = peer_id;
				peers.push_back(p);

				if (user_id != NetworkedMultiplayerDiscord::local_user_id) {
					_setup_peer(user_id, false);
				} else {
					unique_id = peer_id;
				}

				emit_signal("peer_connected", peer_id);
			}

			emit_signal("connection_succeeded");
		} else {
			connection_status = CONNECTION_DISCONNECTED;
			emit_signal("connection_failed");
		}
	});

	return OK;
}

Error NetworkedMultiplayerDiscord::join_lobby_activity(String activitySecret) {
	ERR_FAIL_COND_V_MSG(active, ERR_ALREADY_IN_USE, "The multiplayer instance is already active.");

	connection_status = CONNECTION_CONNECTING;
	lobby_manager->ConnectLobbyWithActivitySecret(activitySecret.utf8(), [this](discord::Result result, discord::Lobby lobby) {
		if (result == discord::Result::Ok) {
			lobby_id = lobby.GetId();
			server = false;
			active = true;
			connection_status = CONNECTION_CONNECTED;

			_store_connection_details();

			//add all already connected peers to peers list
			int32_t count;
			discord::Result result;
			result = lobby_manager->MemberCount(lobby_id, &count);
			ERR_FAIL_COND(result != discord::Result::Ok);
			discord::UserId user_id;

			for (int i = 0; i < count; i++) {
				result = lobby_manager->GetMemberUserId(lobby_id, i, &user_id);
				ERR_CONTINUE(result != discord::Result::Ok);

				int peer_id;
				if (lobby.GetOwnerId() == user_id) {
					peer_id = 1;
				} else {
					peer_id = _gen_unique_id();
				}

				GodotcordPeer p;
				p.discord_id = user_id;
				p.target_id = peer_id;
				peers.push_back(p);

				if (user_id != NetworkedMultiplayerDiscord::local_user_id) {
					_setup_peer(user_id, false);
				} else {
					unique_id = peer_id;
				}
					
				emit_signal("peer_connected", peer_id);
			}

			emit_signal("connection_succeeded");
		} else {
			connection_status = CONNECTION_DISCONNECTED;
			emit_signal("connection_failed");
		}
	});

	return OK;
}

void NetworkedMultiplayerDiscord::_setup_peer(int64_t p_user_id, bool confirm) {
	discord::Result result;

	char peer_id[4096];
	char route[4096];
	result = lobby_manager->GetMemberMetadataValue(lobby_id, p_user_id, "peer_id", peer_id);
	ERR_FAIL_COND(result != discord::Result::Ok)
	result = lobby_manager->GetMemberMetadataValue(lobby_id, p_user_id, "route", route);
	ERR_FAIL_COND(result != discord::Result::Ok)

	String s(peer_id);
	Variant v(s);
	uint64_t p_id = static_cast<uint64_t>((int64_t)v);

	print_line(vformat("Opening connection to %d via %s", p_id, route));

	result = network_manager->OpenPeer(p_id, String(route).utf8());
	ERR_FAIL_COND(result != discord::Result::Ok)
	result = network_manager->OpenChannel(p_id, 0, true);
	ERR_FAIL_COND(result != discord::Result::Ok)
	result = network_manager->OpenChannel(p_id, 1, false);
	ERR_FAIL_COND(result != discord::Result::Ok)

	GodotcordPeer *p = _get_peer_by_discord_id(p_user_id);
	ERR_FAIL_COND(p == NULL)
	p->discord_peer_id = p_id;

	if (confirm) {
		//size 'c' + this->peer_id + confirm->peer_id
		//size 1   +  8      +   8
		uint8_t *data = (uint8_t *)memalloc(17);
		data[0] = 'c';
		encode_uint64(NetworkedMultiplayerDiscord::unique_peer_id, &data[1]);
		encode_uint64(p_id, &data[9]);

		lobby_manager->SendLobbyMessage(lobby_id, data, 17, [](discord::Result result) {
			ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Couldn't send confirm message to other lobby members")
		});

		p->confirmed = true;
	}
}

void NetworkedMultiplayerDiscord::_store_connection_details() {
	ERR_FAIL_COND(!active)
	discord::LobbyMemberTransaction txn{};
	discord::Result result = lobby_manager->GetMemberUpdateTransaction(lobby_id, NetworkedMultiplayerDiscord::local_user_id, &txn);
	ERR_FAIL_COND(result != discord::Result::Ok)

	int64_t i = static_cast<int64_t>(NetworkedMultiplayerDiscord::unique_peer_id);
	Variant v(i);
	String s = (String) v;
	txn.SetMetadata("peer_id", s.utf8());
	txn.SetMetadata("route", NetworkedMultiplayerDiscord::route.utf8());

	lobby_manager->UpdateMember(lobby_id, NetworkedMultiplayerDiscord::local_user_id, txn, [](discord::Result result) {
		if (result != discord::Result::Ok) {
		}
	});
}

void NetworkedMultiplayerDiscord::_resend_messages() {
	discord::Result result;
	for (List<Packet>::Element *E = defered_packets.front(); E; E = E->next()) {
		GodotcordPeer *peer = _get_peer_by_target_id(E->get().from);
		if (peer->confirmed) {
			 result = network_manager->SendMessage(peer->discord_peer_id, E->get().channel, E->get().data, E->get().size);
			print_line(vformat("Sending message to userid %d", peer->discord_id));
			ERR_FAIL_COND_MSG(result != discord::Result::Ok, vformat("Failed to send message to %d", target_peer))

			defered_packets.erase(E);
		}
	}
}

NetworkedMultiplayerDiscord::GodotcordPeer *NetworkedMultiplayerDiscord::_get_peer_by_discord_id(int64_t p_user_id) {
	for (List<GodotcordPeer>::Element *E = peers.front(); E; E = E->next()) {
		if (E->get().discord_id == p_user_id) {
			return &(E->get());
		}
	}

	return NULL;
}

NetworkedMultiplayerDiscord::GodotcordPeer *NetworkedMultiplayerDiscord::_get_peer_by_discord_peer_id(uint64_t p_peer_id) {
	for (List<GodotcordPeer>::Element *E = peers.front(); E; E = E->next()) {
		if (E->get().discord_peer_id == p_peer_id) {
			return &(E->get());
		}
	}

	return NULL;
}

NetworkedMultiplayerDiscord::GodotcordPeer *NetworkedMultiplayerDiscord::_get_peer_by_target_id(int p_target_id) {
	for (List<GodotcordPeer>::Element *E = peers.front(); E; E = E->next()) {
		if (E->get().target_id == p_target_id) {
			return &(E->get());
		}
	}

	return NULL;
}

void NetworkedMultiplayerDiscord::poll() {
	_pop_current_packet();

	discord::Result result = network_manager->Flush();
	ERR_FAIL_COND(result != discord::Result::Ok)
}

bool NetworkedMultiplayerDiscord::is_server() const {
	ERR_FAIL_COND_V_MSG(!active, false, "The multiplayer instance isn't currently active");

	return server;
}

void NetworkedMultiplayerDiscord::close_connection() {
	connection_status = CONNECTION_DISCONNECTED;
	lobby_manager->DisconnectNetwork(lobby_id);
	lobby_manager->DisconnectLobby(lobby_id, [this](discord::Result result) {
		if (result != discord::Result::Ok) {
			//error
		}

		emit_signal("server_disconnected");
	});

	active = false;
}

void NetworkedMultiplayerDiscord::disconnect_peer(int p_peer) {
	ERR_FAIL_COND_MSG(!active, "The multiplayer instance isn't currently active.");
	ERR_FAIL_COND_MSG(!is_server(), "Can't remove peer from lobby when not lobby owner.");

	//impl by sending disconnect message to person 
}

int NetworkedMultiplayerDiscord::get_available_packet_count() const {
	return incomming_packets.size();
}

Error NetworkedMultiplayerDiscord::get_packet(const uint8_t **r_buffer, int &r_buffer_size) {
	ERR_FAIL_COND_V_MSG(incomming_packets.size() == 0, ERR_UNAVAILABLE, "No incomming packets available.");

	_pop_current_packet();

	current_packet = incomming_packets.front()->get();
	incomming_packets.pop_front();

	*r_buffer = (const uint8_t *)(&current_packet.data[0]);
	r_buffer_size = current_packet.size;

	return OK;
}

Error NetworkedMultiplayerDiscord::put_packet(const uint8_t *p_buffer, int p_buffer_size) {
	ERR_FAIL_COND_V_MSG(!active, ERR_UNCONFIGURED, "The multiplayer instance isn't currently active.");
	ERR_FAIL_COND_V_MSG(connection_status != CONNECTION_CONNECTED, ERR_UNCONFIGURED, "The multiplayer instance isn't currently connected to any server or client.");

	if (target_peer == unique_id || target_peer * -1 == unique_id)
		return ERR_INVALID_PARAMETER;

	uint8_t channel = 0;
	uint32_t discord_size = p_buffer_size + 5;

	uint8_t *data = (uint8_t*)memalloc(discord_size);
	data[0] = 'i';
	encode_uint32(p_buffer_size, &data[1]);
	copymem(&data[5], p_buffer, p_buffer_size);

	if (transfer_mode == TRANSFER_MODE_UNRELIABLE) {
		channel = 1;
	}

	if (target_peer > 0) {
		GodotcordPeer *peer = _get_peer_by_target_id(target_peer);
		ERR_FAIL_COND_V_MSG(peer->discord_peer_id == NULL, Error::ERR_INVALID_PARAMETER, vformat("Couldn't find peer id: %d", target_peer))
		if (peer->confirmed) {
			discord::Result result;
			result = network_manager->SendMessage(peer->discord_peer_id, channel, data, discord_size);
			print_line(vformat("Sending message to userid %d", peer->discord_id));
			ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, Error::ERR_CANT_RESOLVE, vformat("Failed to send message to %d", target_peer))
		} else {
			Packet p;
			p.data = data;
			p.from = target_peer;
			p.channel = channel;
			p.size = discord_size;
			defered_packets.push_back(p);
		}
	} else if (target_peer == 0) {
		discord::Result result;
		for (List<GodotcordPeer>::Element *E = peers.front(); E; E = E->next()) {
			if (E->get().confirmed) {
				result = network_manager->SendMessage(E->get().discord_peer_id,channel, data, discord_size);
				print_line(vformat("Sending message to userid %d", E->get().discord_id));
				ERR_CONTINUE_MSG(result != discord::Result::Ok, vformat("Couldn't send message to userid &d", E->get().discord_id))
			} else {
				Packet p;
				p.data = data;
				p.from = E->get().target_id;
				p.channel = channel;
				p.size = discord_size;
				defered_packets.push_back(p);
			}
		}
	} else {
		target_peer *= -1;
		discord::Result result;
		for (List<GodotcordPeer>::Element *E = peers.front(); E; E = E->next()) {
			if (E->get().target_id == target_peer)
				continue;

			if (E->get().confirmed) {
				result = network_manager->SendMessage(E->get().discord_peer_id, channel, data, discord_size);
				print_line(vformat("Sending message to userid %d", E->get().discord_id));
				ERR_CONTINUE_MSG(result != discord::Result::Ok, vformat("Couldn't send message to userid &d", E->get().discord_id))
			} else {
				Packet p;
				p.data = data;
				p.from = E->get().target_id;
				p.channel = channel;
				p.size = discord_size;
				defered_packets.push_back(p);
			}
		}
	}

	return OK;
}

int NetworkedMultiplayerDiscord::get_max_packet_size() const {

	return 1 << 24; // Anything is good
}

void NetworkedMultiplayerDiscord::_pop_current_packet() {
	if (current_packet.data) {
		memfree(current_packet.data);
		current_packet.data = NULL;
		current_packet.from = 0;
		current_packet.channel = -1;
		current_packet.size = 0;
	}
}

NetworkedMultiplayerPeer::ConnectionStatus NetworkedMultiplayerDiscord::get_connection_status() const {

	return connection_status;
}

int NetworkedMultiplayerDiscord::get_unique_id() const {

	ERR_FAIL_COND_V_MSG(!active, 0, "The multiplayer instance isn't currently active.");
	return unique_id;
}

uint32_t NetworkedMultiplayerDiscord::_gen_unique_id() const {

	uint32_t hash = 0;

	while (hash == 0 || hash == 1) {

		hash = hash_djb2_one_32(
				(uint32_t)OS::get_singleton()->get_ticks_usec());
		hash = hash_djb2_one_32(
				(uint32_t)OS::get_singleton()->get_unix_time(), hash);
		hash = hash_djb2_one_32(
				(uint32_t)OS::get_singleton()->get_user_data_dir().hash64(), hash);
		hash = hash_djb2_one_32(
				(uint32_t)((uint64_t)this), hash); // Rely on ASLR heap
		hash = hash_djb2_one_32(
				(uint32_t)((uint64_t)&hash), hash); // Rely on ASLR stack

		hash = hash & 0x7FFFFFFF; // Make it compatible with unsigned, since negative ID is used for exclusion
	}

	return hash;
}

void NetworkedMultiplayerDiscord::set_refuse_new_connections(bool p_enable) {
	discord::LobbyTransaction txn{};
	lobby_manager->GetLobbyUpdateTransaction(lobby_id, &txn);

	txn.SetLocked(p_enable);

	lobby_manager->UpdateLobby(lobby_id, txn, [](discord::Result result) {
		if (result != discord::Result::Ok) {
			//error
		}
	});

	refuse_connections = p_enable;
}

bool NetworkedMultiplayerDiscord::is_refusing_new_connections() const {
	return refuse_connections;
}

void NetworkedMultiplayerDiscord::_bind_methods() {
	ClassDB::bind_method(D_METHOD("create_lobby", "max_clients", "public"), &NetworkedMultiplayerDiscord::create_lobby);
	ClassDB::bind_method(D_METHOD("join_lobby", "id", "secret"), &NetworkedMultiplayerDiscord::join_lobby);
	ClassDB::bind_method(D_METHOD("join_server_activity", "secret"), &NetworkedMultiplayerDiscord::join_lobby_activity);
	ClassDB::bind_method(D_METHOD("close_connection"), &NetworkedMultiplayerDiscord::close_connection);
	ClassDB::bind_method(D_METHOD("disconnect_perr", "id"), &NetworkedMultiplayerDiscord::disconnect_peer);
	ClassDB::bind_method(D_METHOD("init_discord", "discord"), &NetworkedMultiplayerDiscord::init_discord);
	ClassDB::bind_method(D_METHOD("get_lobby_id"), &NetworkedMultiplayerDiscord::get_lobby_id);
	ClassDB::bind_method(D_METHOD("get_lobby_secret"), &NetworkedMultiplayerDiscord::get_lobby_secret);
	ClassDB::bind_method(D_METHOD("get_lobby_activity_secret"), &NetworkedMultiplayerDiscord::get_lobby_activity_secret);
	ClassDB::bind_method(D_METHOD("get_current_members"), &NetworkedMultiplayerDiscord::get_current_members);
	ClassDB::bind_method(D_METHOD("get_max_members"), &NetworkedMultiplayerDiscord::get_max_members);

	ADD_SIGNAL(MethodInfo("created_lobby"));
}

int NetworkedMultiplayerDiscord::get_lobby_id() const {
	ERR_FAIL_COND_V_MSG(!active, -1, "The multiplayer instance is not active currently.");

	return lobby_id;
}

String NetworkedMultiplayerDiscord::get_lobby_secret() const {
	ERR_FAIL_COND_V_MSG(!active, "", "The multiplayer instance is not active currently.")

	discord::Lobby lobby;
	lobby_manager->GetLobby(lobby_id, &lobby);
	String s(lobby.GetSecret());
	return s;
}

String NetworkedMultiplayerDiscord::get_lobby_activity_secret() const {
	ERR_FAIL_COND_V_MSG(!active, "", "The multiplayer instance is not active currently.")

	char c_str[128];
	lobby_manager->GetLobbyActivitySecret(lobby_id, c_str);
	String s(c_str);
	return s;
}

int NetworkedMultiplayerDiscord::get_current_members() const {
	ERR_FAIL_COND_V_MSG(!active, -1, "The multiplayer instance is not active currently.")
	int32_t count;
	discord::Result result = lobby_manager->MemberCount(lobby_id, &count);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, -1, "Could not get current members")

	return count;
}

int NetworkedMultiplayerDiscord::get_max_members() const {
	ERR_FAIL_COND_V_MSG(!active, -1, "The multiplayer instance is not active currently.")
	discord::Lobby lobby;
	discord::Result result = lobby_manager->GetLobby(lobby_id, &lobby);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, -1, "Could not get max members")

	return lobby.GetCapacity();
}

NetworkedMultiplayerDiscord::NetworkedMultiplayerDiscord() {
	active = false;
	refuse_connections = false;
	server = false;
	target_peer = 1;
	channel_count = 0;
	transfer_mode = TransferMode::TRANSFER_MODE_RELIABLE;
	lobby_id = 0;
	unique_id = 1;
	transfer_channel = 0;
	connection_status = CONNECTION_DISCONNECTED;
	current_packet = {NULL, 0, 0};
	lobby_manager = NULL;
	network_manager = NULL;
}

NetworkedMultiplayerDiscord::~NetworkedMultiplayerDiscord() {
	if (active) {
		close_connection();
	}
}
