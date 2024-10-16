# Godotcord
A Godot module to integrate the Discord GameSDK into the engine

> This integration is not official and is not supported by the Discord GameSDK Developers.

> Not every functionality of this module has been thoroughly tested. I advise against using it in production.

Godotcord currently compiles for Windows, Linux and Mac.

# Setup

- You need [scons](https://scons.org/) installed in order to compile the GDExtension.
- Clone the godotcord repository with submodules using `git clone --recurse-submodules -b 4.x git@github.com:Drachenfrucht1/godotcord.git`
The following steps can all be done by running setup.bat (Windows) or setup.sh (Linux/Mac) in the godotcord directory.<br>
If you want to do the setup on your own, here are the steps:
- [Download version 3.2.1 of the Discord Game SDK](https://dl-game-sdk.discordapp.net/3.2.1/discord_game_sdk.zip)
- Unzip the file
- Copy the files in the cpp directory into a folder called 'discord-files' in the godotcord directory
- Copy all libraries in the x86_64 and aarch64 subfolders into the bin folder. Rename the files according to the directory structure below:
```
godotcord/
├─ bin/
│  ├─ godotcord.gdextension
│  ├─ discord_game_sdk.dll(.lib)
│  ├─ libdiscord_game_sdk(.arm64).bundle/.dylib
│  ├─ libdiscord_game_sdk.so
├─ discord-files/
│  ├─ .cpp and .h files
```
- You can now compile the GDExtension by running `scons`.

Copy the bin folder into the root directory of your Godot project in order to use godotcord.

<!-- # Notes

- You can find precompiled versions as artifacts of the github actions.
  These versions are compile with target release_debug and all modules (and the editor) enabled.
  You will most likely get a warning from windows and macos because the executables are not signed.<br>
  **I can not include the shared libraries in the downloads. You have to download the [Discord Game SDK](https://dl-game-sdk.discordapp.net/3.2.1/discord_game_sdk.zip) yourself and copy the required shared library into the same directory as the executable.** -->

# Contribution
If you encounter any problems, feel free to open an issue or join the [discord server](https://discord.gg/KVYWM8shqu).
You are also welcome to open PRs with improvements.

<!-- # Documentation

The documentation can be found in the [wiki](https://github.com/Drachenfrucht1/godotcord/wiki) -->

# License
MIT License<br>
The Discord GameSDK is licensed under the [Discord Developer Terms of Service](https://discord.com/developers/docs/legal)
