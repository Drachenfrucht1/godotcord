#include "godotcord_network_peer.h"
#include "discord-files/discord.h"
#include "core/io/marshalls.h"

void NetworkedMultiplayerDiscord::init_discord(Ref<Godotcord> godotcord) {
	lobby_manager = &(godotcord->get_core()->LobbyManager());

	discord::User user{};
	godotcord->get_core()->UserManager().GetCurrentUser(&user);
	unique_id = user.GetId();

	//LobbyNetworkMessage handler
	lobby_manager->OnNetworkMessage.Connect([this](int64_t p_lobby_id, int64_t p_user_id, int p_channel, uint8_t *data, int64_t a) {
		print_line("Message arrived");
		if (data[0] == 'c') {
			//custom event
		} else if (data[0] == 'b') {
			Packet p;
			p.channel = p_channel;
			p.from = p_user_id;
			p.data = &data[5];
			p.size = decode_uint32(&data[1]);

			incomming_packets.push_back(p);
		}

		return 0;
	});

	lobby_manager->OnMemberConnect.Connect([this](int64_t p_lobby_id, int64_t p_user_id) {
		if (p_lobby_id != lobby_id)
			return;

		peers.push_back(p_user_id);

		emit_signal("peer_connected", p_user_id);
	});

	lobby_manager->OnMemberDisconnect.Connect([this](int64_t p_lobby_id, int64_t p_user_id) {
		if (p_lobby_id != lobby_id)
			return;
		peers.erase(p_user_id);

		emit_signal("peer_disconnected", p_user_id);
	});

	//LobbyDelete handler
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

			lobby_manager->ConnectNetwork(lobby_id);
			lobby_manager->OpenNetworkChannel(lobby_id, 0, true);
			lobby_manager->OpenNetworkChannel(lobby_id, 0, false);

			server_peer = unique_id;
			unique_id = 1;



			emit_signal("created_lobby");
			//SetOwner causes currently crash of game
			/*discord::LobbyTransaction uxn{};
			lobby_manager->GetLobbyUpdateTransaction(lobby_id, &uxn);
			uxn.SetOwner(unique_id);
			lobby_manager->UpdateLobby(lobby_id, uxn, [](discord::Result result) {
				if (result != discord::Result::Ok) {
					//error
				}
			});*/
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

			lobby_manager->ConnectNetwork(lobby_id);
			lobby_manager->OpenNetworkChannel(lobby_id, 0, true);
			lobby_manager->OpenNetworkChannel(lobby_id, 0, false);

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
				result = lobby_manager->GetMemberMetadataValue(lobby_id, user_id, "server", value);

				if (value == "true" && result == discord::Result::Ok) {
					peers.push_back(user_id);
					server_peer = user_id;
				} else {
					peers.push_back(user_id);
				}
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

			lobby_manager->ConnectNetwork(lobby_id);
			lobby_manager->OpenNetworkChannel(lobby_id, 0, true);
			lobby_manager->OpenNetworkChannel(lobby_id, 0, false);

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
				result = lobby_manager->GetMemberMetadataValue(lobby_id, user_id, "server", value);

				if (value == "true" && result == discord::Result::Ok) {
					peers.push_back(user_id);
					server_peer = user_id;
				} else {
					peers.push_back(user_id);
				}
			}

			emit_signal("connection_succeeded");
		} else {
			connection_status = CONNECTION_DISCONNECTED;
			emit_signal("connection_failed");
		}
	});

	return OK;
}

void NetworkedMultiplayerDiscord::poll() {
	_pop_current_packet();
	//handle disconnect packet
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

	*r_buffer = (const uint8_t *)(&current_packet.data);
	r_buffer_size = sizeof(current_packet.data);

	return OK;
}

