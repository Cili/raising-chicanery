#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//#include <Windows.h> // required for Sleep() in Intro

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
    sf::CircleShape pizzaSauce;
    sf::Text screenText;
    sf::Text specialityText;
    sf::Music gameSounds;
    vector<sf::Sprite> screenAssets;
    sf::RenderWindow* gameWindow;
    vector<sf::Shape> screenShapes;

    //other var
    bool isStageOver;

    void configurePizza(int radius, sf::Color pizzaColor, int xCoord, int yCoord) {
        pizzaCrust.setRadius(radius);
        pizzaCrust.setFillColor(pizzaColor);
        pizzaCrust.setPosition(xCoord, yCoord);

        pizzaSauce.setRadius(radius - 20);
        pizzaSauce.setFillColor(sf::Color::Red);
        pizzaSauce.setPosition(xCoord + 20, yCoord + 20);
    }

    void configureText(sf::Text theText, int fontSize, sf::Color textColor, string text, int xCoord, int yCoord) {
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
        configurePizza(200, sf::Color::White, squareWindowSize / 4, squareWindowSize / 4);
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
            sf::Sprite aLogo(logo);
            aLogo.setPosition(x, y);
            screenAssets.push_back(aLogo);
        }
        //sets up towerimage
        sf::Sprite aTower(tower);
        aTower.setPosition(int(squareWindowSize)/2, int(squareWindowSize)/ 3);
        aTower.rotate(-8);
        screenAssets.push_back(aTower);

        //sets up welcome txt
        string welcomeText = "Welcome to Raising Chicanery's Pizza! \n Press enter \n to go into \n our fine \n establishment";
        configureText(screenText, 30, sf::Color::White, welcomeText, squareWindowSize/4, squareWindowSize/4);

        //sets up sound
        gameSounds.openFromFile("intro_music.wav"); // fix path
        gameSounds.setLoop(true);
        gameSounds.play();

        //display and call to action
        while(!isStageOver) {
            for (auto asset : screenAssets) gameWindow->draw(asset);
            gameWindow->draw(screenText);
            gameWindow->display();
            while (gameWindow->pollEvent(event)) 
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) isStageOver = true;
        }
        
        gameSounds.stop();
        gameWindow->clear();
    }
};

class Intro : public Game {
public:
    int red = 255;
    int green = 237;
    int blue = 185;
    int loopCount = 1;
    int multiplier = 50;
    sf::Color pizzaColor;
  

    Intro(RenderWindow* theWindow) : Game(theWindow) {
        // sets up crust and instructional text
        configureText(screenText, 30, sf::Color::White, "press f to cooka da pizza /n /n /n /n /n press enter when you're done", 10, 10); // text needs to be properly repositioned!
        
        while (!isStageOver) {
            pizzaColor = sf::Color(red, green, blue);
            pizzaCrust.setFillColor(pizzaColor);
            gameWindow->draw(screenText);
            gameWindow->draw(specialityText);
            gameWindow->draw(pizzaCrust);
            gameWindow->draw(pizzaSauce);
            gameWindow->display();
            while (gameWindow->pollEvent(event)) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) isStageOver = true; // if enter is pressed, move on to the next stage
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) { //F for flame
                    // if f is pressed, adjust the rgb values of the pizza crust color to make it appear darker
                    red = red > multiplier ? red - multiplier : 0;
                    green = green > multiplier ? green - multiplier: 0;
                    blue = blue > multiplier ? red - multiplier : 0;

                    if (red == 0 && green == 0 && blue == 0) { // resets the dough to the initial state if it gets too charred.. not sure if this is what we want?
                        // if the pizza is completely black, display a message that the pizza is burned, wait a few seconds, then reset the pizza color
                        configureText(specialityText, 30, sf::Color::White, "You burned the pizza!\nTry again.", squareWindowSize / 4, 20); // text needs to be properly repositioned
                        red = 255;
                        blue = 185;
                        green = 237;
                    }
                    loopCount++;
                }
            }
        }
        gameWindow->clear();
    }
};

class Toppings: public Game {
  public:
    sf::Sprite currentTopping;
    int toppingRadiusApproximation = 10; //an approximation for the "radius" of a topping

    bool inPizza(int xCoord, int yCoord) {
        int a = xCoord - (squareWindowSize / 2);
        int b = yCoord - (squareWindowSize / 2);
        int r = pizzaCrust.getRadius() - toppingRadiusApproximation;
        int radiusSquared = r * r;
        return (a * a) + (b * b) < radiusSquared;
    }

