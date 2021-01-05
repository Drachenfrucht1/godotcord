# GodotcordActivity

## GDScript methods/properties

`String state`<br>
`String details`<br>
`String largeImage`<br>
`String largeText`
- tooltip for the large image

`String smallImage`<br>
`String smallText`
- tooltip for the small image

`String partyID`
- the id of the lobby the user is in

`int partyMax`
- the max size of the party the user is in

`int partyCurrent`
- the current size of the party the user is in

`String matchSecret`<br>
`String joinSecret`
- secret used for chat invitations and ask to join
  
`String spectateSecret`<br>
`int start`
- unix starttime of the users activity

`int end`
- unix endtime of the users activity

## Usage
This class is used together with the GodotcordActivtyManager to update the user's Game Activity.