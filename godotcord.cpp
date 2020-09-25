#include "godotcord.h"
#include "godotcord_relationship.h"
#include "core/func_ref.h"

Godotcord *Godotcord::singleton = NULL;

Godotcord::Godotcord() {
	_route = String("");

	singleton = this;
}

Godotcord* Godotcord::get_singleton() {
	return singleton;
}

void Godotcord::run_callbacks() {
	if (init_bool) {
		_core->RunCallbacks();
	}
}

void Godotcord::_bind_methods() {
    ClassDB::bind_method(D_METHOD("init", "client_id"), &Godotcord::init);
	ClassDB::bind_method(D_METHOD("init_debug", "client_id", "instance_id"), &Godotcord::init_debug);
	ClassDB::bind_method(D_METHOD("run_callbacks"), &Godotcord::run_callbacks);
    ClassDB::bind_method(D_METHOD("set_activity", "activity" ), &Godotcord::setActivity);
    ClassDB::bind_method(D_METHOD("clear_activity"), &Godotcord::clearActivity);
	ClassDB::bind_method(D_METHOD("search_lobbies", "search_parameters", "limit"), &Godotcord::search_lobbies);
	ClassDB::bind_method(D_METHOD("get_lobbies", "limit"), &Godotcord::get_lobbies);

	ClassDB::bind_method(D_METHOD("get_current_username"), &Godotcord::get_current_username);
	ClassDB::bind_method(D_METHOD("get_current_user_discriminator"), &Godotcord::get_current_user_discriminator);
	ClassDB::bind_method(D_METHOD("get_current_user_id"), &Godotcord::get_current_user_id);

	ClassDB::bind_method(D_METHOD("set_lobby_metadata", "lobby_id", "key", "value"), &Godotcord::set_lobby_metadata);
	ClassDB::bind_method(D_METHOD("get_lobby_metadata", "lobby_id", "key"), &Godotcord::get_lobby_metadata);

	ClassDB::bind_method(D_METHOD("request_profile_picture", "user_id", "size"), &Godotcord::request_profile_picture);

	ClassDB::bind_method(D_METHOD("filter_relationships", "object", "function_name"), &Godotcord::filter_relationships);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "user_name"), "", "get_current_username");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "user_discriminator"), "", "get_current_user_discriminator");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "user_id"), "", "get_current_user_id");

	ADD_SIGNAL(MethodInfo("join_request", PropertyInfo(Variant::STRING, "name"), PropertyInfo(Variant::INT, "id")));
	ADD_SIGNAL(MethodInfo("activity_join", PropertyInfo(Variant::STRING, "secret")));
	ADD_SIGNAL(MethodInfo("search_result", PropertyInfo(Variant::ARRAY, "result")));
	ADD_SIGNAL(MethodInfo("profile_image", PropertyInfo(Variant::INT, "user_id"), PropertyInfo(Variant::POOL_BYTE_ARRAY, "img_data")));

	BIND_ENUM_CONSTANT(LOCAL);
	BIND_ENUM_CONSTANT(DEFAULT);
	BIND_ENUM_CONSTANT(EXTENDED);
	BIND_ENUM_CONSTANT(LOCAL);

	BIND_ENUM_CONSTANT(LESS_THAN_OR_EQUAL);
	BIND_ENUM_CONSTANT(LESS_THAN);
	BIND_ENUM_CONSTANT(EQUAL);
	BIND_ENUM_CONSTANT(GREATER_THAN);
	BIND_ENUM_CONSTANT(GREATER_THAN_OR_EQUAL);
	BIND_ENUM_CONSTANT(NOT_EQUAL);

	BIND_ENUM_CONSTANT(STRING);
	BIND_ENUM_CONSTANT(INT);
}

