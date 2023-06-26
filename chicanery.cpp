#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using std::cout;
using std::cin;
using std::string;
using std::to_string;
using std::stoi;

#include <SFML/Graphics.hpp>

int main () {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close();

        window.clear();
        window.draw(shape);
        window.display();
    }
    
    cout << "VS PetCode is awesome" << "\n";
    cout << "Welcome to Raising Chicanery! Watch our dog do some cool tricks: " << '\n';
    return 0;
}