#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Entity.hpp"

class EnemyBullet : public Entity {
public:
	
	///CONSTRUCTORES Y DESTRUCTOR
	EnemyBullet();
	EnemyBullet(sf::Vector2f enemyPos, sf::Texture &t);
	~EnemyBullet();
	
	///FUNCIONES HEREDADAS DE ENTITY
	void update() override;
	void draw(sf::RenderWindow &w)override;
	sf::Sprite &getSprite();					///Devuelve el Sprite de la Bala
	bool collidesWith(Entity *e) override;		///Chequea Colisiones con otras Entidades
	
	///FUNCIONES PROPIAS DE LA CLASE
	bool &isAlive();					///Devuelve el Estado (Vivo o Muerto)
	
private:
	bool Alive;							///Estado (Vivo o Muerto)
	
	sf::Sprite spEnemyBullet;			///Sprite de la Bala
	sf::Vector2f bulletPos;				///Posición de la Bala
	
	sf::Vector2f vectorDir;				///Vector de Dirección
	sf::Vector2f vectorDirN;			///Vector de Dirección Normalizado
	float Large;						///Largo del Vector
	
	float const bulletSpeed = 8;		///Velocidad de Movimiento
};

#endif

