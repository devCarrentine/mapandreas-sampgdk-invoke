#ifndef MAPANDREAS_H
#define MAPANDREAS_H

#include <string_view>
#include <cstdint>

namespace mapandreas
{
  // The map mode that determines its size and detail.
  enum class Mode
  {
    kNone,
    kMinimal,
    kMedium,
    kFull,
    kNoBuffer
  };

  // The default path to the full map.
  constexpr auto kHmapFileFull{"scriptfiles/SAfull.hmap"};

  // The default path to the minimal map.
  constexpr auto kHmapFileMinimal{"scriptfiles/SAmin.hmap"};

  /**
   * @brief Initializes the MapAndreas plugin.
   * @param mode The map mode that determines its size and detail.
   * @param hmapFile The path to the file that holds the map is in .hmap format.
   * @return If successful, then true, otherwise false.
  */
  bool Initialize(
    const Mode mode = Mode::kFull, 
    const std::string_view& hmapFile = kHmapFileFull);

  /**
   * @brief Unloads the MapAndreas plugin.
   * @param hmapFile The path to the file that holds the map is in .hmap format.
   * @param message Message when unloading.
   * @return If successful, then true, otherwise false.
  */
  bool Unload(
    const std::string_view& hmapFile, 
    const std::string_view& message);

  /**
   * @brief 
   * @param hmapFile 
   * @return 
  */
  bool saveCurrentHmap(
    const std::string_view& hmapFile);

  /**
   * @brief Finds the Z coordinate at x and y.
   * 
   * Limitations:
   * - San Andreas is a 3D world, although the output provided by this plugin only represents a single dimension. It will only return the highest Z co-ord for the X,Y position you provide. As an example, someone could be standing underneath a bridge and you won't be able to find the ground level which they are standing on. That means it's valid for a player to be beneath the highest ground level. Although using a height map has some serious drawbacks compared to 3D data, it is extremely fast and you can call this function almost as often as you like.
   * - The Z return value is accurate to 1.0 square world unit (1m²) for the entire San Andreas landmass (6km²).
   * - The Z return value is accurate to within a few centimeters from the actual ground surface position.
   * - There is no data about heights below sea level (0.0Z). The function will always return 0.0 for those areas.
   * - There are parts of San Andreas below sea level that do not contain water. ie the quarry in LV and the underground airport terminal in LS.
   * - The SA map has small holes in some places. They are fairly rare, although these holes are often not big enough to fall through. The function will return 0.0 for these co-ords. You can potentially check neighbouring co-ordinates if you want to check if the 0.0 return value is a hole.
   * - This works only in interior 0 (main SA world) and cannot handle areas with custom objects.
   * 
   * @param x X-coordinate.
   * @param y Y-coordinate.
   * @param z Variable to which, if the calculation is successful, the z-coordinate will be written.
   * @return If successful, then true, otherwise false.
  */
  bool findZFor2dCoord(
    const float x, 
    const float y, 
    float& z);

  /**
   * @brief Finds the average Z-coordinate at x and y.
   * @param x X-coordinate.
   * @param y Y-coordinate.
   * @param z Variable to which, if the calculation is successful, the z-coordinate will be written.
   * @return If successful, then true, otherwise false.
  */
  bool findAverageZ(
    const float x, 
    const float y, 
    float& z);

  /**
   * @brief Sets the Z-coordinate to the position at x and y.
   * @param x X-coordinate.
   * @param y Y-coordinate.
   * @param z Z-coordinate.
   * @return If successful, then true, otherwise false.
  */
  bool setZFor2dCoord(
    const float x, 
    const float y, 
    const float z);
}

#endif // MAPANDREAS_H
