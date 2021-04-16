#ifndef GODOTCORD_USER_H
#define GODOTCORD_USER_H

#include "core/reference.h"
#include "godotcord_utils.h"

class GodotcordUser : public Reference {
	GDCLASS(GodotcordUser, Reference)
protected:
	static void _bind_methods() {
		ADD_GODOTCORD_PROPERTY(GodotcordUser, id, Variant::INT);
		ADD_GODOTCORD_PROPERTY(GodotcordUser, name, Variant::STRING);
		ADD_GODOTCORD_PROPERTY(GodotcordUser, discriminator, Variant::STRING);
		ADD_GODOTCORD_PROPERTY(GodotcordUser, avatar, Variant::STRING);
		ADD_GODOTCORD_PROPERTY(GodotcordUser, bot, Variant::BOOL);
	};
public:
	uint64_t id = 0;
	String name = "";
	String discriminator = "";
	String avatar = "";
	bool bot = false;

	GET_SET_COMBO(id, uint64_t)
	GET_SET_COMBO(name, String)
	GET_SET_COMBO(discriminator, String)
	GET_SET_COMBO(avatar, String)
	GET_SET_COMBO(bot, bool)
};

#endif //GODOTCORD_USER_H
