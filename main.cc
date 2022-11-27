#include "config_tools/config_tools.hh"

#include <SFML/Graphics.hpp>

#include <cstdint>

namespace
{

constexpr double nominal_window_width_px = 680.0;
constexpr double nominal_window_height_px = 480.0;
constexpr uint32_t window_width_px = 680U;
constexpr uint32_t window_height_px = 480U;

constexpr uint32_t score_font_size_px()
{
  constexpr double nominal_score_font_size_px = 18.0;
  return (nominal_score_font_size_px / nominal_window_width_px) * window_width_px;
}

constexpr uint32_t score_vertical_position()
{
  return score_font_size_px();
}

constexpr uint32_t left_score_position()
{
  return (window_width_px / 2) - (2 * score_font_size_px());
}

constexpr uint32_t right_score_position()
{
  return (window_width_px / 2) + (score_font_size_px() / 3) + score_font_size_px();
}

constexpr uint32_t side_divider_width_px()
{
  constexpr double nominal_width_px = 2.0;
  return (nominal_width_px / nominal_window_width_px) * window_width_px;
}

constexpr uint32_t side_divider_position()
{
  return (window_width_px / 2) - (side_divider_width_px() / 2);
}

constexpr float ball_radius_px()
{
  constexpr double nominal_width_px = 10.0;
  return (nominal_width_px / nominal_window_width_px) * window_width_px;
}

constexpr uint32_t ball_point_count()
{
  constexpr double nominal_count = 30.0;
  constexpr float nominal_ball_radius_px = 15.0f;
  return (nominal_count / nominal_ball_radius_px) * ball_radius_px();
}

constexpr uint32_t paddle_width_px()
{
  return ball_radius_px() / 2.0;
}

constexpr uint32_t paddle_height_px()
{
  constexpr double nominal_height_px = 48.0;
  return (nominal_height_px / nominal_window_height_px) * window_height_px;
}

constexpr uint32_t left_paddle_position()
{
  return 1;
}

constexpr uint32_t right_paddle_position()
{
  return window_width_px - paddle_width_px() - 1;
}


}  // end anonymous namespace

int main()
{
  sf::Font sans_serif;
  if (!sans_serif.loadFromFile(pong::font_path(pong::FontType::sans_serif)))
  {
    return 1;
  }

  sf::RenderWindow window(sf::VideoMode(::window_width_px, ::window_height_px), "Pong");
  window.setVerticalSyncEnabled(true);

  sf::RectangleShape side_divider(sf::Vector2f(side_divider_width_px(), ::window_height_px));
  side_divider.setPosition(side_divider_position(), 0);

  sf::Text left_score;
  left_score.setFont(sans_serif);
  left_score.setCharacterSize(score_font_size_px());
  left_score.setFillColor(sf::Color::White);
  left_score.setStyle(sf::Text::Bold);
  left_score.setString("0");
  left_score.setPosition(left_score_position(), score_vertical_position());

  sf::Text right_score;
  right_score.setFont(sans_serif);
  right_score.setCharacterSize(score_font_size_px());
  right_score.setFillColor(sf::Color::White);
  right_score.setStyle(sf::Text::Bold);
  right_score.setString("0");
  right_score.setPosition(right_score_position(), score_vertical_position());

  sf::CircleShape ball(ball_radius_px());
  ball.setFillColor(sf::Color::White);
  ball.setPointCount(ball_point_count());

  sf::RectangleShape left_paddle(sf::Vector2f(paddle_width_px(), paddle_height_px()));
  left_paddle.setPosition(sf::Vector2f(left_paddle_position(), 0));

  sf::RectangleShape right_paddle(sf::Vector2f(paddle_width_px(), paddle_height_px()));
  right_paddle.setPosition(sf::Vector2f(right_paddle_position(), 0));

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(ball);
    window.draw(left_score);
    window.draw(right_score);
    window.draw(side_divider);
    window.draw(left_paddle);
    window.draw(right_paddle);
    window.display();
  }

  return 0;
}
