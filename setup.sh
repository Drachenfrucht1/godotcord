wget https://dl-game-sdk.discordapp.net/latest/discord_game_sdk.zip
unzip discord_game_sdk
mv cpp ./discord-files
mv lib/x86_64 ./libpath
rm -rf examples c csharp lib
rm discord_game_sdk.zip