#include "godotcord_lobby_manager.h"

GodotcordLobbyManager *GodotcordLobbyManager::singleton = NULL;

GodotcordLobbyManager *GodotcordLobbyManager::get_singleton() {
	return GodotcordLobbyManager::singleton;
}

GodotcordLobbyManager::GodotcordLobbyManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordActivityManager should exist")
	singleton = this;
}

GodotcordLobbyManager::~GodotcordLobbyManager() {
}
