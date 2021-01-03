Write-Output "Adding #include <cstdint> to types.h"
(Get-Content .\discord-files\types.h).replace("#pragma once", "#pragma once`r`n#include <cstdint>") | Set-Content .\discord-files\types.h
Write-Output "Done! Setup complete."