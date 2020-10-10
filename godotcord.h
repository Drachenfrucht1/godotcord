#ifndef GODOTCORD_H
#define GODOTCORD_H

#include "core/object.h"
#include "scene/resources/texture.h"
#include <string.h>
#include "discord-files/discord.h"
#include "godotcord_activity.h"
#include "godotcord_relationship.h"
#include "godotcord_lobby.h"

class Godotcord : public Object {
    GDCLASS(Godotcord, Object)

public:
	enum LobbyDistance {
		LOCAL,
		DEFAULT,
		EXTENDED,
		GLOBAL
	};

	enum LobbyComparison {
		LESS_THAN_OR_EQUAL,
		LESS_THAN,
		EQUAL,
		GREATER_THAN,
		GREATER_THAN_OR_EQUAL,
		NOT_EQUAL
	};

	enum LobbyCast {
		STRING,
		INT,
	};

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

	//ACTIVITY
    void setActivity(Ref<GodotcordActivity> p_act);

    void clearActivity();

	//USER
	String get_current_username();
	String get_current_user_discriminator();
	int64_t get_current_user_id();

	//LOBBY
	void set_lobby_metadata(int64_t lobby_id, String key, String value);
	String get_lobby_metadata(int64_t lobby_id, String key);

	void search_lobbies(Variant params, int limit);
	void get_lobbies(int p_count);

	//IMAGE
	void request_profile_picture(int64_t p_user_id, uint32_t p_size);

	//RELATIONSHIP
	Array filter_relationships(Object* p_object, StringName p_func_name);
	Array get_relationsips();

	bool is_init() const {
		return init_bool;
	}

	String get_route() { return _route; }

	void removeRouteEvent();

	discord::Core *get_core();

    Godotcord();
};

VARIANT_ENUM_CAST(Godotcord::LobbyDistance);
VARIANT_ENUM_CAST(Godotcord::LobbyCast);
VARIANT_ENUM_CAST(Godotcord::LobbyComparison);

#endif
