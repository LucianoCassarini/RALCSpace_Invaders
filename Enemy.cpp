#include "Enemy.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
using namespace sf;

Enemy::Enemy(){}

Enemy::~Enemy(){}

Enemy::Enemy( sf::Texture &t, sf::Clock &c1, float x, float y, float lLimit, float rLimit, int HP, bool dir ) {
	
	///Textura
	spEnemy.setTexture( t );
	
	///Posicion
	EnemyPos = Vector2f( x, y );
	
	///Límite lateral izquierdo
	leftLimit = lLimit;
	
	///Límite lateral derecho
	rightLimit = rLimit;
	
	///Les doy origen en el centro de la textura, los posiciono, los roto 180 grados y los escalo al mismo tamaño
	///de la textura de Player
	spEnemy.setOrigin( spEnemy.getTexture()->getSize().x / 2, spEnemy.getTexture()->getSize().y / 2 );
	spEnemy.setPosition( x, y );
	spEnemy.rotate( 180 );
	spEnemy.setScale( 40.f / spEnemy.getTexture()->getSize().x, 40.f / spEnemy.getTexture()->getSize().y );
	
	///Reloj de movimiento hacia adelante
	moveClock=c1;

	Alive=true;
	
	///Puntos que otorga al morir
	pointsPerHit=HP;
	
	///Variables de movimiento
	rate=.2f;
	totalMoveCount=0;
	moveCount=0;
	acceleration=.006f;
	moveFlag = dir;
}

float &Enemy::getLLimit(){	return leftLimit;}

float &Enemy::getRLimit(){	return rightLimit;}

void Enemy::update(){
	if(Alive){
		if(moveClock.getElapsedTime().asSeconds()>rate){
			
			if(spEnemy.getPosition().x < leftLimit){
				spEnemy.setPosition(leftLimit,spEnemy.getPosition().y);
				moveFlag=false;
				Crash();
			}
			
			if(spEnemy.getPosition().x > rightLimit){
				spEnemy.setPosition(rightLimit,spEnemy.getPosition().y);
				moveFlag=true;
				Crash();
			}
			
			if(moveFlag){
				spEnemy.move(-15,0);
			}
			else{
				spEnemy.move(15,0);
			}
			moveClock.restart();
		}
		if (moveCount >= 2) {
			moveCount = 0;
			spEnemy.move(0,25);
		}
	}
}

void Enemy::Crash() {
	moveCount++;
	totalMoveCount++;
	///Velocidad de movimiento, a menos rate más rápido
	rate = -0.6f * (totalMoveCount * acceleration + 1) + .75f;
}

void Enemy::draw(sf::RenderWindow &w){
	if(Alive) w.draw(spEnemy);
}

const int Enemy::getPPH(){	return pointsPerHit;}

bool &Enemy::isAlive(){	return Alive;}

Sprite &Enemy::getSprite(){	return spEnemy;}

bool Enemy::collidesWith(Entity *e){
	sf::FloatRect thisRect = this->getSprite().getGlobalBounds();
	sf::FloatRect eRect = e->getSprite().getGlobalBounds();
	return thisRect.intersects(eRect);
}
