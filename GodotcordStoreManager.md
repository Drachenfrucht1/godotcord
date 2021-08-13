# GodotcordStoreManager

A wrapper of the Discord Game SDK Store Manager.
### Description

A wrapper of the Discord Game SDK Store Manager.

| | |
----|----
void|[fetch_skus](#fetch_skus)()
Array|[get_skus](#get_skus)()
void|[fetch_entitlements](#fetch_entitlements)()
Array|[fetch_entitlements](#fetch_entitlements)()
bool|[fetch_entitlements](#fetch_entitlements)(sku_id : int)
void|[start_purchase](#start_purchase)(sku_id : int)

### Method Descriptions

* <a name="fetch_skus"></a> void fetch_skus()



----
* <a name="get_skus"></a> Array get_skus()



----
* <a name="fetch_entitlements"></a> void fetch_entitlements()

Refetches the entitlements of the local user

----
* <a name="fetch_entitlements"></a> Array fetch_entitlements()

Returns the entitlements of the local user.

----
* <a name="fetch_entitlements"></a> bool fetch_entitlements(sku_id : int)

Returns whether the local user has an entitlement for the sku `sku_id`.

----
* <a name="start_purchase"></a> void start_purchase(sku_id : int)

Opens the discord client and starts a purchase dialog for the sku `sku_id`.

----
