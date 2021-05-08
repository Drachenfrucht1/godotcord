#include "register_types.h"

#include "core/class_db.h"
#include "core/engine.h"
#include "scene/main/viewport.h"
#include "godotcord.h"
#include "godotcord_activity.h"
#include "godotcord_relationship.h"
#include "godotcord_network_peer.h"

#include "godotcord_achievement_manager.h"
#include "godotcord_activity_manager.h"
#include "godotcord_image_manager.h"
#include "godotcord_lobby_manager.h"
#include "godotcord_overlay_manager.h"
#include "godotcord_relationship_manager.h"
#include "godotcord_storage_manager.h"
#include "godotcord_store_manager.h"
#include "godotcord_user_manager.h"
#include "godotcord_voice_manager.h"

#include "godotcord_lobby.h"
#include "godotcord_search_parameter.h"
#include "godotcord_achievement.h"
#include "godotcord_user.h"
#include "godotcord_store_data.h"
static Godotcord *GC_ptr = NULL;
static GodotcordAchievementManager *GC_ACH_ptr = NULL;
static GodotcordActivityManager *GC_ACT_ptr = NULL;
static GodotcordImageManager *GC_IMG_ptr = NULL;
static GodotcordLobbyManager *GC_LOBBY_ptr = NULL;
static GodotcordOverlayManager *GC_OVRL_ptr = NULL;
static GodotcordRelationshipManager *GC_RELSHIP_ptr = NULL;
static GodotcordStorageManager *GC_STORGE_ptr = NULL;
static GodotcordStoreManager *GC_STORE_ptr = NULL;
static GodotcordUserManager *GC_USR_ptr = NULL;
static GodotcordVoiceManager *GC_VC_ptr = NULL;


void register_godotcord_types() {
	ClassDB::register_class<Godotcord>();
	ClassDB::register_class<GodotcordActivity>();
	ClassDB::register_class<GodotcordRelationship>();
	ClassDB::register_class<GodotcordPresence>();
	ClassDB::register_class<NetworkedMultiplayerGodotcord>();
	ClassDB::register_class<GodotcordLobby>();
	ClassDB::register_class<GodotcordSearchParameter>();
	ClassDB::register_class<GodotcordAchievement>();
	ClassDB::register_class<GodotcordUser>();
	ClassDB::register_class<GodotcordFileStat>();
	ClassDB::register_class<GodotcordPeer>();
	ClassDB::register_class<GodotcordEntitlement>();
	ClassDB::register_class<GodotcordSKU>();
	ClassDB::register_class<GodotcordSKUPrice>();
	ClassDB::register_class<GodotcordInputmode>();

	ClassDB::register_class<GodotcordAchievementManager>();
	ClassDB::register_class<GodotcordActivityManager>();
	ClassDB::register_class<GodotcordImageManager>();
	ClassDB::register_class<GodotcordLobbyManager>();
	ClassDB::register_class<GodotcordRelationshipManager>();
	ClassDB::register_class<GodotcordStorageManager>();
	ClassDB::register_class<GodotcordStoreManager>();
	ClassDB::register_class<GodotcordUserManager>();
	ClassDB::register_class<GodotcordVoiceManager>();

	GC_ptr = memnew(Godotcord);
	Engine::get_singleton()->add_singleton(Engine::Singleton("Godotcord", Godotcord::get_singleton()));

	GC_ACH_ptr = memnew(GodotcordAchievementManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordAchievementManager", GodotcordAchievementManager::get_singleton()));

	GC_ACT_ptr = memnew(GodotcordActivityManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordActivityManager", GodotcordActivityManager::get_singleton()));

	GC_IMG_ptr = memnew(GodotcordImageManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordImageManager", GodotcordImageManager::get_singleton()));

	GC_LOBBY_ptr = memnew(GodotcordLobbyManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordLobbyManager", GodotcordLobbyManager::get_singleton()));

	GC_OVRL_ptr = memnew(GodotcordOverlayManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordOverlayManager", GodotcordOverlayManager::get_singleton()));

	GC_RELSHIP_ptr = memnew(GodotcordRelationshipManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordRelationshipManager", GodotcordRelationshipManager::get_singleton()));

	GC_STORGE_ptr = memnew(GodotcordStorageManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordStorageManager", GodotcordStorageManager::get_singleton()));

	GC_STORE_ptr = memnew(GodotcordStoreManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordStoreManager", GodotcordStoreManager::get_singleton()));

	GC_USR_ptr = memnew(GodotcordUserManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordUserManager", GodotcordUserManager::get_singleton()));

	GC_VC_ptr = memnew(GodotcordVoiceManager);
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotcordVoiceManager", GodotcordVoiceManager::get_singleton()));
}

void unregister_godotcord_types() {
	memdelete(GC_ptr);
	memdelete(GC_ACH_ptr);
	memdelete(GC_ACT_ptr);
	memdelete(GC_IMG_ptr);
	memdelete(GC_LOBBY_ptr);
	memdelete(GC_OVRL_ptr);
	memdelete(GC_RELSHIP_ptr);
    memdelete(GC_STORGE_ptr);
	memdelete(GC_STORE_ptr);
	memdelete(GC_USR_ptr);
	memdelete(GC_VC_ptr);
}
