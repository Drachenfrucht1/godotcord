#include "godotcord_overlay_manager.h"

GodotcordOverlayManager *GodotcordOverlayManager::singleton = NULL;

GodotcordOverlayManager *GodotcordOverlayManager::get_singleton() {
	return GodotcordOverlayManager::singleton;
}

void GodotcordOverlayManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("is_enabled"), &GodotcordOverlayManager::is_enabled);
	ClassDB::bind_method(D_METHOD("is_locked"), &GodotcordOverlayManager::is_locked);
	ClassDB::bind_method(D_METHOD("set_locked", "locked"), &GodotcordOverlayManager::set_locked);
	ClassDB::bind_method(D_METHOD("open_voice_settings"), &GodotcordOverlayManager::open_voice_settings);
	ClassDB::bind_method(D_METHOD("open_activity_invite", "type"), &GodotcordOverlayManager::open_activity_invite);
	ClassDB::bind_method(D_METHOD("open_guild_invite", "invite_code"), &GodotcordOverlayManager::open_guild_invite);
}

bool GodotcordOverlayManager::is_enabled() {
	bool b;
	Godotcord::get_singleton()->get_core()->OverlayManager().IsEnabled(&b);
	return b;
}

bool GodotcordOverlayManager::is_locked() {
	bool b;
	Godotcord::get_singleton()->get_core()->OverlayManager().IsLocked(&b);
	return b;
}

void GodotcordOverlayManager::set_locked(bool p_locked) {
	Godotcord::get_singleton()->get_core()->OverlayManager().SetLocked(p_locked, [](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occurred while trying set locked of the overlay");
	});
}

void GodotcordOverlayManager::open_voice_settings() {
	Godotcord::get_singleton()->get_core()->OverlayManager().OpenVoiceSettings([](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occurred while trying to open the voice settings overlay");
	});
}

void GodotcordOverlayManager::open_activity_invite(GodotcordActivity::ActivityActionType p_type) {
	Godotcord::get_singleton()->get_core()->OverlayManager().OpenActivityInvite((discord::ActivityActionType)p_type, [](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occurred while trying to open an activity invite dialog in the overlay");
	});
}

void GodotcordOverlayManager::open_guild_invite(String p_invite_code) {
	Godotcord::get_singleton()->get_core()->OverlayManager().OpenGuildInvite(p_invite_code.utf8(), [](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occurred while trying to open the guild invite dialog in the overlay");
	});
}

GodotcordOverlayManager::GodotcordOverlayManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordOverlayManager should exist");

	singleton = this;
}
