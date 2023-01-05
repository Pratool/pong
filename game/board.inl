#include <cstdint>
#include <cmath>

namespace
{

constexpr double nominal_window_width_px = 680.0;
constexpr double nominal_window_height_px = 480.0;

}  // end anonymous namespace

namespace pong
{

[[nodiscard]] constexpr uint32_t score_font_size_px(const uint32_t window_width_px)
{
  constexpr double nominal_score_font_size_px = 18.0;
  return (nominal_score_font_size_px / nominal_window_width_px) * window_width_px;
}

[[nodiscard]] constexpr uint32_t score_vertical_position_px(const uint32_t window_width_px)
{
  return score_font_size_px(window_width_px);
}

[[nodiscard]] constexpr uint32_t left_score_position(const uint32_t window_width_px)
{
  return (window_width_px / 2) - (2 * score_font_size_px(window_width_px));
}

[[nodiscard]] constexpr uint32_t right_score_position(const uint32_t window_width_px)
{
  const auto font_size = score_font_size_px(window_width_px);
  return (window_width_px / 2) + (font_size / 3) + font_size;
}

[[nodiscard]] constexpr uint32_t side_divider_width_px(const uint32_t window_width_px)
{
  constexpr double nominal_width_px = 2.0;
  return (nominal_width_px / nominal_window_width_px) * window_width_px;
}

[[nodiscard]] constexpr uint32_t side_divider_position(const uint32_t window_width_px)
{
  return (window_width_px / 2) - (side_divider_width_px(window_width_px) / 2);
}

[[nodiscard]] constexpr float ball_radius_px(const uint32_t window_width_px)
{
  constexpr double nominal_width_px = 10.0;
  return (nominal_width_px / nominal_window_width_px) * window_width_px;
}

[[nodiscard]] constexpr uint32_t ball_point_count(const uint32_t window_width_px)
{
  constexpr double nominal_count = 30.0;
  constexpr float nominal_ball_radius_px = 15.0f;
  return (nominal_count / nominal_ball_radius_px) * ball_radius_px(window_width_px);
}

[[nodiscard]] constexpr uint32_t paddle_width_px(const uint32_t window_width_px)
{
  return ball_radius_px(window_width_px) / 2.0;
}

[[nodiscard]] constexpr uint32_t paddle_height_px(const uint32_t window_height_px)
{
  constexpr double nominal_height_px = 48.0;
  return (nominal_height_px / nominal_window_height_px) * window_height_px;
}

[[nodiscard]] constexpr uint32_t left_paddle_position()
{
  return 1;
}

[[nodiscard]] constexpr uint32_t right_paddle_position(const uint32_t window_width_px)
{
  return window_width_px - paddle_width_px(window_width_px) - 1;
}

}  //  namespace pong
