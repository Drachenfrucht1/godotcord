#ifndef GODOTCORD_VOICE_MANAGER
#define GODOTCORD_VOICE_MANAGER

#include "core/object.h"

class GodotcordVoiceManager : public Object {
    GDCLASS(GodotcordVoiceManager, Object);

public:
	enum InputModeType {
		VOICE_ACVTIVITY = 0,
		PUSH_TO_TALK = 1,
	};

protected:
    static void _bind_methods();

public:
	static GodotcordVoiceManager *singleton;
	static GodotcordVoiceManager *get_singleton();

	Dictionary get_input_mode();
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

VARIANT_ENUM_CAST(GodotcordVoiceManager::InputModeType);

#endif //GODOTCORD_VOICE_MANAGER
