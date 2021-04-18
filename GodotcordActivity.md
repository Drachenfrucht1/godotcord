# GodotcordActivity

## GDScript methods/properties

`String state`  

- State of the activity if any.
`String details`  

- Details of the activity if any.

`String large_image`  

- Name of the image in the art assets of your application in Discord Developer Portal to use as a large image if any.

`String large_text`

- Tooltip of the large image, only applicable if you provide large_image

`String small_image`

- Name of the image in the art assets of your application in Discord Developer Portal to use as a small image if any.

`String small_text`

- Tooltip for the small image, only applicable if you provide small_image

`String party_id`

- The id of the lobby the user is in

`int party_max`

- the max size of the party the user is in

`int party_current`

- the current size of the party the user is in

`String match_secret`  

- Secret used for joining matches.

`String join_secret`

- Secret used for chat invitations and ask to join
  
`String spectate_secret`  

- Secret used for spectating matches.

`int start`

- Unix starttime of the users activity

`int end`

- Unix endtime of the users activity

## Usage

This class is used together with the GodotcordActivtyManager to update the user's Game Activity.
