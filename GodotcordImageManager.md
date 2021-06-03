# GodotcordImageManager

A wrapper of the Discord Game SDK Achievement Manager.
### Description

A wrapper of the Discord Game SDK Activity Manager. This class is used to fetch the profile image of users.
| | |
----|----
void|[get_profile_picture](#get_profile_picture)(user_id : int, size : int)

### Signals

* profile_picture_callback(user_id : int, image_data : PoolByteArray)

Emitted when a profile picture has been fetched. The image data is returned as a byte array in `image_data`.
                See the example on how to convert the raw image data into a texture to use it in Godot.

----
### Method Descriptions

* <a name="get_profile_picture"></a> void get_profile_picture(user_id : int, size : int)

Fetches the profile picture of user `user_id`.
                Emitts the signal `profile_picture_callback` with the image data cropped to `size*size` pixels.

----
