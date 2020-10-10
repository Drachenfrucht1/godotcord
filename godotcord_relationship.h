#ifndef GODOTCORD_RELATIONSHIP_H
#define GODOTCORD_RELATIONSHIP_H

#include "core/object.h"
#include "godotcord_utils.h"

class GodotcordRelationship : public Object {
    GDCLASS(GodotcordRelationship, Object)

public:
	enum RelationshipType {
		NONE,
		FRIEND,
		BLOCKED,
		PENDING_INCOMING,
		PENDING_OUTGOING,
		IMPLICIT
	};

	enum PresenceStatus {
		OFFLINE,
		ONLINE,
		IDLE,
		DO_NOT_DISTURB
	};



protected:
    static void _bind_methods() {
        ADD_GODOTCORD_PROPERTY(GodotcordRelationship, type, Variant::INT);
        ADD_GODOTCORD_PROPERTY(GodotcordRelationship, user_id, Variant::INT);
        ADD_GODOTCORD_PROPERTY(GodotcordRelationship, presence, Variant::DICTIONARY);

		BIND_ENUM_CONSTANT(NONE);
		BIND_ENUM_CONSTANT(FRIEND);
		BIND_ENUM_CONSTANT(BLOCKED);
		BIND_ENUM_CONSTANT(PENDING_INCOMING);
		BIND_ENUM_CONSTANT(PENDING_OUTGOING);
		BIND_ENUM_CONSTANT(IMPLICIT);

		BIND_ENUM_CONSTANT(OFFLINE);
		BIND_ENUM_CONSTANT(ONLINE);
		BIND_ENUM_CONSTANT(IDLE);
		BIND_ENUM_CONSTANT(DO_NOT_DISTURB);
    }

public:

    RelationshipType type = NONE;
    int64_t user_id = 0;
    Dictionary presence;

    GET_SET_COMBO(type, RelationshipType);
    GET_SET_COMBO(user_id, int64_t);
    GET_SET_COMBO(presence, Dictionary);

	Dictionary to_dictionary() {
		Dictionary d;

		d["type"] = type;
		d["user_id"] = user_id;
		d["presence"] = presence;

		return d;
	}
};


VARIANT_ENUM_CAST(GodotcordRelationship::RelationshipType);
VARIANT_ENUM_CAST(GodotcordRelationship::PresenceStatus);

#endif
