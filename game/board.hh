#pragma once

#include <cstdint>
#include <cmath>

namespace pong
{

[[nodiscard]] constexpr uint32_t score_font_size_px(const uint32_t window_width_px);
[[nodiscard]] constexpr uint32_t score_vertical_position_px(const uint32_t window_width_px);
[[nodiscard]] constexpr uint32_t left_score_position(const uint32_t window_width_px);
[[nodiscard]] constexpr uint32_t right_score_position(const uint32_t window_width_px);
[[nodiscard]] constexpr uint32_t side_divider_width_px(const uint32_t window_width_px);
[[nodiscard]] constexpr uint32_t side_divider_position(const uint32_t window_width_px);
[[nodiscard]] constexpr float ball_radius_px(const uint32_t window_width_px);
[[nodiscard]] constexpr uint32_t ball_point_count(const uint32_t window_width_px);
[[nodiscard]] constexpr uint32_t paddle_width_px(const uint32_t window_width_px);
[[nodiscard]] constexpr uint32_t paddle_height_px(const uint32_t window_height_px);
[[nodiscard]] constexpr uint32_t left_paddle_position();
[[nodiscard]] constexpr uint32_t right_paddle_position(const uint32_t window_width_px);

}  //  namespace pong

#include "board.inl"
