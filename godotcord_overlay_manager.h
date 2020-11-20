#ifndef GODOTCORD_OVERLAY_MANAGER
#define GODOTCORD_OVERLAY_MANAGER

#include "core/object.h"
#include "godotcord.h"

class GodotcordOverlayManager : public Object {
	GDCLASS(GodotcordOverlayManager, Object);

protected:
	static void _bind_methods();
public:
	static GodotcordOverlayManager *singleton;
	static GodotcordOverlayManager *get_singleton();

	bool is_enabled();
	bool is_locked();
	void set_locked(bool p_locked);
	void open_voice_settings();
	void open_activity_invite(GodotcordActivity::ActivityActionType p_type);
	void open_guild_invite(String p_invite_code);

	GodotcordOverlayManager();
};

#endif
