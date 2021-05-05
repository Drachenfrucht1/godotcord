# Godotcord
The Godotcord class is provided as a singleton named `Godotcord`. I recommend to use this instance and not create a new one.

## GDScript Methods/Properties

`init(int clientId, CreateFlags createFlags)`
- inits the Discord Game SDK
- Example syntax: `Godotcord.init(ClientID, Godotcord.CreateFlags_DEFAULT);`
- CreateFlags are:
- `CreateFlags_DEFAULT`
- `CreateFlags_NO_REQUIRE_DISCORD`

`init_debug(int clientId, string instance_id, CreateFlags createFlags)`
- used for testing with two clients locally
- read [discord docs](https://discord.com/developers/docs/game-sdk/sdk-starter-guide#testing-locally-with-two-clients) for usage

`run_callbacks()`
- calls all callbacks of the Discord Game SDK
- best to call every frame (in `_process`)

**All properties of the local user will only return successfully after the first call of `run_callbacks`.
Otherwise, 0 or an empty string is returned.**

## Usage
At the startup of your program you should connect to the Discord client of the user 
by calling `Godotcord.init(CLIENT_ID, CREATE_FLAGS)`.<br>
You have to use `Godotcord.init_debug(CLIENT_ID, INSTANCE, CREATE_FLAGS)` when testing with more than one client on one maschine. To learn more about that have a look [here](https://discord.com/developers/docs/game-sdk/sdk-starter-guide#testing-locally-with-two-clients).<br>

enum `CREATE_FLAGS`
`CreateFlags_Default` or `CreateFlags_NO_REQUIRE_DISCORD`
Used in `Godotcord.init`: `Godotcord.init(ClientID, Godotcord.CreateFlags_DEFAULT);`
To learn more about what they do, head over to the [Game SDK docs](https://discord.com/developers/docs/game-sdk/discord#data-models-createflags-enum)

To constantly get messages from the Discord client you have to call `Godotcord.run_callback()` often. I recommend calling it in the `_process` method of a node.<br>
*Some functions only work properly after the first call of `Godotcord.run_callback`*
