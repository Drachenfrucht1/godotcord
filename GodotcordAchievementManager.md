# GodotcordAchievementManager

A wrapper of the Discord Game SDK Achievement Manager.
### Description

A wrapper of the Discord Game SDK Activity Manager. This class is used to organise the achievements of the local user.
| | |
----|----
void|[set_user_achievement](#set_user_achievement)(achievement_id : int, percent : int)
void|[fetch_user_achievement](#fetch_user_achievement)()
Array|[get_user_achievements](#get_user_achievements)()

### Signals

* fetch_user_achievements()

Emitted when the user achievements have been fetched.

----
### Method Descriptions

* <a name="set_user_achievement"></a> void set_user_achievement(achievement_id : int, percent : int)

Sets the achievement `achievement` to be `percent` completed.

----
* <a name="fetch_user_achievement"></a> void fetch_user_achievement()

Fetched the users achievements. Emitts `fetch_user_achievements` when the fetching is complete.

----
* <a name="get_user_achievements"></a> Array get_user_achievements()

Returns all achievements and their progress.

----
