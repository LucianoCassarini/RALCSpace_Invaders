#ifndef SHIELD_H
#define SHIELD_H
#include <SFML/Graphics/Sprite.hpp>
#include "Entity.hpp"
#include "Shield.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Shield : public Entity {
public:
	
	///CONSTRUCTORES Y DESTRUCTOR
	Shield();
	Shield(sf::Texture &t,float x, float y);
	~Shield();
	
	///FUNCIONES HEREDADAS DE ENTITY
	void update() override;
	void draw(sf::RenderWindow &w) override;
	sf::Sprite& getSprite() override;			///Devuelve el Sprite de la Bala
	bool collidesWith(Entity *e) override;		///Chequea Colisiones con otras Entidades
	
	///FUNCIONES PROPIAS DE LA CLASE
	int &getLivesCount();	///Devuelve la cantidad de Vidas
	bool &isAlive();		///Devuelve el Estado (Vivo o Muerto)
	
private:
	bool Alive;				///Estado (Vivo o Muerto)
	sf::Sprite spShield;	///Sprite de Escudo
	
	int Lives=15;			///Cantidad de Vidas
	
};

#endif

