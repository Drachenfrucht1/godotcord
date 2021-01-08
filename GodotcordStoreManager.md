# GodotcordStoreManager

The GodotcordStoreManager class is provided as a singleton named `GodotcordStoreManager`. I recommend to use this instance and not create a new one.

## GDScript methods/properties

`fetch_skus(Object o, String function_name)`

- refetches skus and returns them as array to callback function `function_name`
- skus are returned as Dictionaries. See `get_skus` for structure of Dictionaries

`Array get_skus()`

- returns the skus as array of Dictionaries
- Dictionaries include the fields `id`, `name`, `type`, `price`
- `price` is a Dictionary with the fields `amount` and `currrency`

`fetch_entitlements(Object o, String function_name)`

- refetches entitlements and returns them as array to callback function `function_name`
- entitlements are returned as Dictionaries. See `get_entitlements` for structure of Dictionaries

`Array get_entitlements()`

- returns the entitlements as array of Dictionaries
- Dictionaries include the fields `id`, `sku_id` and `type`

`bool has_local_user_entitlement(int sku_id)`

- returns whether the local user is entitled for the `sku_id`

`start_purchase(int sku_id)`

- opens the overlay or discord client and enables the user to buy the sku

## Usage

This manager can be used to check if the user hsa purchased DLC content.

You can also use it to create an ingame-store.
