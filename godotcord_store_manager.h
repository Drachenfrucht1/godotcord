#ifndef GODOTCORD_STORE_MANAGER_H
#define GODOTCORD_STORE_MANAGER_H

#include "core/object.h"

class GodotcordStoreManager : public Object {
	GDCLASS(GodotcordStoreManager, Object)

public:

protected:
	static void _bind_methods();

public:
	static GodotcordStoreManager *singleton;
    static GodotcordStoreManager *get_singleton();

	void fetch_skus(Object *p_object, StringName p_funcname);
	void fetch_entitlements(Object *p_objects, StringName p_funcname);
	void start_purchase(int64_t);


	void init();
    GodotcordStoreManager();
};
#endif
