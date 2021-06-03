# GodotcordRelationship

Data class for a discord relationship
### Description

Data class for a discord relationship
| | |
----|----
RelationshipType|[type](#type)|
int|[user_id](#user_id)|0
GodotcordPresence|[presence](#presence)|0

| | |
----|----
RelationshipStatus|[get_type](#get_type)()
void|[set_type](#set_type)(property : RelationshipStatus)
int|[get_user_id](#get_user_id)()
void|[set_user_id](#set_user_id)(property : int)
GodotcordPresence|[get_presence](#get_presence)()
void|[set_presence](#set_presence)(property : GodotcordPresence)

### Enumerations

enum **RelationshipType**

* **NONE**=**0** --- The user has no intrinsic relationship
* **FRIEND**=**1** --- The user is a friend
* **BLOCKED**=**2** --- The user is blocked
* **PENDING_INCOMING**=**3** --- The current user has a pending incoming friend request from the user
* **PENDING_OUTGOING**=**4** --- The current user has a pending outgoing friend request to the user
* **IMPLICIT**=**5** --- The user is no friend but they interact often
----
### Method Descriptions

* <a name="get_type"></a> RelationshipStatus get_type()



----
* <a name="set_type"></a> void set_type(property : RelationshipStatus)



----
* <a name="get_user_id"></a> int get_user_id()



----
* <a name="set_user_id"></a> void set_user_id(property : int)



----
* <a name="get_presence"></a> GodotcordPresence get_presence()



----
* <a name="set_presence"></a> void set_presence(property : GodotcordPresence)



----
