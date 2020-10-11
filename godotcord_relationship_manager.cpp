#include "godotcord_relationship_manager.h"

GodotcordRelationshipManager *GodotcordRelationshipManager::singleton = NULL;

GodotcordRelationshipManager *GodotcordRelationshipManager::get_singleton() {
	return GodotcordRelationshipManager::singleton;
}

GodotcordRelationshipManager::GodotcordRelationshipManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordActivityManager should exist")
	singleton = this;
}

GodotcordRelationshipManager::~GodotcordRelationshipManager() {
}
