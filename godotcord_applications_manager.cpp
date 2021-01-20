#include "godotcord_applications_manager.h"
#include "godotcord.h"
#include "core/func_ref.h"
#include "core/bind/core_bind.h"
#include "core/io/json.h"

#if defined _WIN32 || defined __linux
#ifndef SODIUM_STATIC
#define SODIUM_STATIC
#endif
#include "libsodium/sodium.h"
#endif



GodotcordApplicationsManager *GodotcordApplicationsManager::singleton = NULL;

GodotcordApplicationsManager* GodotcordApplicationsManager::get_singleton() {
	return singleton;
}

void GodotcordApplicationsManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_current_locale"), &GodotcordApplicationsManager::get_current_locale);
	ClassDB::bind_method(D_METHOD("get_current_branch"), &GodotcordApplicationsManager::get_current_branch);
	ClassDB::bind_method(D_METHOD("get_oauth_token", "object", "function_name"), &GodotcordApplicationsManager::get_oauth2_token);
	ClassDB::bind_method(D_METHOD("validate_or_exit"), &GodotcordApplicationsManager::validate_or_exit);
#if defined _WIN32 || defined __linux
	ClassDB::bind_method(D_METHOD("get_ticket", "object", "function_name"), &GodotcordApplicationsManager::get_ticket);
#endif

	ADD_SIGNAL(MethodInfo("oauth_token_return", PropertyInfo(Variant::DICTIONARY, "oauth_token")));
	ADD_SIGNAL(MethodInfo("exit"));
	ADD_SIGNAL(MethodInfo("ticket_return", PropertyInfo(Variant::STRING, "ticket")));
}

String GodotcordApplicationsManager::get_current_locale() {
	char ret[128];
	Godotcord::get_singleton()->get_core()->ApplicationManager().GetCurrentLocale(ret);

	return String(ret);
}

String GodotcordApplicationsManager::get_current_branch() {
	char ret[128];
	Godotcord::get_singleton()->get_core()->ApplicationManager().GetCurrentBranch(ret);

	return String(ret);
}

void GodotcordApplicationsManager::get_oauth2_token() {

	Godotcord::get_singleton()->get_core()->ApplicationManager().GetOAuth2Token([this](discord::Result result, discord::OAuth2Token token) {
		Dictionary d;
		d["token"] = token.GetAccessToken();
		d["scopes"] = token.GetScopes();
		d["expires"] = token.GetExpires();

		this->emit_signal("oauth_token_return", d);
	});
}

void GodotcordApplicationsManager::validate_or_exit() {
	Godotcord::get_singleton()->get_core()->ApplicationManager().ValidateOrExit([this](discord::Result result) {
		this->emit_signal("exit");
	});
}

#if defined _WIN32 || defined __linux
void GodotcordApplicationsManager::get_ticket() {
	Godotcord::get_singleton()->get_core()->ApplicationManager().GetTicket([this](discord::Result result, const char * ticket) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Something went wrong while getting the ticket");

		String a(ticket);
		Vector<String> split = a.split(".");

		ERR_FAIL_COND_MSG(split[0] != "2", "The version of the ticket is not accepted");

		unsigned long long signature_length = split[1].length();
		unsigned long long message_length = split[2].length();
		int matching = crypto_sign_detached((unsigned char *)split[1].c_str(), &signature_length, (unsigned char *)split[2].c_str(), message_length, Godotcord::get_singleton()->get_public_key()) != 0;
		ERR_FAIL_COND_MSG(matching != 0, "The signature doens't match");
		String raw = _Marshalls::get_singleton()->base64_to_utf8(split[2]);

		Variant ret;
		String err;
		int line;
		JSON::parse(raw, ret, err, line);

		this->emit_signal("get_ticket_return", ret);
 });
}
#endif

GodotcordApplicationsManager::GodotcordApplicationsManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordApplicationsManager should exist");
	singleton = this;
}
