#pragma once

#include <SFML/System/Vector2.hpp>

#include <chrono>
#include <cstdint>

namespace pong
{

enum class PaddleDirection : uint8_t
{
  up = 0,
  down,
};

class Paddle
{
public:
  ~Paddle() = default;
  Paddle(const Paddle&) = default;
  Paddle(Paddle&&) = default;
  Paddle& operator=(const Paddle&) = default;
  Paddle& operator=(Paddle&&) = default;

  Paddle(const float x_position_px, const uint32_t frame_height_px, const uint32_t height_px);

  [[nodiscard]] sf::Vector2f update(const uint64_t elapsed_ns, const PaddleDirection direction) noexcept;

private:
  const float frame_height_px_;
  const float speed_px_per_sec_;
  const float height_px_;
  const float x_position_px_;
  float y_position_px_{0.0f};
};

}  // end namespace pong
