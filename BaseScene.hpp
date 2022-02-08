#ifndef BASESCENE_HPP
#define BASESCENE_HPP
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <fstream>
using namespace std;


/***
 * Representa una escena del juego.
 * Para crear una nueva clase de escena, heredar de �sta clase
 * y redefinir el comportamiento de los m�todos
 */ 

///STRUCT DE PUNTAJE
struct Score{
	char name[11]; 			///Nombre del Player - El tama�o es 11 por los 10 caracteres + el '/0'
	int score;				///Puntaje del Player
};
class BaseScene {
public:
	///CONSTRUCTOR Y DESTRUCTOR
	BaseScene();
	~BaseScene();
	
	///Funci�n que para actualizar la escena
	virtual void update() = 0;
	
	///Funci�n para dibujar la escena
	virtual void draw(sf::RenderWindow &w) = 0;
	
	///Funci�n para manejar los eventos de Pantalla
	virtual void windowEvents(sf::Event &E, sf::RenderWindow &w) = 0;
};

#endif

