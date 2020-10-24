#ifndef GODOTCORD_H
#define GODOTCORD_H

#include "core/object.h"
#include "scene/resources/texture.h"
#include <string.h>
#include "discord-files/discord.h"
#include "godotcord_activity.h"
#include "godotcord_relationship.h"
#include "godotcord_lobby.h"

#include "godotcord_activity_manager.h"

class Godotcord : public Object {
    GDCLASS(Godotcord, Object)

private:
	discord::Core *_core{};
	bool init_bool = false;
	String _route;
	uint8_t *public_key = NULL;

	void _init_discord();

protected:
    static void _bind_methods();

public:
	static Godotcord *singleton;
	static Godotcord *get_singleton();

    void init(discord::ClientId clientId);
	void init_debug(discord::ClientId clientId, String id);
	

	void run_callbacks();

	//USER
	String get_current_username();
	String get_current_user_discriminator();
	int64_t get_current_user_id();

	void set_public_key(String p_public_key) {
		public_key = godotcord_hex_str_to_uint8(p_public_key);
	}
	uint8_t *get_public_key() const {
		return public_key;
	}

	bool is_init() const {
		return init_bool;
	}

	String get_route() { return _route; }

	void removeRouteEvent();

	discord::Core *get_core();

    Godotcord();
};

#endif
