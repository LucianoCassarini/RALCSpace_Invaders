#include "EnemyBullet.h"
#include <cmath>
using namespace std;

EnemyBullet::EnemyBullet() {}

EnemyBullet::EnemyBullet( sf::Vector2f enemyPos, sf::Texture &t ){
	
	///Textura
	spEnemyBullet.setTexture(t);

	Alive=true;
	
	spEnemyBullet.setScale((25.f / (spEnemyBullet.getTexture()->getSize().x)), 45.f / spEnemyBullet.getTexture()->getSize().y);
	spEnemyBullet.setPosition(enemyPos.x+7,enemyPos.y);
	spEnemyBullet.rotate(180.f);
	
	///Vector de movimiento
	vectorDir.x = 0;															///Direccion del movimiento (0 en x y -playerPos en y)
	vectorDir.y = enemyPos.y;
	Large = sqrt( ( pow( vectorDir.x, 2 ) ) + ( pow( vectorDir.y, 2 ) ) );					///Largo del vector
	vectorDirN = ( vectorDir / Large );												///Lo normalizo
}

EnemyBullet::~EnemyBullet() {}

void EnemyBullet::update() {
	
	///Limites de la bala
	bulletPos = spEnemyBullet.getPosition();
	if(bulletPos.y < 0 or bulletPos.y > 600){
		Alive = false;
	}
	
	///Movimiento de la bala
	spEnemyBullet.move(0 * bulletSpeed,vectorDirN.y * bulletSpeed);

}

bool &EnemyBullet::isAlive(){
	return Alive;
}

sf::Sprite & EnemyBullet::getSprite(){
	
	///Sprite de la bala
	return spEnemyBullet;
}

void EnemyBullet::draw( sf::RenderWindow &w ){
	w.draw( spEnemyBullet );
}

bool EnemyBullet::collidesWith( Entity *e ){
	
	sf::FloatRect thisRect = this->getSprite().getGlobalBounds();
	sf::FloatRect eRect = e->getSprite().getGlobalBounds();
	return thisRect.intersects(eRect);

}
