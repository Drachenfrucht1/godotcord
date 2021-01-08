# GodotcordActivityManager

The GodotcordActivityManager class is provided as a singleton named `GodotcordActivityManager`. I recommend to use this instance and not create a new one.

## GDScript methods/properties

`set_activity(GodotcordActivity activity)`

- sets the rich presence of the current discord user

`clear_activity()`

- clears the users activity

`register_command(String command)`

- Used to register a command that will allow Discord to launch your game when needed (for example when someone wants to join a person's game)
- The command can either be a protocol (`my-godot-game://`) or a path to your game's executable.
- The command also supports launch parameters: `path/to/my/game/godotgame.exe --fullscreen --fixed-fps 60`
- More info on the [Game SDK docs](https://discord.com/developers/docs/game-sdk/activities#registercommand)

`register_steam(int steam_id)`

- used to register game that has been distributed using Steam. Check [discord](https://discord.com/developers/docs/game-sdk/activities#registersteam)'s docs for more info.

`send_request_reply(int user_id,egisters a command by which Discord can launch your game. RequestReply request_reply)`

- used to answer a join request
- possible values for `request_reply` are `YES`, `NO` and `IGNORE`

`send_invite(int user_id, ActionType action_type, String message)`

- invites someone to your lobby
- possible values for `action_type` are `JOIN` and `SPECTATE`

`accept_invite(int user_id)`

- accepts a game invite by another user

`Signal activity_join(String secret)`

- called when a user joins a chat party invite or a personal invite is accepted
- secret is the joinMatchSecret of the other person's activity

`Signal activity_spectate(String secret)`

- called when a personal spectate invite is accepted
- secret is the spectateMatchSecret of the other person's activity

`Signal activity_invite(ActionType action_type, String user_name, int user_id, Dictionary activity)`

- emitted when the local user receives an invite from someone

`Signal activity_join_request(String name, int id)`

- called when a user wants to join the local user's lobby.
- name and id are both from the asking user

## Usage

This class is used to set the Game Activity of the user. This is done with the `set_activity(GodotActivity act)` method.

```GDScript
var act = GodotcordActivity.new();
act.details = "Details";
act.state = "Testing";
GodotcordActivityManager.set_activity(act);
```

This result is the following:  
![Example picture](https://cdn.discordapp.com/attachments/618818228508164127/722742670157676544/example.png)

GodotcordActivity has many properties depending on their combination show different Activity designs. For more information check out the Rich Presence Visualizer in the Discord Developer Portal and [this](https://discord.com/developers/docs/game-sdk/activities#activity-action-field-requirements-requirements) table in the documentation.

When another player tries to join the local player's lobby via their profile card the Signal `activity_join_request(name, user_id)` is emitted.
When a player joins a lobby via a chat invite or a personal invite is accepted the Signal `activity_join(String activity_secret)` is emitted.
A join_request can be answered using the `send_request_reply(id, request_reply)` method.
