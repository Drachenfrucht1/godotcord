#include "godotcord_store_manager.h"
#include "godotcord.h"
#include "core/func_ref.h"

GodotcordStoreManager *GodotcordStoreManager::singleton = NULL;

GodotcordStoreManager *GodotcordStoreManager::get_singleton() {
	return GodotcordStoreManager::singleton;
}

void GodotcordStoreManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("fetch_skus", "object", "funcname"), &GodotcordStoreManager::fetch_skus);
	ClassDB::bind_method(D_METHOD("get_skus"), &GodotcordStoreManager::get_skus);
	ClassDB::bind_method(D_METHOD("fetch_entitlements", "object", "funcname"), &GodotcordStoreManager::fetch_entitlements);
	ClassDB::bind_method(D_METHOD("get_entitlements"), &GodotcordStoreManager::get_entitlements);
	ClassDB::bind_method(D_METHOD("has_sku_entitlement", "sku_id"), &GodotcordStoreManager::has_sku_entitlement);
	ClassDB::bind_method(D_METHOD("start_purchase", "sku_id"), &GodotcordStoreManager::start_purchase);

	BIND_ENUM_CONSTANT(APP);
	BIND_ENUM_CONSTANT(DLC);
	BIND_ENUM_CONSTANT(CONSUMABLE);
	BIND_ENUM_CONSTANT(BUNDLE);

	BIND_ENUM_CONSTANT(PURCHASE);
	BIND_ENUM_CONSTANT(PREMIUM_SUBSCRIPTION);
	BIND_ENUM_CONSTANT(DEVELOPER_GIFT);
	BIND_ENUM_CONSTANT(TEST_MODE_PURCHASE);
	BIND_ENUM_CONSTANT(FREE_PURCHASE);
	BIND_ENUM_CONSTANT(USER_GIFT);
	BIND_ENUM_CONSTANT(PREMIUM_PURCHASE);
}

void GodotcordStoreManager::fetch_skus(Object* p_object, StringName p_funcname) {
	ERR_FAIL_NULL(p_object);

	FuncRef callback;
	callback.set_instance(p_object);
	callback.set_function(p_funcname);

	Godotcord::get_singleton()->get_core()->StoreManager().FetchSkus([this, &callback](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching user entitlements");

		Array a;

		a.push_back(this->get_skus());

		callback.call_funcv(a);
	});
}

Array GodotcordStoreManager::get_skus() {
	int32_t sku_count = 0;
	Array ret;
	Godotcord::get_singleton()->get_core()->StoreManager().CountSkus(&sku_count);

	for (int i = 0; i < sku_count; i++) {
		discord::Sku sku;
		Dictionary d;
		discord::Result result = Godotcord::get_singleton()->get_core()->StoreManager().GetSkuAt(i, &sku);
		ERR_CONTINUE(result != discord::Result::Ok);

		d["id"] = sku.GetId();
		d["type"] = (SkuType)sku.GetType();
		d["name"] = sku.GetName();

		Dictionary price;
		price["amount"] = sku.GetPrice().GetAmount();
		price["currency"] = sku.GetPrice().GetCurrency();

		d["price"] = price;


		ret.push_back(d);
	}

	return ret;
}

void GodotcordStoreManager::fetch_entitlements(Object* p_object, StringName p_funcname) {
	ERR_FAIL_NULL(p_object);

	FuncRef callback;
	callback.set_instance(p_object);
	callback.set_function(p_funcname);

	Godotcord::get_singleton()->get_core()->StoreManager().FetchEntitlements([this, &callback](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching user entitlements");

		Array a;

		a.push_back(this->get_skus());

		callback.call_funcv(a);
	});
}

Array GodotcordStoreManager::get_entitlements() {
	int32_t sku_count = 0;
	Array ret;
	Godotcord::get_singleton()->get_core()->StoreManager().CountEntitlements(&sku_count);

	for (int i = 0; i < sku_count; i++) {
		discord::Entitlement entitlement;
		Dictionary d;
		discord::Result result = Godotcord::get_singleton()->get_core()->StoreManager().GetEntitlementAt(i, &entitlement);
		ERR_CONTINUE(result != discord::Result::Ok);

		d["id"] = entitlement.GetId();
		d["type"] = (EntitlementType)entitlement.GetType();
		d["sku_id"] = entitlement.GetSkuId();

		ret.push_back(d);
	}

	return ret;
}

bool GodotcordStoreManager::has_sku_entitlement(int64_t p_sku_id) {
	bool b;
	discord::Result result = Godotcord::get_singleton()->get_core()->StoreManager().HasSkuEntitlement(p_sku_id, &b);

	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, false, "An error occured while checking the sku entitlement");

	return b;
}

void GodotcordStoreManager::start_purchase(int64_t p_sku_id) {
	Godotcord::get_singleton()->get_core()->StoreManager().StartPurchase(p_sku_id, [](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while starting the purchase flow");
	});
}

void GodotcordStoreManager::init() {
	Godotcord::get_singleton()->get_core()->StoreManager().FetchEntitlements([](discord::Result result) { ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching user entitlements") });
	Godotcord::get_singleton()->get_core()->StoreManager().FetchSkus([](discord::Result result) { ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching user entitlements") });

	Godotcord::get_singleton()->get_core()->StoreManager().OnEntitlementCreate.Connect([this](discord::Entitlement p_entitlement) {
		Godotcord::get_singleton()->get_core()->StoreManager().FetchEntitlements([](discord::Result result) { ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching user entitlements") });
	});

	Godotcord::get_singleton()->get_core()->StoreManager().OnEntitlementDelete.Connect([this](discord::Entitlement p_entitlement) {
		Godotcord::get_singleton()->get_core()->StoreManager().FetchEntitlements([](discord::Result result) { ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching user entitlements") });
	});

}

GodotcordStoreManager::GodotcordStoreManager() {
    ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordStoreManager should exist")
	singleton = this;
}
