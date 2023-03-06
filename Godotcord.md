# Godotcord


## Description



| | |
----|----
void|[init](#init)(client_id : int, createFlags : CreateFlags)
void|[init_debug](#init_debug)(client_id : int, id : string, createFlags : CreateFlags)
void|[run_callbacks](#run_callbacks)()
bool|[is_init](#is_init)()

## Enumerations

enum **CreateFlags**

* **CreateFlags_DEFAULT**=**0** --- 
* **CreateFlags_NO_REQUIRE_DISCORD**=**1** --- 

----
## Method Descriptions

* <a name="init"></a> void init(client_id : int, createFlags : CreateFlags)



----
* <a name="init_debug"></a> void init_debug(client_id : int, id : string, createFlags : CreateFlags)



----
* <a name="run_callbacks"></a> void run_callbacks()

Runs all the callbacks from the Discord Game SDK.
                This should be run every frame.

----
* <a name="is_init"></a> bool is_init()

Returns whether Godotcord is initialized.

----
