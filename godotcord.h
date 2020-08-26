#ifndef GODOTCORD_H
#define GODOTCORD_H

#include "core/object.h"
#include "scene/resources/texture.h"
#include <string.h>
#include "discord-files/discord.h"
#include "godotcord_activity.h"
#include "godotcord_lobby.h"

class Godotcord : public Object {
    GDCLASS(Godotcord, Object)

private:
	discord::Core *_core{};
	bool init_bool = false;
	String _route;

protected:
    static void _bind_methods();

public:
	static Godotcord *singleton;
	static Godotcord *get_singleton();

    Error init(discord::ClientId clientId);
	void init_debug(discord::ClientId clientId, String id);

	void run_callbacks();

    void setActivity(Ref<GodotcordActivity>);

    void clearActivity();

	String get_current_username();
	String get_current_user_discriminator();
	int64_t get_current_user_id();

	void set_lobby_metadata(int64_t lobby_id, String key, String value);
	String get_lobby_metadata(int64_t lobby_id, String key);

	void search_lobbies(String p_max_users);
	void get_lobbies(int p_count);

	void removeRouteEvent();

	void request_profile_picture(int64_t p_user_id, uint32_t p_size);

	bool is_init() const {
		return init_bool;
	}

	String get_route() { return _route; }

	discord::Core *get_core();

    Godotcord();
};

#endif
