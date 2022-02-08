#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "Entity.hpp"

class PlayerBullet:public Entity {
public:
	
	///CONSTRUCTORES Y DESTRUCTOR
	PlayerBullet();
	PlayerBullet(sf::Vector2f playerPos,sf::Texture &t);
	~PlayerBullet();
	
	///FUNCIONES HEREDADAS DE ENTITY
	void update() override;
	void draw(sf::RenderWindow &w) override;
	sf::Sprite &getSprite();					///Devuelve el Sprite de la Bala
	bool collidesWith(Entity *e) override;		///Chequea Colisiones con otras Entidades
	
	///FUNCIONES PROPIAS DE LA CLASE
	bool &isAlive();				///Devuelve el Estado (Vivo o Muerto)

private:
	bool Alive;						///Estado (Vivo o Muerto)
	
	sf::Sprite spPlayerBullet;		///Sprite de la Bala
	sf::Vector2f bulletPos;			///Posición de la Bala
	
	sf::Vector2f vectorDir;			///Vector de Dirección
	sf::Vector2f vectorDirN;		///Vector de Dirección Normalizado
	float Large;					///Largo del Vector
	
	float const bulletSpeed = 10;	///Velocidad de Movimiento
};

#endif

