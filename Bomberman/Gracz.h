#pragma once
#include "Bomb.h"


class Gracz : public sf::Drawable /// class Gracz inherits after sfml class Drawable, this makes displaying player easier
{

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Texture hearts;
	sf::Sprite OponentSprite;

	bool movingLeft = false;
	bool movingUp = false;
	bool movingRight = false;
	bool movingDown = false;
	bool placeBomb = false;

	int playerNR;

	float posX;
	float posY;

	float StartPosX;
	float StartPosY;

	int indexX;
	int indexY;

	int OponentIndexY;
	int OponentIndexX;

	float velocity;
	int lives;

	std::vector<sf::Sprite> zycia;
	std::vector<std::vector<Pole*>> pola;
	std::vector<std::vector<int>> walls;
	std::vector<std::vector<Beka*>> beki;
	std::vector<Bomb*> bomby;
	std::vector<Bomb*> EnemyBomb;

	

public:

	Gracz(float posX, float posY, const int playerNR, const std::vector<std::vector<int>> walls,
		const std::vector<std::vector<Pole*>> pola, std::vector<std::vector<Beka*>> beki) : 
		playerNR(playerNR), posX(posX), posY(posY), StartPosX(posX), StartPosY(posY), pola(pola), walls(walls), beki(beki) /// Constructor for class Gracz
	{	
		
		if (playerNR == 1) texture.loadFromFile("img/p1.png"); 
		if (playerNR == 2) texture.loadFromFile("img/p2.png");

		sprite.setTexture(texture); 
		sprite.setOrigin(sf::Vector2f(15.5f, 13.f)); 
		sprite.setPosition(posX, posY); 

		hearts.loadFromFile("img/heart.png");

		indexX = (posX - 100.f) / 36;
		indexY = (posY) / 36;

		velocity = 2.f;

		bomby.resize(2);
		bomby[0] = nullptr;
		bomby[1] = nullptr;

		EnemyBomb.resize(2);
		EnemyBomb[0] = nullptr;
		EnemyBomb[1] = nullptr;

		lives = 3;
		zycia.resize(lives);
		zycia[0].setTexture(hearts);
		if (playerNR == 1) zycia[0].setPosition(0.f, 40.f);
		if (playerNR == 2) zycia[0].setPosition(0.f, 120.f);
		zycia[1].setTexture(hearts);
		if (playerNR == 1) zycia[1].setPosition(32.f, 40.f);
		if (playerNR == 2) zycia[1].setPosition(32.f, 120.f);
		zycia[2].setTexture(hearts);
		if (playerNR == 1) zycia[2].setPosition(64.f, 40.f);
		if (playerNR == 2) zycia[2].setPosition(64.f, 120.f);

		/** This constructor creates a player and sets everything that is needed to default or nullptr values. So lives are set to 3, 
		their texture and sprites are set and their position is set correctly for each player. It also resets both bombs to prevent bugs.*/

	}
	
	int getIndexX() const { return indexX; } 
	int getIndexY() const { return indexY; }
	sf::Sprite getSprite() const { return sprite; }
	//void setOponentIndexY(int OponentIndexY) { this->OponentIndexY = OponentIndexY; }
	//void setOponentIndexX(int OponentIndexX) { this->OponentIndexX = OponentIndexX; }
	std::vector<Bomb*> getBombs() const { return bomby; }
	int getHP() const { return lives; }
	void setBeki(std::vector<std::vector<Beka*>> beki) { this->beki = beki; }
	void setPola(std::vector<std::vector<Pole*>> pola) { this->pola = pola; } 
	void setEnemyBombs(std::vector<Bomb*> EnemyBombs) { this->EnemyBomb = EnemyBomb; }


