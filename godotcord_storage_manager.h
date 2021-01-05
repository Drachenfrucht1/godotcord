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
    unsigned char* read(String name);
    void read_async(String name);
    void read_async_partial(String name, int32_t offset, int32_t length);
    void write(String name, unsigned char* data);
    void write_async(String name, unsigned char* data);
    void destroy(String name);
    void exists(String name);
    void stat(String name);
    uint32_t count();
    void stat_at(int32_t index);

    void init();
    GodotcordStorageManager();
};

#endif //GGODOTCORD_STORAGE_MANAGER_H