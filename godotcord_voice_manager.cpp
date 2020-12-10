#include "godotcord_voice_manager.h"

GodotcordVoiceManager *GodotcordVoiceManager::singleton = NULL;

GodotcordVoiceManager* GodotcordVoiceManager::get_singleton() {
	return GodotcordVoiceManager::singleton;
}

void GodotcordVoiceManager::_bind_methods() {

}

GodotcordVoiceManager::GodotcordVoiceManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordVoiceManager should exist.");
	singleton = this;
}
