#include "godotcord_user_manager.h"
#include "godotcord.h"

GodotcordUserManager *GodotcordUserManager::singleton = NULL;

GodotcordUserManager* GodotcordUserManager::get_singleton() {
	return GodotcordUserManager::singleton;
}

void GodotcordUserManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_user", "user_id"), &GodotcordUserManager::get_user);
	ClassDB::bind_method(D_METHOD("get_current_user"), &GodotcordUserManager::get_current_user);
	ClassDB::bind_method(D_METHOD("get_current_user_premium_type"), &GodotcordUserManager::get_current_user_premium_type);
	ClassDB::bind_method(D_METHOD("has_current_user_flag", "user_flag"), &GodotcordUserManager::has_current_user_flag);

	ADD_SIGNAL(MethodInfo("get_user_callback", PropertyInfo(Variant::OBJECT, "user")));
	ADD_SIGNAL(MethodInfo("local_user_updated"));

	BIND_ENUM_CONSTANT(PARTNER);
	BIND_ENUM_CONSTANT(HYPE_SQUAD_EVENTS);
	BIND_ENUM_CONSTANT(HYPE_SQUAD_HOUSE_1);
	BIND_ENUM_CONSTANT(HYPE_SQUAD_HOUSE_2);
	BIND_ENUM_CONSTANT(HYPE_SQUAD_HOUSE_3);

	BIND_ENUM_CONSTANT(ERROR);
	BIND_ENUM_CONSTANT(NONE);
	BIND_ENUM_CONSTANT(TIER_1);
	BIND_ENUM_CONSTANT(TIER_2);
}

void GodotcordUserManager::get_user(int64_t p_user_id) {
	Godotcord::get_singleton()->get_core()->UserManager().GetUser(p_user_id, [this](discord::Result result, discord::User user) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while trying to fetch the user");
		Ref<GodotcordUser> godotcordUser;
                godotcordUser.instance();

		godotcordUser->id = user.GetId();
	        godotcordUser->name = user.GetUsername();
		godotcordUser->discriminator = user.GetDiscriminator();
		godotcordUser->avatar = user.GetAvatar();
		godotcordUser->bot = user.GetBot();

		emit_signal("get_user_callback", godotcordUser);
	});
}


Ref<GodotcordUser> GodotcordUserManager::get_current_user() {
	discord::User user{};
	Ref<GodotcordUser> godotcordUser;
        godotcordUser.instance();
	discord::Result result = Godotcord::get_singleton()->get_core()->UserManager().GetCurrentUser(&user);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, godotcordUser, "An error occured while trying to fetch the user");

//	ret["id"] = user.GetId();
//	ret["name"] = user.GetUsername();
//	ret["discriminator"] = user.GetDiscriminator();
//	ret["avatar"] = user.GetAvatar();
//	ret["bot"] = user.GetBot();
	godotcordUser->id = user.GetId();
	godotcordUser->name = user.GetUsername();
	godotcordUser->discriminator = user.GetDiscriminator();
	godotcordUser->avatar = user.GetAvatar();
	godotcordUser->bot = user.GetBot();

	return godotcordUser;
}

GodotcordUserManager::PremiumType GodotcordUserManager::get_current_user_premium_type() {
	discord::PremiumType premium_type;
	discord::Result result = Godotcord::get_singleton()->get_core()->UserManager().GetCurrentUserPremiumType(&premium_type);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, PremiumType::ERROR, "An error occured while fetching the users premium type");

	return (PremiumType)premium_type;
}

bool GodotcordUserManager::has_current_user_flag(GodotcordUserManager::UserFlag p_flag) {
	bool b;
	discord::Result result = Godotcord::get_singleton()->get_core()->UserManager().CurrentUserHasFlag((discord::UserFlag)p_flag, &b);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, false, "An error occured while fetching the users premium type");

	return b;
}

void GodotcordUserManager::init() {
	Godotcord::get_singleton()->get_core()->UserManager().OnCurrentUserUpdate.Connect([this]() {
		print_verbose("Local Discord user updated");

		emit_signal("local_user_updated");
	});
}

GodotcordUserManager::GodotcordUserManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordUserManager should exist");

	singleton = this;
}
