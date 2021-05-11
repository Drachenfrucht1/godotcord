#ifndef GODOTCORD_STORAGE_MANAGER_H
#define GODOTCORD_STORAGE_MANAGER_H

#include "core/object.h"
#include "godotcord.h"

class GodotcordFileStat : public Reference {
    GDCLASS(GodotcordFileStat, Reference)
protected:
	static void _bind_methods() {
		ADD_GODOTCORD_PROPERTY(GodotcordFileStat, file_name, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordFileStat, last_modified, Variant::INT)
		ADD_GODOTCORD_PROPERTY(GodotcordFileStat, size, Variant::INT)

	}
public:
	String file_name = "";
	uint64_t last_modified = 0;
	uint64_t size = 0;

	GET_SET_COMBO(file_name, String)
	GET_SET_COMBO(last_modified, uint64_t)
	GET_SET_COMBO(size, uint64_t)

};

class GodotcordStorageManager : public Object {
    GDCLASS(GodotcordStorageManager, Object)
protected:
    static void _bind_methods();

public:
    static GodotcordStorageManager *singleton;
    static GodotcordStorageManager *get_singleton();

    String get_path();
    PoolByteArray read(String p_name);
    void read_async(String p_name);
    void read_async_partial(String p_name, int32_t p_offset, int32_t p_length);
    void write(String p_name, PoolByteArray p_data);
    void write_async(String p_name, PoolByteArray p_data);
    void destroy(String p_name);
    bool exists(String p_name);
    Ref<GodotcordFileStat> stat(String p_name);
    uint32_t count();
    Ref<GodotcordFileStat> stat_at(int32_t p_index);

    GodotcordStorageManager();
    ~GodotcordStorageManager();
};

#endif //GODOTCORD_STORAGE_MANAGER_H
