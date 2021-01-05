#include "godotcord_storage_manager.h"
#include "godotcord.h"

#include "core/func_ref.h"

GodotcordStorageManager *GodotcordStorageManager::singleton = NULL;

GodotcordStorageManager* GodotcordStorageManager::get_singleton() {
    return GodotcordStorageManager::singleton;
}

void GodotcordStorageManager::_bind_methods() {

}

String GodotcordStorageManager::get_path() {
    char path[4096];
    discord::Result result = Godotcord::get_singleton()->get_core()->StorageManager().GetPath(path);
    ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, path,"Something went wrong while getting path.")
    return path;
}

unsigned char* GodotcordStorageManager::read(String p_name) {
    unsigned char* data;
    uint32_t* read;
    discord::Result result = Godotcord::get_singleton()->get_core()->StorageManager().Read(p_name.utf8(), data, (uint32_t)data, read);
    ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, data, "Something went wrong while reading the save file.")
}

void GodotcordStorageManager::read_async(String p_name, Object* p_object, StringName p_funcname) {
    
}

void GodotcordStorageManager::read_async_partial(String p_name, int32_t p_offset, int32_t p_length, Object* p_object, StringName p_funcname) {

}

void GodotcordStorageManager::write(String p_name, uint8_t* p_data) {
    discord::Result result = Godotcord::get_singleton()->get_core()->StorageManager().Write(p_name.utf8(), p_data, (uint32_t)p_data);
    ERR_FAIL_COND_MSG(result != discord::Result::Ok,"Something went wrong while writing to save file.")
}

void GodotcordStorageManager::write_async(String p_name, uint8_t* p_data) {

    Godotcord::get_singleton()->get_core()->StorageManager().WriteAsync(p_name.utf8(), p_data, (uint32_t)p_data, [](discord::Result result) {
        ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Something went wrong while writing to save file asynchronously.")
    });
}

void GodotcordStorageManager::destroy(String p_name) {

}

void GodotcordStorageManager::exists(String p_name) {

}

void GodotcordStorageManager::stat(String p_name) {

}

uint32_t GodotcordStorageManager::count() {

}

void GodotcordStorageManager::stat_at(int32_t p_index) {

}

void GodotcordStorageManager::init() {

}

GodotcordStorageManager::GodotcordStorageManager() {
    ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordStorageManager can be created.");

    singleton = this;
}