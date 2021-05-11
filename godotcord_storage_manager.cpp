#include "godotcord_storage_manager.h"
#include "godotcord.h"

#include "core/func_ref.h"

GodotcordStorageManager *GodotcordStorageManager::singleton = NULL;

GodotcordStorageManager* GodotcordStorageManager::get_singleton() {
    return GodotcordStorageManager::singleton;
}

void GodotcordStorageManager::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_path"), &GodotcordStorageManager::get_path);
    ClassDB::bind_method(D_METHOD("read", "name"), &GodotcordStorageManager::read);
    ClassDB::bind_method(D_METHOD("read_async", "name"), &GodotcordStorageManager::read_async);
    ClassDB::bind_method(D_METHOD("read_async_partial", "name", "offset", "length"), &GodotcordStorageManager::read_async_partial);
    ClassDB::bind_method(D_METHOD("write", "name", "data"), &GodotcordStorageManager::write);
    ClassDB::bind_method(D_METHOD("write_async", "name", "data"), &GodotcordStorageManager::write_async);
    ClassDB::bind_method(D_METHOD("destroy", "name"), &GodotcordStorageManager::destroy);
    ClassDB::bind_method(D_METHOD("exists", "name"), &GodotcordStorageManager::exists);
    ClassDB::bind_method(D_METHOD("stat", "name"), &GodotcordStorageManager::stat);
    ClassDB::bind_method(D_METHOD("count"), &GodotcordStorageManager::count);
    ClassDB::bind_method(D_METHOD("stat_at", "index"), &GodotcordStorageManager::stat_at);

    ADD_SIGNAL(MethodInfo("async_data_read", PropertyInfo(Variant::POOL_BYTE_ARRAY, "data")));
    ADD_SIGNAL(MethodInfo("async_data_written"));
}

String GodotcordStorageManager::get_path() {
    char path[4096];
    discord::Result result = Godotcord::get_singleton()->get_core()->StorageManager().GetPath(path);
    ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, path,"Something went wrong while getting path.")
    return path;
}

PoolByteArray GodotcordStorageManager::read(String p_name) {
    uint64_t data_length = stat(p_name)->size;
    uint8_t* data = (uint8_t*)memalloc(data_length);
    uint32_t read = 0;
    discord::Result result = Godotcord::get_singleton()->get_core()->StorageManager().Read(p_name.utf8(), data, data_length, &read);
    PoolByteArray poolByteArray;
    for (unsigned int i = 0; i < data_length; i++) {
        poolByteArray.append(data[i]);
    }
    memfree(data);
    ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, poolByteArray, "Something went wrong while reading the save file.")
    return poolByteArray;
}

void GodotcordStorageManager::read_async(String p_name) {
    Godotcord::get_singleton()->get_core()->StorageManager().ReadAsync(p_name.utf8(),[this](discord::Result result, uint8_t* data, uint32_t data_length) {
        ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Something went wrong while reading the save file asynchronously.")
        PoolByteArray poolByteArray;
        for (unsigned int i = 0; i < data_length; i++) {
            poolByteArray.append(data[i]);
        }
        emit_signal("async_data_read", poolByteArray);
    });
}

void GodotcordStorageManager::read_async_partial(String p_name, int32_t p_offset, int32_t p_length) {
    Godotcord::get_singleton()->get_core()->StorageManager().ReadAsyncPartial(p_name.utf8(), p_offset, p_length,[this](discord::Result result, uint8_t* data, uint32_t data_length) {
        ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Something went wrong while traversing the save file asynchronously.")
        PoolByteArray poolByteArray;
        for (unsigned int i = 0; i < data_length; i++) {
            poolByteArray.append(data[i]);
        }
        emit_signal("async_data_read", poolByteArray);
    });
}

void GodotcordStorageManager::write(String p_name, PoolByteArray p_data) {
    discord::Result result = Godotcord::get_singleton()->get_core()->StorageManager().Write(p_name.utf8(),(uint8_t *) p_data.join("").utf8().get_data(), p_data.size());
    ERR_FAIL_COND_MSG(result != discord::Result::Ok,"Something went wrong while writing to save file.")
}

void GodotcordStorageManager::write_async(String p_name, PoolByteArray p_data) {

    Godotcord::get_singleton()->get_core()->StorageManager().WriteAsync(p_name.utf8(), (uint8_t*)p_data.join("").utf8().get_data(), p_data.size(), [this](discord::Result result) {
        ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Something went wrong while writing to save file asynchronously.")
        emit_signal("async_data_written");
    });
}

void GodotcordStorageManager::destroy(String p_name) {
    Godotcord::get_singleton()->get_core()->StorageManager().Delete(p_name.utf8());
}

bool GodotcordStorageManager::exists(String p_name) {
    bool p_exists;
    Godotcord::get_singleton()->get_core()->StorageManager().Exists(p_name.utf8(), &p_exists);
    return p_exists;
}

Ref<GodotcordFileStat> GodotcordStorageManager::stat(String p_name) {
    discord::FileStat discordFileStat{};
	Ref<GodotcordFileStat> godotcordFileStat;
	godotcordFileStat.instance();
    Godotcord::get_singleton()->get_core()->StorageManager().Stat(p_name.utf8(), &discordFileStat);
	godotcordFileStat->file_name = discordFileStat.GetFilename();
	godotcordFileStat->size = discordFileStat.GetSize();
	godotcordFileStat->last_modified = discordFileStat.GetLastModified();
	return godotcordFileStat;
}

uint32_t GodotcordStorageManager::count() {
    int32_t count;
    Godotcord::get_singleton()->get_core()->StorageManager().Count(&count);
    return count;
}

Ref<GodotcordFileStat> GodotcordStorageManager::stat_at(int32_t p_index) {
    discord::FileStat discordFileStat{};
	Ref<GodotcordFileStat> godotcordFileStat;
	godotcordFileStat.instance();
    Godotcord::get_singleton()->get_core()->StorageManager().StatAt(p_index, &discordFileStat);
    godotcordFileStat->file_name = discordFileStat.GetFilename();
    godotcordFileStat->size = discordFileStat.GetSize();
	godotcordFileStat->last_modified = discordFileStat.GetLastModified();
	return godotcordFileStat;
}

GodotcordStorageManager::GodotcordStorageManager() {
    ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordStorageManager can be created.");

    singleton = this;
}

GodotcordStorageManager::~GodotcordStorageManager() {
}
