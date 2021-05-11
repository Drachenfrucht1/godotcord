#include "godotcord_voice_manager.h"
#include "godotcord.h"

GodotcordVoiceManager *GodotcordVoiceManager::singleton = NULL;

GodotcordVoiceManager* GodotcordVoiceManager::get_singleton() {
	return GodotcordVoiceManager::singleton;
}

void GodotcordVoiceManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_input_mode"), &GodotcordVoiceManager::get_input_mode);
	ClassDB::bind_method(D_METHOD("set_voice_activity"), &GodotcordVoiceManager::set_voice_activity);
	ClassDB::bind_method(D_METHOD("set_push_to_talk", "hotkey"), &GodotcordVoiceManager::set_push_to_talk);
	ClassDB::bind_method(D_METHOD("is_self_mute"), &GodotcordVoiceManager::is_self_mute);
	ClassDB::bind_method(D_METHOD("set_self_mute", "boolean"), &GodotcordVoiceManager::set_self_mute);
	ClassDB::bind_method(D_METHOD("is_self_deaf"), &GodotcordVoiceManager::is_self_deaf);
	ClassDB::bind_method(D_METHOD("set_self_deaf", "boolean"), &GodotcordVoiceManager::set_self_deaf);
	ClassDB::bind_method(D_METHOD("is_local_mute", "user_id"), &GodotcordVoiceManager::is_local_mute);
	ClassDB::bind_method(D_METHOD("set_local_mute", "user_id", "boolean"), &GodotcordVoiceManager::set_local_mute);
	ClassDB::bind_method(D_METHOD("get_local_volume", "user_id"), &GodotcordVoiceManager::get_local_volume);
	ClassDB::bind_method(D_METHOD("set_local_volume", "user_id", "value"), &GodotcordVoiceManager::set_local_volume);
}

Ref<GodotcordInputmode> GodotcordVoiceManager::get_input_mode() {
	Ref<GodotcordInputmode> gd_inputmode;
    gd_inputmode.instance();
	discord::InputMode d_input_mode;
	discord::Result result = Godotcord::get_singleton()->get_core()->VoiceManager().GetInputMode(&d_input_mode);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, gd_inputmode, "An error occured while fetching the voice input mode");

	gd_inputmode->type = (GodotcordInputmode::InputModeType) d_input_mode.GetType();
	gd_inputmode->shortcut = d_input_mode.GetShortcut();

	return gd_inputmode;
}

void GodotcordVoiceManager::set_voice_activity() {
	discord::InputMode input_mode;
	input_mode.SetType(discord::InputModeType::VoiceActivity);
	input_mode.SetShortcut("");

	 Godotcord::get_singleton()->get_core()->VoiceManager().SetInputMode(input_mode, [](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching the voice input mode");
	});
}

void GodotcordVoiceManager::set_push_to_talk(String p_hotkey) {
	discord::InputMode input_mode;
	input_mode.SetType(discord::InputModeType::VoiceActivity);
	input_mode.SetShortcut(p_hotkey.utf8());

	Godotcord::get_singleton()->get_core()->VoiceManager().SetInputMode(input_mode, [](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching the voice input mode");
	});
}

bool GodotcordVoiceManager::is_self_mute() {
	bool b;
	discord::Result result = Godotcord::get_singleton()->get_core()->VoiceManager().IsSelfMute(&b);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, false, "An error occured while checking for self mute");

	return b;
}

void GodotcordVoiceManager::set_self_mute(bool b) {
	discord::Result result = Godotcord::get_singleton()->get_core()->VoiceManager().SetSelfMute(b);
	ERR_FAIL_COND_MSG(result != discord::Result::Ok,  "An error occured while setting self mute");
}

bool GodotcordVoiceManager::is_self_deaf() {
	bool b;
	discord::Result result = Godotcord::get_singleton()->get_core()->VoiceManager().IsSelfDeaf(&b);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, false, "An error occured while checking for self deaf");

	return b;
}

void GodotcordVoiceManager::set_self_deaf(bool b) {
	discord::Result result = Godotcord::get_singleton()->get_core()->VoiceManager().SetSelfDeaf(b);
	ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while setting self deaf");
}

bool GodotcordVoiceManager::is_local_mute(uint64_t p_user_id) {
	bool b;
	discord::Result result = Godotcord::get_singleton()->get_core()->VoiceManager().IsLocalMute(p_user_id, &b);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, false, "An error occured while checking for local mute");

	return b;
}

void GodotcordVoiceManager::set_local_mute(uint64_t p_user_id, bool b) {
	discord::Result result = Godotcord::get_singleton()->get_core()->VoiceManager().SetLocalMute(p_user_id, b);
	ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while setting local mute");
}

uint8_t GodotcordVoiceManager::get_local_volume(uint64_t p_user_id) {
	uint8_t b;
	discord::Result result = Godotcord::get_singleton()->get_core()->VoiceManager().GetLocalVolume(p_user_id, &b);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, 0, "An error occured while getting local volume");

	return b;
}

void GodotcordVoiceManager::set_local_volume(uint64_t p_user_id, uint8_t b) {
	discord::Result result = Godotcord::get_singleton()->get_core()->VoiceManager().SetLocalMute(p_user_id, b);
	ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while setting local volume");
}

GodotcordVoiceManager::GodotcordVoiceManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordVoiceManager should exist.");
	singleton = this;
}
