#include "godotcord_store_manager.h"
#include "godotcord.h"

GodotcordStoreManager *GodotcordStoreManager::singleton = NULL;

GodotcordStoreManager *GodotcordStoreManager::get_singleton() {
	return GodotcordStoreManager::singleton;
}

void GodotcordStoreManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("fetch_skus"), &GodotcordStoreManager::fetch_skus);
	ClassDB::bind_method(D_METHOD("get_skus"), &GodotcordStoreManager::get_skus);
	ClassDB::bind_method(D_METHOD("fetch_entitlements"), &GodotcordStoreManager::fetch_entitlements);
	ClassDB::bind_method(D_METHOD("get_entitlements"), &GodotcordStoreManager::get_entitlements);
	ClassDB::bind_method(D_METHOD("has_sku_entitlement", "sku_id"), &GodotcordStoreManager::has_sku_entitlement);
	ClassDB::bind_method(D_METHOD("start_purchase", "sku_id"), &GodotcordStoreManager::start_purchase);

	ADD_SIGNAL(MethodInfo("fetch_skus_callback", PropertyInfo(Variant::ARRAY, "skus")));
	ADD_SIGNAL(MethodInfo("fetch_entitlements_callback", PropertyInfo(Variant::ARRAY, "entitlements")));

}

void GodotcordStoreManager::fetch_skus() {
	Godotcord::get_singleton()->get_core()->StoreManager().FetchSkus([this](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching user entitlements");

		emit_signal("fetch_skus_callback", this->get_skus());
	});
}

Array GodotcordStoreManager::get_skus() {
	int32_t sku_count = 0;
	Array ret;
	Godotcord::get_singleton()->get_core()->StoreManager().CountSkus(&sku_count);

	for (int i = 0; i < sku_count; i++) {
		discord::Sku sku{};
		Ref<GodotcordSKU> godotcordSKU;
		godotcordSKU.instance();
		discord::Result result = Godotcord::get_singleton()->get_core()->StoreManager().GetSkuAt(i, &sku);
		ERR_CONTINUE(result != discord::Result::Ok);

		godotcordSKU->id = sku.GetId();
		godotcordSKU->type = (GodotcordSKU::SkuType)sku.GetType();
		godotcordSKU->name = sku.GetName();

		Ref<GodotcordSKUPrice> price;
		price.instance();
		price->amount = sku.GetPrice().GetAmount();
		price->currency = sku.GetPrice().GetCurrency();

		godotcordSKU->price = price;


		ret.push_back(godotcordSKU);

	}

	return ret;
}

void GodotcordStoreManager::fetch_entitlements() {
	Godotcord::get_singleton()->get_core()->StoreManager().FetchEntitlements([this](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "An error occured while fetching user entitlements");

		emit_signal("fetch_entitlements_callback", this->get_entitlements());
	});
}

Array GodotcordStoreManager::get_entitlements() {
	int32_t sku_count = 0;
	Array ret;
	Godotcord::get_singleton()->get_core()->StoreManager().CountEntitlements(&sku_count);

	for (int i = 0; i < sku_count; i++) {
		discord::Entitlement entitlement{};
		Ref<GodotcordEntitlement> godotcordEntitlement;
		godotcordEntitlement.instance();
		discord::Result result = Godotcord::get_singleton()->get_core()->StoreManager().GetEntitlementAt(i, &entitlement);
		ERR_CONTINUE(result != discord::Result::Ok);

		godotcordEntitlement->id = entitlement.GetId();
		godotcordEntitlement->type = (GodotcordEntitlement::EntitlementType)entitlement.GetType();
		godotcordEntitlement->sku_id = entitlement.GetSkuId();

		ret.push_back(godotcordEntitlement);
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
