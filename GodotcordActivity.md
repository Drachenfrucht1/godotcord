# GodotcordActivity

## GDScript methods/properties

`String state`  
`String details`  
`String largeImage`  
`String largeText`

- tooltip for the large image

`String smallImage`  
`String smallText`

- tooltip for the small image

`String partyID`

- the id of the lobby the user is in

`int partyMax`

- the max size of the party the user is in

`int partyCurrent`

- the current size of the party the user is in

`String matchSecret`  
`String joinSecret`

- secret used for chat invitations and ask to join
  
`String spectateSecret`  
`int start`

- unix starttime of the users activity

`int end`

- unix endtime of the users activity

## Usage

This class is used together with the GodotcordActivtyManager to update the user's Game Activity.