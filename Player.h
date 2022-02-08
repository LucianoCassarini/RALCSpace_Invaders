#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Entity.hpp"
#include "PlayerBullet.h"
#include "Player.h"

class Player:public Entity {
public:
	
	///CONSTRUCTORES Y DESTRUCTOR
	Player();
	Player(const sf::Vector2f &PlayerPos,sf::Font &lifeFont);
	~Player();
	
	///FUNCIONES HEREDADAS DE ENTITY
	void update() override;
	void draw(sf::RenderWindow &w) override;
	sf::Sprite &getSprite() override;			///Devuelve el Sprite del Player
	bool collidesWith(Entity *e) override;		///Chequea Colisiones con otras Entidades
	
	///FUNCIONES PROPIAS DE LA CLASE	
	bool &isAlive();		///Devuelve el Estado (Vivo o Muerto)	
	int &getLivesCount();	///Devuelve la Ccntidad de Vidas

private:
	bool Alive;				///Estado (Vivo o Muerto)
	sf::Texture texPlayer;	///Textura del Player
	sf::Sprite spPlayer;	///Sprite del Player
	
	///BARRA DE VIDA
	sf::Texture texLife[4]; ///Array de Texturas de Barra de Vida
	sf::Sprite spLife[4];	///Array de Sprites de Barra de Vida
	sf::Text lifeText;		///Texto de la Barra de Vida
	int Lives=4;			///Con cada bala enemiga acercada resto 1 a las vidas y así cambia el sprite en draw()
};

#endif

