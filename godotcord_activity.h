#ifndef GODOTCORD_ACTIVITY_H
#define GODOTCORD_ACTIVITY_H

#include "core/reference.h"
#include "godotcord_utils.h"

class GodotcordActivity : public Reference {
	GDCLASS(GodotcordActivity, Reference)

public:
	enum ActivityRequestReply {
		NO,
		YES,
		IGNORE
	};

	enum ActivityActionType {
		JOIN = 1,
		SPECTATE = 2
	};

protected:
	static void _bind_methods() {
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, state, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, details, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, large_image, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, large_text, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, small_image, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, small_text, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, party_id, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, party_max, Variant::INT)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, party_current, Variant::INT)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, match_secret, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, join_secret, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, spectate_secret, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, start, Variant::INT)
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, end, Variant::INT)
		
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, application_id, Variant::INT);

		BIND_ENUM_CONSTANT(NO);
		BIND_ENUM_CONSTANT(YES);
		BIND_ENUM_CONSTANT(IGNORE);

		BIND_ENUM_CONSTANT(JOIN);
		BIND_ENUM_CONSTANT(SPECTATE);
	}

public:
	static Dictionary from_discord_activity(discord::Activity p_act) {
		Dictionary ret;
		ret["state"] = p_act.GetState();
		ret["details"] = p_act.GetDetails();
		ret["party_id"] = p_act.GetParty().GetId();
		ret["party_current"] = p_act.GetParty().GetSize().GetCurrentSize();
		ret["party_max"] = p_act.GetParty().GetSize().GetMaxSize();
		ret["application_id"] = p_act.GetApplicationId();
		ret["match_secret"] = p_act.GetSecrets().GetMatch();
		ret["join_secret"] = p_act.GetSecrets().GetJoin();
		ret["spectate_secret"] = p_act.GetSecrets().GetSpectate();
		ret["start"] = p_act.GetTimestamps().GetStart();
		ret["end"] = p_act.GetTimestamps().GetEnd();

		return ret;
	}

	String state = "";
	String details = "";
	String large_image = "";
	String large_text = "";
	String small_image = "";
	String small_text = "";
	String party_id = "";
	int party_max = -1;
	int party_current = -1;
	String match_secret = "";
	String join_secret = "";
	String spectate_secret = "";
	int start = 0;
	int end = 0;

	int64_t application_id;

	GET_SET_COMBO(state, String)
	GET_SET_COMBO(details, String)
	GET_SET_COMBO(large_image, String)
	GET_SET_COMBO(large_text, String)
	GET_SET_COMBO(small_image, String)
	GET_SET_COMBO(small_text, String)
	GET_SET_COMBO(party_id, String)
	GET_SET_COMBO(party_max, int)
	GET_SET_COMBO(party_current, int)
	GET_SET_COMBO(match_secret, String)
	GET_SET_COMBO(join_secret, String)
	GET_SET_COMBO(spectate_secret, String)
	GET_SET_COMBO(start, int)
	GET_SET_COMBO(end, int)

	GET_SET_COMBO(application_id, int64_t);
};

VARIANT_ENUM_CAST(GodotcordActivity::ActivityRequestReply);
VARIANT_ENUM_CAST(GodotcordActivity::ActivityActionType);

#endif
