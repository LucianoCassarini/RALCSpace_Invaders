#ifndef ASTEROID_H
#define ASTEROID_H
#include "Entity.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "Asteroid.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class Asteroid : public Entity {
public:
	
	///CONSTRUCTORES Y DESTRUCTOR
	Asteroid();
	Asteroid(sf::Texture &t,sf::Vector2f playerPos/*,sf::SoundBuffer &sb*/);
	~Asteroid();
	
	///FUNCIONES HEREDADAS DE ENTITY
	void update() override;
	void draw (sf::RenderWindow & w) override;
	sf::Sprite &getSprite() override;				///Devuelve el Sprite del Enemigo
	bool collidesWith(Entity *e) override;			///Chequea Colisiones con otras Entidades
	
	///FUNCIONES PROPIAS DE LA CLASE
	bool &isAlive();				///Devuelve el Estado (Vivo o Muerto)
	const int getPPH();				///Devuelve los puntos ganados por matarlo
private:
	int pointsPerHit=5;				///Puntos que otorga al matarlo
	sf::Sprite spAsteroid;			///Sprite del Asteroide
	bool Alive;						///Estado (Vivo o Muerto)
	
//	sf::Sound moveSound;
	sf::Vector2f asteroidPos;		///Posición del Asteroide en Pantalla
	sf::Vector2f VectorDir;			///Vector de Dirección
	sf::Vector2f VectorDirN;		///Vector de Dirección Normalizado
	float Large,Angle;				///Largo del Vector y Ángulo de Rotación
	
	const int asteroidSpeed=7;		///Velocidad de Movimiento
};

#endif

