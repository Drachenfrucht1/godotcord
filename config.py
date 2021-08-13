def can_build(env, platform):
    return True

def configure(env):
    pass

def get_doc_classes():
    return [
        "Godotcord",
        "GodotcordAchievementManager",
        "GodotcordActivity",
        "GodotcordActivityManager",
        "GodotcordFileStat",
        "GodotcordImageManager",
        "GodotcordInputMode",
        "GodotcordLobby",
        "GodotcordLobbyManager",
        "GodotcordOverlayManager",
        "GodotcordPresence",
        "GodotcordRelationship",
        "GodotcordRelationshipManager",
        "GodotcordSearchParameter",
        "GodotcordStorageManager",
        "GodotcordStoreManager",
        "GodotcordUser",
        "GodotcordUserManager",
        "GodotcordVoiceManager",
        "NetworkedMultiplayerGodotcord"
    ]


def get_doc_path():
    return "docs"