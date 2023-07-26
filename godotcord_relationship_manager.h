#ifndef GODOTCORD_RELATIONSHIP_MANAGER_H
#define GODOTCORD_RELATIONSHIP_MANAGER_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/array.hpp>

#include "godotcord.h"


class GodotcordRelationshipManager : public Object {
	GDCLASS(GodotcordRelationshipManager, Object);

protected:
	static void _bind_methods();

public:
	static GodotcordRelationshipManager *singleton;
	static GodotcordRelationshipManager *get_singleton();
	void init();

	Array filter_relationships(Callable filter_func);
	Array get_relationships();

	GodotcordRelationshipManager();
	~GodotcordRelationshipManager();
};

#endif //GODOTCORD_RELATIONSHIP_MANAGER_H
