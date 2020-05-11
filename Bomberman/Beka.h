#pragma once


class Beka : public sf::Drawable /// class Beka inherits after sfml class Drawable, this makes displaying barrels easier
{
	sf::Texture texture;
	std::string filename = "img/beka2.png";
	sf::Sprite sprite; 
	/** Only class fields needed are barrel texture and sprite. */

public:

	Beka(float posX, float posY) /// simple constructor creating a new barrel
	{ 
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		sprite.setPosition(posX, posY);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const /// inheriting after sf::Drawable requires this sfml function to be overwritten
	{
		target.draw(sprite, states);
	}

	bool isColliding(sf::Sprite PlayerSprite) /// function responsible for detecting collision with player
	{
		if (PlayerSprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) return true; 
		else return false;
		/** It uses an sfml function intersect to check if sprites are colliding with each other. It return true if they do and false if they don't. */
	}
};
