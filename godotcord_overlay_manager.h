#ifndef GODOTCORD_OVERLAY_MANAGER
#define GODOTCORD_OVERLAY_MANAGER

#include "core/object.h"

class GodotcordOverlayManager : public Object {
public:

protected:
	static void _bind_methods();
public:
	static GodotcordOverlayManager *singleton;
	static GodotcordOverlayManager *get_singleton();

	GodotcordOverlayManager();
};

#endif
