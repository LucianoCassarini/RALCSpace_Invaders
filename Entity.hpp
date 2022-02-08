#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Entity {
public:
virtual void update() = 0;
virtual void draw(sf::RenderWindow &w) = 0;
virtual bool collidesWith(Entity *e) = 0;
virtual sf::Sprite &getSprite() = 0;
};

#endif

