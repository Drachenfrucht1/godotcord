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
cd discord-files
sed -i '2s/.*/#include <cstdint>/' types.h
cd ..
