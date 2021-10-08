
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
    int cant = 0;
    float x1, y1;
    float x2, y2;
    RenderWindow window(VideoMode(700, 700), "SFML works!");
    RectangleShape line(sf::Vector2f(150, 5));
    line.rotate(70);
    line.setPosition(Vector2f(150, 150));
    line.setFillColor(Color::Green);


    sf::Vertex lines;

    
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
             
            if (event.type == Event::MouseButtonPressed) {
                cant++;
                if (cant == 1) {
                    x1 = Mouse::getPosition(window).x;
                    y1 = Mouse::getPosition(window).y;
                }
                else if (cant == 2) {
                    x2 = Mouse::getPosition(window).x;
                    y2 = Mouse::getPosition(window).y;
                }
                else if (cant == 3) {
                    cant = 0;
                }

                cout << Mouse::getPosition(window).x << " , " << Mouse::getPosition(window).y << endl;
            }
        }

        window.clear();
        if (cant == 2) {

            sf::Vertex lines[] =
            {
                sf::Vertex(sf::Vector2f(x1, y1)),
                sf::Vertex(sf::Vector2f(x2, y2))
            };

            window.draw(lines, 2, sf::Lines);
        }
        
        window.display();
    }

    return 0;
}
