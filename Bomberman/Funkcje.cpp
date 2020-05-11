#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>


bool validator()
{
	sf::Texture validate;
	if (!validate.loadFromFile("img/map.png"))
	{
		return false;
	}
	if (!validate.loadFromFile("img/mur.png"))
	{
		return false;
	}
	if (!validate.loadFromFile("img/floor.png"))
	{
		return false;
	}
	if (!validate.loadFromFile("img/beka2.png"))
	{
		return false;
	}
	if (!validate.loadFromFile("img/p1.png"))
	{
		return false;
	}
	if (!validate.loadFromFile("img/p2.png"))
	{
		return false;
	}
	if (!validate.loadFromFile("img/bomb.png"))
	{
		return false;
	}
	if (!validate.loadFromFile("img/heart.png"))
	{
		return false;
	}
	if (!validate.loadFromFile("img/player1.png"))
	{
		return false;
	}
	if (!validate.loadFromFile("img/player2.png"))
	{
		return false;
	}
	std::ifstream load;
	load.open("maps/mapa1.txt"); //otwarcie pliku
	if (!load.is_open())     //sprawdzenie czy plik istnieje
	{
		std::cout << "Plik " << "maps/mapa1.txt" << " nie istnieje!" << std::endl;
		return false;
	}
	return true;
}


