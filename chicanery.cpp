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
using sf::RenderWindow;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int squareWindowSize = 750;

class Game {
  public:
    //sf Objects
    sf::Font coolFont;
    sf::Event event;
    sf::CircleShape pizzaCrust;
    sf::Text screenText;
    sf::Music gameSounds;
    vector<sf::Sprite> screenAssets;
    sf::RenderWindow* gameWindow;

    //other var
    bool isStageOver;

    void configurePizzaCrust(int radius, sf::Color pizzaColor, float xCoord, float yCoord) {
        pizzaCrust.setRadius(radius);
        pizzaCrust.setFillColor(pizzaColor);
        pizzaCrust.setPosition(xCoord, yCoord);
    }

    void configureScreenText(int fontSize, sf::Color textColor, string text) {
        coolFont.loadFromFile("Apple Chancery.ttf");
        screenText.setFont(coolFont);
        screenText.setCharacterSize(fontSize);
        screenText.setFillColor(textColor);
        screenText.setString(text);
    }

    Game(RenderWindow* theWindow) {
        gameWindow = theWindow;
        isStageOver = false;
        while (gameWindow->pollEvent(event)) if (event.type == sf::Event::Closed) gameWindow->close();
    }
};

class Prologue: public Game {
  public:
    sf::Texture logo;
    sf::Sprite logoSprite;
    Prologue(RenderWindow* theWindow) : Game(theWindow) {
        logo.loadFromFile("pizza_logo.avif");
        //puts the logo in each four corners of the Prologue Screen
        for (int i = 0; i < 4; i++) {
            vector<int> coords = {10, int(squareWindowSize) - 10};
            int z = coords.at(i/2);
            sf::Sprite aLogo(logo);
            aLogo.setPosition(z, z);
            screenAssets.push_back(aLogo);
        }
        string welcomeText = "Welcome to Raising Chicanery's Pizza! \n Press enter \n to go into our fine establishment";
        configureScreenText(30, sf::Color::White, welcomeText);

        gameSounds.openFromFile(""); // fix path

        while(!isStageOver) {
            for (auto asset : screenAssets) gameWindow->draw(asset);
            gameWindow->draw(screenText);
            gameWindow->display();
            while (gameWindow->pollEvent(event)) 
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                    isStageOver = true;
        }
    }
};

class Intro: public Game {
  public:
    Intro(RenderWindow* theWindow) : Game(theWindow) {
        configurePizzaCrust(200, sf::Color::White, 175, 175);
    }
};

class Toppings: public Game {
  public:
    vector<sf::Sprite> toppings;
    Toppings(RenderWindow* theWindow, int charredness) : Game(theWindow) { //accepts int between 0 and 5
    //     if (event.type == sf::Event::MouseButtonPressed) {
    //         sf::CircleShape *shape = new sf::CircleShape(50);
    //         sf::Sprite *sprite = new sf::Sprite();
    //         sprite->setPosition(event.mouseButton.x,event.mouseButton.y);
    //         sprite->setFillColor(sf::Color(255, 1, 1));
    //         shapes.push_back(shape);
    //     }
    // }
    //             window.clear();

    //             for(auto it=shapes.begin();it!=shapes.end();it++)
    //             {
    //                 window.draw(**it);
    //             }
    
    }
};

class Endgame: public Game {
  public:
    Endgame(RenderWindow* theWindow) : Game(theWindow) {
    }
};

int main () {
    sf::RenderWindow mainWindow(sf::VideoMode(squareWindowSize, squareWindowSize), "Raising Chicanery's Pizza");
    Prologue stage1(&mainWindow);
    //Intro stage2(mainWindow); //pizza crust
    //Toppings stage3(mainWindow, stage2.getCrispiness());
    //Endgame stage4(mainWindow, stage3.getToppings());
    //while (mainWindow.pollEvent(mainEvent)) if (mainEvent.type == sf::Event::Closed) mainWindow.close();
    //cout << "VS PetCode is awesome" << "\n";
    //cout << "Welcome to Raising Chicanery! Watch our dog do some cool tricks: " << '\n';
    return 0;
}
