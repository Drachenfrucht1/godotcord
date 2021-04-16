#ifndef GODOTCORD_RELATIONSHIP_H
#define GODOTCORD_RELATIONSHIP_H

#include "core/reference.h"
#include "godotcord_utils.h"
#include "godotcord_activity.h"

class GodotcordPresence : public Reference {
	GDCLASS(GodotcordPresence, Reference);

public:
	enum PresenceStatus {
		OFFLINE,
		ONLINE,
		IDLE,
		DO_NOT_DISTURB
	};

protected:
	static void _bind_methods() {
		ADD_GODOTCORD_PROPERTY(GodotcordPresence, status, Variant::INT);
        ADD_GODOTCORD_PROPERTY(GodotcordPresence, activity, Variant::OBJECT);

		BIND_ENUM_CONSTANT(OFFLINE);
		BIND_ENUM_CONSTANT(ONLINE);
		BIND_ENUM_CONSTANT(IDLE);
		BIND_ENUM_CONSTANT(DO_NOT_DISTURB);
	}

public:
	PresenceStatus status;
	Ref<GodotcordActivity> activity;

	GET_SET_COMBO(status, PresenceStatus);
    GET_SET_COMBO_OBJ(activity, GodotcordActivity);
};

class GodotcordRelationship : public Reference {
    GDCLASS(GodotcordRelationship, Reference)

public:
	enum RelationshipType {
		NONE,
		FRIEND,
		BLOCKED,
		PENDING_INCOMING,
		PENDING_OUTGOING,
		IMPLICIT
	};

protected:
    static void _bind_methods() {
        ADD_GODOTCORD_PROPERTY(GodotcordRelationship, type, Variant::INT);
        ADD_GODOTCORD_PROPERTY(GodotcordRelationship, user_id, Variant::INT);
        ADD_GODOTCORD_PROPERTY(GodotcordRelationship, presence, Variant::OBJECT);

		BIND_ENUM_CONSTANT(NONE);
		BIND_ENUM_CONSTANT(FRIEND);
		BIND_ENUM_CONSTANT(BLOCKED);
		BIND_ENUM_CONSTANT(PENDING_INCOMING);
		BIND_ENUM_CONSTANT(PENDING_OUTGOING);
		BIND_ENUM_CONSTANT(IMPLICIT);
    }

public:
    RelationshipType type = NONE;
    int64_t user_id = 0;
    Ref<GodotcordPresence> presence;

    GET_SET_COMBO(type, RelationshipType);
    GET_SET_COMBO(user_id, int64_t);
    GET_SET_COMBO_OBJ(presence, GodotcordPresence);
};


VARIANT_ENUM_CAST(GodotcordRelationship::RelationshipType);
VARIANT_ENUM_CAST(GodotcordPresence::PresenceStatus);

#endif