Error NetworkedMultiplayerDiscord::put_packet(const uint8_t *p_buffer, int p_buffer_size) {
	ERR_FAIL_COND_V_MSG(!active, ERR_UNCONFIGURED, "The multiplayer instance isn't currently active.");
	ERR_FAIL_COND_V_MSG(connection_status != CONNECTION_CONNECTED, ERR_UNCONFIGURED, "The multiplayer instance isn't currently connected to any server or client.");

	int packet_flags = 0;
	int channel = 0;

	uint32_t size = p_buffer_size;

	uint8_t *data = (uint8_t*)memalloc(sizeof(uint8_t) * (size + 5));
	data[0] = 'i';
	encode_uint32(size, &data[1]);
	copymem(&data[5], p_buffer, size);

	if (transfer_mode == TRANSFER_MODE_UNRELIABLE) {
		channel = 1;
	}

	if (target_peer > 0) {
		if (peers.find(target_peer) != NULL) {
			discord::Result result;
			if (target_peer == 1) {
				target_peer = server_peer;
			}
			result = lobby_manager->SendNetworkMessage(lobby_id, target_peer, channel, data, (size + 5));
			ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, Error::ERR_CANT_RESOLVE, vformat("Failed to send message to %d", target_peer))
		} else {
			ERR_FAIL_V_MSG(Error::ERR_INVALID_PARAMETER, "Couldn't find peer id: %d", target_peer);
		}
	} else if (target_peer == 0) {
		discord::Result result;
		for (List<int64_t>::Element *E = peers.front(); E;E=E->next()) {
			result = lobby_manager->SendNetworkMessage(lobby_id, E->get(), channel, data, (size + 5));
			ERR_CONTINUE_MSG(result != discord::Result::Ok, vformat("Couldn't send message to user &d", E->get()));
		}
	} else {
		target_peer *= -1;
		if (peers.find(target_peer) != NULL) {
			discord::Result result;
			if (target_peer == 1) {
				target_peer = server_peer;
			}
			for (List<int64_t>::Element *E = peers.front(); E; E = E->next()) {
				if (E->get() == target_peer)
					continue;
				result = lobby_manager->SendNetworkMessage(lobby_id, E->get(), channel, data, (size + 5));
				ERR_CONTINUE_MSG(result != discord::Result::Ok, vformat("Couldn't send message to user &d", E->get()));
			}
		} else {
			ERR_FAIL_V_MSG(Error::ERR_INVALID_PARAMETER, "Couldn't find peer id: %d", target_peer);
		}
	}

	lobby_manager->FlushNetwork();

	return OK;
}

int NetworkedMultiplayerDiscord::get_max_packet_size() const {

	return 1 << 24; // Anything is good
}

void NetworkedMultiplayerDiscord::_pop_current_packet() {
	if (current_packet.data) {
		memfree(current_packet.data);
		current_packet.data = NULL;
		current_packet.from = -0;
		current_packet.channel = -1;
	}
}

NetworkedMultiplayerPeer::ConnectionStatus NetworkedMultiplayerDiscord::get_connection_status() const {

	return connection_status;
}

int NetworkedMultiplayerDiscord::get_unique_id() const {

	ERR_FAIL_COND_V_MSG(!active, 0, "The multiplayer instance isn't currently active.");
	return unique_id;
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

	ADD_SIGNAL(MethodInfo("created_lobby"));
}

int NetworkedMultiplayerDiscord::get_lobby_id() const {
	ERR_FAIL_COND_V_MSG(!active, -1, "The multiplayer instance is not active currently.");

	return lobby_id;
}

String NetworkedMultiplayerDiscord::get_lobby_secret() {
	ERR_FAIL_COND_V_MSG(!active, "", "The multiplayer instance is not active currently.");

	discord::Lobby lobby;
	lobby_manager->GetLobby(lobby_id, &lobby);
	String s(lobby.GetSecret());
	return s;
}

String NetworkedMultiplayerDiscord::get_lobby_activity_secret() {
	ERR_FAIL_COND_V_MSG(!active, "", "The multiplayer instance is not active currently.");

	char c_str[128];
	lobby_manager->GetLobbyActivitySecret(lobby_id, c_str);
	String s(c_str);
	return s;
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
}

NetworkedMultiplayerDiscord::~NetworkedMultiplayerDiscord() {
	if (active) {
		close_connection();
	}
}
