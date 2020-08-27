# Godotcord
A Godot module to integrate the Discord GameSDK into the engine

> This integration is not official and is not supported by the Discord GameSDK Developers.

> Not every functionality of this module has been thoroughly tested. I advise against using it in production.

Godotcord currently supports Windows (64 and 32 bit) and Linux (64 bit).

# Setup

- Clone the godot repository to a local directory
- Checkout out at the 3.2.1-stable tag
- Clone the godotcord repository into the modules folder
  
The following steps can all be done by running the setup.bat in the godotcord directory.<br>
If you want to do the setup on your own, here are the steps:
- [Download version 2.5.6 of the Discord Game SDK](https://dl-game-sdk.discordapp.net/2.5.6/discord_game_sdk.zip)
- Unzip the file
- Copy the files in the cpp into a folder called 'discord-files' in the godotcord directory
- Rename the x86 dlls to discord_game_sdk.32.dll and discord_game_sdk.32.dll.lib
- Copy the all dll's and libs into a folder called libpath in the godotcord directory
  
The final step is to [recompile Godot](https://docs.godotengine.org/en/stable/development/compiling/compiling_for_windows.html).

Remember that the shared library has to be accesible by the final executable.

# Documentation

The documentation can be found in the [wiki](https://github.com/Drachenfrucht1/godotcord/wiki)

# License
MIT License<br>
The Discord GameSDK is licensed under the [Discord Developer Terms of Service](https://discord.com/developers/docs/legal)