#ifndef GODOTCORD_STORAGE_MANAGER_H
<<<<<<< HEAD
#define GODGODOTCORD_STORAGE_MANAGER_H
=======
#define GODOTCORD_STORAGE_MANAGER_H
>>>>>>> c4d681b (parent ad073dfbe083110e5e7d1b32df7ca6718e378ff0)

#include "core/object.h"
#include "godotcord.h"

class GodotcordStorageManager : public Object {
    GDCLASS(GodotcordStorageManager, Object)
protected:
    static void _bind_methods();
    static Dictionary _file_stat(discord::FileStat fileStat) {
        Dictionary p_stat;
        p_stat["file_name"] = fileStat.GetFilename();
        p_stat["last_modified"] = fileStat.GetLastModified();
        p_stat["size"] = fileStat.GetSize();
        return p_stat;
    }

public:
    static GodotcordStorageManager *singleton;
    static GodotcordStorageManager *get_singleton();

    String get_path();
    PoolByteArray read(String p_name);
    void read_async(String p_name);
    void read_async_partial(String p_name, int32_t p_offset, int32_t p_length);
    void write(String p_name, PoolByteArray* p_data);
    void write_async(String p_name, PoolByteArray* p_data);
    void destroy(String p_name);
    bool exists(String p_name);
    Dictionary stat(String p_name);
    uint32_t count();
    Dictionary stat_at(int32_t p_index);

    GodotcordStorageManager();
};

#endif //GODOTCORD_STORAGE_MANAGER_H
