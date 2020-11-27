#include "godotcord_achievement_manager.h"

GodotcordAchievementManager *GodotcordAchievementManager::singleton = NULL;

GodotcordAchievementManager* GodotcordAchievementManager::get_singleton() {
	return GodotcordAchievementManager::singleton;
}

void GodotcordAchievementManager::_bind_methods() {

}

GodotcordAchievementManager::GodotcordAchievementManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordAchievementManager should be created");

	singleton = this;
}
