#include "PlayerBullet.h"
#include <cmath>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/Sound.hpp>
using namespace std;

PlayerBullet::PlayerBullet( sf::Vector2f playerPos, sf::Texture &t ) {
	
	///Textura
	spPlayerBullet.setTexture( t );
	
	Alive = true;
	
	///Escala
	spPlayerBullet.setScale( ( 15.f / ( spPlayerBullet.getTexture()->getSize().x ) ), 30.f / spPlayerBullet.getTexture()->getSize().y );
	
	///Posición
	spPlayerBullet.setPosition( playerPos.x-8, playerPos.y );
	
	///Vector de Movimiento
	vectorDir.x = 0;															///Direccion del movimiento (0 en x y -playerPos en y)
	vectorDir.y = -playerPos.y;
	Large = sqrt( ( pow( vectorDir.x,2 ) ) + ( pow( vectorDir.y,2 ) ) );		///Largo del vector
	vectorDirN = (vectorDir/Large);												///Lo normalizo	
	
}

PlayerBullet::~PlayerBullet(){}

void PlayerBullet::update(){
	
	///Limites de la bala
	bulletPos = spPlayerBullet.getPosition();
	if( bulletPos.y < 0 or bulletPos.y > 600 ){
		Alive = false;
	}
	
	///Movimiento de la bala
	spPlayerBullet.move( 0 * bulletSpeed, vectorDirN.y * bulletSpeed );

}

bool &PlayerBullet::isAlive(){	return Alive; }

sf::Sprite & PlayerBullet::getSprite(){	return spPlayerBullet; }

void PlayerBullet::draw(sf::RenderWindow &w){
	w.draw(spPlayerBullet);
}

bool PlayerBullet::collidesWith(Entity *e){
	
	sf::FloatRect thisRect = this->getSprite().getGlobalBounds();
	sf::FloatRect eRect = e->getSprite().getGlobalBounds();
	return thisRect.intersects(eRect);
	
}