Error Godotcord::init(discord::ClientId clientId) {
	discord::Result result = discord::Core::Create(clientId, DiscordCreateFlags_Default, &_core);

	ERR_FAIL_COND_V(result != discord::Result::Ok, ERR_CANT_CONNECT);

	init_bool = true;

	_core->SetLogHook(discord::LogLevel::Info, [](discord::LogLevel level, const char *msg) {
		switch (level) {
			case discord::LogLevel::Warn:
				print_line(vformat("[DiscordGameSDK][Warn] %s", msg));
				break;
			case discord::LogLevel::Info:
				print_line(vformat("[DiscordGameSDK][Info] %s", msg));
				break;
			case discord::LogLevel::Error:
				print_error(vformat("[DiscordGameSDK][ERR] %s", msg));
				break;
		}
	});

	_core->ActivityManager().OnActivityJoinRequest.Connect([this](discord::User p_user) {
		emit_signal("join_request", p_user.GetUsername(), p_user.GetId());
	});

	_core->ActivityManager().OnActivityJoin.Connect([this](const char * p_secret) {
		emit_signal("activity_join", String(p_secret));
	});

	_core->UserManager().OnCurrentUserUpdate.Connect([this]() {
		print_verbose("Local Discord user updated");
	});

	_core->NetworkManager().OnRouteUpdate.Connect([this](const char *p_route) {
		_route = String(p_route);
	});

	_core->RelationshipManager().OnRefresh.Connect([this]() {
		print_line("Relationships updated");
	});

	return OK;
}

void Godotcord::init_debug(discord::ClientId clientId, String id) {
#ifdef _WIN32
	_putenv_s("DISCORD_INSTANCE_ID", id.utf8());
#else
	setenv("DISCORD_INSTANCE_ID", id.utf8(), true);
#endif
	print_line(vformat("Set DISCORD_INSTANCE_ID to %s", id));
	print_line(vformat("Read DISCORD_INSTANCE_ID is %s", getenv("DISCORD_INSTANCE_ID")));
    discord::Result result = discord::Core::Create(clientId, DiscordCreateFlags_Default, &_core);

    ERR_FAIL_COND(result != discord::Result::Ok);

	init_bool = true;

	_core->SetLogHook(discord::LogLevel::Info, [](discord::LogLevel level, const char *msg) {
		switch (level) {
			case discord::LogLevel::Warn:
				print_line(vformat("[DiscordGameSDK][Warn] %s", msg));
				break;
			case discord::LogLevel::Info:
				print_line(vformat("[DiscordGameSDK][Info] %s", msg));
				break;
			case discord::LogLevel::Error:
				print_error(vformat("[DiscordGameSDK][ERR] %s", msg));
				break;
		}
	});

	_core->ActivityManager().OnActivityJoinRequest.Connect([this](discord::User p_user) {
		emit_signal("join_request", p_user.GetUsername(), p_user.GetId());
	});

	_core->ActivityManager().OnActivityJoin.Connect([this](const char *p_secret) {
		emit_signal("activity_join", String(p_secret));
	});

	_core->UserManager().OnCurrentUserUpdate.Connect([this]() {
		print_verbose("Local Discord user updated");
	});

	_core->NetworkManager().OnRouteUpdate.Connect([this](const char *p_route) {
		_route = String(p_route);
	});
}

void Godotcord::setActivity(Ref<GodotcordActivity> act) {

    discord::Activity activity{};
    
	if (act->state != "") {
		activity.SetState(act->state.utf8());
	}

	if(act->details != "") {
		activity.SetDetails(act->details.utf8());
	}

	if (act->largeText != "") {
        activity.GetAssets().SetLargeText(act->largeText.utf8());
    }

    if (act->largeImage != "") {
        activity.GetAssets().SetLargeImage(act->largeImage.utf8());
    }

    if (act->smallText != "") {
        activity.GetAssets().SetSmallText(act->smallText.utf8());
    }

    if (act->smallImage != "") {
        activity.GetAssets().SetSmallImage(act->smallImage.utf8());
    }

    if (act->partyID != "") {
        activity.GetParty().SetId(act->partyID.utf8());
    }

    if (act->partyMax >= 0) {
        activity.GetParty().GetSize().SetMaxSize(act->partyMax);
    }    

    if (act->partyCurrent >= 0) {
        activity.GetParty().GetSize().SetCurrentSize(act->partyCurrent);
    }

    if (act->matchSecret != "") {
        activity.GetSecrets().SetMatch(act->matchSecret.utf8());
    }    

    if (act->joinSecret != "") {
        activity.GetSecrets().SetJoin(act->joinSecret.utf8());
    }

    if (act->spectateSecret != "") {
        activity.GetSecrets().SetSpectate(act->spectateSecret.utf8());
    }

    if (act->start != 0) {
        activity.GetTimestamps().SetStart(act->start);
    }

    if (act->end != 0) {
        activity.GetTimestamps().SetEnd(act->end);
    }

    _core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
        if (result != discord::Result::Ok) {
            //error
        }
    });
}

