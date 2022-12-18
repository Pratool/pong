#pragma once

#include <SFML/System/Vector2.hpp>

#include <chrono>
#include <cstdint>

namespace pong
{

enum class Side : uint8_t
{
  vertical = 0,
  horizontal,
};

class Ball
{
public:
  ~Ball() = default;
  Ball(const Ball&) = default;
  Ball(Ball&&) = default;
  Ball& operator=(const Ball&) = delete;
  Ball& operator=(Ball&&) = delete;

  Ball(const float radius_px, const float speed_px_per_sec, sf::Vector2f&& unit_direction, sf::Vector2f&& position);

  [[nodiscard]] const float& radius_px() const noexcept;

  [[nodiscard]] const sf::Vector2f& direction() const noexcept;

  [[nodiscard]] sf::Vector2f update(const uint64_t elapsed_ns) noexcept;

  [[nodiscard]] sf::Vector2f bounce_from(const Side side, const uint64_t elapsed_ns) noexcept;

private:
  const float radius_px_;
  const float speed_px_per_sec_;

  sf::Vector2f unit_direction_;
  sf::Vector2f position_px_;
};

}  // end namespace pong
