@echo off
bitsadmin /transfer DiscordGameSDKDownload /download /priority normal https://dl-game-sdk.discordapp.net/3.2.1/discord_game_sdk.zip %~dp0\discord_game_sdk.zip
powershell.exe "Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('discord_game_sdk.zip', 'dgsdk');"
mkdir discord-files
copy dgsdk\cpp discord-files
mkdir libpath

copy dgsdk\lib\x86_64\discord_game_sdk.so libpath\libdiscord_game_sdk.so
copy dgsdk\lib\x86_64\discord_game_sdk.bundle libpath\libdiscord_game_sdk.bundle
copy dgsdk\lib\x86_64\discord_game_sdk.dylib libpath\libdiscord_game_sdk.dylib
copy dgsdk\lib\aarch64\discord_game_sdk.bundle libpath\libdiscord_game_sdk.arm64.bundle
copy dgsdk\lib\aarch64\discord_game_sdk.dylib libpath\libdiscord_game_sdk.arm64.dylib
del dgsdk\lib\x86_64\discord_game_sdk.so
copy dgsdk\lib\x86_64 libpath
del discord_game_sdk.zip
RMDIR /S /Q dgsdk

PowerShell.exe -ExecutionPolicy Bypass -Command "& './finish_setup.ps1'"
