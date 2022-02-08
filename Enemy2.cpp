#include "Enemy2.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <SFML/System/Time.hpp>
using namespace std;

Enemy2::Enemy2() {}
Enemy2::~Enemy2() {}

Enemy2::Enemy2(sf::Texture &t,float x, float y, bool &dir){
	spEnemy2.setTexture(t);
	Enemy2Pos=sf::Vector2f(x,y);
	
	Alive=true;
	moveFlag = dir;
	
	spEnemy2.setOrigin(spEnemy2.getTexture()->getSize().x / 2, spEnemy2.getTexture()->getSize().y / 2);
	spEnemy2.setPosition(Enemy2Pos);
	if(moveFlag) spEnemy2.rotate(-90);
	else spEnemy2.rotate(90);
	spEnemy2.setScale(40.f / spEnemy2.getTexture()->getSize().x, 80.f / spEnemy2.getTexture()->getSize().y);
	
	
	vectorDir.x = Enemy2Pos.x+50;								///Direccion del movimiento (0 en x y -playerPos en y)
	vectorDir.y = 0;
	Large = sqrt((pow(vectorDir.x,2))+(pow(vectorDir.y,2)));	///Largo del vector
	vectorDirN = (vectorDir/Large);								///Lo normalizo
}

void Enemy2::update(){
	if(Alive){
		///Limites del Enemigo tipo 2
		Enemy2Pos = spEnemy2.getPosition();
		if(Enemy2Pos.x < 0 or Enemy2Pos.y > 800){
			Alive = false;
		}
		///Movimiento del Enemigo tipo 2
		if(moveFlag) spEnemy2.move(vectorDirN.x * enemy2Speed,0 * enemy2Speed);
		if(!moveFlag) spEnemy2.move(-vectorDirN.x * enemy2Speed,0 * enemy2Speed);
		if(Alive == false){
			spEnemy2.move(2000,0);
		}
	}
}

float Enemy2::getTime(){
	
	///Tiempo en segundos
	sf::Time t = ShootClock.getElapsedTime();
	return t.asSeconds();
}

sf::Clock &Enemy2::getClock(){
	
	///Reloj de balas
	return ShootClock; 
}

void Enemy2::draw( sf::RenderWindow &w ) {
	if( Alive ) w.draw( spEnemy2 );
}

const int Enemy2::getPPH() {
	
	///Puntos que otorga al morir
	return pointsPerHit; 
}

bool Enemy2::collidesWith ( Entity *e ) {
	
	sf::FloatRect thisRect = this->getSprite().getGlobalBounds();
	sf::FloatRect eRect = e->getSprite().getGlobalBounds();
	return thisRect.intersects(eRect);
	
}

bool &Enemy2::isAlive() {	return Alive; }

sf::Sprite &Enemy2::getSprite() {	return spEnemy2; }
