#include "godotcord.h"

#include <godot_cpp/core/class_db.hpp>
// #include "godotcord_relationship_manager.h"
// #include "godotcord_user_manager.h"

using namespace godot;

Godotcord *Godotcord::singleton = NULL;

Godotcord::Godotcord() {

	singleton = this;
}

Godotcord::~Godotcord() {
	if (this == singleton && this->is_init()) {
		_core->~Core();
	}
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
    ClassDB::bind_method(D_METHOD("init", "client_id", "createFlags"), &Godotcord::init);
	ClassDB::bind_method(D_METHOD("init_debug", "client_id", "instance_id", "createFlags"), &Godotcord::init_debug);
	ClassDB::bind_method(D_METHOD("run_callbacks"), &Godotcord::run_callbacks);

	BIND_ENUM_CONSTANT(CreateFlags_DEFAULT);
	BIND_ENUM_CONSTANT(CreateFlags_NO_REQUIRE_DISCORD);
}
	
Error Godotcord::init(int64_t clientId, int createFlags = CreateFlags_DEFAULT) {
	discord::Result result = discord::Core::Create(clientId, createFlags, &_core);

	ERR_FAIL_COND_V(result != discord::Result::Ok, ERR_CANT_CONNECT);

	_init_discord();

	return OK;
}

void Godotcord::init_debug(int64_t clientId, String id, int createFlags = CreateFlags_DEFAULT) {
#ifdef _WIN32
	_putenv_s("DISCORD_INSTANCE_ID", id.utf8().get_data());
#else
	setenv("DISCORD_INSTANCE_ID", id.utf8().get_data(), true);
#endif
	// print_line(vformat("Set DISCORD_INSTANCE_ID to %s", id));
	// print_line(vformat("Read DISCORD_INSTANCE_ID is %s", getenv("DISCORD_INSTANCE_ID")));
	discord::Result result = discord::Core::Create(clientId, createFlags, &_core);

    ERR_FAIL_COND(result != discord::Result::Ok);

	_init_discord();
}

void Godotcord::_init_discord() {
	init_bool = true;

	// _core->SetLogHook(discord::LogLevel::Info, [](discord::LogLevel level, const char *msg) {
	// 	switch (level) {
	// 		case discord::LogLevel::Warn:
	// 			print_line(vformat("[DiscordGameSDK][Warn] %s", msg));
	// 			break;
	// 		case discord::LogLevel::Info:
	// 			print_line(vformat("[DiscordGameSDK][Info] %s", msg));
	// 			break;
	// 		case discord::LogLevel::Error:
	// 			print_error(vformat("[DiscordGameSDK][ERR] %s", msg));
	// 			break;
	// 	}
	// });

	// GodotcordActivityManager::get_singleton()->init();
	// GodotcordRelationshipManager::get_singleton()->init();
	// GodotcordUserManager::get_singleton()->init();
}

discord::Core* Godotcord::get_core() {
	return _core;
}
