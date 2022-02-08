#include "Shield.h"
#include <SFML/Graphics/Texture.hpp>

Shield::Shield() {}

Shield::~Shield() {}

Shield::Shield( sf::Texture &t, float x, float y ){
	
	///Textura
	spShield.setTexture(t);
	
	///Origen del Sprite
	spShield.setOrigin( spShield.getLocalBounds().width/2, spShield.getLocalBounds().height/2 );
	
	///Escala
	spShield.setScale( 100.f / spShield.getTexture()->getSize().x, 60.f / spShield.getTexture()->getSize().y );
	
	///Posición
	spShield.setPosition( x , y );
	
	Alive = true;
}

void Shield::update(){}

void Shield::draw( sf::RenderWindow &w ){
	
	///Daño por impacto de balas
	spShield.setColor( sf::Color( 255, 255, 255, 128 + 255 / 30 * Lives ) );
	if( Alive ) w.draw( spShield );
}

bool &Shield::isAlive(){	return Alive;}

bool Shield::collidesWith( Entity *e ){
	sf::FloatRect thisRect = this->getSprite().getGlobalBounds();
	sf::FloatRect eRect = e->getSprite().getGlobalBounds();
	return thisRect.intersects( eRect );
}

sf::Sprite &Shield::getSprite(){	return spShield;}

int &Shield::getLivesCount(){	return Lives;}
