#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vld.h>
#include <iostream>
#include <random>
#include "Funkcje.h"
#include "Mapa.h"
#include "Pole.h"
#include "Sciana.h"
#include "Beka.h"
#include "Podloga.h"
#include "Gracz.h"
#include "Bomb.h"


int main() {

	if(validator() == false)
	{
		getchar();
		return 0;
	}
	/// Game window
	/** Window resolution set to 776x576, turn off window resizing, framerate per second set to 60	*/
	///	window(sf::VideoMode(776, 576), "Bomberman!", sf::Style::Titlebar | sf::Style::Close); 
	///	window.setFramerateLimit(60);
	sf::RenderWindow window(sf::VideoMode(776, 576), "Bomberman!", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	/// New Mapa object
	/** Map size 16x16 tiles, pattern loaded from file mapa1.txt*/
		///Mapa map(16, 16);
		///map.Load("maps/mapa1.txt");
	Mapa map(16, 16);
	map.Load("maps/mapa1.txt");
	Mapa* mapPointer;
	mapPointer = &map;

	///	map tiles
	/** Getting vectors containing map fields (barrels, walls and floors) and a matrix containg field pattern using accesors*/
		///map.getPola();
		///map.getMap();
		///map.getBeki();
	std::vector<std::vector<Pole*>> pola = mapPointer->getPola();
	std::vector<std::vector<int>> walls = mapPointer->getMap();
	std::vector<std::vector<Beka*>> beki = mapPointer->getBeki();

	/// Players
	/** Creating two independent players */
		///Gracz p1(154.f, 54.f, 1, walls, pola, beki);
		///Gracz p2(622.f, 522.f, 2, walls, pola, beki);
	Gracz p1(154.f, 54.f, 1, walls, pola, beki);
	Gracz p2(622.f, 522.f, 2, walls, pola, beki);

	Gracz* p1Point;
	p1Point = &p1;

	Gracz* p2Point;
	p2Point = &p2;

	/// Interface
	/** Setting interface with code for player one as example*/
		///sf::Texture Player1;
		///Player1.loadFromFile("img/player1.png");
		///sf::Sprite Player1Sprite;
		///Player1Sprite.setTexture(Player1);
	sf::Texture Player1;
	Player1.loadFromFile("img/player1.png");
	sf::Sprite Player1Sprite;
	Player1Sprite.setTexture(Player1);

	sf::Texture Player2;
	Player2.loadFromFile("img/player2.png");
	sf::Sprite Player2Sprite;
	Player2Sprite.setTexture(Player2);
	Player2Sprite.setPosition(0.f, 80.f);
	
	/// Bomb timers
	/** Setting bomb timers and turning them off till a bomb is placed by player */
	sf::Clock P1bomb1Clock;
	sf::Clock P1bomb2Clock;
	sf::Clock P2bomb1Clock;
	sf::Clock P2bomb2Clock;
	
	bool Clock1 = false;
	bool Clock2 = false;
	bool Clock3 = false;
	bool Clock4 = false;

	/// Sounds and music
	/** Setting soundtrack */
	sf::Music soundtrack;
	soundtrack.openFromFile("sounds/energy.flac");
	soundtrack.play();
	soundtrack.setVolume(5.f);
	soundtrack.setLoop(true);
	
	/** Setting sound buffer for bomb explosions and assigning that bufferto bombs  */
	sf::SoundBuffer buffer;
	buffer.loadFromFile("sounds/explode.wav");

	sf::Sound blow1;
	sf::Sound blow2;
	sf::Sound blow3;
	sf::Sound blow4;

	blow1.setBuffer(buffer);
	blow2.setBuffer(buffer);
	blow3.setBuffer(buffer);
	blow4.setBuffer(buffer);

	blow1.setVolume(50.f);
	blow2.setVolume(50.f);
	blow3.setVolume(50.f);
	blow4.setVolume(50.f);

	bool notEnd = true; /// notEnd <- variable from which depends if the game should pause after a player died

	/// Victory sound
	/** Setting buffer and a sf::Sound played when one of players won */
	sf::SoundBuffer WinSoundBuffer;
	WinSoundBuffer.loadFromFile("sounds/win.wav");
	sf::Sound win;
	win.setBuffer(WinSoundBuffer);

	/// Endgame screen
	/** Setting two seperate pictures that will be displayed when one of players wins*/
	sf::Texture P1WonTexture;
	P1WonTexture.loadFromFile("img/P1Won.png");
	sf::Sprite P1WonSprite;
	P1WonSprite.setTexture(P1WonTexture);
	P1WonSprite.setOrigin(287.f, 49.5f);
	P1WonSprite.setPosition(388.f, 288.f);

	sf::Texture P2WonTexture;
	P2WonTexture.loadFromFile("img/P2Won.png");
	sf::Sprite P2WonSprite;
	P2WonSprite.setTexture(P2WonTexture);
	P2WonSprite.setOrigin(287.f, 49.5f);
	P2WonSprite.setPosition(388.f, 288.f);

	/// while (window.isOpen()){} <- game window loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) /// while (window.pollEvent(event)){} <- event poll loop
		{
			switch (event.type)
			{

			case sf::Event::KeyPressed:
				if (notEnd == true){
					p1.handlePlayerInput(event.key.code, true);	  ///	p1.handlePlayerInput(event.key.code, true);	<- method controlling player one input
					p2.handlePlayerInput(event.key.code, true);	  ///	p2.handlePlayerInput(event.key.code, true);	<- method controlling player two input
				}
				else if (notEnd == false) {
					if (event.key.code == sf::Keyboard::R) { /// when game is paused, pressing R button resets the game to beginning
						window.clear(); /// clearing window
						map.MapReset(); /// deleting old map
						map.Load("maps/mapa1.txt"); /// loading a new one
						mapPointer = &map; /// reassigning pointer to new map object
						p1.resetPlayer(map.getPola(), map.getBeki()); /// reseting player one
						p2.resetPlayer(map.getPola(), map.getBeki()); /// reseting player two
						notEnd = true; /// setting notEnd to true to unpause the game
					}
				}
				break;

			case sf::Event::KeyReleased:
				p1.handlePlayerInput(event.key.code, false);
				p2.handlePlayerInput(event.key.code, false);
				break;

			case sf::Event::Closed: window.close(); break;
			}
		}



		window.clear(); 
		window.draw(map); /// drawing map

		window.draw(Player1Sprite); /// drawing interface for player 1
		window.draw(Player2Sprite); /// drawing interface for player 2

		//p1.setEnemyBombs(p2.getBombs());
		//p2.setEnemyBombs(p1.getBombs());

		p1.update(); /// a method handling move and collision of player one
		window.draw(p1); /// drawing player ones

		p1.handlePlayerBombs(); /// a method handling player one bombs
		p1.FindOponent(p2.getIndexY(), p2.getIndexX(), p2.getSprite()); /// a method notifying player 1 about position of player 2, needed for collision

		std::vector<Bomb*> bombyP1 = p1.getBombs(); /// getting all placed bombs from player one

		if (bombyP1[0] != nullptr && Clock1 == false) { P1bomb1Clock.restart(); Clock1 = true; } /// bomb timers control
		if (bombyP1[1] != nullptr && Clock2 == false) { P1bomb2Clock.restart(); Clock2 = true; } /// bomb timers control

		
		if (P1bomb1Clock.getElapsedTime().asSeconds() >= 3 && blow1.getStatus() != sf::Sound::Playing &&  Clock1 == true) { /// after 3 seconds bomb should explode, that if instruction handles it
			blow1.play(); /// playing explosion sound
			if (bombyP1[0]->HurtedPlayers(mapPointer, p2.getIndexY(), p2.getIndexX())) p2.PlayerGotHurt(); /// checking if player 2 should be injured by bomb and if yes hurting him with the method PlayerGotHurt()
			if (bombyP1[0]->HurtedPlayers(mapPointer, p1.getIndexY(), p1.getIndexX())) p1.PlayerGotHurt(); /// checking if player 1 should be injured by bomb and if yes hurting him with the method PlayerGotHurt()
			bombyP1[0]->Blow(mapPointer/*, p1Point, p2Point*/); /// checking which barrels to destroy and destroying them
			p1.setBeki(mapPointer->getBeki()); /// updating players with current barrels pattern
			p2.setBeki(mapPointer->getBeki());

			Clock1 = false; /// turning off clock
		} 
		/** Above happens to all bombs and both players. */
		if (P1bomb2Clock.getElapsedTime().asSeconds() >= 3 && blow2.getStatus() != sf::Sound::Playing &&  Clock2 == true) { /// after 3 seconds bomb should explode, that if instruction handles it
			blow2.play();
			if (bombyP1[1]->HurtedPlayers(mapPointer, p2.getIndexY(), p2.getIndexX())) p2.PlayerGotHurt();
			if (bombyP1[1]->HurtedPlayers(mapPointer, p1.getIndexY(), p1.getIndexX())) p1.PlayerGotHurt();
			bombyP1[1]->Blow(mapPointer/*, p1Point, p2Point*/);
			p1.setBeki(mapPointer->getBeki());
			p2.setBeki(mapPointer->getBeki());
			Clock2 = false; 
		}

		p1.BlowIt(P1bomb1Clock.getElapsedTime(), P1bomb2Clock.getElapsedTime(), Clock1, Clock2); /// method deleting bombs after elapsed time


		p2.update();
		window.draw(p2);

		p2.handlePlayerBombs();
		p2.FindOponent(p1.getIndexY(), p1.getIndexX(), p1.getSprite());

		std::vector<Bomb*> bombyP2 = p2.getBombs();

		if (bombyP2[0] != nullptr && Clock3 == false) { P2bomb1Clock.restart(); Clock3 = true; }
		if (bombyP2[1] != nullptr && Clock4 == false) { P2bomb2Clock.restart(); Clock4 = true; }


		if (P2bomb1Clock.getElapsedTime().asSeconds() >= 3 && blow3.getStatus() != sf::Sound::Playing && Clock3 == true) {
			blow3.play();
			if (bombyP2[0]->HurtedPlayers(mapPointer, p2.getIndexY(), p2.getIndexX())) p2.PlayerGotHurt();
			if (bombyP2[0]->HurtedPlayers(mapPointer, p1.getIndexY(), p1.getIndexX())) p1.PlayerGotHurt();
			bombyP2[0]->Blow(mapPointer/*, p1Point, p2Point*/);
			p1.setBeki(mapPointer->getBeki());
			p2.setBeki(mapPointer->getBeki());
			Clock3 = false;  
		}
		if (P2bomb2Clock.getElapsedTime().asSeconds() >= 3 && blow4.getStatus() != sf::Sound::Playing && Clock4 == true) { 
			blow4.play();
			if (bombyP2[1]->HurtedPlayers(mapPointer, p2.getIndexY(), p2.getIndexX())) p2.PlayerGotHurt();
			if (bombyP2[1]->HurtedPlayers(mapPointer, p1.getIndexY(), p1.getIndexX())) p1.PlayerGotHurt();
			bombyP2[1]->Blow(mapPointer/*, p1Point, p2Point*/);
			p1.setBeki(mapPointer->getBeki());
			p2.setBeki(mapPointer->getBeki());
			Clock4 = false; 
		}

		p2.BlowIt(P2bomb1Clock.getElapsedTime(), P2bomb2Clock.getElapsedTime(), Clock3, Clock4);

		if (p1.CheckPlayerHP()) { /// checking if player one is dead
			if (win.getStatus() != sf::Sound::Playing) win.play(); /// playing victory sound 
			window.draw(P2WonSprite); /// drawing victory screen for player 2
			notEnd = false; /// pausing the game
		}
		/** The above describes same detection for player two */
		if (p2.CheckPlayerHP()) {
			if (win.getStatus() != sf::Sound::Playing) win.play();
			window.draw(P1WonSprite);
			notEnd = false;
		}

		window.display(); /// displying everything on screen
	}



	map.~Mapa(); /// cleaning after the game has been finished and game window closed, to prevent memory leaks

	return 0;
}

