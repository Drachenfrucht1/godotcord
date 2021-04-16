#ifndef GODOTCORD_SEARCH_PARAMETER_H
#define GODOTCORD_SEARCH_PARAMETER_H

#include "core/reference.h"
#include "godotcord_lobby_manager.h"

#include "godotcord_utils.h"

class GodotcordSearchParameter : public Reference {
    GDCLASS(GodotcordSearchParameter, Reference)

protected:
    static void _bind_methods() {
        ADD_GODOTCORD_PROPERTY(GodotcordSearchParameter, property, Variant::STRING);
        ADD_GODOTCORD_PROPERTY(GodotcordSearchParameter, comparison, Variant::INT);
        ADD_GODOTCORD_PROPERTY(GodotcordSearchParameter, cast, Variant::INT);
        ADD_GODOTCORD_PROPERTY(GodotcordSearchParameter, value, Variant::STRING);
    }

public:
    String property;
    GodotcordLobbyManager::LobbyComparison comparison;
    GodotcordLobbyManager::LobbyCast cast;
    String value;

    GET_SET_COMBO(property, String);
    GET_SET_COMBO(comparison, GodotcordLobbyManager::LobbyComparison);
    GET_SET_COMBO(cast, GodotcordLobbyManager::LobbyCast);
    GET_SET_COMBO(value, String);
};

#endif