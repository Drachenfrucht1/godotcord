# GodotcordActivityManager

A wrapper of the Discord Game SDK Activity Manager.
### Description

A wrapper of the Discord Game SDK Activity Manager. This class is used to manage the rich presence of the user and to receive and send game invites via Discord.
        It is provided as a singleton named GodotcordActivityManger

| | |
----|----
void|[set_activity](#set_activity)(activity : GodotcordActivity)
void|[clear_activity](#clear_activity)()
void|[register_steam](#register_steam)(steam_id : int)
void|[register_command](#register_command)(command : string)
void|[send_request_reply](#send_request_reply)(user_id : int, reply : GodotcordActivity.ActivityRequestReply)
void|[send_invite](#send_invite)(user_id : int, type : GodotcordActivity.ActivityActionType, message : string)
void|[accept_invite](#accept_invite)(user_id : int)

### Signals

* activity_join_request(name : string, user_id : int)

Emitted when a join request has been send by the user with the name `name` and user id `user_id`

----
* activity_invite(type : GodotcordActivity.ActivityActionType, name : string, user_id : int, activity : Dictionary)

Emitted when a join/spectate request is received.

----
* acvitiy_join(activity_secret : string)

Emitted when a chat invite has been pressed or a join request has been accepted.

----
* activity_spectate(activity_secret : string)

Emmitted when a spectate request has been accepted.

----
### Method Descriptions

* <a name="set_activity"></a> void set_activity(activity : GodotcordActivity)

Set the game activity to the provided activity.

----
* <a name="clear_activity"></a> void clear_activity()

Removes the current game activity.

----
* <a name="register_steam"></a> void register_steam(steam_id : int)

Register the steam id of the game. Used by Discord to launch the game when pressing on an invite.

----
* <a name="register_command"></a> void register_command(command : string)

Register a command that launches the game. Used by Discord to launch the game when pressing on an invite.

----
* <a name="send_request_reply"></a> void send_request_reply(user_id : int, reply : GodotcordActivity.ActivityRequestReply)

Answers the request received by `user_id` with the provided reply.

----
* <a name="send_invite"></a> void send_invite(user_id : int, type : GodotcordActivity.ActivityActionType, message : string)

Sends an invite of type `type` to `user_id` with the message `message`

----
* <a name="accept_invite"></a> void accept_invite(user_id : int)

Accepts the invite received by `user_id`

----
