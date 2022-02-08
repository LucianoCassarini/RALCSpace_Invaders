#ifndef GAME_HPP
#define GAME_HPP
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "BaseScene.hpp"
#include <SFML/Window/Event.hpp>
using namespace std;


/***
 * Clase para manejar un bucle de juego con distintas escenas
 */
class Game {
public:
	~Game();
	
	/// comenzar el bucle de juego
	void GameLoop();
	
	/// cambiar la escena actual por otra 
	void switchScene(BaseScene *scene);
	
	/// obtener la instancia de juego
	static Game &getInstance();
	
	///crear un una instancia de juego especificando el modo de video y la escena inicial
	static Game &create(const sf::VideoMode &videoMode, BaseScene *scene, const string &name = "");

private:	
	///PANTALLA
	sf::RenderWindow w;
	
	///ESCENAS
	BaseScene *currentScene, *nextScene; ///Punteros a escenas para cambiar de pantalla
	
	Game();
	void update();
	void Events(sf::Event &E);
	void draw();
	static Game *instance; 				///De esta forma me aseguro que haya una sola ventana de juego
};

#endif

