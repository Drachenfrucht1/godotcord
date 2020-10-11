#ifndef GODOTCORD_LOBBY_MANAGER_H
#define GODOTCORD_LOBBY_MANAGER_H

#include "core/object.h"

class GodotcordLobbyManager : public Object {
	GDCLASS(GodotcordLobbyManager, Object)

public:
	static GodotcordLobbyManager *singleton;
	static GodotcordLobbyManager *get_singleton();

	GodotcordLobbyManager();
	~GodotcordLobbyManager();
};

#endif //GODOTCORD_LOBBY_MANAGER_H
