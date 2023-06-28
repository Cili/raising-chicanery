chicaneryJon: chicanery.cpp 
	g++ -std=c++17 chicanery.cpp -I/opt/homebrew/include -o chicaneryJon -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

chicaneryDylan: chicanery.cpp
	g++ -std=c++17 chicanery.cpp -I/usr/local/Cellar/sfml/2.5.1_2/include -o chicaneryDylan -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system

chicaneryHMC: chicanery.cpp
	g++ -std=c++17 chicanery.cpp -I/usr/local/Cellar/sfml/2.5.1_2/include -o chicaneryHMC -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system
