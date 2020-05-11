#pragma once

class Pole : public sf::Drawable  /** This class represents general field. Two inheriting classes represent special case of field. Pole can be represented as Podloga or Sciana.Depending on that player can either collide with that field(in case of walls(Sciana)), or walk over it(in case of floor(Podloga)) */
{

public:

	sf::Sprite sprite;
	Pole() {}
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const /// inheriting after sf::Drawable requires this sfml function to be overwritten
	{
		target.draw(sprite, states);
	}


	bool isColliding(sf::Sprite PlayerSprite) /// Function used to check collision
	{
		if (PlayerSprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) return true;
		else return false;
		/** This function returns true if player is colliding with field and false if it's not. 
		It is not specified here with what player should collide and with what he shouldn't. That is specified in 
		class Gracz method update().*/

	}

	//bool isColliding(sf::Sprite Playersprite) {

	//	sf::FloatRect shape1 = Playersprite.getGlobalBounds();
	//	sf::FloatRect shape2 = sprite.getGlobalBounds();

	//	if (Playersprite.getPosition().x < sprite.getPosition().x + shape2.width &&
	//		Playersprite.getPosition().x + shape1.width > sprite.getPosition().x &&
	//		Playersprite.getPosition().y < sprite.getPosition().y + shape2.height &&
	//		shape1.height + Playersprite.getPosition().y > sprite.getPosition().y) return true;
	//	else return false;
	//}

	/** This class represents general field. Two inheriting classes represent special case of field. Pole can be represented
	as Podloga or Sciana. Depending on that player can either collide with that field (in case of walls (Sciana)),
	or walk over it (in case of floor (Podloga))*/

};
