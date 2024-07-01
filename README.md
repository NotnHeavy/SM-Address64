# SM-Address64

This is a temporary extension that provides a `int64_t` enum struct, containing the fields `low` and `high` in their respective order, respecting little-endianness. Provided is a few basic arithmetic natives, alongside addressing natives - the main point of this extension. These addressing natives provide basic addressing functionality within 64-bit SourceMod plugins, which may be necessary following the eventual transition of Team Fortress 2 from 32-bit to 64-bit.

The following addressing natives are exposed:
- LoadFromAddress64
- StoreToAddress64
- FromPseudoAddress
- ToPseudoAddress
- GetEntityAddress64

Hopefully a better solution will come round soon. There does exist this [extension as well](https://github.com/skial-com/port64/), for anyone curious.

## Why not use pseudo addresses?
Pseudo-addressing was a feature implemented in SourceMod's API as a consequence of SourcePawn only providing 32-bit cells. Pseudo addresses allocate 6 bits as an index, with the following 26 bits being a relative address. The index (0-63) is used in an internal table, which provides the absolute address of any internally loaded module's image base (such as server.dll/server_srv.so) referenced by the desired index. The relative address is added onto this, which is then used to create a complete address.

While this is decent enough for addressing subroutines in loaded modules, for things like SDKCalls and DHooks, the limitations are immediately met once you work with dynamically allocated memory, such as with entity addresses or other object pointers. This may be a problem for some plugin developers - hence this extension!

## Usage
You can either compile the extension yourself with `AMBuild`, or head over to the releases tab. Place the contents of the `addons` folder into your `addons` folder. You will want to take the include `addons/sourcemod/scripting/include/smaddress64.inc` and use it in your plugin development environment, in order to interface with the natives and the `int64_t` enum struct.

See `addons/sourcemod/csripting/smaddress64-test.sp` for some basic example code.
