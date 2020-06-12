#ifndef GODOTCORD_LOBBY_H
#define GODOTCORD_LOBBY_H

#include "core/dictionary.h"

class GodotcordLobby {

protected:

public:
	String secret;
	//String activity_secret;
	int64_t id;
	int max_users;
	int32_t current_users;


    static Dictionary get_dictionary(GodotcordLobby *l) {
        Dictionary d;

        d["id"] = l->id;
		d["secret"] = l->secret;
		d["max_users"] = l->max_users;
		d["current_users"] = l->current_users;

        return d;
    }
};

#endif
