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


	void init();
	GodotcordAchievementManager();
};


#endif //GODOTCORD_ACHIEVEMENT_MANAGER
