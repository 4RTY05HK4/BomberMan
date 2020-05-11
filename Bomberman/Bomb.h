#pragma once
#include "Mapa.h"
//#include "Gracz.h"

class Bomb : public sf::Drawable /// class Bomb inherits after sfml class Drawable, this makes displaying bombs easier
{ 

	sf::Texture texture;
	sf::Sprite sprite;

	float posX;
	float posY;
	
	int indexY;
	int indexX;

	std::vector<int> N;

	/** each bomb has it's own position represented by float values and by integer index values and it's own range saved in vector N */

public:

	Bomb(const int indexY, const int indexX) : indexY(indexY), indexX(indexX) /// Constructor for class Bomb objects
	{ 
		texture.loadFromFile("img/bomb.png");
		sprite.setTexture(texture); 
		sprite.setOrigin(15.5f, 15.5f); 
		posY = indexY * 36.f + 36.f - 18.f;
		posX = indexX * 36.f + 136.f - 18.f; 
		sprite.setPosition(posX, posY); 

		std::random_device rnd_device;
		std::mt19937 mersenne_engine{ rnd_device() };
		std::uniform_int_distribution<int> DD{ 3, 8 };
		auto gen = [&DD, &mersenne_engine]() {return DD(mersenne_engine); };
		N.resize(1);
		std::generate(N.begin(), N.end(), gen); 
		/** Constructor sets bomb texture and sprite, set bomb position and map index. Additionaly it generates random value which will be the range of the explosion */
	}

	int getIndexY() { return indexY; }
	int getIndexX() { return indexX; }
	sf::Sprite getSprite() { return sprite; }
	//bool HurtedPlayers(Mapa* map, int PlayerIndexY, int PlayerIndexX) {
	//	std::vector<std::vector<Pole*>> pola = map->getPola();
	//	std::vector<std::vector<int>> mapa = map->getMap();
	//	bool prevTileIsWall = false;
	//	if (indexX == PlayerIndexX && indexY == PlayerIndexY) return true;
	//	for (int i = 1; i <= 3; i++) {
	//		if (prevTileIsWall != true) {
	//			//if (mapa[indexY][indexX - i] == 1 || mapa[indexY][indexX - i] == 2) prevTileIsWall = true;
	//			//if (mapa[indexY][indexX - i] == 0 && indexY == PlayerIndexY && indexX - i == PlayerIndexX) return true;
	//			switch (mapa[indexY][indexX - i])
	//			{
	//			case 0:
	//				if (indexY == PlayerIndexY && indexX - i == PlayerIndexX) return true;
	//				break;
	//			case 1:
	//				prevTileIsWall = true;
	//				break;
	//			case 2:
	//				prevTileIsWall = true;
	//				break;
	//			default:
	//				prevTileIsWall = true;
	//				break;
	//			}
	//		}
	//	}
	//	prevTileIsWall = false;
	//	for (int i = 1; i <= 3; i++) {
	//		if (prevTileIsWall != true) {
	//			if (mapa[indexY][indexX + i] == 1 || mapa[indexY][indexX + i] == 2) prevTileIsWall = true;
	//			if (mapa[indexY][indexX + i] == 0 && indexY == PlayerIndexY && indexX + i == PlayerIndexX) return true;
	//			//switch (mapa[indexY][indexX + i])
	//			//{
	//			//case 0:
	//			//	if (indexY == PlayerIndexY && indexX + i == PlayerIndexX) return true;
	//			//	break;
	//			//case 1:
	//			//	prevTileIsWall = true;
	//			//	break;
	//			//case 2:
	//			//	prevTileIsWall = true;
	//			//	break;
	//			//default:
	//			//	prevTileIsWall = true;
	//			//	break;
	//			//}
	//		}
	//	}
	//	prevTileIsWall = false;
	//	for (int i = 1; i <= 3; i++) {
	//		if (prevTileIsWall != true) {
	//			if (mapa[indexY - i][indexX] == 1 || mapa[indexY - i][indexX] == 2) prevTileIsWall = true;
	//			if (mapa[indexY - i][indexX] == 0 && indexY - i == PlayerIndexY && indexX == PlayerIndexX) return true;
	//			//switch (mapa[indexY - i][indexX])
	//			//{
	//			//case 0:
	//			//	if (indexY - i == PlayerIndexY && indexX == PlayerIndexX) return true;
	//			//	break;
	//			//case 1:
	//			//	prevTileIsWall = true;
	//			//	break;
	//			//case 2:
	//			//	prevTileIsWall = true;
	//			//	break;
	//			//default:
	//			//	prevTileIsWall = true;
	//			//	break;
	//			//}
	//		}
	//	}
	//	prevTileIsWall = false;
	//	for (int i = 1; i <= 3; i++) {
	//		if (prevTileIsWall != true) {
	//			if (mapa[indexY + i][indexX] == 1 || mapa[indexY + i][indexX] == 2) prevTileIsWall = true;
	//			if (mapa[indexY + i][indexX] == 0 && indexY + i == PlayerIndexY && indexX == PlayerIndexX) return true;
	//			//switch (mapa[indexY + i][indexX])
	//			//{
	//			//case 0:
	//			//	if (indexY + i == PlayerIndexY && indexX == PlayerIndexX) return true;
	//			//	break;
	//			//case 1:
	//			//	prevTileIsWall = true;
	//			//	break;
	//			//case 2:
	//			//	prevTileIsWall = true;
	//			//	break;
	//			//default:
	//			//	prevTileIsWall = true;
	//			//	break;
	//			//}
	//		}
	//	}
	//	prevTileIsWall = false;
	//	return false;
	//}

