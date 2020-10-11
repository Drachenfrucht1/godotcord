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

	void _init_discord();

protected:
    static void _bind_methods();

public:
	static Godotcord *singleton;
	static Godotcord *get_singleton();

    Error init(discord::ClientId clientId);
	void init_debug(discord::ClientId clientId, String id);

	void run_callbacks();

	//USER
	String get_current_username();
	String get_current_user_discriminator();
	int64_t get_current_user_id();

	bool is_init() const {
		return init_bool;
	}

	String get_route() { return _route; }

	void removeRouteEvent();

	discord::Core *get_core();

    Godotcord();
};

#endif
