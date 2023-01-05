#include "board.hh"
#include "config_tools/config_tools.hh"
#include "kinematics/paddle.hh"
#include "kinematics/ball.hh"

#include <SFML/Graphics.hpp>

#include <array>
#include <chrono>
#include <cstdint>
#include <cmath>

namespace
{

constexpr uint32_t window_width_px = 680U*2;
constexpr uint32_t window_height_px = 480U*2;

}  // end anonymous namespace

enum class GameState : uint8_t
{
  start = 0,
  end,
  play
};

struct KinematicState
{
  using Clock = std::chrono::high_resolution_clock;
  using Timepoint = std::chrono::time_point<Clock>;

  Timepoint last_update;
  GameState state{GameState::start};
};

int main()
{
  using namespace pong;
  KinematicState::Clock clock;
  KinematicState kstate;
  kstate.last_update = clock.now();

  sf::Font sans_serif;
  if (!sans_serif.loadFromFile(pong::font_path(pong::FontType::sans_serif)))
  {
    return 1;
  }

  sf::RenderWindow window(sf::VideoMode(::window_width_px, ::window_height_px), "Pong");
  window.setVerticalSyncEnabled(true);

  sf::RectangleShape side_divider(sf::Vector2f(side_divider_width_px(window_width_px), ::window_height_px));
  side_divider.setPosition(side_divider_position(window_width_px), 0);

  sf::Text left_score;
  left_score.setFont(sans_serif);
  left_score.setCharacterSize(score_font_size_px(window_width_px));
  left_score.setFillColor(sf::Color::White);
  left_score.setStyle(sf::Text::Bold);
  left_score.setString("0");
  left_score.setPosition(left_score_position(window_width_px), score_vertical_position_px(window_width_px));

  sf::Text right_score;
  right_score.setFont(sans_serif);
  right_score.setCharacterSize(score_font_size_px(window_width_px));
  right_score.setFillColor(sf::Color::White);
  right_score.setStyle(sf::Text::Bold);
  right_score.setString("0");
  right_score.setPosition(right_score_position(window_width_px), score_vertical_position_px(window_width_px));

  pong::Ball ball(
    ball_radius_px(window_width_px),
    0.7 * std::sqrt((static_cast<double>(::window_height_px)*::window_height_px) + (::window_width_px*::window_width_px))
              / std::chrono::nanoseconds(std::chrono::seconds(1)).count(),
    sf::Vector2f(0.4472135954999579, -0.8944271909999159),
    sf::Vector2f(300, 300)
  );
    
  sf::CircleShape ball_shape(ball_radius_px(window_width_px));
  ball_shape.setFillColor(sf::Color::White);
  ball_shape.setPointCount(ball_point_count(window_width_px));
  ball_shape.setPosition(ball.update(1));

  pong::Paddle lpaddle(left_paddle_position(), ::window_height_px, paddle_height_px(window_width_px));
  sf::RectangleShape left_paddle(sf::Vector2f(paddle_width_px(window_width_px), paddle_height_px(window_width_px)));
  left_paddle.setPosition(lpaddle.update(0, pong::PaddleDirection::up));

  pong::Paddle rpaddle(right_paddle_position(window_width_px), ::window_height_px, paddle_height_px(window_width_px));
  sf::RectangleShape right_paddle(sf::Vector2f(paddle_width_px(window_width_px), paddle_height_px(window_width_px)));
  right_paddle.setPosition(rpaddle.update(0, pong::PaddleDirection::up));

  sf::Text start_text;
  start_text.setFont(sans_serif);
  start_text.setCharacterSize(score_font_size_px(window_width_px));
  start_text.setFillColor(sf::Color::White);
  start_text.setStyle(sf::Text::Bold);
  start_text.setString("Hit W to begin game");
  start_text.setPosition(right_score_position(window_width_px), score_vertical_position_px(window_width_px));

  auto end_text = start_text;
  end_text.setString("Game Over\nHit W to begin game");

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (kstate.state == GameState::start)
    {
      kstate.last_update = clock.now();
      window.clear();
      window.draw(start_text);
      window.display();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      {
        kstate.state = GameState::play;
      }
      continue;
    }

    if (kstate.state == GameState::end)
    {
      kstate.last_update = clock.now();
      window.clear();
      window.draw(end_text);
      window.display();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      {
        kstate.state = GameState::play;
      }
      continue;
    }

    if (auto update_time = clock.now(); update_time - kstate.last_update > std::chrono::milliseconds(15))
    {
      const auto update_duration = (update_time - kstate.last_update).count();
      kstate.last_update = std::move(update_time);

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      {
        left_paddle.setPosition(lpaddle.update(update_duration, pong::PaddleDirection::up));
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
      {
        left_paddle.setPosition(lpaddle.update(update_duration, pong::PaddleDirection::down));
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {
        right_paddle.setPosition(rpaddle.update(update_duration, pong::PaddleDirection::up));
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
        right_paddle.setPosition(rpaddle.update(update_duration, pong::PaddleDirection::down));
      }

      auto ball_position = ball.update(update_duration);
      const bool ball_going_right = ball.direction().x > 0;
      const bool ball_going_down = ball.direction().y > 0;
      if (ball_position.x <= lpaddle.x_position_px() && !ball_going_right)
      {
        if (ball_position.y <= lpaddle.y_position_px() + lpaddle.height_px()
            && ball_position.y + 2*ball.radius_px() >= lpaddle.y_position_px())
        {
          ball_position = ball.bounce_from(pong::Side::horizontal, update_duration);
        }
        else
        {
          right_score.setString("Game over");
          kstate.state = GameState::end;
          continue;
        }

      }
      else if (ball_position.x + 2*ball.radius_px() >= rpaddle.x_position_px() && ball_going_right)
      {
        if (ball_position.y <= rpaddle.y_position_px() + rpaddle.height_px()
            && ball_position.y + 2*ball.radius_px() >= rpaddle.y_position_px())
        {
          ball_position = ball.bounce_from(pong::Side::horizontal, update_duration);
        }
        else
        {
          right_score.setString("Game over");
          kstate.state = GameState::end;
          continue;
        }
      }
      else if ((ball_position.y <= 0.0f && !ball_going_down)
               || (ball_position.y + 2*ball.radius_px() >= ::window_height_px && ball_going_down))
      {
        ball_position = ball.bounce_from(pong::Side::vertical, update_duration);
      }

      ball_shape.setPosition(std::move(ball_position));
    }

    window.clear();
    window.draw(ball_shape);
    window.draw(left_score);
    window.draw(right_score);
    window.draw(side_divider);
    window.draw(left_paddle);
    window.draw(right_paddle);
    window.display();
  }

  return 0;
}
