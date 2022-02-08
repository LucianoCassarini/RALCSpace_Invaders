#include "Game.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
using namespace std;

Game *Game::instance = nullptr;

Game::Game() {}

Game:: ~Game (){
	delete currentScene;
	delete nextScene;
	delete instance;
}

Game &Game::create( const sf::VideoMode &videoMode, BaseScene *scene, const string &name ){
	if( instance ){
		cerr << "ERROR: can't call create(), game already running." << endl; ///Por si el usuario intenta ejecutar dos veces el juego
	}
	else{
		Game & g = getInstance();
		g.w.create( videoMode, name, sf::Style::Close );
		g.nextScene = nullptr;
		g.currentScene = scene;
		g.w.setFramerateLimit( 60 );
	}
	return getInstance();
}


Game &Game::getInstance(){ ///Creo la instancia de juego
	if( !instance ){
		instance = new Game();
	}
	return *instance;
}

///Bucle principal del juego
void Game::GameLoop(){
	
	///Mientras la ventana está abierta
	while( w.isOpen() && currentScene != nullptr ) {
		sf::Event e;
		
		Events( e );
		update( );
		draw( );
		
		///Cambio a la escena siguiente
		if( nextScene != nullptr ){
			delete currentScene;
			currentScene = nextScene;
			nextScene = nullptr;
		}
	}
}

void Game::update(){
	
	///Actualizo la escena actual
	currentScene->update();
}

void Game::draw(){
	w.clear();
	
	///Dibujo la escena
	currentScene->draw( w );
	w.display();
}

void Game::switchScene( BaseScene *scene ){
	
	///Cambio a la siguiente escena
	nextScene = scene;
}


void Game::Events( sf::Event &E ) {
	
	///Bucle de eventos
	while( w.pollEvent( E ) ) {
		
		///Si el juego se cierra cierro la pantalla
		if(E.type == sf::Event::Closed ){
			w.close();
		}
		
		///Invoco los eventos de la escena actual
		currentScene->windowEvents(E,w);
	}
}
