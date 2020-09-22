#ifndef GODOTCORD_RELATIONSHIP_H
#define GODOTCORD_RELATIONSHIP_H

#include "core/object.h"
#include "godotcord.h"
#include "godotcord_utils.h"

class GodotcordRelationship : public Object {
    GDCLASS(GodotcordRelationship, Object)

protected:
    static void _bind_methods() {
        ADD_GODOTCORD_PROPERTY(GodotcordRelationship, type, Variant::INT);
        ADD_GODOTCORD_PROPERTY(GodotcordRelationship, user_id, Variant::INT);
        ADD_GODOTCORD_PROPERTY(GodotcordRelationship, presence, Variant::DICTIONARY);
    }

public:
    Godotcord::RelationshipType type;
    int64_t user_id;
    Dictionary presence;

    GET_SET_COMBO(type, Godotcord::RelationshipType);
    GET_SET_COMBO(user_id, int64_t);
    GET_SET_COMBO(presence, Dictionary);
};

#endif
