#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Enemy.h"
#include "Entity.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Enemy : public Entity {
public:
	
	///CONSTRUCTORES Y DESTRUCTOR
	Enemy();
	Enemy(sf::Texture &t,sf::Clock &c1,float x, float y, float lLimit,float rLimit,int HP, bool dir);
	~Enemy();
	
	///FUNCIONES HEREDADAS DE ENTITY
	void update() override;
	void draw(sf::RenderWindow &w) override;
	sf::Sprite &getSprite() override;			///Devuelve el Sprite del Enemigo
	bool collidesWith(Entity *e) override;		///Chequea Colisiones con otras Entidades
	
	///FUNCIONES PROPIAS DE LA CLASE
	bool &isAlive();				///Devuelve el Estado (Vivo o Muerto)
	
	void Crash();					///Chequea que toque un l�mite lateral
	float &getLLimit();				///Devuelve el l�mite izquierdo
	float &getRLimit();				///Devuelve el l�mite derecho
	
	const int getPPH();				///Devuelve los puntos ganados por matarlo
private:
	bool Alive;
	bool moveFlag=true;				///Bandera de Movimiento	
	float leftLimit,rightLimit;		///L�mites izquierdo y derecho
	
	int pointsPerHit;				///Puntos que otorga al matarlo
	
	///VARIABLES DE MOVIMIENTO LATERAL Y VERTICAL
	int moveCount,totalMoveCount;
	float rate,acceleration;
	
	sf::Clock moveClock; ///Reloj que cuenta los segundos para el movimiento del enemigo, toma por referencia el de PlayScene
	
	sf::Sprite spEnemy; 			///Sprite del Enemigo
	sf::Vector2f EnemyPos;			///Posici�n del Enemigo
};

#endif

