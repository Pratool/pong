#include "config_tools/config_tools.hh"

#include <SFML/Graphics.hpp>

int main()
{
  sf::Font sans_serif;
  if (!sans_serif.loadFromFile(pong::font_path(pong::FontType::sans_serif)))
  {
    return 1;
  }

  sf::RenderWindow window(sf::VideoMode(680, 400), "SFML works!");
  window.setVerticalSyncEnabled(true);

  sf::Text text;
  text.setFont(sans_serif);
  text.setString("This is printed");
  text.setCharacterSize(18);
  text.setFillColor(sf::Color::Magenta);
  text.setStyle(sf::Text::Bold);

  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(shape);
    window.draw(text);
    window.display();
  }

  return 0;
}
