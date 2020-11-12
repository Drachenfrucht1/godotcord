#include "godotcord_store_manager.h"
#include "godotcord.h"

GodotcordStoreManager *GodotcordStoreManager::singleton = NULL;

GodotcordStoreManager *GodotcordStoreManager::get_singleton() {
	return GodotcordStoreManager::singleton;
}

void GodotcordStoreManager::_bind_methods() {

}

void GodotcordStoreManager::init() {
	Godotcord::get_singleton()->get_core()->StoreManager().FetchEntitlements([](discord::Result result) { ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching user entitlements") });
	Godotcord::get_singleton()->get_core()->StoreManager().FetchSkus([](discord::Result result) { ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching user entitlements") });

	Godotcord::get_singleton()->get_core()->StoreManager().OnEntitlementCreate.Connect([this](discord::Entitlement p_entitlement) {
		
	});

	Godotcord::get_singleton()->get_core()->StoreManager().OnEntitlementDelete.Connect([this](discord::Entitlement p_entitlement) {

	});

}

GodotcordStoreManager::GodotcordStoreManager() {
    ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordStoreManager should exist")
	singleton = this;
}
