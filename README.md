# Godotcord
A Godot module to integrate the Discord GameSDK into the engine

> This integration is not official and is not supported by the Discord GameSDK Developers.

> Not every functionality of this module has been thoroughly tested. I advise against using it in production.

Godotcord currently compiles for Windows, Linux and Mac.

# Setup

- Clone the [godot repository](https://github.com/godotengine/godot) to a local directory
- Checkout out at the 3.2.1-stable tag
- Clone the godotcord repository into the modules folder
  
The following steps can all be done by running setup.bat (Windows) or setup.sh (Linux/Mac) in the godotcord directory.<br>
If you want to do the setup on your own, here are the steps:
- [Download version 2.5.6 of the Discord Game SDK](https://dl-game-sdk.discordapp.net/2.5.6/discord_game_sdk.zip)
- Unzip the file
- Copy the files in the cpp into a folder called 'discord-files' in the godotcord directory
- Rename the x86 dlls to discord_game_sdk.32.dll and discord_game_sdk.32.dll.lib
- Copy the all dll's and libs into a folder called libpath in the godotcord directory
  
The second last step is to [recompile Godot](https://docs.godotengine.org/en/stable/development/compiling/index.html).

The final step is to copy the following libraries into the same folder as the executable you compiled:
- On Windows: Copy the .dll files
- On Linux: Copy the .so file
- On Mac: Copy the .dylib file and rename it to discord_game_sdk.dylib
These files should be in `/path/to/godot/modules/godotcord/libpath` if setup correctly.

# Notes

- You can find precompiled versions as artifacts of the github actions.
  These versions are compile with target release_debug and all modules (and the editor) enabled.
  You will most likely get a warning from windows and macos because the executables are not signed.<br>
  **I can not include the shared libraries in the downloads. You have to download the [Discord Game SDK](https://dl-game-sdk.discordapp.net/2.5.6/discord_game_sdk.zip) yourself and copy the required shared library into the same directory as the executable.**

- On Mac the shared library will not be found automatically.
  Execute `install_name_tool -add_rpath @executable_path GODOT_EXECUTABLE_NAME` in the bin directory to fix this issue.

# Documentation

The documentation can be found in the [wiki](https://github.com/Drachenfrucht1/godotcord/wiki)

# License
MIT License<br>
The Discord GameSDK is licensed under the [Discord Developer Terms of Service](https://discord.com/developers/docs/legal)
