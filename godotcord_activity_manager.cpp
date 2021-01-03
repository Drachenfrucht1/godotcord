#include "godotcord_activity_manager.h"

GodotcordActivityManager *GodotcordActivityManager::singleton = NULL;

GodotcordActivityManager *GodotcordActivityManager::get_singleton() {
	return GodotcordActivityManager::singleton;
}

void GodotcordActivityManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_activity", "activity"), &GodotcordActivityManager::set_activity);
	ClassDB::bind_method(D_METHOD("clear_activity"), &GodotcordActivityManager::clear_activity);
	ClassDB::bind_method(D_METHOD("send_request_reply", "user_id", "reply"), &GodotcordActivityManager::send_request_reply);
	ClassDB::bind_method(D_METHOD("send_invite", "user_id", "action_type", "message"), &GodotcordActivityManager::send_invite);
	ClassDB::bind_method(D_METHOD("accept_invite", "user_id"), &GodotcordActivityManager::accept_invite);

	ADD_SIGNAL(MethodInfo("activity_join_request", PropertyInfo(Variant::STRING, "name"), PropertyInfo(Variant::INT, "id")));
	ADD_SIGNAL(MethodInfo("activity_invite", PropertyInfo(Variant::INT, "type"), PropertyInfo(Variant::STRING, "name"), PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::DICTIONARY, "activity")));
	ADD_SIGNAL(MethodInfo("activity_join", PropertyInfo(Variant::STRING, "secret")));
	ADD_SIGNAL(MethodInfo("activity_spectate", PropertyInfo(Variant::STRING, "secret")));
}

void GodotcordActivityManager::set_activity(Ref<GodotcordActivity> p_activity) {
	discord::Activity activity{};

	if (p_activity->state != "") {
		activity.SetState(p_activity->state.utf8());
	}

	if (p_activity->details != "") {
		activity.SetDetails(p_activity->details.utf8());
	}

	if (p_activity->large_text != "") {
		activity.GetAssets().SetLargeText(p_activity->large_text.utf8());
	}

	if (p_activity->large_image != "") {
		activity.GetAssets().SetLargeImage(p_activity->large_image.utf8());
	}

	if (p_activity->small_text != "") {
		activity.GetAssets().SetSmallText(p_activity->small_text.utf8());
	}

	if (p_activity->small_image != "") {
		activity.GetAssets().SetSmallImage(p_activity->small_image.utf8());
	}

	if (p_activity->party_id != "") {
		activity.GetParty().SetId(p_activity->party_id.utf8());
	}

	if (p_activity->party_max >= 0) {
		activity.GetParty().GetSize().SetMaxSize(p_activity->party_max);
	}

	if (p_activity->party_current >= 0) {
		activity.GetParty().GetSize().SetCurrentSize(p_activity->party_current);
	}

	if (p_activity->match_secret != "") {
		activity.GetSecrets().SetMatch(p_activity->match_secret.utf8());
	}

	if (p_activity->join_secret != "") {
		activity.GetSecrets().SetJoin(p_activity->join_secret.utf8());
	}

	if (p_activity->spectate_secret != "") {
		activity.GetSecrets().SetSpectate(p_activity->spectate_secret.utf8());
	}

	if (p_activity->start != 0) {
		activity.GetTimestamps().SetStart(p_activity->start);
	}

	if (p_activity->end != 0) {
		activity.GetTimestamps().SetEnd(p_activity->end);
	}

	Godotcord::get_singleton()->get_core()->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Something went wrong while settings the activity");
	});
}

void GodotcordActivityManager::clear_activity() {
	Godotcord::get_singleton()->get_core()->ActivityManager().ClearActivity([](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Something went wrong while clearing the activity");
	});
}

void GodotcordActivityManager::send_request_reply(int64_t p_user_id, GodotcordActivity::ActivityRequestReply p_reply) {
	Godotcord::get_singleton()->get_core()->ActivityManager().SendRequestReply(p_user_id, (discord::ActivityJoinRequestReply)p_reply, [this](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Seomthing went wrong while replying to the request");
	});
}

void GodotcordActivityManager::send_invite(int64_t p_user_id, GodotcordActivity::ActivityActionType p_type, String p_message) {
	Godotcord::get_singleton()->get_core()->ActivityManager().SendInvite(p_user_id, (discord::ActivityActionType)p_type, p_message.utf8(), [this](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Seomthing went wrong while sending the invite");
	});
}

void GodotcordActivityManager::accept_invite(int64_t p_user_id) {
	Godotcord::get_singleton()->get_core()->ActivityManager().AcceptInvite(p_user_id, [this](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Seomthing went wrong while accepting the invite");
	});
}

void GodotcordActivityManager::init() {
	Godotcord::get_singleton()->get_core()->ActivityManager().OnActivityInvite.Connect([this](discord::ActivityActionType p_type, discord::User p_user, discord::Activity p_activity) {
		emit_signal("activity_invite", (GodotcordActivity::ActivityActionType)p_type, p_user.GetUsername(), p_user.GetId(), GodotcordActivity::from_discord_activity(p_activity));
	});

	Godotcord::get_singleton()->get_core()->ActivityManager().OnActivityJoin.Connect([this](const char *secret) {
		emit_signal("activity_join", secret);
	});

	Godotcord::get_singleton()->get_core()->ActivityManager().OnActivityJoinRequest.Connect([this](discord::User p_user) {
		emit_signal("activity_join_request", p_user.GetUsername(), p_user.GetId());
	});

	Godotcord::get_singleton()->get_core()->ActivityManager().OnActivitySpectate.Connect([this](const char *secret) {
		emit_signal("activity_spectate", secret);
	});
}

GodotcordActivityManager::GodotcordActivityManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordActivityManager should exist")
	singleton = this;
}

GodotcordActivityManager::~GodotcordActivityManager() {

}
