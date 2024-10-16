@echo off
bitsadmin /transfer DiscordGameSDKDownload /download /priority normal https://dl-game-sdk.discordapp.net/3.2.1/discord_game_sdk.zip %~dp0\discord_game_sdk.zip
powershell.exe "Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('discord_game_sdk.zip', 'dgsdk');"
mkdir discord-files
copy dgsdk\cpp discord-files

copy dgsdk\lib\x86_64\discord_game_sdk.so bin\libdiscord_game_sdk.so
copy dgsdk\lib\x86_64\discord_game_sdk.bundle bin\libdiscord_game_sdk.bundle
copy dgsdk\lib\x86_64\discord_game_sdk.dylib bin\libdiscord_game_sdk.dylib
copy dgsdk\lib\aarch64\discord_game_sdk.bundle bin\libdiscord_game_sdk.arm64.bundle
copy dgsdk\lib\aarch64\discord_game_sdk.dylib bin\libdiscord_game_sdk.arm64.dylib
copy dgsdk\lib\x86_64\discord_game_sdk.dll bin\discord_game_sdk.dll
copy dgsdk\lib\x86_64\discord_game_sdk.dll.lib bin\discord_game_sdk.dll.lib
del discord_game_sdk.zip
RMDIR /S /Q dgsdk

PowerShell.exe -ExecutionPolicy Bypass -Command "& './finish_setup.ps1'"
