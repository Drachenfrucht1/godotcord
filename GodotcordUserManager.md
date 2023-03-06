# GodotcordUserManager

A wrapper of the Discord Game SDK User Manager.
## Description

A wrapper of the Discord Game SDK User Manager.

| | |
----|----
void|[get_user](#get_user)(user_id : int)
GodotcordUser|[get_current_user](#get_current_user)()
PremiumType|[get_current_user_premium_type](#get_current_user_premium_type)()
bool|[has_current_user_flag](#has_current_user_flag)(flag : UserFlag)

## Enumerations

enum **UserFlag**

* **HYPE_SQUAD_HOUSE_2**=**128** --- The user is a member of the house of brilliance.
* **PARTNER**=**2** --- The user is a discord partner.
* **HYPE_SQUAD_HOUSE_3**=**256** --- The user is a  member of the house of balance.
* **HYPE_SQUAD_EVENTS**=**4** --- The user is a hypesquad events participant
* **HYPE_SQUAD_HOUSE_1**=**64** --- The user is a member of the house of bravery.

----
enum **PremiumType**

* **ERROR**=**-1** --- An error has occured while retrieving the premium type.
* **NONE**=**0** --- The user is not a nitro subscriber.
* **TIER_1**=**1** --- The user is a nitro classic subscriber.
* **TIER_2**=**2** --- The user is a nitro subscriber.

----
## Method Descriptions

* <a name="get_user"></a> void get_user(user_id : int)

Request the user object of `user_id`.
                The user object is returned via the `get_user_callback` signal.

----
* <a name="get_current_user"></a> GodotcordUser get_current_user()

Returns the user objects of the local user.

----
* <a name="get_current_user_premium_type"></a> PremiumType get_current_user_premium_type()

Returns the premium type of the local user.

----
* <a name="has_current_user_flag"></a> bool has_current_user_flag(flag : UserFlag)

Returns whether the local user has `flag`.

----
