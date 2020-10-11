#include "godotcord_image_manager.h"
#include "godotcord.h"
#include "core/func_ref.h"

GodotcordImageManager *GodotcordImageManager::singleton = NULL;

GodotcordImageManager *GodotcordImageManager::get_singleton() {
	return GodotcordImageManager::singleton;
}

void GodotcordImageManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_profile_picture", "user_id", "size", "object", "function_name"), &GodotcordImageManager::get_profile_picture);
}

void GodotcordImageManager::get_profile_picture(int64_t p_user_id, int p_size, Object* p_object, StringName p_funcname) {
	ERR_FAIL_NULL(p_object);
	FuncRef callback;
	callback.set_instance(p_object);
	callback.set_function(p_funcname);

	discord::ImageHandle handle;
	handle.SetId(p_user_id);
	handle.SetSize(p_size);
	handle.SetType(discord::ImageType::User);
	Godotcord::get_singleton()->get_core()->ImageManager()
			.Fetch(
					handle, false, [this, p_user_id, &callback](discord::Result result, discord::ImageHandle returned_handle) {
						ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Something went wrong while requesting the profile picture");

						discord::ImageDimensions dim;
						Godotcord::get_singleton()->get_core()->ImageManager().GetDimensions(returned_handle, &dim);

						uint32_t data_size = dim.GetWidth() * dim.GetHeight() * 4;
						PoolByteArray data;
						data.resize(data_size);
						PoolByteArray::Write write = data.write();
						Godotcord::get_singleton()->get_core()->ImageManager().GetData(returned_handle, &write[0], data_size);

						write.release();

						Array a;
						a.push_back(p_user_id);
						a.push_back(data);
						callback.call_funcv(a);
					});
}

GodotcordImageManager::GodotcordImageManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordImageManager should exist")
	singleton = this;
}

GodotcordImageManager::~GodotcordImageManager() {
}
