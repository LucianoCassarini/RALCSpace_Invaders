#include "MenuScene.hpp"
#include <iostream>
#include "Game.hpp"
#include "PlayScene.hpp"
#include <sstream>
#include <SFML/Audio/Music.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include "EndGameScene.h"
#include <cstring>
using namespace std;
using namespace sf;

MenuScene::~MenuScene(){
	menuTheme.stop();
}
void MenuScene::windowEvents(sf::Event &E,sf::RenderWindow &w){	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		menuTheme.stop();
		w.close();
	}
}
MenuScene::MenuScene(){
	///Leo los puntajes
	readScore();
	
	///Fuente de texto
	foMenu.loadFromFile("Fonts/cs_regular.ttf");
	
	///Música de fondo
	menuTheme.openFromFile("Music/MenuTheme.wav");
	menuTheme.setVolume(15);
	menuTheme.play();
	
	///Textos de puntaje
	highScore1Names.setFont(foMenu);
	highScore2Names.setFont(foMenu);
	highScore3Names.setFont(foMenu);
	highScore1.setFont(foMenu);
	highScore2.setFont(foMenu);
	highScore3.setFont(foMenu);
	
	stringstream ssN1,ss1,ssN2,ss2,ssN3,ss3;
	ssN1<<"1: "<<"NOMBRE: "<<highScore[0].name;
	ss1<<"PUNTAJE: "<<highScore[0].score;
	ssN2<<"2: "<<"NOMBRE: "<<highScore[1].name;
	ss2<<"PUNTAJE: "<<highScore[1].score;
	ssN3<<"3: "<<"NOMBRE: "<<highScore[2].name;
	ss3<<"PUNTAJE: "<<highScore[2].score;
	
	highScore1Names.setString(ssN1.str());
	highScore2Names.setString(ssN2.str());
	highScore3Names.setString(ssN3.str());
	
	highScore1.setString(ss1.str());
	highScore2.setString(ss2.str());
	highScore3.setString(ss3.str());
	
	highScore1Names.setCharacterSize(17);
	highScore2Names.setCharacterSize(17);
	highScore3Names.setCharacterSize(17);
	
	highScore1.setCharacterSize(17);
	highScore2.setCharacterSize(17);
	highScore3.setCharacterSize(17);
	
	///Posicion de Textos
	highScore1Names.setPosition(sf::Vector2f(30, 510));
	highScore2Names.setPosition(sf::Vector2f(30, 540));
	highScore3Names.setPosition(sf::Vector2f(30, 570));
	
	highScore1.setPosition(sf::Vector2f(260, 510));
	highScore2.setPosition(sf::Vector2f(260, 540));
	highScore3.setPosition(sf::Vector2f(260, 570));
	
	///Titulos
	title1.setFont(foMenu);
	title1.setString("RALC`s");
	title1.setCharacterSize(40);
	title1.setCharacterSize(40);
	title1.setPosition(sf::Vector2f((800-title1.getLocalBounds().width)/2.0 - 200, 80));
	
	title2.setFont(foMenu);
	title2.setString("Space Invaders");
	title2.setCharacterSize(65);
	title2.setPosition(sf::Vector2f((800-title2.getLocalBounds().width)/2.0, 100));
	
	///Texto de Start
	pressStartText.setFont(foMenu);
	pressStartText.setString("Presione ENTER para comenzar");
	pressStartText.setCharacterSize(20);
	pressStartText.setPosition(sf::Vector2f((800-pressStartText.getLocalBounds().width)/2.0, 300));
	
	///Texto Space Bar
	instructionsText.setFont(foMenu);
	instructionsText.setString("Presione BARRA ESPARCIADORA para  ver las instrucciones");
	instructionsText.setCharacterSize(20);
	instructionsText.setPosition(sf::Vector2f((800-instructionsText.getLocalBounds().width)/2.0, 350));
	
	///Texto ESC
	exitText.setFont(foMenu);
	exitText.setString("Presione ESCAPE para salir");
	exitText.setCharacterSize(20);
	exitText.setPosition(sf::Vector2f((800-exitText.getLocalBounds().width)/2.0, 400));
	
	///Fondo de pantalla
	texBackground.loadFromFile("Images/MenuBackground.jpg");
	spBackground.setTexture(texBackground);
	spBackground.setScale(800.f / texBackground.getSize().x,600.f / texBackground.getSize().y);

	///Pantalla de Instrucciones
	texInstructionsBackground.loadFromFile("Images/InstructionsBackground.png");
	spInstructionsBackground.setTexture(texInstructionsBackground);
	
}

void MenuScene::update(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		menuTheme.stop();
	}
	
	///Iniciar juego
	if(!instructions){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
			menuTheme.stop();
			Game::getInstance().switchScene(new PlayScene(highScore));
		}
	}
	
	///Mostrar instrucciones
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && instructionsClock.getElapsedTime().asSeconds() > 0.5){
		instructionsClock.restart();
		if(!instructions) instructions=true;
	}
	
	///Cerrar instrucciones
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && instructionsClock.getElapsedTime().asSeconds() > 0.5){
		instructionsClock.restart();
		if(instructions) instructions=false;
	}
}

void MenuScene::readScore(){
	Score s;
	ifstream arch("bin/score.bin",ios::binary|ios::ate);
	arch.seekg(0,ios::end);
	int fsize = arch.tellg();
	if(fsize){
		int i=0;
		arch.seekg(0,ios::beg);
		for(auto i=0;i<3;i++){
			arch.read((char*)&s,sizeof(s));
			highScore.push_back(s);
		}
	}else {
		string c=" ";
		strcpy(s.name,c.c_str());
		s.score=0;
		for(auto i=0;i<3;i++){
			highScore.push_back(s);
		}
	}
	arch.close();
}

void MenuScene::draw(sf::RenderWindow &w){
	if(!instructions){
		w.draw(spBackground);
		w.draw(title1);
		w.draw(title2);
		w.draw(pressStartText);
		w.draw(instructionsText);
		w.draw(exitText);
		w.draw(highScore1Names);
		w.draw(highScore2Names);
		w.draw(highScore3Names);
		w.draw(highScore1);
		w.draw(highScore2);
		w.draw(highScore3);
	}
	else{
		w.draw(spInstructionsBackground);
	}
}
