# GodotcordRelationshipManager

A wrapper of the Discord Game SDK Relationship Manager.
### Description

A wrapper of the Discord Game SDK Relationship Manager. This class is used to fetch the users relationships.

| | |
----|----
Array|[filter_relationships](#filter_relationships)(object : Object, function_name : string)
Array|[get_relationships](#get_relationships)()

### Method Descriptions

* <a name="filter_relationships"></a> Array filter_relationships(object : Object, function_name : string)

Fetches the users relationships and filters them using the provided function of the provided object. 
                The function has to a GodotcordRelationship as parameter and must return a boolean. The boolean indicates whether the relationship should be included in the list or not.
                Returns an array containing all filtered relationships.

----
* <a name="get_relationships"></a> Array get_relationships()

Returns an array containing all relationships using the last filter.

----
