# GodotcordStorageManager
The GodotcordStorageManger class is provided as a singleton named `GodotcordStorageManager`. I recommend to use this instance and not create a new one.

## GDScript methods/properties

`String get_path()`
- Returns the filepath that was set in `DISCORD_STORAGE_PATH`.
- use this to get the save path to save files.
- read more about this function [here](https://discord.com/developers/docs/game-sdk/storage#getpath).

`PoolByteArray read(String name)`
- reads and returns the binary data.
- data is being saved in the format of key-value pairs.
- read more about this function [here](https://discord.com/developers/docs/game-sdk/storage#read).

`void read_async(String name)`
- reads and returns the string data using signal `async_data_read` asynchronously.
- read more about this function [here](https://discord.com/developers/docs/game-sdk/storage#readasync).

`void read_async_partial(String name, int offset, int length)`
- reads and returns data using signal `async_data_read` asynchronously.
- starts reading from offset and upto given length.
- read more about this function [here](https://discord.com/developers/docs/game-sdk/storage#readasyncpartial)

`void write(String name, PoolByteArray data)`
- writes the data into the save file.
- data is being saved in the format of key-value pairs.
- read more about this function here.

`void write_async(String name, PoolByteArray data)`
- writes data into the save file asynchronously.
- `async_data_written` signal will be emitted once the data has been written in the save file.
- read more about this function here.

`void destroy(String name)`
- deletes the key and it's value.
- read more about this function here.

`bool exists(String name)`
- checks if the key exists in the save file.
- read more about this function here.

`Dictionary stat(String name)`
- returns the file info of the file.
- read more about this function here.

`int count()`
- returns the number of files the storage manager has used.
- read more about this function here.

`Dictionary stat_at(int index)`
- returns the stat of the file at the current index.
- mainly used for getting the stats of the while iterating over the files.

## Signals:
`async_data_read`
- emitted when the read_async and read_async_partial completes reading data.

`async_data_written`
- emitted when the write_async completes writing data.

## Example:
```gdscript
func save(data: Dictionary):
    for key in data:
        GodotcordStorageManager.write(key, data[key].to_utf8())

func load(list_of_load_keys: PoolStringArray) -> Dictionary:
    var dict = Dictionary.new()
    for key in list_of_load_keys:
        if GodotcordStorageManager.exists(key):
            dict[key] = GodotcordStorageManager.read(key)
    return dict
```
