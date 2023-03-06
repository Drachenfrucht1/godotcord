# GodotcordActivity

Data class for the discord game activity
## Description

Data class for the discord game activity.

| | |
----|----
string|[state](#state)|
string|[details](#details)|
string|[large_image](#large_image)|
string|[large_text](#large_text)|
string|[small_image](#small_image)|
string|[small_text](#small_text)|
string|[party_id](#party_id)|
int|[party_max](#party_max)|-1
int|[party_current](#party_current)|-1
string|[match_secret](#match_secret)|
string|[join_secret](#join_secret)|
string|[spectate_secret](#spectate_secret)|
int|[start](#start)|0
int|[end](#end)|0
int|[application_id](#application_id)|0

## Enumerations

enum **ActivityRequestReply**

* **NO**=**0** --- Reject the request
* **YES**=**1** --- Accept the request
* **IGNORE**=**2** --- Ignore the request

----
enum **ActivityActionType**

* **JOIN**=**1** --- Marks a join request
* **SPECTATE**=**2** --- Marks a spectate request

----
