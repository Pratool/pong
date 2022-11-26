#include "config_tools/config_tools.hh"

#include <filesystem>

namespace
{

inline std::filesystem::path sys_root()
{
  // Intended to be run on Linux.  /proc/self/exe is a symbolic link to the executable running.
  return std::filesystem::canonical("/proc/self/exe").parent_path().parent_path();
}

inline std::filesystem::path resources_path()
{
  return sys_root() / "resources";
}

inline std::string generate_font_path(const std::string_view file_name)
{
  return (resources_path() / "fonts" / file_name).string();
}

} // end anonymous namespace

namespace pong
{

std::string font_path(const FontType font_type)
{
  switch (font_type)
  {
    case FontType::sans_serif:
      return generate_font_path("sans_serif.otf");
    // Do not specify default to permit compiler warning if enum value is unhandled.
  }

  return "";
}

} // end namespace pong
