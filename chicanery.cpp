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
using std::vector;
using sf::Mouse;
using sf::Color;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game {
  public:
    //sf Objects
    sf::Event event;
    sf::RenderWindow window;//(sf::VideoMode(1500, 1500), "Raising Chicanery's Pizza");
    sf::CircleShape pizzaCrust;
    sf::Text welcomeText;

    //Bools
    bool isOver;

    void configurePizzaCrust(int radius, Color pizzaColor, float xCoord, float yCoord) {
        pizzaCrust.setRadius(radius);
        pizzaCrust.setFillColor(pizzaColor);
        pizzaCrust.setPosition(xCoord, yCoord);
    }

    Game(int windowSize = 1500) {
       isOver = false;
       configurePizzaCrust(500, Color::White, 250, 250);
       //construct window;
    }
    
};

class Prologue: public Game {
  public:
    sf::Font coolFont;
    sf::Texture logo;
    vector<sf::Sprite> logos;

    Prologue() {
        coolFont.loadFromFile("Apple Chancery.ttf");
        logo.loadFromFile("file"); //fix later
        for (int i = 0; i < 4; i++) {
            vector<int> coords = {50, int(window.getSize().x) - 50};
            int z = coords.at(i/2);
            sf::Sprite aLogo(logo);
            aLogo.setPosition(z, z);
        }
        welcomeText.setFont(coolFont);
        welcomeText.setCharacterSize(60);
        welcomeText.setFillColor(sf::Color::White);
        welcomeText.setString("Welcome to Raising Chicanery's Pizza! \n Press enter \n to go into ourfine establishment");
    }
    
};

class Intro: public Game {
  public:
    
};

class Toppings: public Game {
  public:
    
};

class Endgame: public Game {
  public:
    Endgame() {
    sf::Texture texture;
    texture.loadFromFile("bad_ending.jpg");
    sf::Sprite endingSprite(texture);
    }
    
};

int main () {
    




    while (window.isOpen()) {
        while (window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close();

        window.draw(welcomeText);
        window.display();

        bool finishedPrologue = false;
        bool finishedIntro = false;
        bool finishedToppings = false;
        bool finishedPizza = false;

        //initialized Prologue screen here
        while(!finishedPrologue) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) finishedPrologue = true;
        }
        window.clear();

        //initialized Intro screen here
        while(!finishedIntro) {

        }
        window.clear();

        //initialized Intro screen here
        while(!finishedToppings) {

        }
        window.clear();

        if (Mouse::isButtonPressed(sf::Mouse::Left)) {
            cout << "Left button was pressed so fire fire fire!";
        }

        
        //Add Shape on Click Code
        switch (event.type) {
            case sf::Event::Closed: {
                window.close();
                return 0;
            }
            case sf::Event::MouseButtonPressed: {
                sf::CircleShape *shape = new sf::CircleShape(50);
                shape->setPosition(event.mouseButton.x,event.mouseButton.y);
                shape->setFillColor(sf::Color(255, 1, 1));
                shapes.push_back(shape);
            } 
        }
    }

                window.clear();

                for(auto it=shapes.begin();it!=shapes.end();it++)
                {
                    window.draw(**it);
                }


        window.clear();
        window.draw(pizzaCrust);
        window.draw(endingSprite);
        //window.draw(texture);
        window.display();
    
    cout << "VS PetCode is awesome" << "\n";
    cout << "Welcome to Raising Chicanery! Watch our dog do some cool tricks: " << '\n';
    return 0;
}