	void update() /// Function handling movement and collision
	{
		sf::Vector2f movement(0.f, 0.f);
		sf::Vector2f PlayerPos(sprite.getPosition());
		indexX = (PlayerPos.x - 100.f) / 36;
		indexY = (PlayerPos.y) / 36;

		if (movingUp) {

			sprite.setRotation(-90.f); sprite.setTextureRect(sf::IntRect(0, 0, 32, 25));

			switch (walls[indexY - 1][indexX])
			{
			case 0 :
				if (indexY - 1 == OponentIndexY && indexX == OponentIndexX && sprite.getGlobalBounds().intersects(OponentSprite.getGlobalBounds())) break;
				//else if (EnemyBomb[0] != nullptr) {
				//	if (indexY - 1 == EnemyBomb[0]->getIndexY() && indexX == EnemyBomb[0]->getIndexX() && sprite.getGlobalBounds().intersects(EnemyBomb[0]->getSprite().getGlobalBounds())) break;
				//}
				movement.y -= velocity;
				break;
			case 1 :
				if (pola[indexY - 1][indexX]->isColliding(sprite)) break;
				else movement.y -= velocity;
				break;
			case 2 :
				if (beki[indexY - 1][indexX] != nullptr && beki[indexY - 1][indexX]->isColliding(sprite)) break;
				else if (beki[indexY - 1][indexX] == nullptr) {
					if (indexY - 1 == OponentIndexY && indexX == OponentIndexX && sprite.getGlobalBounds().intersects(OponentSprite.getGlobalBounds())) break; 
					//else if (EnemyBomb[0] != nullptr) {
					//	if (indexY - 1 == EnemyBomb[0]->getIndexY() && indexX == EnemyBomb[0]->getIndexX() && sprite.getGlobalBounds().intersects(EnemyBomb[0]->getSprite().getGlobalBounds())) break;
					//}
				}
				movement.y -= velocity;
				break;
			default:
				break;
			}

		}
		if (movingDown) {
			
			sprite.setRotation(90.f); sprite.setTextureRect(sf::IntRect(0, 0, 32, 25));

			switch (walls[indexY + 1][indexX])
			{
			case 0:
				if (indexY + 1 == OponentIndexY && indexX == OponentIndexX && sprite.getGlobalBounds().intersects(OponentSprite.getGlobalBounds())) break;
				movement.y += velocity;
				break;
			case 1:
				if (pola[indexY + 1][indexX]->isColliding(sprite)) break;
				else movement.y += velocity; break;
				break;
			case 2:
				if (beki[indexY + 1][indexX] != nullptr && beki[indexY + 1][indexX]->isColliding(sprite)) break;
				else if (beki[indexY + 1][indexX] == nullptr) {
					if (indexY + 1 == OponentIndexY && indexX == OponentIndexX && sprite.getGlobalBounds().intersects(OponentSprite.getGlobalBounds())) break;
				}
				movement.y += velocity;
				break;
			default:
				break;
			}
		}
		if (movingLeft) {

			sprite.setRotation(0.f); sprite.setTextureRect(sf::IntRect(32, 0, -32, 25));

			switch (walls[indexY][indexX - 1])
			{
			case 0:
				if (indexX - 1 == OponentIndexX && indexY == OponentIndexY && sprite.getGlobalBounds().intersects(OponentSprite.getGlobalBounds())) break;
				movement.x -= velocity;
				break;
			case 1:
				if (pola[indexY][indexX - 1]->isColliding(sprite)) break;
				else movement.x -= velocity; break;
				break;
			case 2:
				if (beki[indexY][indexX - 1] != nullptr && beki[indexY][indexX - 1]->isColliding(sprite)) break;
				else if (beki[indexY][indexX - 1] == nullptr) {
					if (indexX - 1 == OponentIndexX && indexY == OponentIndexY && sprite.getGlobalBounds().intersects(OponentSprite.getGlobalBounds())) break;
				}
				movement.x -= velocity;
				break;
			default:
				break;
			}

		}
		if (movingRight) {

			sprite.setRotation(0.f); sprite.setTextureRect(sf::IntRect(0, 0, 32, 25));

			switch (walls[indexY][indexX + 1])
			{
			case 0:
				if (indexX + 1 == OponentIndexX && indexY == OponentIndexY && sprite.getGlobalBounds().intersects(OponentSprite.getGlobalBounds())) break;
				movement.x += velocity;
				break;
			case 1:
				if (pola[indexY][indexX + 1]->isColliding(sprite)) break;
				else movement.x += velocity; break;
				break;
			case 2:
				if (beki[indexY][indexX + 1] != nullptr && beki[indexY][indexX + 1]->isColliding(sprite)) break;
				else if (beki[indexY][indexX + 1] == nullptr) {
					if (indexX + 1 == OponentIndexX && indexY == OponentIndexY && sprite.getGlobalBounds().intersects(OponentSprite.getGlobalBounds())) break;
				}
				movement.x += velocity;
				break;
			default:
				break;
			}

		}

		sprite.move(movement);
		/** Direction of movement depends on bool variables. If movingUp is set to true that means 
		the function will detect collision with walls and barrels above player. It works same in every direction. Function also
		transforms player sprite to point him in the direction he wants to move. */
	}

