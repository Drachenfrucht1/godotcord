wget https://dl-game-sdk.discordapp.net/2.5.6/discord_game_sdk.zip
unzip discord_game_sdk -d dgsk
mv dgsk/cpp ./discord-files
mv dgsk/lib/x86_64 ./libpath
mv ./libpath/discord_game_sdk.so ./libpath/libdiscord_game_sdk.so
mv ./libpath/discord_game_sdk.bundle ./libpath/libdiscord_game_sdk.bundle
mv ./libpath/discord_game_sdk.dylib ./libpath/libdiscord_game_sdk.dylib

mv dgsk/lib/x86/discord_game_sdk.dll ./libpath/discord_game_sdk.32.dll
mv dgsk/lib/x86/discord_game_sdk.dll.lib ./libpath/discord_game_sdk.32.dll.lib

rm -rf dgsk
rm discord_game_sdk.zip

wget https://ncloud.drachenfrucht1.de/s/fP8NWK3NKsm9nHw/download
unzip download -d libs
mv libs/include ./libsodium
cp libs/lib/* ./libpath

rm -rf libs
rm download