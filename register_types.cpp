#include "register_types.h"

#include "core/class_db.h"
#include "core/engine.h"
#include "scene/main/viewport.h"
#include "godotcord.h"
#include "godotcord_activity.h"
#include "godotcord_network_peer.h"

static Godotcord *GC_ptr = NULL;

void register_godotcord_types() {
	ClassDB::register_class<Godotcord>();
	ClassDB::register_class<GodotcordActivity>();
	ClassDB::register_class<NetworkedMultiplayerGodotcord>();


	GC_ptr = memnew(Godotcord);
	Engine::get_singleton()->add_singleton(Engine::Singleton("Godotcord", Godotcord::get_singleton()));
}

void unregister_godotcord_types() {
	memdelete(GC_ptr);
}
