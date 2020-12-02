#ifndef GODOTCORD_ACHIEVEMENT_MANAGER
#define GODOTCORD_ACHIEVEMENT_MANAGER

#include "core/object.h"

class GodotcordAchievementManager : public Object {
	GDCLASS(GodotcordAchievementManager, Object)

protected:
	static void _bind_methods();

public:
	static GodotcordAchievementManager *singleton;
	static GodotcordAchievementManager *get_singleton();

	void set_user_achievement(int64_t p_achievement_id, int8_t p_percent);
	void fetch_user_achievements(Object *p_object, StringName p_funcname);
	Array get_user_achievements();


	void init();
	GodotcordAchievementManager();
};


#endif //GODOTCORD_ACHIEVEMENT_MANAGER
