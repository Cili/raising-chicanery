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
    vector<sf::Shape> screenShapes;

    //other var
    bool isStageOver;
    int charLevel; //char as in, charred as coal

    void configurePizzaCrust(int radius, sf::Color pizzaColor, int xCoord, int yCoord) {
        pizzaCrust.setRadius(radius);
        pizzaCrust.setFillColor(pizzaColor);
        pizzaCrust.setPosition(xCoord, yCoord);
    }

    void configureScreenText(int fontSize, sf::Color textColor, string text, int xCoord, int yCoord) {
        coolFont.loadFromFile("Apple Chancery.ttf");
        screenText.setFont(coolFont);
        screenText.setCharacterSize(fontSize);
        screenText.setFillColor(textColor);
        screenText.setPosition(xCoord, yCoord);
        screenText.setString(text);
    }

    Game(RenderWindow* theWindow) {
        gameWindow = theWindow;
        isStageOver = false;
    }
};

class Prologue: public Game {
  public:
    sf::Texture logo;
    sf::Texture tower;
    Prologue(RenderWindow* theWindow) : Game(theWindow) {
        logo.loadFromFile("pizza_Icon_larger.jpeg");
        tower.loadFromFile("pisaTower.jpg");
        //puts the logo in each four corners of the Prologue Screen
        for (int i = 0; i < 4; i++) {
            vector<int> xCoords = {10, int(squareWindowSize) - 70, 10, int(squareWindowSize) - 70};
            vector<int> yCoords = {10, 10, int(squareWindowSize) - 70, int(squareWindowSize) - 70};
            int x = xCoords.at(i);
            int y = yCoords.at(i);
            sf::Sprite aLogo;
            aLogo.setTexture(logo);
            aLogo.setPosition(x, y);
            screenAssets.push_back(aLogo);
        }
        //sets up towerimage
        sf::Sprite aTower;
        aTower.setTexture(tower);
        aTower.setPosition(int(squareWindowSize)/2, int(squareWindowSize)/ 3);
        aTower.rotate(-8);
        screenAssets.push_back(aTower);

        //sets up welcome txt
        string welcomeText = "Welcome to Raising Chicanery's Pizza! \n Press enter \n to go into \n our fine \n establishment";
        configureScreenText(30, sf::Color::White, welcomeText, squareWindowSize/4, squareWindowSize/4);

        //sets up sound
        gameSounds.openFromFile("intro_music.wav"); // fix path
        gameSounds.setLoop(true);
        gameSounds.play();


        while(!isStageOver) {
            for (auto asset : screenAssets) gameWindow->draw(asset);
            gameWindow->draw(screenText);
            gameWindow->display();
            while (gameWindow->pollEvent(event)) 
                //if (event.type == sf::Event::Closed) gameWindow->close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) isStageOver = true;
        }
        gameSounds.stop();
    }
};

class Intro : public Game {
public:
    sf::Event event;
    int red = 255;
    int blue = 237;
    int green = 185;
    int loopcount = 1;
    int multiplier = 5;
    sf::Color pizzaColor = sf::Color(red, green, blue);

    

    Intro(RenderWindow* theWindow) : Game(theWindow) {

        configurePizzaCrust(200, pizzaColor, 175, 175);

        while (!isStageOver) {
            while (gameWindow->pollEvent(event)) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    isStageOver = true;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                    red -= loopcount * multiplier;
                    blue -= loopcount * multiplier * (237 / 255);
                    green -= loopcount * multiplier * (185 / 255);

                    if (red <= 0) red = 0;
                    if (blue <= 0) blue = 0;
                    if (green <= 0) green = 0;

                    cout << red << ", " << green << ", " << blue << "\n";

                    pizzaColor = sf::Color( red, green, blue );

                    configurePizzaCrust(200, pizzaColor, 175, 175);
                    loopcount++;

                }
            }

            gameWindow->draw(pizzaCrust);
            gameWindow->display();
        }
    }
};

class Toppings: public Game {
  public:
    vector<sf::Sprite> toppings;
    Toppings(RenderWindow* theWindow, int charredness) : Game(theWindow) { //accepts int between 0 and 5
        charLevel = charredness; //char as in, charred as coal
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
