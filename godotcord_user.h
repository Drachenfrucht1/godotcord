#ifndef GODOTCORD_USER_H
#define GODOTCORD_USER_H

#include "core/reference.h"

class GodotcordUser : public Reference {
	GDCLASS(GodotcordUser, Reference)
public:
	uint64_t id = -1;
	String name = "";
	String discriminator = "";
	String avatar = "";
	bool bot = false;

};

#endif //GODOTCORD_USER_H
