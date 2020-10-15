#include "register_types.h"

#include "core/class_db.h"
#include "core/engine.h"
#include "scene/main/viewport.h"
#include "godotcord.h"
#include "godotcord_activity.h"
#include "godotcord_relationship.h"
#include "godotcord_network_peer.h"

#include "godotcord_activity_manager.h"
#include "godotcord_applications_manager.h"
#include "godotcord_image_manager.h"
#include "godotcord_lobby_manager.h"
#include "godotcord_relationship_manager.h"

static Godotcord *GC_ptr = NULL;
static GodotcordActivityManager *GC_ACT_ptr = NULL;
static GodotcordApplicationsManager *GC_APP_ptr = NULL;
static GodotcordImageManager *GC_IMG_ptr = NULL;
static GodotcordLobbyManager *GC_LOBBY_ptr = NULL;
static GodotcordRelationshipManager *GC_RELSHIP_ptr = NULL;

void register_godotcord_types() {
	ClassDB::register_class<Godotcord>();
	ClassDB::register_class<GodotcordActivity>();
	ClassDB::register_class<GodotcordRelationship>();
	ClassDB::register_class<NetworkedMultiplayerGodotcord>();

	ClassDB::register_class<GodotcordActivityManager>();
	ClassDB::register_class<GodotcordApplicationsManager>();
	ClassDB::register_class<GodotcordImageManager>();
	ClassDB::register_class<GodotcordLobbyManager>();
	ClassDB::register_class<GodotcordRelationshipManager>();

	GC_ptr = memnew(Godotcord);
	Engine::get_singleton()->add_singleton(Engine::Singleton("Godotcord", Godotcord::get_singleton()));

	GC_ACT_ptr = memnew(GodotcordActivityManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordActivityManager", GodotcordActivityManager::get_singleton()));

	GC_APP_ptr = memnew(GodotcordApplicationsManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordApplicationsManager", GodotcordApplicationsManager::get_singleton()));

	GC_IMG_ptr = memnew(GodotcordImageManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordImageManager", GodotcordImageManager::get_singleton()));

	GC_LOBBY_ptr = memnew(GodotcordLobbyManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordLobbyManager", GodotcordLobbyManager::get_singleton()));

	GC_RELSHIP_ptr = memnew(GodotcordRelationshipManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordRelationshipManager", GodotcordRelationshipManager::get_singleton()));
}

void unregister_godotcord_types() {
	memdelete(GC_ptr);
	memdelete(GC_ACT_ptr);
	memdelete(GC_APP_ptr);
	memdelete(GC_IMG_ptr);
	memdelete(GC_LOBBY_ptr);
	memdelete(GC_RELSHIP_ptr);
}
