#ifndef GODOTCORD_ACTIVITY_MANAGER_H
#define GODOTCORD_ACTIVITY_MANAGER_H

#include "core/object.h"

class GodotcordActivityManager : public Object {
	GDCLASS(GodotcordActivityManager, Object)

public:
	static GodotcordActivityManager *singleton;
	static GodotcordActivityManager *get_singleton();

	GodotcordActivityManager();
	~GodotcordActivityManager();
};

#endif //GODOTCORD_ACTIVITY_MANAGER_H
