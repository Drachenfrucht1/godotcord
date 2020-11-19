#include "godotcord_overlay_manager.h"

GodotcordOverlayManager *GodotcordOverlayManager::singleton = NULL;

GodotcordOverlayManager *GodotcordOverlayManager::get_singleton() {
	return GodotcordOverlayManager::singleton;
}


GodotcordOverlayManager::GodotcordOverlayManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordOverlayManager should exist");

	singleton = this;
}
