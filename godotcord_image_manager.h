#ifndef GODOTCORD_IMAGE_MANAGER_H
#define GODOTCORD_IMAGE_MANAGER_H

#include "core/object.h"

class GodotcordImageManager : public Object {
	GDCLASS(GodotcordImageManager, Object)

public:
	static GodotcordImageManager *singleton;
	static GodotcordImageManager *get_singleton();

	GodotcordImageManager();
	~GodotcordImageManager();
};

#endif //GODOTCORD_IMAGE_MANAGER_H
