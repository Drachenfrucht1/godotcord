#include "godotcord_voice_manager.h"
#include "godotcord.h"

GodotcordVoiceManager *GodotcordVoiceManager::singleton = NULL;

GodotcordVoiceManager* GodotcordVoiceManager::get_singleton() {
	return GodotcordVoiceManager::singleton;
}

void GodotcordVoiceManager::_bind_methods() {
	BIND_ENUM_CONSTANT(VOICE_ACVTIVITY);
	BIND_ENUM_CONSTANT(PUSH_TO_TALK);
}

Dictionary GodotcordVoiceManager::get_input_mode() {
	Dictionary d;
	discord::InputMode d_input_mode;
	discord::Result result = Godotcord::get_singleton()->get_core()->VoiceManager().GetInputMode(&d_input_mode);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, d, "An error occured while fetching the voice input mode");

	d["type"] = (GodotcordVoiceManager::InputModeType) d_input_mode.GetType();
	d["hotkey"] = d_input_mode.GetShortcut();

	return d;
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
