# GodotcordOverlayManager

A wrapper of the Discord Game SDK Overlay Manager.
### Description

A wrapper of the Discord Game SDK Activity Manager. This class is used to interface with the ingame discord overlay.

| | |
----|----
boolean|[is_enabled](#is_enabled)()
boolean|[is_locked](#is_locked)()
void|[set_locked](#set_locked)(locked : boolean)
void|[open_voice_settings](#open_voice_settings)()
void|[open_activity_invite](#open_activity_invite)(type : ActivityActionType)
void|[open_build_invite](#open_build_invite)(invite_code : string)

### Signals

* profile_picture_callback(user_id : int, image_data : PoolByteArray)

Emitted when a profile picture has been fetched. The image data is returned as a byte array in `image_data`.
                See the example on how to convert the raw image data into a texture to use it in Godot.

----
### Method Descriptions

* <a name="is_enabled"></a> boolean is_enabled()

Returns whether the overlay is enabled

----
* <a name="is_locked"></a> boolean is_locked()

Returns whether the overlay is locked

----
* <a name="set_locked"></a> void set_locked(locked : boolean)

The the locking status to `locked`.

----
* <a name="open_voice_settings"></a> void open_voice_settings()

Signals the overlay to open the voice settings.

----
* <a name="open_activity_invite"></a> void open_activity_invite(type : ActivityActionType)

Opens a dialog to send activity invites to user, channels, groups, ...

----
* <a name="open_build_invite"></a> void open_build_invite(invite_code : string)

Opens the "Join a guild" dialog with the specified invite code.

----