	bool HurtedPlayers(Mapa* map, int PlayerIndexY, int PlayerIndexX) /// Function checking if player should be injured
	{ 
		std::vector<std::vector<Pole*>> pola = map->getPola();
		std::vector<std::vector<int>> mapa = map->getMap();
		std::vector<std::vector<Beka*>> beki = map->getBeki();

		if (indexX == PlayerIndexX && indexY == PlayerIndexY) return true; 
		bool prevTileIsWall = false;
		int i = 1;
		while (i <= N[0] && !prevTileIsWall) {
			switch (mapa[indexY -  i][indexX])
			{
			case 0:
				if (indexY - i == PlayerIndexY && indexX == PlayerIndexX) return true;
				break;
			case 1:
				prevTileIsWall = true;
				break;
			case 2:
				if(beki[indexY - i][indexX] == nullptr){ if (indexY - i == PlayerIndexY && indexX == PlayerIndexX) return true; }
				else{ prevTileIsWall = true; }
				break;
			default:
				prevTileIsWall = true;
				break;
			}
			i++;
		}
		prevTileIsWall = false;
		i = 1;
		while (i <= N[0] && !prevTileIsWall) {
			switch (mapa[indexY + i][indexX])
			{
			case 0:
				if (indexY + i == PlayerIndexY && indexX == PlayerIndexX) return true;
				break;
			case 1:
				prevTileIsWall = true;
				break;
			case 2:
				if (beki[indexY + i][indexX] == nullptr) { if (indexY + i == PlayerIndexY && indexX == PlayerIndexX) return true; }
				else { prevTileIsWall = true; }
				break;
			default:
				prevTileIsWall = true;
				break;
			}
			i++;
		}
		prevTileIsWall = false;
		i = 1;
		while (i <= N[0] && !prevTileIsWall) {
			switch (mapa[indexY][indexX - i])
			{
			case 0:
				if (indexY == PlayerIndexY && indexX - i == PlayerIndexX) return true;
				break;
			case 1:
				prevTileIsWall = true;
				break;
			case 2:
				if (beki[indexY][indexX - i] == nullptr) { if (indexY == PlayerIndexY && indexX - i == PlayerIndexX) return true; }
				else { prevTileIsWall = true; }
				break;
			default:
				prevTileIsWall = true;
				break;
			}
			i++;
		}
		prevTileIsWall = false;
		i = 1;
		while (i <= N[0] && !prevTileIsWall) {
			switch (mapa[indexY][indexX + i])
			{
			case 0:
				if (indexY == PlayerIndexY && indexX + i == PlayerIndexX) return true;
				break;
			case 1:
				prevTileIsWall = true;
				break;
			case 2:
				if (beki[indexY][indexX + i] == nullptr) { if (indexY == PlayerIndexY && indexX + i == PlayerIndexX) return true; }
				else { prevTileIsWall = true; }
				break;
			default:
				prevTileIsWall = true;
				break;
			}
			i++;
		}
		prevTileIsWall = false;
		return false;

		/** This function basicly checks if the player is in the range of explosion and return true if yes*/

	}

