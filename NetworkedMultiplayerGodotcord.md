# NetworkedMultiplayerGodotcord

A multiplayer peer that uses the Discord Network
### Description

A multiplayer peer that uses the Discord Network.
        There are multiple id's connected with multiplayer. The first on is the peer id.
        It is used to identify a user in a lobby. It can however not be used to retrieve other data of a user (e.g. profile picture).
        The peer id will be set as the sender if of rcp calls.
        The other one is the user id. It can be used to retrieve additional information about a user.
        You can convert from one to the other using `get_user_id_by_peer` and `get_peer_id_by_user`
| | |
----|----
void|[create_lobby](#create_lobby)(max_users : int, public : boolean = false)
void|[join_lobby](#join_lobby)(lobby_id : int, secret : string)
void|[join_lobby_activity](#join_lobby_activity)(activity_secret : string)
void|[close_connection](#close_connection)()
void|[disconnect_peer](#disconnect_peer)(id : int)
int|[get_lobby_id](#get_lobby_id)()
string|[get_lobby_secret](#get_lobby_secret)()
string|[get_lobby_activity_secret](#get_lobby_activity_secret)()
int|[get_current_members](#get_current_members)()
int|[get_max_members](#get_max_members)()
void|[set_public](#set_public)(public : boolean)
void|[set_size](#set_size)(size : int)
void|[set_metadata](#set_metadata)(key : string, value : string)
string|[get_metadata](#get_metadata)(key : string)
Array|[get_connected_peers](#get_connected_peers)()
void|[get_user_id_by_peer](#get_user_id_by_peer)(peer_id : int)
void|[get_peer_id_by_user](#get_peer_id_by_user)(user_id : int)

### Signals

* created_lobby()

Emitted when a new lobby has been creates successfully.

----
### Method Descriptions

* <a name="create_lobby"></a> void create_lobby(max_users : int, public : boolean = false)

Creates a new lobby with `max_users` slots.
                The creator will automatically set as the owner and joins the lobby himself.

                ...public

----
* <a name="join_lobby"></a> void join_lobby(lobby_id : int, secret : string)

Joins the lobby with the id `lobby_id` using the id and secret.

----
* <a name="join_lobby_activity"></a> void join_lobby_activity(activity_secret : string)

Joins the lobby encoded in `activity_secret`

----
* <a name="close_connection"></a> void close_connection()

Disconnect from the current lobby.
                Should only be called when the user is currently in a lobby.

----
* <a name="disconnect_peer"></a> void disconnect_peer(id : int)

Removes the user with the id `id` from the lobby.
                Will only be executed when the local user is the owner of the lobby.

----
* <a name="get_lobby_id"></a> int get_lobby_id()

Returns the lobby id of the current lobby.
                Prints an error if the instance is not connected to a lobby.

----
* <a name="get_lobby_secret"></a> string get_lobby_secret()

Returns the lobby secret of the current lobby.
                Prints an error if the instance is not connected to a lobby.

----
* <a name="get_lobby_activity_secret"></a> string get_lobby_activity_secret()

Returns the activity secret of the current lobby.
                Prints an error if the instance is not connected to a lobby.

----
* <a name="get_current_members"></a> int get_current_members()

Returns the number of currently connected users.
                Prints an error if the instance is not connected to a lobby.

----
* <a name="get_max_members"></a> int get_max_members()

Returns the capacity of the lobby.
                Prints an error if the instance is not connected to a lobby.

----
* <a name="set_public"></a> void set_public(public : boolean)



----
* <a name="set_size"></a> void set_size(size : int)



----
* <a name="set_metadata"></a> void set_metadata(key : string, value : string)

Can only be run as the lobby owner.
                Sets the key/value pair as metadata of the current lobby . 
                Overwrites the value if the key already exists(?).

----
* <a name="get_metadata"></a> string get_metadata(key : string)

Returns the value associated with the key.

----
* <a name="get_connected_peers"></a> Array get_connected_peers()

Returns an array with all connected users

----
* <a name="get_user_id_by_peer"></a> void get_user_id_by_peer(peer_id : int)

Returns the user id associated with `peer_id`.

----
* <a name="get_peer_id_by_user"></a> void get_peer_id_by_user(user_id : int)

Returns the peer id associated with `user_id`.

----
