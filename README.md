# mapandreas-sampgdk-invoke

# Content
0. [Brief](#Brief).
1. [Important](#Important).
2. [Possible uses](#PossibleUses).
    1. [Teleporting](#Teleporting).
    2. [Anti-cheat](#Anti-cheat).
    3. [Dynamic object placement](#DynamicObjectPlacement).
3. [namespace mapandreas](#mapandreas).
    1. [* Limitations of findZFor2dCoord(...)](#Limitations).
    2. [Dependencies](#Dependencies).
    3. [Questions](#Questions).

<a name="Brief"></a>
### A thing for calling MapAndreas functions via sampgdk.
MapAndreas plugin is designed to read provided data regarding the San Andreas map and provide that information to SA-MP plugins.

This version contains a height map of the San Andreas geometry and provides a function to obtain the highest ground position from a provided 2D point. It is expected that future versions could include other types of maps, such as water maps and road maps.

<a name="Important"></a>
### Important: MapAndreas plugin uses approximately 70MB of RAM. If you are using shared hosting or a VPS, please confirm with your host that this is okay. A version that uses less RAM is there although it won't have the same level of accuracy.

<a name="PossibleUses"></a>
# Possible uses

MapAndreas plugin potentially has many uses although here are some obvious examples:

<a name="Teleporting"></a>
### Teleporting
When the server wants to teleport a player or vehicle to another player, right now the scripts will usually pick a point on the same Z position as the other player. It is only luck most of the time that prevents you from being teleported in to a building or wall, or even below the ground. Using the data made available by this plugin, the server could search around player to find a suitable ground position for teleporting.

<a name = "Anti-cheat"></a>
### Anti-cheat
Using MapAndreas plugin you can tell the difference between someone still on top of a building and someone still floating in the air.

<a name = "DynamicObjectPlacement"></a>
### Dynamic object placement
You can potentially use MapAndreas plugin to determine the ground position around a player for placing objects.
 
<a name = "mapandreas"></a>
# namespace mapandreas
|Name|Params|Return|
|-------|-------|:-----:|
|Initialize|const mapandreas::Mode mode, const std::string_view& hmapFile|bool (false failed/true success)|
|Unload|const std::string_view& hmapFile, const std::string_view& message|bool (false failed/true success)|
|saveCurrentHmap|const std::string_view& hmapFile|bool (false failed/true success)|
|findZFor2dCoord *|const float x, const float y, float& z|bool (false failed/true success)|
|findAverageZ|const float x, const float y, float& z|bool (false failed/true success)|
|setZFor2dCoord|const float x, const float y, const float z|bool (false failed/true success)|

<a name = "Limitations"></a>
### * Limitations of findZFor2dCoord(...)

- San Andreas is a 3D world, although the output provided by this plugin only represents a single dimension. It will only return the highest Z co-ord for the X,Y position you provide. As an example, someone could be standing underneath a bridge and you won't be able to find the ground level which they are standing on. That means it's valid for a player to be beneath the highest ground level. Although using a height map has some serious drawbacks compared to 3D data, it is extremely fast and you can call this function almost as often as you like.
- The Z return value is accurate to 1.0 square world unit (1mІ) for the entire San Andreas landmass (6kmІ).
- The Z return value is accurate to within a few centimeters from the actual ground surface position.
- There is no data about heights below sea level (0.0Z). The function will always return 0.0 for those areas.
- There are parts of San Andreas below sea level that do not contain water. ie the quarry in LV and the underground airport terminal in LS.
- The SA map has small holes in some places. They are fairly rare, although these holes are often not big enough to fall through. The function will return 0.0 for these co-ords. You can potentially check neighbouring co-ordinates if you want to check if the 0.0 return value is a hole.
- This works only in interior 0 (main SA world) and cannot handle areas with custom objects.

<a name = "Dependencies"></a>
### Dependencies
- MapAndreas: https://github.com/philip1337/samp-plugin-mapandreas
- sampgdk: https://github.com/Zeex/sampgdk

<a name = "Questions"></a>
### Questions
- ### Doesn't compile, gives an error.
- Look at the second line of mapandreas.cpp. Make sure you put the path to sampgdk in your compilation settings. Otherwise change this path to your own.
- ### It compiles, but it doesn't work. What to do?
- Make sure that you have loaded the mapandreas plugin into the plugins folder and connected it in the server settings. Check the scriptfiles folder, there should be a file SAfull.hmap. Otherwise, download it from the official repository.
