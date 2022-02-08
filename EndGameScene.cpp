#include "EndGameScene.h"
#include "Game.hpp"
#include "PlayScene.hpp"
#include "MenuScene.hpp"
#include <sstream>
#include "InputBox.h"
#include <SFML/Window/Event.hpp>
#include <vector>
#include <cstring>
using namespace std;

EndGameScene::EndGameScene( int s , vector<Score> &HS , bool win ) {
	
	///Fuente de texto
	foWinLose.loadFromFile( "Fonts/GOWFont.ttf" );
	
	///Variables de puntaje
	result = win;
	score = s;
	highScore = HS;
	
	///Booleanos de puntaje
	SS = false;
	ASS = false;
	
	///Fondo de pantalla
	texBackground.loadFromFile( "Images/EndGameBackground.png" );
	spBackground.setTexture( texBackground );
	spBackground.setScale( 800.f / texBackground.getSize().x,600.f / texBackground.getSize().y );
	
	if( win ){
		
		///Si el Player gana
		
		//	texWin.loadFromFile("Images/winImg.png");
		//	spWin.setTexture(texWin);
		//	spBackground.setScale(50.f / texWin.getSize().x,25.f / texWin.getSize().y);
		
		title1.setFont( foWinLose );
		title1.setString( "FELICITACIONES" );
		title1.setCharacterSize( 65 );
		title1.setPosition( sf::Vector2f( ( 800-title1.getLocalBounds().width ) / 2.0 - 25 , 100) );
		
		title2.setFont( foWinLose );
		title2.setString( "HAS GANADO" );
		title2.setCharacterSize( 65 );
		title2.setPosition( sf::Vector2f( ( 800-title2.getLocalBounds().width ) / 2.0 , 150 ) );
	}
	else{
		
		///Si el Player 
		///Imagen de perdedor
		texLose.loadFromFile( "Images/loseImg.png" );
		spLose.setTexture( texLose );
		spLose.setScale( 400.f / texLose.getSize().x , 200.f / texLose.getSize().y );
		spLose.setPosition( sf::Vector2f( ( 1040-spLose.getLocalBounds().width ) / 2.0 , 25) );
		
		///Títulos
		title1.setFont( foWinLose );
		title1.setString( "HAS PERDIDO!" );
		title1.setCharacterSize( 40 );
		title1.setPosition( sf::Vector2f( ( 800-title1.getLocalBounds().width ) / 2.0 , 230) );
	}
	
	///Variables de Ingreso de Puntajes
	///Ingreso de nombre
	nameText.setFont( foWinLose );
	nameText.setFont( foWinLose );
	nameText.setCharacterSize( 35 );
	nameText.setString( "Ingresa tu nombre: " );
	nameText.setPosition( 400-nameText.getLocalBounds().width / 2.0 , 270 );
	
	///Cuadro de texto
	texInput.loadFromFile( "Images/inputText.png" );
	spInput.setTexture( texInput );
	spInput.setOrigin( texInput.getSize().x / 2.0 , texInput.getSize().y / 2.0 );
	spInput.setScale( 450.f / texInput.getSize().x , 50.f / texInput.getSize().y );
	spInput.setPosition( 670-spInput.getLocalBounds().width / 2.0 , 335.f );
	
	///Variable de InputBox
	textIn.setFont( foWinLose );
	textIn.setColor( sf::Color::Black );
	textIn.setCharacterSize( 40 );
	textIn.setPosition( nameText.getPosition().x-20 , 310 );
	textIn.setMaxChars( 10 );
	textIn.setSingleWord( true );
	
	///Texto del puntaje
	scoreText.setFont( foWinLose );
	stringstream ss;
	ss << "Tu puntaje: " << score;
	scoreText.setString( ss.str() );
	scoreText.setCharacterSize( 35 );
	scoreText.setPosition( sf::Vector2f( ( 800-scoreText.getLocalBounds().width) / 2.0 , 350) );
	
	///Texto BackSpace
	backSpaceText.setFont( foWinLose );
	backSpaceText.setString( "Presione BACKSPACE para volver al menu principal" );
	backSpaceText.setCharacterSize( 25 );
	backSpaceText.setPosition( sf::Vector2f( ( 800-backSpaceText.getLocalBounds().width) / 2.0 , 350 ) );
	
	///Texto ESC
	escapeText.setFont( foWinLose );
	escapeText.setString( "Presione ESCAPE para salir" );
	escapeText.setCharacterSize( 25 );
	escapeText.setPosition( sf::Vector2f( ( 800-escapeText.getLocalBounds().width ) / 2.0 , 420 ) );
}

EndGameScene::EndGameScene(){}

EndGameScene::~EndGameScene(){}

void EndGameScene::windowEvents( sf::Event &E , sf::RenderWindow &w ){
	if(!nameFlag){
		
		///Cerrar luego de ingresar puntaje
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			w.close();
		}
	}
	if(nameFlag){
		textIn.processEvent(E);
		
		if (E.type==sf::Event::KeyPressed && E.key.code==sf::Keyboard::Return){
			if(textIn.getValue().size()){
				textIn.setEditable(false);
				inputName = textIn.getString();
				SS=true;
			}
		}
	}
}

void EndGameScene::writeScore(){
	string s1=highScore[0].name,s2=highScore[1].name,s3=highScore[2].name;
	
	if(score>=highScore[2].score and score>0){
		
		if(score>highScore[1].score){
			
			if(score>highScore[0].score){
				
				highScore[2].score=highScore[1].score;
				highScore[1].score=highScore[0].score;
				
				strcpy(highScore[2].name,s2.c_str());
				strcpy(highScore[1].name,s1.c_str());
				
				highScore[0].score=score;
				strcpy(highScore[0].name,inputName.c_str());
			}
			else{
				
				highScore[2].score=highScore[1].score;
				strcpy(highScore[2].name,s2.c_str());
				
				highScore[1].score=score;
				strcpy(highScore[1].name,inputName.c_str());
			}
		}
		else{
			
			highScore[2].score=score;
			strcpy(highScore[2].name,inputName.c_str());
		}
		
		ofstream arch("bin/score.bin",ios::binary|ios::trunc);
		
		for(auto i=0;i<3;i++){
			Score s;
		
			string c=highScore[i].name;;
			strcpy(s.name,c.c_str());
			
			s.score=highScore[i].score;
			arch.write((char*)&s,sizeof(s));
		}
		arch.close();
	}
	ASS=true;
}

void EndGameScene::update() {
	
	///Si aparece el caracter '|' al final de la cadena ingresada lo elimino
	if(nameFlag) {
		
		textIn.update();
		
		if(SS==true and ASS==false){
		
			auto it=--inputName.end();
			if((*it)=='|') it=inputName.erase(it);
			writeScore();
		}
		
		if(SS == true and ASS == true) nameFlag=false;
	}
	if(!nameFlag){
		
		///Volver al menú luego de ingresar el puntaje
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
		
			Game::getInstance().switchScene(new MenuScene());
		}
	}
}

void EndGameScene::draw(sf::RenderWindow &w){
	w.draw(spBackground);
	
	if(result){
//		w.draw(spWin);
		w.draw(title1);
		w.draw(title2);
	}
	else{
		w.draw(spLose);
		w.draw(title1);
	}
	
	if(nameFlag){
		
		w.draw(scoreText);
		w.draw(nameText);
		w.draw(spInput);
		w.draw(textIn);
	}
	else{
		w.draw(playAgainText);
		w.draw(backSpaceText);
		w.draw(escapeText);
	}
}
