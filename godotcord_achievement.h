#ifndef GODOTCORD_ACHIEVEMENT_H
#define GODOTCORD_ACHIEVEMENT_H

#include "core/reference.h"

#include "godotcord_utils.h"

class GodotcordAchievement : public Reference {
	GDCLASS(GodotcordAchievement, Reference);

protected:
	static void _bind_methods() {
		ADD_GODOTCORD_PROPERTY(GodotcordAchievement, user_id, Variant::INT);
		ADD_GODOTCORD_PROPERTY(GodotcordAchievement, achievement_id, Variant::INT);
		ADD_GODOTCORD_PROPERTY(GodotcordAchievement, percent_complete, Variant::INT);
		ADD_GODOTCORD_PROPERTY(GodotcordAchievement, unlocked_at, Variant::STRING);
	}
public:
	int64_t user_id;
	int64_t achievement_id;
    uint8_t percent_complete;
    String unlocked_at;
    

	GET_SET_COMBO(user_id, int64_t);
	GET_SET_COMBO(achievement_id, int64_t);
	GET_SET_COMBO(percent_complete, uint64_t);
	GET_SET_COMBO(unlocked_at, String);
};

#endif
