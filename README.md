# Godotcord
A Godot module to integrate the Discord GameSDK into the engine

> This integration is not official and is not supported by the Discord GameSDK Developers.

> Not every functionality of this module has been thoroughly tested. I advise against using it in production.

Godotcord currently compiles for Windows, Linux and Mac.

# Setup

- Clone the [godot repository](https://github.com/godotengine/godot) to a local directory
- Checkout out at the 3.2.1-stable tag
- Clone the godotcord repository into the modules folder
  
The following steps can all be done by running the setup.bat in the godotcord directory.<br>
If you want to do the setup on your own, here are the steps:
- [Download version 2.5.6 of the Discord Game SDK](https://dl-game-sdk.discordapp.net/2.5.6/discord_game_sdk.zip)
- Unzip the file
- Copy the files in the cpp into a folder called 'discord-files' in the godotcord directory
- Rename the x86 dlls to discord_game_sdk.32.dll and discord_game_sdk.32.dll.lib
- Copy the all dll's and libs into a folder called libpath in the godotcord directory
  
The final step is to [recompile Godot](https://docs.godotengine.org/en/stable/development/compiling/index.html).

The final step is to copy the shared libraries into the bin directory.
On Windows copy the .dll files into the bin directory.
On Linux copy the .so file into the bin directory.
on Mac copy the .dylib file into the bin directory and rename it to discord_game_sdk.dylib.

# Notes

On Mac the shared library will not be found automatically.
Execute `install_name_tool -add_rpath @executable_path GODOT_EXECUTABLE_NAME` in the bin directory to fix this issue.

# Contribution
If you encounter any problems, feel free to open an issue or join the [discord server](https://discord.gg/KVYWM8shqu).
You are also welcome to open PRs with improvements.

# Documentation

The documentation can be found in the [wiki](https://github.com/Drachenfrucht1/godotcord/wiki)

# License
MIT License<br>
The Discord GameSDK is licensed under the [Discord Developer Terms of Service](https://discord.com/developers/docs/legal)