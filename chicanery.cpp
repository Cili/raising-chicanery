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
using sf::Mouse;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main () {
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(1500, 1500), "Raising Chicanery's Pizza"); 

    //pizza
    sf::CircleShape pizza(500);
    pizza.setFillColor(sf::Color{210, 180, 140});
    pizza.setPosition(250, 250);

    //font
    sf::Font coolFont;
    coolFont.loadFromFile("Apple Chancery.ttf");

    //Welcome Text
    sf::Text welcomeText;
    welcomeText.setFont(coolFont);
    welcomeText.setCharacterSize(100);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setString("Welcome to Raising Chicanery's Pizza! \n Press enter to alight into our fine establishment");

    //bad_ending
    sf::Texture texture;
    texture.loadFromFile("bad_ending.jpg");
    sf::Sprite endingSprite(texture);

    while (window.isOpen()) {
        while (window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close();

        window.draw(welcomeText);
        window.display();

        bool hasStarted = false;
        while(!hasStarted) if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) hasStarted = true;;

        if (Mouse::isButtonPressed(sf::Mouse::Left)) {
            cout << "Left button was pressed so fire fire fire!";
        }

        
        window.clear();
        window.draw(pizza);
        window.draw(endingSprite);
        //window.draw(texture);
        window.display();
    }
    
    cout << "VS PetCode is awesome" << "\n";
    cout << "Welcome to Raising Chicanery! Watch our dog do some cool tricks: " << '\n';
    return 0;
}