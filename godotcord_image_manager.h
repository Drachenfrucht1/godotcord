#ifndef GODOTCORD_IMAGE_MANAGER_H
#define GODOTCORD_IMAGE_MANAGER_H

#include "core/object.h"

class GodotcordImageManager : public Object {
	GDCLASS(GodotcordImageManager, Object)

protected:
	static void _bind_methods();

public:
	static GodotcordImageManager *singleton;
	static GodotcordImageManager *get_singleton();

	void get_profile_picture(int64_t p_user_id, int p_size, Object *p_object, StringName p_funcname);

	GodotcordImageManager();
	~GodotcordImageManager();
};

#endif //GODOTCORD_IMAGE_MANAGER_H
