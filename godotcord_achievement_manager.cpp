#include "godotcord_achievement_manager.h"
#include "godotcord.h"

#include "core/func_ref.h"

GodotcordAchievementManager *GodotcordAchievementManager::singleton = NULL;

GodotcordAchievementManager* GodotcordAchievementManager::get_singleton() {
	return GodotcordAchievementManager::singleton;
}

void GodotcordAchievementManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_user_achievement", "achievement_id", "percent_complete"), &GodotcordAchievementManager::set_user_achievement);
	ClassDB::bind_method(D_METHOD("fetch_user_achievements", "object", "function_name"), &GodotcordAchievementManager::fetch_user_achievements);
	ClassDB::bind_method(D_METHOD("get_user_achievements"), &GodotcordAchievementManager::get_user_achievements);
}

void GodotcordAchievementManager::set_user_achievement(int64_t p_achievement_id, int8_t p_percent) {
	Godotcord::get_singleton()->get_core()->AchievementManager().SetUserAchievement(p_achievement_id, p_percent, [](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occures while set the users achievement progress");
	});
}

void GodotcordAchievementManager::fetch_user_achievements(Object *p_object, StringName p_funcname) {
	ERR_FAIL_NULL(p_object);

	Godotcord::get_singleton()->get_core()->AchievementManager().FetchUserAchievements([this, p_object, p_funcname](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching the local users achievements");
		FuncRef callback;
		callback.set_instance(p_object);
		callback.set_function(p_funcname);

		Array r;

		callback.call_funcv(r);
	});
}

Array GodotcordAchievementManager::get_user_achievements() {
	Array ret_value;
	int32_t count;
	Godotcord::get_singleton()->get_core()->AchievementManager().CountUserAchievements(&count);

	for (int i = 0; i < count; i++) {
		discord::UserAchievement achievement;
		discord::Result result = Godotcord::get_singleton()->get_core()->AchievementManager().GetUserAchievementAt(i, &achievement);
		ERR_CONTINUE(result != discord::Result::Ok);

		Dictionary d;
		d["user_id"] = achievement.GetUserId();
		d["achievement_id"] = achievement.GetAchievementId();
		d["percent_complete"] = achievement.GetPercentComplete();
		d["unlocked_at"] = achievement.GetUnlockedAt();

		ret_value.push_back(d);
	}

	return ret_value;
}

void GodotcordAchievementManager::init() {
	Godotcord::get_singleton()->get_core()->AchievementManager().OnUserAchievementUpdate.Connect([](discord::UserAchievement p_achievement) {
		Godotcord::get_singleton()->get_core()->AchievementManager().FetchUserAchievements([](discord::Result result) {
			ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching the local users achievements");
		});
	});

	Godotcord::get_singleton()->get_core()->AchievementManager().FetchUserAchievements([](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching the local users achievements");
	});
}

GodotcordAchievementManager::GodotcordAchievementManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordAchievementManager should be created");

	singleton = this;
}
