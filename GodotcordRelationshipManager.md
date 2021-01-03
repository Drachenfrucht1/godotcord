# GodotcordRelationshipManager
The GodotcordRelationshipManager class is provided as a singleton named `GodotcordRelationshipManager`. I recommend to use this instance and not create a new one.

## GDScript methods/properties
`Array filter_relationships(Object o, String function_name)`
- filters the user's relationships using the callback `function_name` of Object `o`
- the callback should have a GodotcordRelationship as a parameter
- the callback should return `true` if the relationship should be included in the list and false if not
- the returned array contains all matching relationships as dictionaries

`Array get_relationshis()`
- should only be called after the relationships have been filtered (see above)
- returns all filtered relationships as dictionaries

## Usage
Before accessing the relationships of the user you have to filter them.
This is done using the `GodotcordRealtionshipManager.filter_realtionships(Object o, String function_name)`.

Object `o` has to have a function called `function_name`. This function will be called for every relationship and will determine if it is filtered or not.

`function_name` will take one parameter of type dictionary and will return a boolean.

The dictionary will have the same fields as the [Relationship struct](https://discord.com/developers/docs/game-sdk/relationships#data-models-relationship-struct) of the Game SDK.

The relationship will be added to the filtered list if `function_name` returns true and not if false is returned.

Example:
--------
```GDScript
var friends = GodotcordRelationshipManager.filter_relationships(self, "_filter_func");

func _filter_func(relationship):
    if relationship["type"] == FRIEND:
        return true;
    else:
        return false;
```