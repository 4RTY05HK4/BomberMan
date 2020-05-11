#pragma once


class Sciana : public Pole /// Inherits after class Pole
{

	sf::Texture texture;
	std::string filename = "img/mur.png";

public:

	Sciana(float posX, float posY) {
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		sprite.setPosition(posX, posY);
	}

	/** This class represents the special case of class Pole. */

};