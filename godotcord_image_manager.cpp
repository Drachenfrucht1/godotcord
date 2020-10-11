#include "godotcord_image_manager.h"

GodotcordImageManager *GodotcordImageManager::singleton = NULL;

GodotcordImageManager *GodotcordImageManager::get_singleton() {
	return GodotcordImageManager::singleton;
}

GodotcordImageManager::GodotcordImageManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordActivityManager should exist")
	singleton = this;
}

GodotcordImageManager::~GodotcordImageManager() {
}
