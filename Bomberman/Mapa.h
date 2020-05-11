#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "Pole.h"
#include "Sciana.h"
#include "Podloga.h"
#include "Beka.h"

class Mapa : public sf::Drawable /// class Mapa inherits after sfml class Drawable, this makes displaying map and it's fields easier
{
private:

	sf::Texture texture;
	sf::Sprite sprite;
	std::string filename = "img/map.png";
	std::vector<std::vector<int>> mapa;
	std::vector<std::vector<Pole*>> pola;
	std::vector<std::vector<Beka*>> beki;
	std::vector<std::pair<int, int>> walls;

public:

	Mapa(int sizeX, int sizeY) /// Constructor for class Mapa
	{
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		sprite.setPosition(100.f, 0.f);
		mapa.resize(sizeX);
		for(int i = 0; i<sizeX; i++ )
		{
			mapa[i].resize(sizeY);
		}
		/** This constructor sets map background and is creating a 2D vector of integers. It will be later filled with numbers corresponding blocks. */
	}

	std::vector<std::vector<Pole*>> getPola() const { return pola; }
	std::vector<std::pair<int, int>> getWalls() const { return walls; }
	std::vector<std::vector<int>> getMap() const { return mapa; }
	std::vector<std::vector<Beka*>> getBeki() { return beki; }
	//sf::Sprite getSprite() { return sprite; }
	
	void Load(std::string  fileName) /// This function loads map
	{
		
		std::ifstream mapload;
		mapload.open(fileName);
		int iter = 0;
		walls.resize(128);
		for (int i = 0; i < mapa.size(); i++) {
			for (int j = 0; j < mapa[i].size(); j++) {
				mapload >> mapa[i][j];
				if(mapa[i][j] == 1){ 
					walls[iter].first = i;
					walls[iter].second = j;
					iter++;
				}
				std::cout << mapa[i][j];
			}
			std::cout<<std::endl;
		}
		//std::cout << iter;
		float posX = 100.f;
		float posY = 0.f;

		pola.resize(mapa.size());
		beki.resize(mapa.size());
		for (int i = 0; i<mapa.size(); i++)
		{
			pola[i].resize(mapa[i].size());
			beki[i].resize(mapa[i].size());
		}

		for (int i = 0; i < mapa.size(); i++)
		{
			for (int j = 0; j < mapa[i].size(); j++)
			{
				if (mapa[i][j] == 1) { pola[i][j] = new Sciana(posX, posY); beki[i][j] = nullptr; }
				if (mapa[i][j] == 0) { pola[i][j] = new Podloga(posX, posY); beki[i][j] = nullptr; }
				if (mapa[i][j] == 2) { pola[i][j] = new Podloga(posX, posY); beki[i][j] = new Beka(posX, posY); }
				posX = posX + 36.f;
			}
			posX = 100.f;
			posY = posY + 36.f;
		}
		/** This function loads 16x16 matrix which contains map pattern represented by 0, 1 and 2. It then creates walls, floors 
		an barrels according to the pattern.*/
	}
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const /// inheriting after sf::Drawable requires this sfml function to be overwritten
	{
		target.draw(sprite, states);
		for (int i = 0; i < pola.size(); i++)
		{
			for (int j = 0; j < pola[i].size(); j++)
			{
				target.draw(*pola[i][j]);
				if(beki[i][j] != nullptr) target.draw(*beki[i][j]);
			}
		}
	}
	
	void BarrelDestroy(int indexY, int indexX) /// Function used to destroy barrels
	{
		delete beki[indexY][indexX];
		beki[indexY][indexX] = nullptr;
		/** This function is being called whenever a bomb detects a barrel that is supposed to be destroyed.
		It deletes a barrel and then overwrites matching index with nullptr. It prevents memory leaks and certain errors 
		from occuring.*/
	}
	
	void MapReset() /// Function used to rese map
	{
		for (int i = 0; i < pola.size(); i++)
		{
			for (int j = 0; j < pola[i].size(); j++)
			{
				delete pola[i][j];
				delete beki[i][j];
			}
		}
		/** This function simply deletes all objects created for previous map. After reseting it's being called,
		to delete all the remains of map from previous game to prevent memory leaks.*/
	}

	~Mapa() /// Destructor 
	{
		for (int i = 0; i < pola.size(); i++)
		{
			for (int j = 0; j < pola[i].size(); j++)
			{
				delete pola[i][j];
				delete beki[i][j];
			}
		}
		/** It does exactly the same thing as MapReset(), but it's being called after program has been closed.
		Has to be seperated for possible future changes.*/
	}
};