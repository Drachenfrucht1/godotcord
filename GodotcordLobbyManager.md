# GodotcordLobbyManager

A wrapper of the Discord Game SDK Achievement Manager.
### Description

A wrapper of the Discord Game SDK Activity Manager. This class is used to search lobbies and manipulate their metadata.

| | |
----|----
void|[set_lobby_metadata](#set_lobby_metadata)(lobby_id : int, key : string, value : string)
string|[get_lobby_metadata](#get_lobby_metadata)(lobby_id : int, key : string)
void|[search_lobbies](#search_lobbies)(parameters : Variant, limit : int)

### Signals

* search_lobbies_callback(lobbies : Array)

Emitted after a lobby search has been completed.

----
### Enumerations

enum **LobbyDistance**

* **LOCAL**=**0** --- Lobbies in the same region
* **DEFAULT**=**1** --- Lobbies in adjacent regions.
* **Extended**=**2** --- Lobbies in regions far apart, e.g. Europe and the US
* **GLOBAL**=**3** --- Lobbies from all around the world.

----
enum **LobbyComparison**

* **LESS_THAN_OR_EQUAL**=**0** --- 
* **LESS_THAN**=**1** --- 
* **EQUAL**=**2** --- ==
* **GREATER_THAN**=**3** --- 
* **GREATER_THAN_OR_EQUAL**=**4** --- 
* **NOT_EQUAL**=**6** --- !=

----
### Method Descriptions

* <a name="set_lobby_metadata"></a> void set_lobby_metadata(lobby_id : int, key : string, value : string)

Sets the key/value pair as metadata of the lobby `lobby_id`. 
                The local user has be the owner of the lobby. Otherwise nothing will happen.
                Overwrites the value if the key already exists(?).

----
* <a name="get_lobby_metadata"></a> string get_lobby_metadata(lobby_id : int, key : string)

Returns the value associated with the key.

----
* <a name="search_lobbies"></a> void search_lobbies(parameters : Variant, limit : int)

Searches all lobbies for ones that match the provided parameters.
                Returns at most `limit` lobbies via the Signal `search_lobbies_callback`.

----