	/*bool isColliding(sf::Sprite PlayerSprite)
	{
		sf::Vector2f PlayerPos(PlayerSprite.getPosition());
		int PlayerIndexX = (PlayerPos.x - 100.f) / 36;
		int PlayerIndexY = (PlayerPos.y) / 36;
		if (sprite.getGlobalBounds().intersects(PlayerSprite.getGlobalBounds())) return true;
		else return false;
	}*/

	void Blow(Mapa* map/*, Gracz*& p1Point, Gracz*& p2Point*/) /// function checking which barrels to destroy
	{ 
		std::vector<std::vector<Pole*>> pola = map->getPola();
		std::vector<std::vector<Beka*>> beki = map->getBeki();
		std::vector<std::vector<int>> mapa = map->getMap();

		bool prevTileIsWall = false;

		//sf::Vector2f BombPos(sprite.getPosition());
		//indexX = (BombPos.x - 100.f) / 36;
		//indexY = (BombPos.y) / 36;

		for (int i = 1; i <= N[0]; i++) {
			if (prevTileIsWall != true) {
				switch (mapa[indexY][indexX - i])
				{
				case 0:
					//if (p1Point->getIndexY == indexY && p1Point->getIndexX == indexX - i) p1Point->PlayerGotHurt();
					//if (p2Point->getIndexY == indexY && p2Point->getIndexX == indexX - i) p2Point->PlayerGotHurt();
					break;
				case 1:
					prevTileIsWall = true;
					break;
				case 2:
					if (i < N[0]-1) map->BarrelDestroy(indexY, indexX - i);
					break;
				default:
					break;
				}
			}
		}
		prevTileIsWall = false;
		for (int i = 1; i <= N[0]; i++) {
			if (prevTileIsWall != true) {
				switch (mapa[indexY][indexX + i])
				{
				case 0:
					//if (p1Point->getIndexY == indexY && p1Point->getIndexX == indexX + i) p1Point->PlayerGotHurt();
					//if (p2Point->getIndexY == indexY && p2Point->getIndexX == indexX + i) p2Point->PlayerGotHurt();
					break;
				case 1:
					prevTileIsWall = true;
					break;
				case 2:
					if (i < N[0] - 1) map->BarrelDestroy(indexY, indexX + i);
					break;
				default:
					break;
				}
			}
		}
		prevTileIsWall = false;
		for (int i = 1; i <= N[0]; i++) {
			if (prevTileIsWall != true) {
				switch (mapa[indexY - i][indexX])
				{
				case 0:
					//if (p1Point->getIndexY == indexY - i && p1Point->getIndexX == indexX) p1Point->PlayerGotHurt();
					//if (p2Point->getIndexY == indexY - i && p2Point->getIndexX == indexX) p2Point->PlayerGotHurt();
					break;
				case 1:
					prevTileIsWall = true;
					break;
				case 2:
					if (i < N[0] - 1) map->BarrelDestroy(indexY - i, indexX);
					break;
				default:
					break;
				}
			}
		}
		prevTileIsWall = false;
		for (int i = 1; i <= N[0]; i++) {
			if (prevTileIsWall != true) {
				switch (mapa[indexY + i][indexX])
				{
				case 0:
					//if (p1Point->getIndexY == indexY + i && p1Point->getIndexX == indexX) p1Point->PlayerGotHurt();
					//if (p2Point->getIndexY == indexY + i && p2Point->getIndexX == indexX) p2Point->PlayerGotHurt();
					break;
				case 1:
					prevTileIsWall = true;
					break;
				case 2:
					if (i < N[0] - 1) map->BarrelDestroy(indexY + i, indexX);
					break;
				default:
					break;
				}
			}
		}

		/** This function checks all the barrels in the range of bomb and destroys them using pointer to Mapa instance*/
	}

	//void Blow() {
	//	sf::SoundBuffer buffer;
	//	sf::Sound blow;
	//	buffer.loadFromFile("sounds/explode.wav");
	//	blow.setBuffer(buffer);
	//	blow.play();
	//}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const /// inheriting after sf::Drawable requires this sfml function to be overwritten
	{ 
		target.draw(sprite, states);
	}

};
