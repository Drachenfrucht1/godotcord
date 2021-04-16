#ifndef GODOTCORD_LOBBY_MANAGER_H
#define GODOTCORD_LOBBY_MANAGER_H

#include "core/object.h"

class GodotcordLobbyManager : public Object {
	GDCLASS(GodotcordLobbyManager, Object)

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

protected:
	static void _bind_methods();

public:
	static GodotcordLobbyManager *singleton;
	static GodotcordLobbyManager *get_singleton();

	void set_lobby_metadata(int64_t lobby_id, String key, String value);
	String get_lobby_metadata(int64_t lobby_id, String key);

	void search_lobbies(Array params, int limit);

	GodotcordLobbyManager();
	~GodotcordLobbyManager();
};

VARIANT_ENUM_CAST(GodotcordLobbyManager::LobbyDistance);
VARIANT_ENUM_CAST(GodotcordLobbyManager::LobbyComparison);
VARIANT_ENUM_CAST(GodotcordLobbyManager::LobbyCast);

#endif //GODOTCORD_LOBBY_MANAGER_H
