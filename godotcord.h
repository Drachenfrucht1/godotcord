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

protected:
    static void _bind_methods();

public:
    void init(discord::ClientId clientId);
	//void init_debug(discord::ClientId clientId, String id);

    void callbacks();

    void setActivity(Ref<GodotcordActivity>);

    void clearActivity();

	discord::Core *get_core();

    Godotcord();
};

#endif
