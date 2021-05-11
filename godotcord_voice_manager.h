#ifndef GODOTCORD_VOICE_MANAGER
#define GODOTCORD_VOICE_MANAGER

#include "core/object.h"
#include "core/reference.h"
#include "godotcord_utils.h"

class GodotcordInputmode : public Reference {
	GDCLASS(GodotcordInputmode, Reference);

public:
	enum InputModeType {
		VOICE_ACVTIVITY = 0,
		PUSH_TO_TALK = 1,
	};

protected:
	static void _bind_methods() {
		ADD_GODOTCORD_PROPERTY(GodotcordInputmode, type, Variant::INT);
		ADD_GODOTCORD_PROPERTY(GodotcordInputmode, shortcut, Variant::STRING);

		BIND_ENUM_CONSTANT(VOICE_ACVTIVITY);
		BIND_ENUM_CONSTANT(PUSH_TO_TALK);
	};

public:
	InputModeType type;
	String shortcut;

	GET_SET_COMBO(type, InputModeType);
	GET_SET_COMBO(shortcut, String);
};

class GodotcordVoiceManager : public Object {
    GDCLASS(GodotcordVoiceManager, Object);	

protected:
    static void _bind_methods();

public:
	static GodotcordVoiceManager *singleton;
	static GodotcordVoiceManager *get_singleton();

	Ref<GodotcordInputmode> get_input_mode();
	void set_voice_activity();
	void set_push_to_talk(String p_hotkey);

	bool is_self_mute();
	void set_self_mute(bool b);

	bool is_self_deaf();
	void set_self_deaf(bool b);

	bool is_local_mute(uint64_t p_user_id);
	void set_local_mute(uint64_t p_user_id, bool b);

	uint8_t get_local_volume(uint64_t p_user_id);
	void set_local_volume(uint64_t p_user_id, uint8_t b);

    GodotcordVoiceManager();
	~GodotcordVoiceManager() {}
};

VARIANT_ENUM_CAST(GodotcordInputmode::InputModeType);

#endif //GODOTCORD_VOICE_MANAGER
