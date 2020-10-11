#include "register_types.h"

#include "core/class_db.h"
#include "core/engine.h"
#include "scene/main/viewport.h"
#include "godotcord.h"
#include "godotcord_activity.h"
#include "godotcord_relationship.h"
#include "godotcord_network_peer.h"

#include "godotcord_activity_manager.h"
#include "godotcord_image_manager.h"
#include "godotcord_lobby_manager.h"
#include "godotcord_relationship_manager.h"

static Godotcord *GC_ptr = NULL;

void register_godotcord_types() {
	ClassDB::register_class<Godotcord>();
	ClassDB::register_class<GodotcordActivity>();
	ClassDB::register_class<GodotcordRelationship>();
	ClassDB::register_class<NetworkedMultiplayerGodotcord>();

	ClassDB::register_class<GodotcordActivityManager>();
	ClassDB::register_class<GodotcordImageManager>();
	ClassDB::register_class<GodotcordLobbyManager>();
	ClassDB::register_class<GodotcordRelationshipManager>();

	GC_ptr = memnew(Godotcord);
	Engine::get_singleton()->add_singleton(Engine::Singleton("Godotcord", Godotcord::get_singleton()));
}

void unregister_godotcord_types() {
	memdelete(GC_ptr);
}