    Toppings(RenderWindow* theWindow, sf::Color crustColor) : Game(theWindow) { //accepts int between 0 and 5
        pizzaCrust.setFillColor(crustColor);
        currentTopping.setPosition(squareWindowSize - 70, 10);

        string instructionsText = "Time for Toppings!\n-------------\n Press key to queue topping \n Tap anywhere on pizza to add topping \n | p -> pineapple |\n| s -> sausage |\n| a -> anchioves |\n| b -> broccoli | m -> mushrooms | -> | o -> black olives |\n| f -> buffalo |";
        configureText(screenText, 20, sf::Color::White, instructionsText, 30, 30);

        sf::Texture pineapple;
        pineapple.loadFromFile("pineapple.png");
        sf::Texture sausage;
        sausage.loadFromFile("sausage.jpg");
        sf::Texture anchovy;
        anchovy.loadFromFile("anchovy.png");
        sf::Texture broccoli;
        broccoli.loadFromFile("broccoli.tiff");
        sf::Texture mushroom;
        mushroom.loadFromFile("mushroom.jpeg");
        sf::Texture olive;
        olive.loadFromFile("olive.jpeg");
        sf::Texture buffalo;
        buffalo.loadFromFile("buffalo.jpeg");

        while(!isStageOver) {
            gameWindow->draw(pizzaCrust);
            gameWindow->draw(pizzaSauce);
            for (auto asset : screenAssets) gameWindow->draw(asset);
            gameWindow->draw(screenText);
            gameWindow->display();
            while (gameWindow->pollEvent(event)) 
                //if (event.type == sf::Event::Closed) gameWindow->close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) currentTopping.setTexture(pineapple);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) currentTopping.setTexture(buffalo);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) currentTopping.setTexture(sausage);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) currentTopping.setTexture(anchovy);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) currentTopping.setTexture(broccoli);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) currentTopping.setTexture(mushroom);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) currentTopping.setTexture(olive);
                else if (event.type == sf::Event::MouseButtonPressed) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    if (inPizza(x, y)) {
                        sf::Sprite topping = currentTopping;
                        topping.setPosition(event.mouseButton.x,event.mouseButton.y);
                        screenAssets.push_back(topping);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) isStageOver = true;
        }  
        sf::Image screenshot = gameWindow->capture();
        screenshot.saveToFile("screenshot.jpg");
        gameWindow->clear();
    }
    
};

class Endgame: public Game {
  public:
    Endgame(RenderWindow* theWindow, int charLevel) : Game(theWindow) {
        string endGameText;
        switch (charLevel % 5) {
            case 0:
                endGameText = "Nice Pizza! Baked... extra extra rare.";
                break;
            case 1:
                endGameText = "Nice Pizza! Not too shabby.";
                break;
            case 2:
                endGameText = "Ah very nice. Well done.";
                break;
            case 3:
                endGameText = "Hmm, that's what we call a 'medium-well-done' pizza.";
                break;
            case 4:
                endGameText = "My oh my, that Pizza is charred to perfection.";
                break;
        }
        configureText(screenText, 20, sf::Color::White, endGameText, squareWindowSize / 4, 20);
        sf::Texture result;
        result.loadFromFile("screenshot.jpg");
        sf::Sprite resultDisplay(result); //should auto-position to (0, 0)
        while(!isStageOver) {
            gameWindow->draw(resultDisplay);
            gameWindow->draw(screenText);
            while (gameWindow->pollEvent(event)) 
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) isStageOver = true;
        }
        gameWindow->clear();
    }
};

int main () {
    sf::RenderWindow mainWindow(sf::VideoMode(squareWindowSize, squareWindowSize), "Raising Chicanery's Pizza");
    Prologue stage1(&mainWindow);
    Intro stage2(&mainWindow); //pizza crust
    Toppings stage3(&mainWindow, stage2.pizzaColor);
    Endgame stage4(&mainWindow, stage2.loopCount);
    
    //while (mainWindow.pollEvent(mainEvent)) if (mainEvent.type == sf::Event::Closed) mainWindow.close();
    //cout << "VS PetCode is awesome" << "\n";
    //cout << "Welcome to Raising Chicanery! Watch our dog do some cool tricks: " << '\n';
    return 0;
}
