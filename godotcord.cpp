#include "godotcord.h"
Godotcord::Godotcord() {}

void Godotcord::_bind_methods() {
    ClassDB::bind_method(D_METHOD("init", "id"), &Godotcord::init);
    ClassDB::bind_method(D_METHOD("callbacks"), &Godotcord::callbacks);
    ClassDB::bind_method(D_METHOD("set_activity", "activity" ), &Godotcord::setActivity);
    ClassDB::bind_method(D_METHOD("clear_activity"), &Godotcord::clearActivity);

	ADD_SIGNAL(MethodInfo("join_request", PropertyInfo(Variant::STRING, "name"), PropertyInfo(Variant::INT, "id")));
	ADD_SIGNAL(MethodInfo("activity_join", PropertyInfo(Variant::STRING, "secret")));
}

void Godotcord::init(discord::ClientId clientId) {
	auto result = discord::Core::Create(clientId, DiscordCreateFlags_Default, &_core);

	if (result != discord::Result::Ok) {
		//error
	}

	_core->ActivityManager().OnActivityJoinRequest.Connect([this](discord::User p_user) {
		emit_signal("join_request", p_user.GetUsername(), p_user.GetId());
	});

	_core->ActivityManager().OnActivityJoin.Connect([this](const char * p_secret) {
		//workaround because onActivityJoin event is fired twice by discord
		emit_signal("activity_join", String(p_secret));
	});

	_core->UserManager().OnCurrentUserUpdate.Connect([this]() {
		print_verbose("Local Discord user updated");
	});
}

/*void Godotcord::init_debug(discord::ClientId clientId, String id) {
	_putenv_s("DISCORD_INSTANCE_ID", id.utf8());
	print_line(vformat("Set DISCORD_INSTANCE_ID to %s", id));
	print_line(vformat("Read DISCORD_INSTANCE_ID is %s", getenv("DISCORD_INSTANCE_ID")));
    auto result = discord::Core::Create(clientId, DiscordCreateFlags_Default, &_core);

    if (result != discord::Result::Ok) {
        //error
    }
}*/

void Godotcord::callbacks() {
    _core->RunCallbacks();
}

void Godotcord::setActivity(Ref<GodotcordActivity> act) {

    discord::Activity activity{};
    
	if (act->state != "") {
		activity.SetState(act->state.utf8());
	}

	if(act->details != "") {
		activity.SetDetails(act->details.utf8());
	}

	if (act->largeText != "") {
        activity.GetAssets().SetLargeText(act->largeText.utf8());
    }

    if (act->largeImage != "") {
        activity.GetAssets().SetLargeImage(act->largeImage.utf8());
    }

    if (act->smallText != "") {
        activity.GetAssets().SetSmallText(act->smallText.utf8());
    }

    if (act->smallImage != "") {
        activity.GetAssets().SetSmallImage(act->smallImage.utf8());
    }

    if (act->partyID != "") {
        activity.GetParty().SetId(act->partyID.utf8());
    }

    if (act->partyMax >= 0) {
        activity.GetParty().GetSize().SetMaxSize(act->partyMax);
    }    

    if (act->partyCurrent >= 0) {
        activity.GetParty().GetSize().SetCurrentSize(act->partyCurrent);
    }

    if (act->matchSecret != "") {
        activity.GetSecrets().SetMatch(act->matchSecret.utf8());
    }    

    if (act->joinSecret != "") {
        activity.GetSecrets().SetJoin(act->joinSecret.utf8());
    }

    if (act->spectateSecret != "") {
        activity.GetSecrets().SetSpectate(act->spectateSecret.utf8());
    }

    if (act->start != 0) {
        activity.GetTimestamps().SetStart(act->start);
    }

    if (act->end != 0) {
        activity.GetTimestamps().SetEnd(act->end);
    }

    _core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
        if (result != discord::Result::Ok) {
            //error
        }
    });
}

void Godotcord::clearActivity() {
    _core->ActivityManager().ClearActivity([](discord::Result result) {
        if (result != discord::Result::Ok) {
            //error
        }
    });
}

discord::Core* Godotcord::get_core() {
	return _core;
}
