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
        coolFont.loadFromFile("assets/Apple Chancery.ttf");
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
        logo.loadFromFile("assets/pizza_Icon_larger.jpeg");
        tower.loadFromFile("assets/pisaTower.jpg");
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
        gameSounds.openFromFile("assets/intro_music.wav"); // fix path
        gameSounds.setLoop(true);
        gameSounds.play();

        //display and call to action
        while(!isStageOver) {
            gameWindow->clear(sf::Color::Black);
            for (auto asset : screenAssets) gameWindow->draw(asset);
            gameWindow->draw(screenText);
            gameWindow->display();
            while (gameWindow->pollEvent(event)) 
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) isStageOver = true;
        }
        gameSounds.stop();
    }
};

class Prepping : public Game {
public:
    int red = 255;
    int green = 237;
    int blue = 185;
    int loopCount = 1;
    int multiplier = 30;
    sf::Color pizzaColor;
  

    Prepping(RenderWindow* theWindow) : Game(theWindow) {
        // sets up crust and instructional text
        configureText(screenText, 30, sf::Color::White, "press f to cooka da pizza \n press enter when you're done", 10, 10);
        
        while (!isStageOver) {
            gameWindow->clear(sf::Color::Black);
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
    }
};

class Toppings: public Game {
  public:
    //sf::Sound spongey;
    sf::Sprite currentTopping;
    int toppingRadiusApproximation = 10; //an approximation for the "radius" of a topping
    sf::SoundBuffer buffer;
    sf::Sound sound;

    bool inPizza(int xCoord, int yCoord) {
        int a = xCoord - (squareWindowSize / 2);
        int b = yCoord - (squareWindowSize / 2);
        int r = pizzaCrust.getRadius() - toppingRadiusApproximation;
        int radiusSquared = r * r;
        return (a * a) + (b * b) < radiusSquared;
    }

    Toppings(RenderWindow* theWindow, sf::Color crustColor) : Game(theWindow) { //accepts int between 0 and 5
        gameWindow->clear(sf::Color::Black);
        pizzaCrust.setFillColor(crustColor);
        currentTopping.setPosition(squareWindowSize - 70, 10);

        string instructionsText = "Time for Toppings!\n-------------\n Press key to queue topping \n Tap anywhere on pizza to add topping \n| p -> pineapple |\n| s -> sausage |\n| a -> anchioves |\n| b -> broccoli |\n| m -> mushrooms |\n| o -> black olives |\n| f -> buffalo |";
        configureText(screenText, 20, sf::Color::White, instructionsText, 30, 30);

        sf::Texture pineapple;
        pineapple.loadFromFile("assets/pineapple.png");
        sf::Texture sausage;
        sausage.loadFromFile("assets/sausage.jpg");
        sf::Texture anchovy;
        anchovy.loadFromFile("assets/anchovy.png");
        sf::Texture broccoli;
        broccoli.loadFromFile("assets/broccoli.jpg");
        sf::Texture mushroom;
        mushroom.loadFromFile("assets/mushroom.jpeg");
        sf::Texture olive;
        olive.loadFromFile("assets/olive.jpeg");
        sf::Texture buffalo;
        buffalo.loadFromFile("assets/buffalo.jpeg");

        /*
        sf::SoundBuffer buffer;
        buffer.loadFromFile("assets/filename.wav")

        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.play();
        */

        while(!isStageOver) {
            gameWindow->clear(sf::Color::Black);
            buffer.loadFromFile("assets/spongey.wav");
            sound.setBuffer(buffer);
            sound.setLoop(true);
            sound.play();
            // gameSounds.openFromFile("assets/intro_music.wav");
            // gameSounds.setLoop(true);
            // gameSounds.play();
            gameWindow->draw(pizzaCrust);
            gameWindow->draw(pizzaSauce);
            for (auto asset : screenAssets) gameWindow->draw(asset);
            gameWindow->draw(screenText);
            gameWindow->display();
            while (gameWindow->pollEvent(event)) 
                
                //allows user to choose desired topping with keyboard input
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

        //GameWindow must be refreshed without the screentext for screenshot
        gameWindow->clear(sf::Color::Black);
        gameWindow->draw(pizzaCrust);
        gameWindow->draw(pizzaSauce);
        for (auto asset : screenAssets) gameWindow->draw(asset);
        sf::Image screenshot = gameWindow->capture();
        sound.stop();
        screenshot.saveToFile("assets/screenshot.jpg"); //stores picture of pizza for stage 4
        gameWindow->clear(sf::Color::Black);
    }
    
};

class Endgame: public Game {
  public:
    Endgame(RenderWindow* theWindow, int charLevel) : Game(theWindow) {
        sf::Text finalText;
        finalText.setFont(coolFont);
        finalText.setCharacterSize(30);
        finalText.setFillColor(sf::Color::White);
        finalText.setPosition(squareWindowSize / 10, 20);
        string endGameText = "test";
        switch (charLevel % 5) {
            case 0:
                endGameText = "Nice Pizza! \nBaked... extra extra rare.\nThanks for playing!";
                break;
            case 1:
                endGameText = "Coolio! \nNot too shabby.\nThanks for playing!";
                break;
            case 2:
                endGameText = "Ah very nice. \nWell done.\nThanks for playing!";
                break;
            case 3:
                endGameText = "Hmm, that's what we call \na 'medium-well-done' pizza.\nThanks for playing!";
                break;
            case 4:
                endGameText = "My oh my, that Pizza is \ncharred to perfection.\nThanks for playing!";
                break;
            default:
                endGameText = "Snazzy pizza!\nThanks for playing!";
        }
        finalText.setString(endGameText);
        configureText(screenText, 20, sf::Color::White, endGameText, squareWindowSize / 10, 20);
        sf::Texture result;
        result.loadFromFile("assets/screenshot.jpg");
        sf::RectangleShape resultDisplay(sf::Vector2f(squareWindowSize, squareWindowSize));
        resultDisplay.setTexture(&result); //should auto-position to (0, 0)
        while(!isStageOver) {
            gameWindow->clear(sf::Color::Black);
            gameWindow->draw(screenText);
            gameWindow->draw(resultDisplay);
            gameWindow->draw(finalText); //finalText is co-dependent on screenText for some reason;
            gameWindow->display();
            while (gameWindow->pollEvent(event)) 
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) isStageOver = true;
        }
        gameWindow->clear();
    }
};

int main () {
    sf::RenderWindow mainWindow(sf::VideoMode(squareWindowSize, squareWindowSize), "Raising Chicanery's Pizza");
    Prologue stage1(&mainWindow);
    Prepping stage2(&mainWindow);
    Toppings stage3(&mainWindow, stage2.pizzaColor);
    Endgame stage4(&mainWindow, stage2.loopCount);
    return 0;
}