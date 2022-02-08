#include "Asteroid.h"
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <SFML/Audio/SoundBuffer.hpp>
using namespace std;

Asteroid::Asteroid() {}

Asteroid::~Asteroid() {}

Asteroid::Asteroid( sf::Texture &t, sf::Vector2f playerPos ) {
	
	///Textura
	spAsteroid.setTexture( t );
	
	///Origen del Sprite
	spAsteroid.setOrigin( spAsteroid.getLocalBounds().width / 2 , spAsteroid.getLocalBounds().height / 2 );
	
	///Escala
	spAsteroid.setScale( 40.f / spAsteroid.getTexture()->getSize().x , 40.f / spAsteroid.getTexture()->getSize().y );
	
	///Posición
	spAsteroid.setPosition( rand()%800 , rand()%50 );
	
	///Vector del Movimiento
	VectorDir.x = playerPos.x - spAsteroid.getPosition().x;			///Direccion de la velocidad (posicion fijada - posicion Player)
	VectorDir.y = playerPos.y - spAsteroid.getPosition().y;
	
	Large = sqrt( ( pow( VectorDir.x , 2 ) ) + ( pow ( VectorDir.y , 2 ) ) );		/// Largo del vector
	
	VectorDirN = ( VectorDir / Large );									/// Lo normalizo
	Angle = -atan2( VectorDirN.x, VectorDirN.y ) * 180 / 3.14;
	spAsteroid.setRotation( Angle );
	
	Alive=true;
}


void Asteroid::update (){
	if( Alive == false ){
		spAsteroid.move(0,2000);
	}
	
	if( Alive ){
		spAsteroid.move( VectorDirN.x * asteroidSpeed , VectorDirN.y * asteroidSpeed );
		
		asteroidPos=spAsteroid.getPosition();
		if( asteroidPos.x < 0 ) Alive = false;
		if( asteroidPos.x > 800 ) Alive = false;
		if( asteroidPos.y > 600 ) Alive = false;
		spAsteroid.setPosition( asteroidPos );
	}
}

void Asteroid::draw ( sf::RenderWindow & w ) {
	if( Alive ) w.draw( spAsteroid );
}

bool &Asteroid::isAlive(){
	return Alive;
}

const int Asteroid::getPPH(){
	return pointsPerHit;
}

sf::Sprite &Asteroid::getSprite(){	///devuelve el sprite del asteroide
	return spAsteroid;
}
bool Asteroid::collidesWith(Entity *e){	///Devuelve un booleano si el sprite colisiona contra otro

	sf::FloatRect thisRect = this->getSprite().getGlobalBounds();
	sf::FloatRect eRect = e->getSprite().getGlobalBounds();
	return thisRect.intersects(eRect);

}