void Godotcord::clearActivity() {
    _core->ActivityManager().ClearActivity([](discord::Result result) {
        if (result != discord::Result::Ok) {
            //error
        }
    });
}

String Godotcord::get_current_username() {
	//has to be added - editor crashed otherwise
	if (!_core)
		return "";
	discord::User user;
	discord::Result result = _core->UserManager().GetCurrentUser(&user);
	ERR_FAIL_COND_V(result != discord::Result::Ok, "");
	return user.GetUsername();
}

String Godotcord::get_current_user_discriminator() {
	//has to be added - editor crashed otherwise
	if (!_core)
		return "";
	discord::User user;
	discord::Result result = _core->UserManager().GetCurrentUser(&user);
	ERR_FAIL_COND_V(result != discord::Result::Ok, "");
	return user.GetDiscriminator();
}

int64_t Godotcord::get_current_user_id() {
	//has to be added - editor crashed otherwise
	if (!_core)
		return 0;
	discord::User user;
	discord::Result result = _core->UserManager().GetCurrentUser(&user);
	ERR_FAIL_COND_V(result != discord::Result::Ok, 0);
	return user.GetId();
}

void Godotcord::set_lobby_metadata(int64_t lobby_id, String key, String value) {

	discord::LobbyTransaction txn{};
	_core->LobbyManager().GetLobbyUpdateTransaction(lobby_id, &txn);

	txn.SetMetadata(key.utf8(), value.utf8());

	_core->LobbyManager().UpdateLobby(lobby_id, txn, [](discord::Result result) {
		ERR_FAIL_COND(result != discord::Result::Ok);
	});
}

String Godotcord::get_lobby_metadata(int64_t lobby_id, String key) {
	char value[4096];

	discord::Result result = _core->LobbyManager().GetLobbyMetadataValue(lobby_id, key.utf8(), value);

	ERR_FAIL_COND_V(result != discord::Result::Ok, "");

	return String(value);
}

void Godotcord::search_lobbies(Variant ref_params, int limit) {
	ERR_FAIL_COND(!ref_params.is_array());
	Array params = ref_params;
	discord::LobbySearchQuery query;
	discord::Result result = _core->LobbyManager().GetSearchQuery(&query);
	ERR_FAIL_COND(result != discord::Result::Ok);

	for (int i = 0; i < params.size(); i++) {
		Variant element = params[i];
		ERR_CONTINUE(element.get_type() != Variant::DICTIONARY);
		Dictionary d = element;

		String property = d.get("property", "");
		int comparison = d.get("comparison", -1);
		int cast = d.get("cast", -1);
		Variant value = d.get("value", "");

		query.Limit(limit);

		if (property == "distance") {
			ERR_CONTINUE(value.get_type() != Variant::INT);
			discord::LobbySearchDistance distance;
			int i_value = value;
			switch (i_value) {
				case LOCAL:
					distance = discord::LobbySearchDistance::Local;
					break;
				case DEFAULT:
					distance = discord::LobbySearchDistance::Default;
					break;
				case EXTENDED:
					distance = discord::LobbySearchDistance::Extended;
					break;
				case GLOBAL:
					distance = discord::LobbySearchDistance::Global;
					break;
				default:
					continue;
			}

			query.Distance(distance);
		}
		else {
			ERR_CONTINUE(property == "" || comparison == -1 || cast == -1 || value.get_type() != Variant::STRING);
			String s_value = value;

			discord::LobbySearchCast d_cast;
			discord::LobbySearchComparison d_comp;

			switch (cast) {
				case STRING:
					d_cast = discord::LobbySearchCast::String;
					break;
				case INT:
					d_cast = discord::LobbySearchCast::Number;
					break;
				default:
					continue;
			}

			switch (comparison) {
				case LESS_THAN_OR_EQUAL:
					d_comp = discord::LobbySearchComparison::LessThanOrEqual;
					break;
				case LESS_THAN:
					d_comp = discord::LobbySearchComparison::LessThan;
					break;
				case EQUAL:
					d_comp = discord::LobbySearchComparison::Equal;
					break;
				case GREATER_THAN:
					d_comp = discord::LobbySearchComparison::GreaterThan;
					break;
				case GREATER_THAN_OR_EQUAL:
					d_comp = discord::LobbySearchComparison::GreaterThanOrEqual;
					break;
				case NOT_EQUAL:
					d_comp = discord::LobbySearchComparison::NotEqual;
					break;
				default:
					continue;
			}

			query.Filter(property.utf8(), d_comp, d_cast, s_value.utf8());
		}
	}

	_core->LobbyManager().Search(query, [this](discord::Result result) {
		ERR_FAIL_COND(result != discord::Result::Ok);

		Vector<Variant> vec;
		int64_t lobby_id;
		discord::Lobby lobby;
		int32_t lobby_count;
		_core->LobbyManager().LobbyCount(&lobby_count);

		for (int32_t i = 0; i < lobby_count; i++) {
			_core->LobbyManager().GetLobbyId(i, &lobby_id);
			_core->LobbyManager().GetLobby(lobby_id, &lobby);

			GodotcordLobby gd_lobby;
			gd_lobby.id = lobby.GetId();
			gd_lobby.secret = lobby.GetSecret();
			gd_lobby.max_users = lobby.GetCapacity();
			gd_lobby.owner_id = lobby.GetOwnerId();
			_core->LobbyManager().MemberCount(lobby_id, &(gd_lobby.current_users));

			vec.push_back(GodotcordLobby::get_dictionary(&gd_lobby));
		}

		emit_signal("search_result", vec);
	});
}

