# GodotcordVoiceManager

A wrapper of the Discord Game SDK Voice Manager.
### Description

A wrapper of the Discord Game SDK Voice Manager.

| | |
----|----
GodotcordInputMode|[get_input_mode](#get_input_mode)()
void|[set_voice_activity](#set_voice_activity)()
void|[set_push_to_talk](#set_push_to_talk)(hotkey : string)
bool|[is_self_mute](#is_self_mute)()
void|[set_self_mute](#set_self_mute)(b : bool)
void|[set_push_to_talk](#set_push_to_talk)(hotkey : string)
bool|[is_self_deaf](#is_self_deaf)()
void|[set_self_deaf](#set_self_deaf)(b : bool)
void|[set_push_to_talk](#set_push_to_talk)(hotkey : string)
bool|[is_local_mute](#is_local_mute)(user_id : int)
void|[set_local_mute](#set_local_mute)(user_id : int, b : bool)
int|[is_local_volume](#is_local_volume)(user_id : int)
void|[set_local_mute](#set_local_mute)(user_id : int, b : int)

### Method Descriptions

* <a name="get_input_mode"></a> GodotcordInputMode get_input_mode()



----
* <a name="set_voice_activity"></a> void set_voice_activity()

Sets the input mode to voice activity.

----
* <a name="set_push_to_talk"></a> void set_push_to_talk(hotkey : string)

Sets the input mode to push to talk with the hotkey `hotkey`.

----
* <a name="is_self_mute"></a> bool is_self_mute()

Returns whether the local user is self mute.

----
* <a name="set_self_mute"></a> void set_self_mute(b : bool)



----
* <a name="set_push_to_talk"></a> void set_push_to_talk(hotkey : string)

Sets the input mode to push to talk with the hotkey `hotkey`.

----
* <a name="is_self_deaf"></a> bool is_self_deaf()

Returns whether the local user is self deaf.

----
* <a name="set_self_deaf"></a> void set_self_deaf(b : bool)



----
* <a name="set_push_to_talk"></a> void set_push_to_talk(hotkey : string)

Sets the input mode to push to talk with the hotkey `hotkey`.

----
* <a name="is_local_mute"></a> bool is_local_mute(user_id : int)

Returns whether `user_id` is muted by the local user.

----
* <a name="set_local_mute"></a> void set_local_mute(user_id : int, b : bool)



----
* <a name="is_local_volume"></a> int is_local_volume(user_id : int)

Returns the local volume of `user_id`.
                The value range is 0 to 200.

----
* <a name="set_local_mute"></a> void set_local_mute(user_id : int, b : int)

The value range is 0 to 200.

----
