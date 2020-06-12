#ifndef GODOTCORD_ACTIVITY_H
#define GODOTCORD_ACTIVITY_H

#include "core/reference.h"

#define GET_SET_COMBO(property, type)    \
	void set_##property(type p_##type) { \
		property = p_##type;             \
	}                                    \
	type get_##property() const {        \
		return property;                 \
	}

#define ADD_GODOTCORD_PROPERTY(class, property, type)                                     \
	ClassDB::bind_method(D_METHOD("set_" #property, #property), &class ::set_##property); \
	ClassDB::bind_method(D_METHOD("get_" #property), &class ::get_##property);            \
	ADD_PROPERTY(PropertyInfo(type, #property), "set_" #property, "get_" #property);


class GodotcordActivity : public Reference {
	GDCLASS(GodotcordActivity, Reference)

protected:
	static void _bind_methods() {
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, state, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, details, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, largeImage, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, largeText, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, smallImage, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, smallText, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, partyID, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, partyMax, Variant::INT)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, partyCurrent, Variant::INT)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, matchSecret, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, joinSecret, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, spectateSecret, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, start, Variant::INT)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, end, Variant::INT)
	}

public:
	String state = "";
	String details = "";
	String largeImage = "";
	String largeText = "";
	String smallImage = "";
	String smallText = "";
	String partyID = "";
	int partyMax = -1;
	int partyCurrent = -1;
	String matchSecret = "";
	String joinSecret = "";
	String spectateSecret = "";
	int start = 0;
	int end = 0;

	GET_SET_COMBO(state, String)
	GET_SET_COMBO(details, String)
	GET_SET_COMBO(largeImage, String)
	GET_SET_COMBO(largeText, String)
	GET_SET_COMBO(smallImage, String)
	GET_SET_COMBO(smallText, String)
	GET_SET_COMBO(partyID, String)
	GET_SET_COMBO(partyMax, int)
	GET_SET_COMBO(partyCurrent, int)
	GET_SET_COMBO(matchSecret, String)
	GET_SET_COMBO(joinSecret, String)
	GET_SET_COMBO(spectateSecret, String)
	GET_SET_COMBO(start, int)
	GET_SET_COMBO(end, int)
};

#endif
