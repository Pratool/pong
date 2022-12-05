#include "kinematics/ball.hh"

#include <algorithm>

namespace pong
{

Ball::Ball(const float radius_px, const float speed_px_per_sec, sf::Vector2f&& unit_direction, sf::Vector2f&& position)
  : radius_px_{radius_px}
  , speed_px_per_sec_{speed_px_per_sec}
  , unit_direction_{std::move(unit_direction)}
  , position_px_{std::move(position)}
{
}

[[nodiscard]] const float& Ball::radius_px() const noexcept
{
  return radius_px_;
}

[[nodiscard]] const sf::Vector2f& Ball::direction() const noexcept
{
  return unit_direction_;
}

[[nodiscard]] sf::Vector2f Ball::update(const uint64_t elapsed_ns) noexcept
{
  const auto adjustment = unit_direction_ * (elapsed_ns * speed_px_per_sec_);
  position_px_ += adjustment;
  return position_px_;
}

[[nodiscard]] sf::Vector2f Ball::bounce_from(const Side side, const uint64_t elapsed_ns) noexcept
{
  switch (side)
  {
    case Side::vertical:
      unit_direction_.y *= -1.0f;
      break;
    case Side::horizontal:
      unit_direction_.x *= -1.0f;
      break;
  }

  return update(elapsed_ns);
}

}  // end namespace pong
