#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP
#include "BaseScene.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <fstream>
#include <SFML/System/Clock.hpp>
#include <vector>
using namespace std;

class MenuScene : public BaseScene {
private:
	
	///PANTALLA
	sf::Text title1, title2, pressStartText,instructionsText, exitText;	///Textos
	sf::Font foMenu;							///Fuente de los Textos
	
	sf::Texture texBackground;					///Textura del fondo
	sf::Sprite spBackground;					///Sprite del fondo
	
	///MUSICA
	sf::Music menuTheme;						///Musica de fondo
	
	///INSTRUCCIONES DEL JUEGO
	bool instructions=false;					///Booleano para mostrarlas
	sf::Clock instructionsClock;				///Reloj de instrucciones
	sf::Texture texInstructionsBackground;		///Textura de las instrucciones
	sf::Sprite spInstructionsBackground;		///Sprite de las instrucciones
	
	///PUNTAJE
	vector<Score> highScore;					///VECTOR CON LOS 3 HIGHSCORES
	sf::Text highScore1,highScore2,highScore3;	///Texto de los HIGHSCORES
	///Texto de los NOMBRES DEL HS
	sf::Text highScore1Names,highScore2Names,highScore3Names;
public:
	///CONSTRUCTOR Y DESTRUCTOR
	MenuScene();
	~MenuScene();
	
	///FUNCIONES HEREDADAS DE LA BASESCENE
	void update();
	void windowEvents(sf::Event &E,sf::RenderWindow &w);
	void draw(sf::RenderWindow &w);
	
	///FUNCIONES PROPIAS DE LA CLASE
	void readScore();							///Leo los puntajes del binario
};

#endif

