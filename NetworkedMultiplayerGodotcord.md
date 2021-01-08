# NetworkedMultiplayerGodotcord

## GDScript methods/properties

`create_lobby(int size, bool public = false)`

- create a discord lobby and joins it

`join_lobby(int id, String secret)`

- join the given lobby with the given secret

`join_lobby_secret(String activitySecret)`

- joins the lobby with the given activity secret

`int get_lobby_id()`

- returns the lobby id of the lobby the player is currently in

`String get_lobby_secret()`

- returns the lobby secret of the lobby the player is currently in

`String get_lobby_activity_secret()`

- returns the activity secret of the lobby the player is currently in
- used for chat invites and ask to join
  
`int get_current_members()`

- returns the numbers of members currently in the lobby

`int get_max_members()`

- returns the maximum amount of players of the lobby

`int get_user_id_by_peer(int peer_id)`

- returns the peer id for the given discord user id

`int get_peer_id_user(int user_id)`

- returns the discord user id for the given peer id

`Signal created_server()`

- called when a lobby is created after `network_peer_connected` has been called for **every player (including the local one)**

The server_connected signal is, too, fired after `network_peer_connected` has been called for **every player (including the local one)**

`Array get_connected_peers()`

- returns an array of currently connected peers (The current members of the lobby). Each value in the Array is a Dictionary representation of the GodotcordPeer struct:
- Each dictionary follows the following layout:

```{
"discord_id": int (The peer's Discord user ID),
"discord_peer_id": int,
"target_id: int (Godot's peer ID),
"confirmed": bool
}```

## Usage

First you have to create a lobby. This is done by creating a new NetworkedMultiplayerGodotcord and calling `create_server(max_players, public)`. You set a NetworkedMultiplayerGodotcord as the network peer of your root node the same way your would with an enet peer.

```GDScript
var peer = NetworkedMultiplayerGodotcord.new()
peer.create_server(10, true);
get_tree().network_peer = peer;
```

Other player can connect either via the ActivitySecret that can be transmitted via the Game Activity, or using the lobby id and lobby secret

```GDScript
var peer = NetworkedMultiplayerGodotcord.new()
peer.join_lobby_secret(lobby_id, lobby_secret);
get_tree().network_peer = peer;

#Alternative

var peer = NetworkedMultiplayerGodotcord.new()
peer.join_lobby(activity_secret);
get_tree().network_peer = peer;
```

You can now use the godot networking features (rpc, rset, master, pupper, ...) as usual.

I had to assign each user a second id (let's call is peer id) **that is not equal to their Discord user id**. The id that is used for network comminucation (e.g. `get_tree().get_rpc_sender_id()`, id for `rpc_id`, ...) is the peer id. You can however use the `get_user_id_by_peer` function to convert to a discord id for use with other Godotcord functions. Conversion the other way around is also possible using `get_peer_id_by_user`.
