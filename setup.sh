wget https://dl-game-sdk.discordapp.net/3.2.1/discord_game_sdk.zip
# wget https://dl-game-sdk.discordapp.net/2.5.6/discord_game_sdk.zip
unzip discord_game_sdk -d dgsk
mv dgsk/cpp ./discord-files
mv dgsk/lib/x86_64/* ./bin
mv ./bin/discord_game_sdk.so ./bin/libdiscord_game_sdk.so
mv ./bin/discord_game_sdk.bundle ./bin/libdiscord_game_sdk.bundle
mv ./bin/discord_game_sdk.dylib ./bin/libdiscord_game_sdk.dylib

mv dgsk/lib/aarch64/discord_game_sdk.bundle ./bin/libdiscord_game_sdk.arm64.bundle
mv dgsk/lib/aarch64/discord_game_sdk.dylib ./bin/libdiscord_game_sdk.arm64.dylib

rm -rf dgsk
rm discord_game_sdk.zip

cd discord-files
sed -i '2s/.*/#include <cstdint>/' types.h
cd ..
