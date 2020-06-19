#ifndef GODOTCORD_LOBBY_H
#define GODOTCORD_LOBBY_H

#include "core/dictionary.h"

class GodotcordLobby {

public:
	String secret;
	//String activity_secret;
	int64_t id;
	uint64_t owner_id;
	int max_users;
	int32_t current_users;


    static Dictionary get_dictionary(GodotcordLobby *l) {
        Dictionary d;

        d["id"] = l->id;
		d["secret"] = l->secret;
		d["max_users"] = l->max_users;
		d["current_users"] = l->current_users;
		d["owner_id"] = l->owner_id;

        return d;
    }
};

#endif
