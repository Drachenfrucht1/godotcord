#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["./", "/discord-files"])
sources = [
    "register_types.cpp",
    "godotcord.cpp",
    "godotcord_activity_manager.cpp",
    "godotcord_overlay_manager.cpp",
    "godotcord_relationship_manager.cpp",
    "godotcord_user_manager.cpp",
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

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "bin/libgodotcord.{}.{}.framework/libgodotcord.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "bin/libgodotcord{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

if env["target"] in ["editor", "template_debug"]:
    try:
        doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")

Default(library)
