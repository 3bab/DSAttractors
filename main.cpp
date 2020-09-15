#include <SFML/Graphics.hpp>
#include "LA/LorenzAttractor.h"

int main() { /// Create a window

    sf::RenderWindow window;//(sf::VideoMode(1980, 1080), "SFML Application", sf::Style::Default);

    window.create(sf::VideoMode(1980, 1080), "Coding Projects", sf::Style::Default, sf::ContextSettings()); window.setPosition(sf::Vector2i(0, 0));
    window.setVerticalSyncEnabled(true); window.setFramerateLimit(60);
        LorenzAttractor l;
        l.run(window);
        /*
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

    }
         */
    return 0;
}
