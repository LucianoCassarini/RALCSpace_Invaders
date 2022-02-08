#include "Game.hpp"
#include "PlayScene.hpp"
#include "MenuScene.hpp"
using namespace sf;

int main(int argc, char *argv[]){
	
	///Creo una nueva escena
	BaseScene *scene = new MenuScene();
	
	///Creo una instancia de juego
	Game &g = Game::create(sf::VideoMode(800, 600), scene, "RALC's Space Invaders");
	
	///Inicio el bucle de juego
	g.GameLoop();
	delete scene;
	
	return 0;
}

