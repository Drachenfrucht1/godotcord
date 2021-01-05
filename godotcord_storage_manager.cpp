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

}

unsigned char * GodotcordStorageManager::read(String name) {

}

void GodotcordStorageManager::read_async(String name) {

}

void GodotcordStorageManager::read_async_partial(String name, int32_t offset, int32_t length) {

}

void GodotcordStorageManager::write(String name, unsigned char* data) {

}

void GodotcordStorageManager::write_async(String name, unsigned char* data) {

}

void GodotcordStorageManager::destroy(String name) {

}

void GodotcordStorageManager::exists(String name) {

}

void GodotcordStorageManager::stat(String name) {

}

uint32_t GodotcordStorageManager::count() {

}

void GodotcordStorageManager::stat_at(int32_t index) {

}

void GodotcordStorageManager::init() {

}

GodotcordStorageManager::GodotcordStorageManager() {
    ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordStorageManager can be created.");

    singleton = this;
}