# GodotcordStorageManager

A wrapper of the Discord Game SDK Storage Manager.
## Description

A wrapper of the Discord Game SDK Storage Manager. This class is used to manage save games in the cloud.

| | |
----|----
string|[get_path](#get_path)()
Array|[read](#read)(name : string)
Array|[read_async](#read_async)(name : string)
Array|[read_async_partial](#read_async_partial)(name : string, offset : int, length : int)
void|[write](#write)(data : Array)
void|[write_async](#write_async)(data : Array)
void|[destroy](#destroy)(name : string)
bool|[exists](#exists)(name : string)
GodotcordFileStat|[stat](#stat)(name : string)
int|[count](#count)()
GodotcordFileStat|[stat_at](#stat_at)(index : int)

## Method Descriptions

* <a name="get_path"></a> string get_path()



----
* <a name="read"></a> Array read(name : string)

Returns the content of file `name`

----
* <a name="read_async"></a> Array read_async(name : string)

Reads the content of `name` asnychronously.
                Returns the content using the `async_data_read` signal.

----
* <a name="read_async_partial"></a> Array read_async_partial(name : string, offset : int, length : int)

Reads `length` bytes beginning from the `offset`th byte from the file `name` asnychronously.
                Returns the content using the `async_data_read` signal.

----
* <a name="write"></a> void write(data : Array)



----
* <a name="write_async"></a> void write_async(data : Array)

Emits the signal `async_data_written` after the completion.

----
* <a name="destroy"></a> void destroy(name : string)

Destroys the file `name`.

----
* <a name="exists"></a> bool exists(name : string)

Returns whether the file `name` exists.

----
* <a name="stat"></a> GodotcordFileStat stat(name : string)

Returns the GodotcordFileStat for the file `name`.

----
* <a name="count"></a> int count()



----
* <a name="stat_at"></a> GodotcordFileStat stat_at(index : int)



----
