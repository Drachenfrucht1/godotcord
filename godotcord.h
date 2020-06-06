#ifndef GODOTCORD_H
#define GODOTCORD_H

#include "core/reference.h"
#include <string.h>
#include "discord-files/discord.h"
#include "godotcord_activity.h"

class Godotcord : public Reference {
    GDCLASS(Godotcord, Reference)

private:
    discord::Core* _core{};
	String _route;

protected:
    static void _bind_methods();

public:
    void init(discord::ClientId clientId);
	//void init_debug(discord::ClientId clientId, String id);

    void callbacks();

    void setActivity(Ref<GodotcordActivity>);

    void clearActivity();

	String get_current_username();
	String get_current_user_discriminator();
	int64_t get_current_user_id();

	void removeRouteEvent();

	String get_route() { return _route; }

	discord::Core *get_core();

    Godotcord();
};

#endif