void Godotcord::get_lobbies(int p_count) {
	discord::LobbySearchQuery query;
	_core->LobbyManager().GetSearchQuery(&query);

	_core->LobbyManager().Search(query, [this](discord::Result result) {
		ERR_FAIL_COND(result != discord::Result::Ok);

		Vector<Variant> vec;
		int64_t lobby_id;
		discord::Lobby lobby;
		int32_t lobby_count;
		_core->LobbyManager().LobbyCount(&lobby_count);

		for (int32_t i = 0; i < lobby_count; i++) {
			_core->LobbyManager().GetLobbyId(i, &lobby_id);
			_core->LobbyManager().GetLobby(lobby_id, &lobby);

			GodotcordLobby gd_lobby;
			gd_lobby.id = lobby.GetId();
			gd_lobby.secret = lobby.GetSecret();
			gd_lobby.max_users = lobby.GetCapacity();
			gd_lobby.owner_id = lobby.GetOwnerId();
			_core->LobbyManager().MemberCount(lobby_id, &(gd_lobby.current_users));

			vec.push_back(GodotcordLobby::get_dictionary(&gd_lobby));
		}

		emit_signal("search_result", vec);
	});
}

void Godotcord::request_profile_picture(int64_t p_user_id, uint32_t p_size) {
	discord::ImageHandle handle;
	handle.SetId(p_user_id);
	handle.SetSize(p_size);
	handle.SetType(discord::ImageType::User);
		_core->ImageManager()
			.Fetch(
					handle, false, [this, p_user_id](discord::Result result, discord::ImageHandle returned_handle) {
				ERR_FAIL_COND(result != discord::Result::Ok);

				discord::ImageDimensions dim;
				_core->ImageManager().GetDimensions(returned_handle, &dim);

				uint32_t data_size = dim.GetWidth() * dim.GetHeight() * 4;
				PoolByteArray data;
				data.resize(data_size);
				PoolByteArray::Write write = data.write();
				_core->ImageManager().GetData(returned_handle, &write[0], data_size);

				write.release();

				emit_signal("profile_image", p_user_id, data);
			});
}

void Godotcord::filter_relationships(Object* p_object, StringName p_func_name) {
	ERR_FAIL_NULL(p_object);
	FuncRef filter_func;
	filter_func.set_instance(p_object);
	filter_func.set_function(p_func_name);

	ERR_FAIL_COND(!filter_func.is_valid());

	_core->RelationshipManager().Filter([&filter_func](discord::Relationship p_relationship) -> bool {
		GodotcordRelationship rel_ship;
		rel_ship.set_type((Godotcord::RelationshipType)p_relationship.GetType());
		rel_ship.set_user_id(p_relationship.GetUser().GetId());
		Dictionary d;
		d["status"] = (Godotcord::PresenceStatus)p_relationship.GetPresence().GetStatus();
		d["activity"] = GodotcordActivity::from_discord_activity(p_relationship.GetPresence().GetActivity());

		rel_ship.set_presence(d);

		Array a;
		a.push_back(&rel_ship);

		return filter_func.call_funcv(a);
	});
}

void Godotcord::removeRouteEvent() {
	_core->NetworkManager().OnRouteUpdate.DisconnectAll();
}

discord::Core* Godotcord::get_core() {
	return _core;
}
