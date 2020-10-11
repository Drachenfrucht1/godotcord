#ifndef GODOTCORD_RELATIONSHIP_MANAGER_H
#define GODOTCORD_RELATIONSHIP_MANAGER_H

#include "core/object.h"

class GodotcordRelationshipManager : public Object {
	GDCLASS(GodotcordRelationshipManager, Object)

public:
	static GodotcordRelationshipManager *singleton;
	static GodotcordRelationshipManager *get_singleton();

	GodotcordRelationshipManager();
	~GodotcordRelationshipManager();
};

#endif //GODOTCORD_RELATIONSHIP_MANAGER_H
