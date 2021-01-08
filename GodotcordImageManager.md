# GodotcordImageManager

The GodotcordImageManager class is provided as a singleton named `GodotcordImageManager`. I recommend to use this instance and not create a new one.

## GDScript methods/properties

`get_profile_picture(int user_id, int size, Object object, String funcname)`

- requests the profile picture of the user `user_id` in the size `size`
- the user_id and the image data are returned to the callback function `funcname`

## Usage

`GodotcordImageManager.request_profile_picture(user_id, size, object, callback)` only returns image data as bytes via the `profile_image` Signal.
An example on how to convert the image data into a texture is below.

```GDScript
func _profile_image_callback(user_id, img_data):
    var img = Image.new();
    img.create_from_data(SIZE, SIZE, false, Image.FORMAT_RGBA8, img_data);

    var texture = ImageTexture.new();
    texture.create_from_image(img);

    # add texture to sprite
```
