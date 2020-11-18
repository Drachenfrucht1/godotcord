#include "godotcord_lobby_manager.h"
#include "godotcord.h"
#include "core/func_ref.h"

GodotcordLobbyManager *GodotcordLobbyManager::singleton = NULL;

GodotcordLobbyManager *GodotcordLobbyManager::get_singleton() {
	return GodotcordLobbyManager::singleton;
}

void GodotcordLobbyManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_lobby_metadata", "lobby_id", "key", "value"), &GodotcordLobbyManager::set_lobby_metadata);
	ClassDB::bind_method(D_METHOD("get_lobby_metadata", "lobby_id", "key"), &GodotcordLobbyManager::get_lobby_metadata);
	ClassDB::bind_method(D_METHOD("search_lobbies", "parameters, limit", "object", "function_name"), &GodotcordLobbyManager::search_lobbies);

	BIND_ENUM_CONSTANT(LOCAL);
	BIND_ENUM_CONSTANT(DEFAULT);
	BIND_ENUM_CONSTANT(EXTENDED);
	BIND_ENUM_CONSTANT(GLOBAL);

	BIND_ENUM_CONSTANT(LESS_THAN_OR_EQUAL);
	BIND_ENUM_CONSTANT(LESS_THAN);
	BIND_ENUM_CONSTANT(EQUAL);
	BIND_ENUM_CONSTANT(GREATER_THAN);
	BIND_ENUM_CONSTANT(GREATER_THAN_OR_EQUAL);
	BIND_ENUM_CONSTANT(NOT_EQUAL);

	BIND_ENUM_CONSTANT(STRING);
	BIND_ENUM_CONSTANT(INT);
}

void GodotcordLobbyManager::set_lobby_metadata(int64_t p_lobby_id, String p_key, String p_value) {
	discord::LobbyTransaction txn{};
	Godotcord::get_singleton()->get_core()->LobbyManager().GetLobbyUpdateTransaction(p_lobby_id, &txn);

	txn.SetMetadata(p_key.utf8(), p_value.utf8());

	Godotcord::get_singleton()->get_core()->LobbyManager().UpdateLobby(p_lobby_id, txn, [](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Something went wrong while setting the lobby metadata");
	});
}

String GodotcordLobbyManager::get_lobby_metadata(int64_t p_lobby_id, String p_key) {
	char value[4096];

	discord::Result result = Godotcord::get_singleton()->get_core()->LobbyManager().GetLobbyMetadataValue(p_lobby_id, p_key.utf8(), value);

	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, "", "Something went wrong while getting the lobby metadata");

	return String(value);
}

void GodotcordLobbyManager::search_lobbies(Variant p_params, int p_limit, Object *p_object, StringName p_funcname) {
	ERR_FAIL_COND_MSG(!p_params.is_array(), "The search_parameters has to be an array");

	ERR_FAIL_NULL(p_object);
	FuncRef callback;
	callback.set_instance(p_object);
	callback.set_function(p_funcname);

	Array params = p_params;
	discord::LobbySearchQuery query;
	discord::Result result = Godotcord::get_singleton()->get_core()->LobbyManager().GetSearchQuery(&query);
	ERR_FAIL_COND(result != discord::Result::Ok);

	for (int i = 0; i < params.size(); i++) {
		Variant element = params[i];
		ERR_CONTINUE(element.get_type() != Variant::DICTIONARY);
		Dictionary d = element;

		String property = d.get("property", "");
		int comparison = d.get("comparison", -1);
		int cast = d.get("cast", -1);
		Variant value = d.get("value", "");

		query.Limit(p_limit);

		if (property == "distance") {
			ERR_CONTINUE(value.get_type() != Variant::INT);
			discord::LobbySearchDistance distance;
			int i_value = value;
			switch (i_value) {
				case LOCAL:
					distance = discord::LobbySearchDistance::Local;
					break;
				case DEFAULT:
					distance = discord::LobbySearchDistance::Default;
					break;
				case EXTENDED:
					distance = discord::LobbySearchDistance::Extended;
					break;
				case GLOBAL:
					distance = discord::LobbySearchDistance::Global;
					break;
				default:
					continue;
			}

			query.Distance(distance);
		} else {
			ERR_CONTINUE(property == "" || comparison == -1 || cast == -1 || value.get_type() != Variant::STRING);
			String s_value = value;

			discord::LobbySearchCast d_cast;
			discord::LobbySearchComparison d_comp;

			switch (cast) {
				case STRING:
					d_cast = discord::LobbySearchCast::String;
					break;
				case INT:
					d_cast = discord::LobbySearchCast::Number;
					break;
				default:
					continue;
			}

			switch (comparison) {
				case LESS_THAN_OR_EQUAL:
					d_comp = discord::LobbySearchComparison::LessThanOrEqual;
					break;
				case LESS_THAN:
					d_comp = discord::LobbySearchComparison::LessThan;
					break;
				case EQUAL:
					d_comp = discord::LobbySearchComparison::Equal;
					break;
				case GREATER_THAN:
					d_comp = discord::LobbySearchComparison::GreaterThan;
					break;
				case GREATER_THAN_OR_EQUAL:
					d_comp = discord::LobbySearchComparison::GreaterThanOrEqual;
					break;
				case NOT_EQUAL:
					d_comp = discord::LobbySearchComparison::NotEqual;
					break;
				default:
					continue;
			}

			query.Filter(property.utf8(), d_comp, d_cast, s_value.utf8());
		}
	}

	Godotcord::get_singleton()->get_core()->LobbyManager().Search(query, [this, &callback](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Something went wrong while filtering the lobbies");

		Vector<Variant> vec;
		int64_t lobby_id;
		discord::Lobby lobby;
		int32_t lobby_count;
		Godotcord::get_singleton()->get_core()->LobbyManager().LobbyCount(&lobby_count);

		for (int32_t i = 0; i < lobby_count; i++) {
			Godotcord::get_singleton()->get_core()->LobbyManager().GetLobbyId(i, &lobby_id);
			Godotcord::get_singleton()->get_core()->LobbyManager().GetLobby(lobby_id, &lobby);

			GodotcordLobby gd_lobby;
			gd_lobby.id = lobby.GetId();
			gd_lobby.secret = lobby.GetSecret();
			gd_lobby.max_users = lobby.GetCapacity();
			gd_lobby.owner_id = lobby.GetOwnerId();
			Godotcord::get_singleton()->get_core()->LobbyManager().MemberCount(lobby_id, &(gd_lobby.current_users));

			vec.push_back(GodotcordLobby::get_dictionary(&gd_lobby));
		}

		Array a;
		a.push_back(vec);
		callback.call_funcv(a);
	});
}

GodotcordLobbyManager::GodotcordLobbyManager() {
	ERR_FAIL_COND_MSG(singleton != NULL, "Only one instance of GodotcordLobbyManager should exist")
	singleton = this;
}

GodotcordLobbyManager::~GodotcordLobbyManager() {
}
