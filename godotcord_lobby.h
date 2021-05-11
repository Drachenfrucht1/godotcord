#ifndef GODOTCORD_LOBBY_H
#define GODOTCORD_LOBBY_H

#include "core/reference.h"

#include "godotcord_utils.h"

class GodotcordLobby : public Reference {
	GDCLASS(GodotcordLobby, Reference);

protected:
	static void _bind_methods() {
		ADD_GODOTCORD_PROPERTY(GodotcordLobby, secret, Variant::STRING);
		ADD_GODOTCORD_PROPERTY(GodotcordLobby, id, Variant::INT);
		ADD_GODOTCORD_PROPERTY(GodotcordLobby, owner_id, Variant::INT);
		ADD_GODOTCORD_PROPERTY(GodotcordLobby, max_users, Variant::INT);
		ADD_GODOTCORD_PROPERTY(GodotcordLobby, current_users, Variant::INT);
	}
public:
	String secret;
	//String activity_secret;
	int64_t id;
	uint64_t owner_id;
	int max_users;
	int32_t current_users;

	GET_SET_COMBO(secret, String);
	GET_SET_COMBO(id, int64_t);
	GET_SET_COMBO(owner_id, uint64_t);
	GET_SET_COMBO(max_users, int);
	GET_SET_COMBO(current_users, int32_t);
};

#endif
