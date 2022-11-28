#pragma once

#include <string>

namespace pong
{

enum class FontType : uint8_t
{
  sans_serif = 0,
};

// @returns path to the specified font type.
std::string font_path(const FontType font_type);

} // end namespace pong