	void handlePlayerBombs() /// Function for planting bombs
	{
		if (placeBomb && bomby[0] == nullptr) {
			bomby[0] = new Bomb(indexY, indexX);
			
			placeBomb = false;
		}
		else if (placeBomb && bomby[1] == nullptr && bomby[0] != nullptr) {
			bomby[1] = new Bomb(indexY, indexX);
			
			placeBomb = false;
		}
		/** Function handling creating new bombs on demand in players location
		and preventing player from planting more than two bombs. */
	}

	void BlowIt(sf::Time elapsedTime1, sf::Time elapsedTime2, bool Clock1, bool Clock2) /// Function handling deleting bombs after elapsed time
	{
		if (elapsedTime1.asSeconds() >= 3 ) { delete bomby[0]; bomby[0] = nullptr; }
		if (elapsedTime2.asSeconds() >= 3 ) { delete bomby[1]; bomby[1] = nullptr; }
	}

	void PlayerGotHurt() /// Function to decrease player lives 
	{
		lives--;
	}

	bool CheckPlayerHP() /// Function returning false as long as player has lives
	{
		if (lives <= 0) return true;
		else return false;
	}

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed) /// Function for handling player keyboard input
	{
		if(playerNR == 1){ 
			if (key == sf::Keyboard::W) { movingUp = isPressed; }
			else if (key == sf::Keyboard::S) { movingDown = isPressed; }
			else if (key == sf::Keyboard::A) { movingLeft = isPressed; }
			else if (key == sf::Keyboard::D) { movingRight = isPressed; }
			else if (key == sf::Keyboard::LControl) { placeBomb = isPressed; }
		}
		else if (playerNR == 2) {
			if (key == sf::Keyboard::Up) { movingUp = isPressed; }
			else if (key == sf::Keyboard::Down) { movingDown = isPressed; }
			else if (key == sf::Keyboard::Left) { movingLeft = isPressed; }
			else if (key == sf::Keyboard::Right) { movingRight = isPressed; }
			else if (key == sf::Keyboard::RControl) { placeBomb = isPressed; }
		}
		/** Depending on which player is it (player one or player two) different keys are controlling them.
		Depending on which key has been pressed a corresponding bool variable is being set to true. */
	}

	void FindOponent(int OponentIndexY, int OponentIndexX, sf::Sprite OponentSprite) /// "Spy" function
	{
		this->OponentIndexY = OponentIndexY;
		this->OponentIndexX = OponentIndexX;
		this->OponentSprite = OponentSprite;
		/** This function gets oponent position. It is needed for collision between players. */
	}

	void resetPlayerHP() /// Function resetting player HP
	{
		lives = 3;
	}

	void resetPlayerPosition() /// Function reseting player position, to his starting position
	{
		sprite.setPosition(StartPosX, StartPosY);
	}

	void resetPlayer(std::vector<std::vector<Pole*>> pola, std::vector<std::vector<Beka*>> beki) /// Function reseting player
	{
		resetPlayerHP();
		resetPlayerPosition();
		setBeki(beki);
		setPola(pola);
		/** This function reset player HP and his position, as well as it updates map pattern */
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const /// inheriting after sf::Drawable requires this sfml function to be overwritten
	{
		target.draw(sprite, states);
		
		for (int i = 0; i < lives; i++) {
			target.draw(zycia[i]);
		}	

		if (bomby[0] != nullptr) target.draw(*bomby[0]);
		if (bomby[1] != nullptr) target.draw(*bomby[1]);
		
	}

};

