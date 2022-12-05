#include "kinematics/paddle.hh"

#include <algorithm>

namespace pong
{

Paddle::Paddle(const float x_position_px, const uint32_t frame_height_px, const uint32_t height_px)
  : x_position_px_{x_position_px}
  , frame_height_px_{static_cast<float>(frame_height_px)}
  , height_px_{static_cast<float>(height_px)}
  , speed_px_per_sec_{frame_height_px / static_cast<float>(std::chrono::nanoseconds(std::chrono::seconds(1)).count())}
{
}

[[nodiscard]] const float& Paddle::x_position_px() const noexcept
{
  return x_position_px_;
}

[[nodiscard]] const float& Paddle::y_position_px() const noexcept
{
  return y_position_px_;
}

[[nodiscard]] const float& Paddle::height_px() const noexcept
{
  return height_px_;
}

[[nodiscard]] sf::Vector2f Paddle::update(const uint64_t elapsed_ns, const PaddleDirection direction) noexcept
{
  const float adjustment{elapsed_ns * speed_px_per_sec_};
  switch (direction)
  {
    case PaddleDirection::up:
      y_position_px_ = std::max(y_position_px_ - adjustment, 0.0f);
      break;
    case PaddleDirection::down:
      y_position_px_ = std::min(y_position_px_ + adjustment, frame_height_px_ - height_px_);
      break;
  }
  return sf::Vector2f(x_position_px_, y_position_px_);
}

}  // end namespace pong
