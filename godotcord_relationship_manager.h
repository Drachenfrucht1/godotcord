#ifndef GODOTCORD_RELATIONSHIP_MANAGER_H
#define GODOTCORD_RELATIONSHIP_MANAGER_H

#include "core/object.h"

class GodotcordRelationshipManager : public Object {
	GDCLASS(GodotcordRelationshipManager, Object)

protected:
	static void _bind_methods();

public:
	static GodotcordRelationshipManager *singleton;
	static GodotcordRelationshipManager *get_singleton();
	void init();

	Array filter_relationships(Object *p_object, StringName p_func_name);
	Array get_relationsips();

	GodotcordRelationshipManager();
	~GodotcordRelationshipManager();
};

#endif //GODOTCORD_RELATIONSHIP_MANAGER_H
