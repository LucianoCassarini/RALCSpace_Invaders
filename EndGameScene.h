#ifndef ENDGAMESCENE_H
#define ENDGAMESCENE_H
#include "BaseScene.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include "InputBox.h"
#include <vector>
using namespace std;

class EndGameScene: public BaseScene {
public:
	
	///CONSTRUCTORES Y DESTRUCTOR
	EndGameScene();
	EndGameScene(int s,vector<Score> &HS, bool win);
	~EndGameScene();
	
	///FUNCIONES HEREDADAS DE BASESCENE
	void update();
	void windowEvents(sf::Event &E,sf::RenderWindow &w);
	void draw(sf::RenderWindow &w);
	
	///FUNCIONES PROPIAS DE LA CLASE
	void writeScore();					///Guarda el puntaje en el binario
private:
	bool result;						///Resultado (Ganador o Perdedor)
	int score;							///Puntaje obtenido en la partida
	
	///Entrada de Texto
	bool nameFlag=true,SS,ASS;			///Booleanos de control
	vector<Score> highScore;			///Vector de 3 HIGHSCORES
	InputText textIn;					///Entrada de Texto por Pantalla
	string inputName;					///String de Entrada
	
	sf::Texture texInput;				///Textura de la Entrada de Texto
	sf::Sprite spInput;					///Sprite de la Entrada de Texto
	
	///PANTALLA
	sf::Text title1, title2,nameText, playAgainText, backSpaceText, escapeText, scoreText;	///Textos
	sf::Font foWinLose;					///Fuente del Texto
	
	sf::Texture texBackground;			///Textura del Fondo
	sf::Sprite spBackground;			///Sprite del Fondo
	
	///PANTALLA GANADOR
	
	///PANTALLA PERDEDOR
	sf::Texture texLose;				///Textura de Perdedor
	sf::Sprite spLose;					///Sprite de Perdedor
};

#endif

