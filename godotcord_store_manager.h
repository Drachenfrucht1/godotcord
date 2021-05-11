#ifndef GODOTCORD_STORE_MANAGER_H
#define GODOTCORD_STORE_MANAGER_H

#include "core/object.h"
#include "core/reference.h"
#include "godotcord_utils.h"

#include "godotcord_store_data.h"

class GodotcordStoreManager : public Object {
	GDCLASS(GodotcordStoreManager, Object)

protected:
	static void _bind_methods();

public:
	static GodotcordStoreManager *singleton;
    static GodotcordStoreManager *get_singleton();

	void fetch_skus();
	Array get_skus();
	void fetch_entitlements();
	Array get_entitlements();
	bool has_sku_entitlement(int64_t p_sku_id);
	void start_purchase(int64_t p_sku_id);
	


	void init();
    GodotcordStoreManager();
};
#endif // GODOTCORD_STORE_MANAGER_H
