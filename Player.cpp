#include "Player.h"
#include <sstream>
#include <SFML/Graphics/Font.hpp>
using namespace std;

Player::Player(){}

Player::~Player(){}

Player::Player(const sf::Vector2f &PlayerPos,sf::Font &lifeFont) {
	
	///Textura y Sprite del Player
	texPlayer.loadFromFile("Images/Player.png");
	spPlayer.setTexture(texPlayer);
	spPlayer.setPosition(PlayerPos);
	spPlayer.setOrigin(spPlayer.getTexture()->getSize().x / 2, spPlayer.getTexture()->getSize().y / 2);
	spPlayer.setScale(40.f / spPlayer.getTexture()->getSize().x, 40.f / spPlayer.getTexture()->getSize().y);
	
	Alive=true;
	
///BARRA DE VIDA
	
	///Texto
	lifeText.setFont(lifeFont);
	lifeText.setCharacterSize(15);
	lifeText.setPosition(sf::Vector2f(620, 580));
	lifeText.setString("VIDAS: ");
	
	for( auto i=0; i<4; i++ ){
		
		///Texturas
		stringstream tmp;
		tmp<<i+1;
		string s="Images/LifeBar"+tmp.str()+".png";
		texLife[i].loadFromFile(s);
		
		///Sprite
		spLife[i].setTexture(texLife[i]);
		
		spLife[i].setPosition(870.f,717.f);
		spLife[i].setOrigin(spLife[i].getPosition().x/2,spLife[i].getPosition().y/2);
		spLife[i].setScale(360.f/spLife[i].getPosition().x,270.f/spLife[i].getPosition().y);
	}
}

int &Player::getLivesCount(){	return Lives; }

void Player::update(){
	
	///Limites laterales del player
	sf::Vector2f charPos = spPlayer.getPosition();
	
	if(charPos.x < 25) charPos.x = 25;
	if(charPos.x > 775)	charPos.x = 775;
	
	spPlayer.setPosition(charPos);
	
///Acciones del teclado sobre Player
	///Movimiento a la izquierda
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){ 
		spPlayer.move(-5,0);
	}
	
	///Movimiento a la derecha
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){ 
		spPlayer.move(5,0);
	}
}

void Player::draw(sf::RenderWindow &w){
	w.draw(lifeText);
	w.draw(spPlayer);
	
	///A medida que baje la vida dibuja el Sprite correspondiente
	w.draw(spLife[4-Lives]);
}

bool &Player::isAlive(){	return Alive; }

sf::Sprite &Player::getSprite(){	return spPlayer; }

bool Player::collidesWith(Entity *e) {
	
	sf::FloatRect thisRect = this->getSprite().getGlobalBounds();
	sf::FloatRect eRect = e->getSprite().getGlobalBounds();
	return thisRect.intersects(eRect);

}
