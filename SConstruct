#!/usr/bin/env python
import os
import sys

sources = [
    "register_types.cpp",
    "godotcord.cpp",
    # "godotcord_activity_manager.cpp",
    # "godotcord_overlay_manager.cpp",
    # "godotcord_relationship_manager.cpp",
    # "godotcord_user_manager.cpp",
    "discord-files/achievement_manager.cpp",
    "discord-files/activity_manager.cpp",
    "discord-files/application_manager.cpp",
    "discord-files/core.cpp",
    "discord-files/image_manager.cpp",
    "discord-files/lobby_manager.cpp",
    "discord-files/network_manager.cpp",
    "discord-files/overlay_manager.cpp",
    "discord-files/relationship_manager.cpp",
    "discord-files/storage_manager.cpp",
    "discord-files/store_manager.cpp",
    "discord-files/types.cpp",
    "discord-files/user_manager.cpp",
    "discord-files/voice_manager.cpp"
]


### Parts copied from https://github.com/GodotVR/godot_xr_reference

# Try to detect the host platform automatically.
# This is used if no `platform` argument is passed
if sys.platform.startswith("linux"):
    host_platform = "linux"
elif sys.platform == "darwin":
    host_platform = "osx"
elif sys.platform == "win32" or sys.platform == "msys":
    host_platform = "windows"
else:
    raise ValueError("Could not detect platform automatically, please specify with " "platform=<platform>")

env = Environment(ENV=os.environ)

opts = Variables([], ARGUMENTS)

# Define our options
opts.Add(EnumVariable("target", "Compilation target", "debug", ["d", "debug", "r", "release"]))
opts.Add(EnumVariable("platform", "Compilation platform", host_platform, ["", "windows", "x11", "linux", "osx"]))
opts.Add(
    EnumVariable("p", "Compilation target, alias for 'platform'", host_platform, ["", "windows", "x11", "linux", "osx"])
)
opts.Add(EnumVariable("bits", "Target platform bits", "64", ("32", "64")))
opts.Add(PathVariable("target_path", "The path where the lib is installed.", "bin/", PathVariable.PathAccept))
opts.Add(PathVariable("target_name", "The library name.", "libgodotcord", PathVariable.PathAccept))

# Local dependency paths, adapt them to your setup
godot_headers_path = "godot-cpp/godot-headers/"
cpp_bindings_path = "godot-cpp/"
cpp_library = "libgodot-cpp"

# Updates the environment with the option variables.
opts.Update(env)
# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))

if env["p"] != "":
    env["platform"] = env["p"]
if env["platform"] == "":
    print("No valid target platform selected")
    quit()

if env["target"] == "debug":
    env.Append(CPPDEFINES=["DEBUG_ENABLED", "DEBUG_METHODS_ENABLED"])

# Platform specific configuration
if env["platform"] == "windows":
    env["target_path"] += "win64/"
    cpp_library += ".windows"
    # This makes sure to keep the session environment variables on windows,
    # that way you can run scons in a vs 2017 prompt and it will find all the required tools
    env.Append(ENV=os.environ)

    env.Append(CPPDEFINES=["WIN32", "_WIN32", "_WINDOWS", "_CRT_SECURE_NO_WARNINGS"])
    env.Append(CCFLAGS=["-W3", "-GR"])
    env.Append(CXXFLAGS=["-std:c++17"])
    if env["target"] in ("debug", "d"):
        env.Append(CPPDEFINES=["_DEBUG"])
        env.Append(CCFLAGS=["-EHsc", "-MDd", "-ZI", "-FS"])
        env.Append(LINKFLAGS=["-DEBUG"])
    else:
        env.Append(CPPDEFINES=["NDEBUG"])
        env.Append(CCFLAGS=["-O2", "-EHsc", "-MD"])

    #Game SDK specific
    if env["bits"] == "64":
        env.Append(LINKFLAGS=['discord_game_sdk.dll.lib'])
    elif env["bits"] == "32":
        env.Append(LINKFLAGS=['discord_game_sdk.32.dll.lib'])
elif env["platform"] == "x11" or env["platform"] == "linux":
    env["target_path"] += "x11/"
    cpp_library += ".linux"
    env.Append(CCFLAGS=["-fPIC"])
    env.Append(CXXFLAGS=["-std=c++17"])
    if env["target"] in ("debug", "d"):
        env.Append(CCFLAGS=["-g3", "-Og"])
    else:
        env.Append(CCFLAGS=["-g", "-O3"])

    #Game SDK specific
    if env["bits"] == "64":
        env.Append(RPATH=[Literal("\$$ORIGIN:.")])
        env.Append(LIBS=['discord_game_sdk'])
    if env["bits"] == "32":
        print("32bit is on linux currently not supported")
        quit()
elif(env["platform"] == "osx"):
    env["target_path"] += "win64/"
    cpp_library += ".windows"
    # This makes sure to keep the session environment variables on windows,
    # that way you can run scons in a vs 2017 prompt and it will find all the required tools
    env.Append(ENV=os.environ)

    env.Append(CPPDEFINES=["WIN32", "_WIN32", "_WINDOWS", "_CRT_SECURE_NO_WARNINGS"])
    env.Append(CCFLAGS=["-W3", "-GR"])
    env.Append(CXXFLAGS=["-std:c++17"])
    if env["target"] in ("debug", "d"):
        env.Append(CPPDEFINES=["_DEBUG"])
        env.Append(CCFLAGS=["-EHsc", "-MDd", "-ZI", "-FS"])
        env.Append(LINKFLAGS=["-DEBUG"])
    else:
        env.Append(CPPDEFINES=["NDEBUG"])
        env.Append(CCFLAGS=["-O2", "-EHsc", "-MD"])

    #Game SDK specific
    env.Append(LIBS=['discord_game_sdk'])
    env.Append(LINKFLAGS=["-Wl,-rpath,@executable_path"])

if env["target"] in ("debug", "d"):
    cpp_library += ".template_debug"
else:
    cpp_library += ".release"

cpp_library += ".x86_64"

env.Append(LIBPATH=['libpath', cpp_bindings_path + "bin/"])
env.Append(CPPPATH=[".", 
                    godot_headers_path, 
                    cpp_bindings_path + "/include", 
                    cpp_bindings_path + "gen/include/",
                    cpp_bindings_path + "gdextension"])
env.Append(LIBS=[cpp_library])


library = env.SharedLibrary(target=env["target_path"] + env["target_name"], source=sources)

Default(library)