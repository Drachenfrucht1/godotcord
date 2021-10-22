#include "godotcord_relationship_manager.h"
#include "core/func_ref.h"
#include "godotcord.h"

GodotcordRelationshipManager *GodotcordRelationshipManager::singleton = NULL;

GodotcordRelationshipManager *GodotcordRelationshipManager::get_singleton() {
	return GodotcordRelationshipManager::singleton;
}

void GodotcordRelationshipManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("filter_relationships", "object", "filter_func"), &GodotcordRelationshipManager::filter_relationships);
	ClassDB::bind_method(D_METHOD("get_relationships"), &GodotcordRelationshipManager::get_relationships);

	ADD_SIGNAL(MethodInfo("relationship_update", PropertyInfo(Variant::OBJECT, "relationship")));
}

Array GodotcordRelationshipManager::filter_relationships(Object *p_object, StringName p_func_name) {
	Array ret;
	ERR_FAIL_NULL_V(p_object, ret);
	FuncRef filter_func;
	filter_func.set_instance(p_object);
	filter_func.set_function(p_func_name);

	ERR_FAIL_COND_V(!filter_func.is_valid(), ret);

	Godotcord::get_singleton()->get_core()->RelationshipManager().Filter([&filter_func](discord::Relationship p_relationship) -> bool {
		Array a;
		Ref<GodotcordRelationship> rel_ship;
		rel_ship.instance();
		rel_ship->type = (GodotcordRelationship::RelationshipType) p_relationship.GetType();
		rel_ship->user_id = p_relationship.GetUser().GetId();

		Ref<GodotcordPresence> presence;
		presence.instance();
		presence->status = (GodotcordPresence::PresenceStatus) p_relationship.GetPresence().GetStatus();
		presence->activity = GodotcordActivity::from_discord_activity(p_relationship.GetPresence().GetActivity());
		rel_ship->presence = presence;

		a.push_back(rel_ship);

		return filter_func.call_funcv(a);
	});

	return get_relationships();
}

Array GodotcordRelationshipManager::get_relationships() {
	Array ret;
	int count;
	Godotcord::get_singleton()->get_core()->RelationshipManager().Count(&count);
	discord::Relationship d_relationship;
	for (int i = 0; i < count; i++) {
		Godotcord::get_singleton()->get_core()->RelationshipManager().GetAt(i, &d_relationship);

		Ref<GodotcordRelationship> rel_ship;
		rel_ship.instance();

		rel_ship->type = (GodotcordRelationship::RelationshipType) d_relationship.GetType();
		rel_ship->user_id = d_relationship.GetUser().GetId();

		Ref<GodotcordPresence> presence;
		presence.instance();
		presence->status = (GodotcordPresence::PresenceStatus) d_relationship.GetPresence().GetStatus();
		presence->activity = GodotcordActivity::from_discord_activity(d_relationship.GetPresence().GetActivity());
		rel_ship->presence = presence;

		ret.push_back(rel_ship);
	}
	return ret;
}

void GodotcordRelationshipManager::init() {
	Godotcord::get_singleton()->get_core()->RelationshipManager().OnRelationshipUpdate.Connect([this](discord::Relationship relation_ship) {
		Ref<GodotcordRelationship> rel_ship;
		rel_ship.instance();
		rel_ship->type = (GodotcordRelationship::RelationshipType) relation_ship.GetType();
		rel_ship->user_id = relation_ship.GetUser().GetId();

		Ref<GodotcordPresence> presence;
		presence.instance();
		presence->status = (GodotcordPresence::PresenceStatus) relation_ship.GetPresence().GetStatus();
		presence->activity = GodotcordActivity::from_discord_activity(relation_ship.GetPresence().GetActivity());
		rel_ship->presence = presence;

		emit_signal("relationship_update", rel_ship);
	});
}

GodotcordRelationshipManager::GodotcordRelationshipManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordRelationshipManager should exist");
	singleton = this;
}

GodotcordRelationshipManager::~GodotcordRelationshipManager() {
}
