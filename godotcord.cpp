#include "godotcord.h"

Godotcord *Godotcord::singleton = NULL;

Godotcord::Godotcord() {
	_route = String("");

	singleton = this;
}

Godotcord* Godotcord::get_singleton() {
	return singleton;
}

void Godotcord::run_callbacks() {
	if (init_bool) {
		_core->RunCallbacks();
	}
}

void Godotcord::_bind_methods() {
    ClassDB::bind_method(D_METHOD("init", "id"), &Godotcord::init);
	ClassDB::bind_method(D_METHOD("run_callbacks"), &Godotcord::run_callbacks);
    ClassDB::bind_method(D_METHOD("set_activity", "activity" ), &Godotcord::setActivity);
    ClassDB::bind_method(D_METHOD("clear_activity"), &Godotcord::clearActivity);

	ClassDB::bind_method(D_METHOD("get_current_username"), &Godotcord::get_current_username);
	ClassDB::bind_method(D_METHOD("get_current_user_discriminator"), &Godotcord::get_current_user_discriminator);
	ClassDB::bind_method(D_METHOD("get_current_user_id"), &Godotcord::get_current_user_id);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "user_name"), "", "get_current_username");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "user_discriminator"), "", "get_current_user_discriminator");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "user_id"), "", "get_current_user_id");

	ADD_SIGNAL(MethodInfo("join_request", PropertyInfo(Variant::STRING, "name"), PropertyInfo(Variant::INT, "id")));
	ADD_SIGNAL(MethodInfo("activity_join", PropertyInfo(Variant::STRING, "secret")));
}

Error Godotcord::init(discord::ClientId clientId) {
	auto result = discord::Core::Create(clientId, DiscordCreateFlags_Default, &_core);


	ERR_FAIL_COND_V(result != discord::Result::Ok, ERR_CANT_CONNECT);


	init_bool = true;

	_core->SetLogHook(discord::LogLevel::Info, [](discord::LogLevel level, const char *msg) {
		switch (level) {
			case discord::LogLevel::Warn:
				print_line(vformat("[DiscordGameSDK][Warn] %s", msg));
				break;
			case discord::LogLevel::Info:
				print_line(vformat("[DiscordGameSDK][Info] %s", msg));
				break;
			case discord::LogLevel::Error:
				print_error(vformat("[DiscordGameSDK][ERR] %s", msg));
				break;
		}
	});

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

	_core->NetworkManager().OnRouteUpdate.Connect([this](const char *p_route) {
		_route = String(p_route);
	});

	return OK;
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

String Godotcord::get_current_username() {
	//has to be added - editor crashed otherwise
	if (!_core)
		return "";
	discord::User user;
	discord::Result result = _core->UserManager().GetCurrentUser(&user);
	ERR_FAIL_COND_V(result != discord::Result::Ok, "")
	return user.GetUsername();
}

String Godotcord::get_current_user_discriminator() {
	//has to be added - editor crashed otherwise
	if (!_core)
		return "";
	discord::User user;
	discord::Result result = _core->UserManager().GetCurrentUser(&user);
	ERR_FAIL_COND_V(result != discord::Result::Ok, "")
	return user.GetDiscriminator();
}

int64_t Godotcord::get_current_user_id() {
	//has to be added - editor crashed otherwise
	if (!_core)
		return 0;
	discord::User user;
	discord::Result result = _core->UserManager().GetCurrentUser(&user);
	ERR_FAIL_COND_V(result != discord::Result::Ok, 0)
	return user.GetId();
}

void Godotcord::removeRouteEvent() {
	_core->NetworkManager().OnRouteUpdate.DisconnectAll();
}

discord::Core* Godotcord::get_core() {
	return _core;
}
