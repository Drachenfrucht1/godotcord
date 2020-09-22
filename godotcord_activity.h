#ifndef GODOTCORD_ACTIVITY_H
#define GODOTCORD_ACTIVITY_H

#include "core/reference.h"
#include "godotcord_utils.h"

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
		
		ADD_GODOTCORD_PROPERTY(GodotcordActivity, application_id, Variant::INT);
	}

public:
	static Dictionary from_discord_activity(discord::Activity p_act) {
		Dictionary ret;
		ret["state"] = p_act.GetState();
		ret["details"] = p_act.GetDetails();
		ret["partyID"] = p_act.GetParty().GetId();
		ret["partyCurrent"] = p_act.GetParty().GetSize().GetCurrentSize();
		ret["partyMax"] = p_act.GetParty().GetSize().GetMaxSize();
		ret["application_id"] = p_act.GetApplicationId();
		ret["matchSecret"] = p_act.GetSecrets().GetMatch();
		ret["joinSecret"] = p_act.GetSecrets().GetJoin();
		ret["spectateSecret"] = p_act.GetSecrets().GetSpectate();
		ret["start"] = p_act.GetTimestamps().GetStart();
		ret["end"] = p_act.GetTimestamps().GetEnd();

		return ret;
	}

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

	int64_t application_id;

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

	GET_SET_COMBO(application_id, int64_t);
};

#endif
