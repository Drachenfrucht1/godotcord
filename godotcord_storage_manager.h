#ifndef GODOTCORD_STORAGE_MANAGER_H
#define GODGODOTCORD_STORAGE_MANAGER_H

#include "core/object.h"
#include "godotcord.h"

class GodotcordStorageManager : public Object {
    GDCLASS(GodotcordStorageManager, Object)
protected:
    static void _bind_methods();

public:
    static GodotcordStorageManager *singleton;
    static GodotcordStorageManager *get_singleton();

    String get_path();
    unsigned char* read(String p_name);
    void read_async(String p_name, Object* p_object, StringName p_funcname);
    void read_async_partial(String p_name, int32_t p_offset, int32_t p_length, Object* p_object, StringName p_funcname);
    void write(String p_name, uint8_t* p_data);
    void write_async(String p_name, unsigned char* p_data);
    void destroy(String p_name);
    void exists(String p_name);
    void stat(String p_name);
    uint32_t count();
    void stat_at(int32_t p_index);

    void init();
    GodotcordStorageManager();
};

#endif //GGODOTCORD_STORAGE_MANAGER_H