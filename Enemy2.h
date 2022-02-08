#ifndef ENEMY2_H
#define ENEMY2_H
#include "Entity.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>

class Enemy2 : public Entity {
public:
	
	///CONSTRUCTORES Y DESTRUCTOR
	Enemy2();
	Enemy2(sf::Texture &t,float x, float y, bool &dir);
	~Enemy2();
	
	
	///FUNCIONES HEREDADAS DE ENTITY
	void update() override;
	void draw(sf::RenderWindow &w) override;
	sf::Sprite &getSprite() override;			///Devuelve el Sprite del Enemigo
	bool collidesWith(Entity *e) override;		///Chequea Colisiones con otras Entidades
	
	///FUNCIONES PROPIAS DE LA CLASE
	bool &isAlive();				///Devuelve el Estado (Vivo o Muerto)
	
	float getTime();				///Devuelve el Tiempo en Segundos
	sf::Clock &getClock();			///Devuelve el Reloj de las Balas
	
	const int getPPH();				///Devuelve los puntos ganados por matarlo
private:
	bool Alive;						///Estado (Vivo o Muerto)
	bool moveFlag;					///Bandera de Movimiento
	
	int pointsPerHit=50;			///Puntos que otorga al matarlo
	
	sf::Sprite spEnemy2;			///Sprite del Enemigo
	sf::Vector2f Enemy2Pos;			///Posición del Enemigo
	sf::Clock ShootClock;			///Reloj de Balas
	
	sf::Vector2f vectorDir;			///Vector de Dirección
	sf::Vector2f vectorDirN;		///Vector de Dirección Normalizado
	float Large;					///Largo del Vector
	
	float const enemy2Speed = 5;	///Velocidad de Movimiento
};

#endif

