#ifndef GODOTCORD_H
#define GODOTCORD_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "discord-files/discord.h"

using namespace godot;

class Godotcord : public Object {
    GDCLASS(Godotcord, Object)

private:
	discord::Core *_core{};
	bool init_bool = false;

	void _init_discord();

protected:
	static void _bind_methods();

public:
	static Godotcord *singleton;
	static Godotcord *get_singleton();

	static const int CreateFlags_DEFAULT = 0;
	static const int CreateFlags_NO_REQUIRE_DISCORD = 1;

	// enum CreateFlags {
	// 	CreateFlags_DEFAULT = 0,
	// 	CreateFlags_NO_REQUIRE_DISCORD = 1,
	// };

    Error init(int64_t clientId, int createFlags);
	void init_debug(int64_t clientId, String id, int createFlags);

	void run_callbacks();

	bool is_init() const {
		return init_bool;
	}

	discord::Core *get_core();

    Godotcord();
	~Godotcord();
};

#endif
