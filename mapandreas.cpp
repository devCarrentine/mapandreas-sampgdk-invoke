#include "mapandreas.h"
#include "sampgdk/sampgdk.h"

/**
 * @brief Invokes the sampgdk native.
 * @tparam T Return type.
 * @tparam ...Args Types of the arguments.
 * @param name Name of the native.
 * @param types String with types using sampgdk-format (see docs).
 * @param ...args Data that should be passed to native call.
 * @return If successful, then true, otherwise false.
*/
template <class T, class ... Args>
static T sampgdkInvokeNative(
  const std::string_view& name, 
  const std::string_view& types, 
  Args&& ... args)
{
  static AMX_NATIVE native{sampgdk::FindNative(name.data())};

  if (nullptr != native)
  {
    return static_cast<T>(
      sampgdk::InvokeNative(
        native, 
        types.data(), 
        std::forward<Args>(args) ...)
      );
  }

  sampgdk::logprintf(
    "[MapAndreas]" " " 
    "[" __FILE__ "]" " " 
    "Attempting to call a function that does not exist: %s", 
    __func__);

  return false;
}

bool mapandreas::Initialize(
  const Mode mode, 
  const std::string_view& hmapFile)
{
  return sampgdkInvokeNative<bool>(
    "MapAndreas_Init", "is", 
    mode, hmapFile.data());
}

bool mapandreas::Unload(
  const std::string_view& hmapFile, 
  const std::string_view& message)
{
  return sampgdkInvokeNative<bool>(
    "MapAndreas_Unload", "ss",
    hmapFile.data(), message.data());
}

bool mapandreas::saveCurrentHmap(
  const std::string_view& hmapFile)
{
  return sampgdkInvokeNative<bool>(
    "MapAndreas_SaveCurrentHMap", "s",
    hmapFile.data());
}

bool mapandreas::findZFor2dCoord(
  const float x, 
  const float y, 
  float& z)
{
  return sampgdkInvokeNative<bool>(
    "MapAndreas_FindZ_For2DCoord", "ffR",
    x, y, &z);
}

bool mapandreas::findAverageZ(
  const float x, 
  const float y, 
  float& z)
{
  return sampgdkInvokeNative<bool>(
    "MapAndreas_FindAverageZ", "ffR",
    x, y, &z);
}

bool mapandreas::setZFor2dCoord(
  const float x, 
  const float y, 
  const float z)
{
  return sampgdkInvokeNative<bool>(
    "MapAndreas_SetZ_For2DCoord", "fff",
    x, y, z);
}
