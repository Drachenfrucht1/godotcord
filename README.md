A GodotEngine module that integrated the Discord Game SDK


#Setup
- Clone the godot repository to a local directory
- Checkout out at the 3.2.1-stable tag
- Clone the godotcord repository into the modules folder
- Download the curent version of the Discord Game SDK
- Copy the cpp files into the folder 'discord-files' in the godotcord directory
- Copy dll's into the folder libpath in the godotcord directoy
- Build godot

#Quickstart
Before using Godotcord you must create an application in the [Discord Developer Portal](https://discord.com/developers/applications).
This application should be owned by a team as state [here](https://discord.com/developers/docs/game-sdk/sdk-starter-guide#get-set-up).
After that you can start using Godotcard with this little code-snippet.
```
func _ready():
    var gc = Godotcord.New()
    gc.init(YOUR_CLIENT_ID)
    var activity = GodotcordAcvitiy.New()
    activity.state = "State"
    activity.details = "Details"
    activity.start = OS.get_unix_time()

    gc.set_activity(activity)
```

#Classes

###Godotcord
**init(int clientId)**
- inits the Discord Game SDK

**callbacks()**
- call alls callbacks of the Discord Game SDK
- needs to be called every frame

**set_activity(GodotcordActivity activity)**
- sets the rich present of the current discord user

**clear_activity()**
- clears the users activity

**Signal activity_join(secret)**
- called when a user joins a chat party invite or a personal invite is accepted
- secret is the joinMatchSecret of the other persons activity

###Godotcordactivity

**String state**
**String details**
**String largeImage**
**String largeText**
- tooltip for the large image

**String smallImage**
**String smallText**
- tooltip for the small image

**String partyID**
- the id of the lobby the user is in

**int partyMax**
- the max size of the party the user is in

**int partyCurrent**
the current size of the party the user is in

**String matchSecret**
**String joinSecret**
**String spectateSecret**
**int start**
- unix starttime of the users activity
**int end**
- unix endtime of the users activity

###NetowrkedMultiplayerDiscord

**ini_discord(Godocord godotcord)**
- inits the NetworkedMultiplayerEnet with the Godotcord instance
- call before joininig/creating lobby
  
**create_lobby(int size, bool public = false)**
- create a discord lobby and joins it

**join_lobby(int id, String secret)**
- join the given lobby with the given secret

**join_lobby_secret(String activitySecret)**
- joins the lobby with the given activity secret

**Signal created_server()**
- called when a server is created after `network_peer_connected` has been called for **every player (including the local one)**

The server_connected signal is, too, fired after `network_peer_connected` has been called for **every player (including the local one)** 

This class contains all others methods and signals on would expect from a NetworkedMultiplayerPeer

