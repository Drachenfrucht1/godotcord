#include "godotcord.h"
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

	ClassDB::bind_method(D_METHOD("get_current_username"), &Godotcord::get_current_username);
	ClassDB::bind_method(D_METHOD("get_current_user_discriminator"), &Godotcord::get_current_user_discriminator);
	ClassDB::bind_method(D_METHOD("get_current_user_id"), &Godotcord::get_current_user_id);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "user_name"), "", "get_current_username");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "user_discriminator"), "", "get_current_user_discriminator");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "user_id"), "", "get_current_user_id");
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

	_core->UserManager().OnCurrentUserUpdate.Connect([this]() {
		print_verbose("Local Discord user updated");
	});

	_core->NetworkManager().OnRouteUpdate.Connect([this](const char *p_route) {
		_route = String(p_route);
	});

	_core->RelationshipManager().OnRelationshipUpdate.Connect([this](discord::Relationship relation_ship) {
		GodotcordRelationship rel_ship;
		rel_ship.set_type((GodotcordRelationship::RelationshipType)relation_ship.GetType());
		rel_ship.set_user_id(relation_ship.GetUser().GetId());
		Dictionary d;
		d["status"] = (GodotcordRelationship::PresenceStatus)relation_ship.GetPresence().GetStatus();
		d["activity"] = GodotcordActivity::from_discord_activity(relation_ship.GetPresence().GetActivity());

		rel_ship.set_presence(d);

		emit_signal("relationship_update", rel_ship.to_dictionary());
	});

	GodotcordActivityManager::get_singleton()->init();

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

	_core->UserManager().OnCurrentUserUpdate.Connect([this]() {
		print_verbose("Local Discord user updated");
	});

	_core->NetworkManager().OnRouteUpdate.Connect([this](const char *p_route) {
		_route = String(p_route);
	});

	_core->RelationshipManager().OnRelationshipUpdate.Connect([this](discord::Relationship relation_ship) {
		GodotcordRelationship rel_ship;
		rel_ship.set_type((GodotcordRelationship::RelationshipType)relation_ship.GetType());
		rel_ship.set_user_id(relation_ship.GetUser().GetId());
		Dictionary d;
		d["status"] = (GodotcordRelationship::PresenceStatus)relation_ship.GetPresence().GetStatus();
		d["activity"] = GodotcordActivity::from_discord_activity(relation_ship.GetPresence().GetActivity());

		rel_ship.set_presence(d);

		emit_signal("relationship_update", rel_ship.to_dictionary());
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

void Godotcord::removeRouteEvent() {
	_core->NetworkManager().OnRouteUpdate.DisconnectAll();
}

discord::Core* Godotcord::get_core() {
	return _core;
}
