# GodotcordLobbyManager
The GodotcordLobbyManager class is provided as a singleton named `GodotcordLobbyManager`. I recommend to use this instance and not create a new one.

## GDScript methods/properties
`search_lobbies(Array search_parameters, int limit)`
- searches for a lobby that matches the parameters

`set_lobby_metadata(int lobby_id, String key, String value)`
- only callable as owner/creator of the lobby
- set a key-value pair that can be read by the other peers

`String get_lobby_metadata(int lobby_id, String key)`
- returns the value for the given key
- returns an empty string when an error occurs

## Usage

You have to setup a parameter array before searching for a lobby.
The array is made up of up dictionaries with up to 4 fields.

The 4 fields are:
- property: The property that should be compared. One of `owner_id`,  `capacity`, `slots`, or `metadata.custom_data`
- comparison: The way the property is compares. One of `LESS_THAN_OR_EQUAL`, `LESS_THAN`, `EQUAL`, `GREATER_THAN`, `GREATER_THAN_OR_EQUAL`, or `NOT_EQUAL`.
- cast: All values can only be passed using strings. This determines if the values should be casted to any other type. One of `STRING` or `INT`
- value: The value to filter against. Has to be a **string**.

A special filter is the property `distance`. It only requires a proeprty and value field. Value can be one of `LOCAL`, `DEFAULT`, `EXTENDED`, or `GLOBAL`.

To learn more about searching lobbies head over to the [Discord docs](https://discord.com/developers/docs/game-sdk/lobbies#lobbysearchqueryfilter) on this topic.

Example:
--------
A lobby search could look like this.
```gdscript
func search_lobby():
    #filter by custom metadata elo
    var elo = {};
    elo["property"] = "metadata.elo";
    elo["comparison"] = Godotcord.GREATER_THAN_OR_EQUAL;
    elo["cast"] = Godotcord.INT;
    elo["value"] = "10"; #has to be string

    #filter by location
    var distance = {};
    distance["property"] = "distance";
    distance["value"] = Godotcord.GLOBAL;

    var params = [elo, distance];

   Godotcord.search_lobbies(params, 10, self, "_callback_func");
```