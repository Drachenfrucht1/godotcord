#include "register_types.h"

#include "core/class_db.h"
#include "godotcord.h"
#include "godotcord_activity.h"
#include "godotcord_network_peer.h"

void register_godotcord_types() {
	ClassDB::register_class<Godotcord>();
	ClassDB::register_class<GodotcordActivity>();
	ClassDB::register_class<NetworkedMultiplayerDiscord>();
}

void unregister_godotcord_types() {

}
