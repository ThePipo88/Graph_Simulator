
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(700, 700), "SFML works!");
    RectangleShape line(sf::Vector2f(150, 5));
    line.rotate(70);
    line.setPosition(Vector2f(150, 150));
    line.setFillColor(Color::Green);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(line);
        window.display();
    }

    return 0;
}
