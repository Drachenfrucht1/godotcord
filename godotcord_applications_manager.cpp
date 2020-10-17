#include "godotcord_applications_manager.h"
#include "godotcord.h"
#include "core/func_ref.h"

GodotcordApplicationsManager *GodotcordApplicationsManager::singleton = NULL;

GodotcordApplicationsManager* GodotcordApplicationsManager::get_singleton() {
	return singleton;
}

void GodotcordApplicationsManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_current_locale"), &GodotcordApplicationsManager::get_current_locale);
	ClassDB::bind_method(D_METHOD("get_current_branch"), &GodotcordApplicationsManager::get_current_branch);
	ClassDB::bind_method(D_METHOD("get_oauth_token", "object", "function_name"), &GodotcordApplicationsManager::get_oauth2_token);
	ClassDB::bind_method(D_METHOD("validate_or_exit"), &GodotcordApplicationsManager::validate_or_exit);
	ClassDB::bind_method(D_METHOD("get_ticket"), &GodotcordApplicationsManager::get_current_locale);
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

void GodotcordApplicationsManager::get_oauth2_token(Object* p_object, StringName p_funcname) {
	ERR_FAIL_NULL(p_object);
	FuncRef callback;
	callback.set_instance(p_object);
	callback.set_function(p_funcname);

	Godotcord::get_singleton()->get_core()->ApplicationManager().GetOAuth2Token([this, &callback](discord::Result result, discord::OAuth2Token token) {
		Dictionary d;
		d["token"] = token.GetAccessToken();
		d["scopes"] = token.GetScopes();
		d["expires"] = token.GetExpires();

		Array a;
		a.push_back(d);
		callback.call_funcv(a);
	});
}

void GodotcordApplicationsManager::validate_or_exit() {
	Godotcord::get_singleton()->get_core()->ApplicationManager().ValidateOrExit([](discord::Result result) {
		CRASH_COND_MSG(result != discord::Result::Ok, "Something went wrong, aborting...");
	});
}

void GodotcordApplicationsManager::get_ticket(Object* p_object, StringName p_funcname) {
	ERR_PRINT_ONCE("This method is currently not implemented");
}

GodotcordApplicationsManager::GodotcordApplicationsManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordApplicationsManager should exist");
	singleton = this;
}
