#ifndef GODOTCORD_VOICE_MANAGER
#define GODOTCORD_VOICE_MANAGER

#include "core/object.h"

class GodotcordVoiceManager : public Object {
    GDCLASS(GodotcordVoiceManager, Object);

protected:
    static void _bind_methods();

public:
	static GodotcordVoiceManager *singleton;
	static GodotcordVoiceManager *get_singleton();

    GodotcordVoiceManager();
	~GodotcordVoiceManager() {}
};

#endif //GODOTCORD_VOICE_MANAGER
