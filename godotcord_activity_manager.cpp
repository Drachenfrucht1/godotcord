#include "godotcord_activity_manager.h"

GodotcordActivityManager *GodotcordActivityManager::singleton = NULL;

GodotcordActivityManager *GodotcordActivityManager::get_singleton() {
	return GodotcordActivityManager::singleton;
}

GodotcordActivityManager::GodotcordActivityManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordActivityManager should exist")
	singleton = this;
}

GodotcordActivityManager::~GodotcordActivityManager() {

}
