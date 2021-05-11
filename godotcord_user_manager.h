#ifndef GODOTCORD_USER_MANAGER_H
#define GODOTCORD_USER_MANAGER_H

#include "godotcord_user.h"
#include "core/object.h"

class GodotcordUserManager : public Object {
    GDCLASS(GodotcordUserManager, Object)

public:
	enum UserFlag {
		PARTNER = 2,
		HYPE_SQUAD_EVENTS = 4,
		HYPE_SQUAD_HOUSE_1 = 64,
		HYPE_SQUAD_HOUSE_2 = 128,
		HYPE_SQUAD_HOUSE_3 = 256,
	};

	enum PremiumType {
		ERROR = -1,
		NONE = 0,
		TIER_1,
		TIER_2
	};

protected:
	static void _bind_methods();

public:
	static GodotcordUserManager *singleton;
	static GodotcordUserManager *get_singleton();

	void get_user(int64_t p_user_id);
	Ref<GodotcordUser> get_current_user();
	PremiumType get_current_user_premium_type();
	bool has_current_user_flag(UserFlag p_flag);

	void init();
	GodotcordUserManager();
};

VARIANT_ENUM_CAST(GodotcordUserManager::UserFlag);
VARIANT_ENUM_CAST(GodotcordUserManager::PremiumType);

#endif
