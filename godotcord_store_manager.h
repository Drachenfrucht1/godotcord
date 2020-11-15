#ifndef GODOTCORD_STORE_MANAGER_H
#define GODOTCORD_STORE_MANAGER_H

#include "core/object.h"

class GodotcordStoreManager : public Object {
	GDCLASS(GodotcordStoreManager, Object)

public:
	enum SkuType {
		APP = 1,
		DLC,
		CONSUMABLE,
		BUNDLE
	};

	enum EntitlementType {
		PURCHASE = 1,
		PREMIUM_SUBSCRIPTION,
		DEVELOPER_GIFT,
		TEST_MODE_PURCHASE,
		FREE_PURCHASE,
		USER_GIFT,
		PREMIUM_PURCHASE,
	};

protected:
	static void _bind_methods();

public:
	static GodotcordStoreManager *singleton;
    static GodotcordStoreManager *get_singleton();

	void fetch_skus(Object *p_object, StringName p_funcname);
	Array get_skus();
	void fetch_entitlements(Object *p_objects, StringName p_funcname);
	Array get_entitlements();
	bool has_sku_entitlement(int64_t p_sku_id);
	void start_purchase(int64_t p_sku_id);
	


	void init();
    GodotcordStoreManager();
};

VARIANT_ENUM_CAST(GodotcordStoreManager::SkuType);
VARIANT_ENUM_CAST(GodotcordStoreManager::EntitlementType);

#endif
