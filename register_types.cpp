#include "register_types.h"

#include <gdextension_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include "godotcord.h"
#include "godotcord_activity.h"
#include "godotcord_relationship.h"

#include "godotcord_activity_manager.h"
#include "godotcord_overlay_manager.h"
#include "godotcord_relationship_manager.h"
#include "godotcord_user_manager.h"

#include "godotcord_user.h"

static Godotcord *GC_ptr = NULL;
static GodotcordActivityManager *GC_ACT_ptr = NULL;
static GodotcordOverlayManager *GC_OVRL_ptr = NULL;
static GodotcordRelationshipManager *GC_RELSHIP_ptr = NULL;
static GodotcordUserManager *GC_USR_ptr = NULL;

using namespace godot;


void register_godotcord_types(ModuleInitializationLevel l) {
	if (l != ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_SCENE) return;

	ClassDB::register_class<Godotcord>();
	ClassDB::register_class<GodotcordActivity>();
	ClassDB::register_class<GodotcordRelationship>();
	ClassDB::register_class<GodotcordPresence>();
	ClassDB::register_class<GodotcordUser>();

	ClassDB::register_class<GodotcordActivityManager>();
	ClassDB::register_class<GodotcordOverlayManager>();
	ClassDB::register_class<GodotcordRelationshipManager>();
	ClassDB::register_class<GodotcordUserManager>();

	GC_ptr = memnew(Godotcord);
	Engine::get_singleton()->register_singleton("Godotcord", Godotcord::get_singleton());

	GC_ACT_ptr = memnew(GodotcordActivityManager);
	Engine::get_singleton()->register_singleton("GodotcordActivityManager", GodotcordActivityManager::get_singleton());

	GC_OVRL_ptr = memnew(GodotcordOverlayManager);
	Engine::get_singleton()->register_singleton("GodotcordOverlayManager", GodotcordOverlayManager::get_singleton());

	GC_RELSHIP_ptr = memnew(GodotcordRelationshipManager);
	Engine::get_singleton()->register_singleton("GodotcordRelationshipManager", GodotcordRelationshipManager::get_singleton());

	GC_USR_ptr = memnew(GodotcordUserManager);
	Engine::get_singleton()->register_singleton("GodotcordUserManager", GodotcordUserManager::get_singleton());
}

void unregister_godotcord_types(ModuleInitializationLevel l) {
	if (l != ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_SCENE) return;
	memdelete(GC_ptr);
	memdelete(GC_ACT_ptr);
	memdelete(GC_OVRL_ptr);
	memdelete(GC_RELSHIP_ptr);
	memdelete(GC_USR_ptr);
}

extern "C" {
GDExtensionBool GDE_EXPORT godotcord_init(const GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.set_minimum_library_initialization_level(ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_SCENE);
	init_obj.register_initializer(register_godotcord_types);
	init_obj.register_terminator(unregister_godotcord_types);

	return init_obj.init();
}
}
