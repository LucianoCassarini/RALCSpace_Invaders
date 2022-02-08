#include "PlayScene.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <sstream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Image.hpp>
#include "MenuScene.hpp"
#include "Game.hpp"
#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include "BaseScene.hpp"
#include <cstdlib>
#include <ctime>
#include "EndGameScene.h"

using namespace std;
using namespace sf;

PlayScene::~PlayScene(){
	delete player;
	
	if(playerBullets.size() > 0){
		
		auto it = playerBullets.begin();
		while(it != playerBullets.end() ){
			delete ( *it );
			it = playerBullets.erase( it );
		}
	}
	else playerBullets.clear();
	
	if(enemiesT2.size() > 0){
		
		auto it = enemiesT2.begin();
		while(it != enemiesT2.end() ){
			delete ( *it );
			it = enemiesT2.erase( it );
		}
	}
	else enemiesT2.clear();
	
	if(shields.size() > 0){
		
		auto it = shields.begin();
		while(it != shields.end() ){
			delete ( *it );
			it = shields.erase( it );
		}
	}
	else shields.clear();
	
	if(asteroids.size() > 0){
		
		auto it = asteroids.begin();
		while(it != asteroids.end() ){
			delete ( *it );
			it = asteroids.erase( it );
		}
	}
	else asteroids.clear();
	
	if( enemyBullets.size() > 0 ) {
		
		auto it = enemyBullets.begin();
		while(it != enemyBullets.end() ){
			delete ( *it );
			it = enemyBullets.erase( it );
		}
	}
	else enemyBullets.clear();
}

void PlayScene::windowEvents(sf::Event &E,sf::RenderWindow &w){}

PlayScene::PlayScene(){}

PlayScene::PlayScene( vector<Score> &HS ){
	
	srand(time(0));  ///REINICIO LA SEMILLA DEL RAND PARA LOS ENEMIGOS
	
	///Cargo la fuente del texto
	if( !fontScoreText.loadFromFile( "Fonts/cs_regular.ttf" ) ){
		cerr << "ERROR: no se encontro la fuente " << "Fonts/cs_regular.ttf" << endl;
	}
	
	///Creo el Player 1
	player = new Player( { 400.f, 550.f } , fontScoreText );
	
	///Vector de puntajes máximos
	highScore = HS;
	
	///Canción de Fondo
	playTheme.openFromFile( "Music/PlayTheme.wav" );
	playTheme.setVolume( 30 );
	playTheme.play();
	
	///Sonido de la PlayerBullet
	pShootBuff.loadFromFile( "Sound/playerShoot.wav" );
	pShootSound.setBuffer( pShootBuff );
	pShootSound.setVolume( 30 );
	
	///Sonido de las EnemyBullets
	eShootBuff.loadFromFile( "Sound/enemyShoot.wav" );
	eShootSound.setBuffer( eShootBuff );
	eShootSound.setVolume( 30 );
	
	///Sonido de muerte de los enemigos
	enemyDeathBuffer.loadFromFile( "Sound/invaderkilled.wav" );
	enemyDeath.setBuffer( enemyDeathBuffer );
	enemyDeath.setVolume( 30 );
	
	///Sonido de golpes al Player
	phBuffer.loadFromFile( "Sound/playerHitted.wav" );
	playerHitted.setBuffer( phBuffer );
	playerHitted.setVolume( 50 );
	
	///Sonido de la muerte del Asteroide
	asteroidBuffer.loadFromFile( "Sound/asteroidDeath.wav" );
	asteroidSound.setBuffer( asteroidBuffer );
	asteroidSound.setVolume( 30 );

	score = 0;			///Inicialización del puntaje actual y el boost actual
	boostScore = 0;
	showBoost = false;	///Booleano del boost
	
	///Fuente de los Textos
	scoreText.setFont( fontScoreText );
	boostScoreText.setFont( fontScoreText );
	highScoreText.setFont( fontScoreText );
	
	///Tamaño de los Textos
	scoreText.setCharacterSize( 15 );
	boostScoreText.setCharacterSize( 15 );
	highScoreText.setCharacterSize( 15 );
	
	///Posición de Textos
	scoreText.setPosition( sf::Vector2f( 350, 580 ) );
	boostScoreText.setPosition( sf::Vector2f( 620,560 ) );
	highScoreText.setPosition( sf::Vector2f( 30, 580 ) );
	
	stringstream tmpScore,tmpHS;
	tmpScore << "SCORE: " << score << endl;
	tmpHS << "HIGHSCORE 3: " << highScore[2].score << endl;
	
	scoreText.setString( tmpScore.str() );
	highScoreText.setString( tmpHS.str() );
	
	
	///Textura y Sprite del fondo
	texBackground.loadFromFile( "Images/PlayBackground.png" );
	spBackground.setTexture( texBackground );
	spBackground.setScale( 800.f / spBackground.sf::Sprite::getTexture() -> sf::Texture::getSize().x, 600.f / spBackground.sf::Sprite::getTexture() -> sf::Texture::getSize().y );
		
	///Inicializo los vectores de enemigos
	vector<Enemy*> enemies1(10);				///Enemigos fila 1
	vector<Enemy*> enemies2(10);				///Enemigos fila 2
	vector<Enemy*> enemies3(10);				///Enemigos fila 3
	
	///Texturas de enemigos tipo 1, tipo 2 y asteroides
	tPB.loadFromFile( "Images/misile.png" );
	tEB.loadFromFile( "Images/enemyBullet.png" );
	t1.loadFromFile( "Images/Enemy1.png" );
	t2.loadFromFile( "Images/Enemy2.png" );
	t3.loadFromFile( "Images/Enemy3.png" );
	t4.loadFromFile( "Images/Enemy4.png" );
	t5.loadFromFile( "Images/Enemy5.png" );
	t6.loadFromFile( "Images/Enemy6.png" );
	t7.loadFromFile( "Images/Enemy7.png" );
	t8.loadFromFile( "Images/Enemy8.png" );	
	
	tE2.loadFromFile( "Images/EnemyT2.png" );
	tAsteroid.loadFromFile( "Images/BigAsteroid.png" );
	tShield.loadFromFile( "Images/Shield.png" );
	
	///Fijo sus posiciones y sus límites de pantalla izquierdo y derecho
	///Luego los añado al vector de la clase base
	x=0, l=48, r=648, cantL=0, cantR=7;
	
	for( int i=0; i<10; i++ ) { 
		enemies3[i]=new Enemy(t1,c1,(48.f+x),100.f,(l+(52*cantL)),(r-(52*cantR)),30, true);
		
		enemies2[i]=new Enemy(t2,c1,(648.f+x),168.f,(l+(52*cantL)),(r-(52*cantR)),20, false);
		
		enemies1[i]=new Enemy(t3,c1,(48.f+x),236.f,(l+(52*cantL)),(r-(52*cantR)),10, false);
		
		x+=52;
		++cantL;
		--cantR;
	}
	enemies.push_back(enemies1);
	enemies.push_back(enemies2);
	enemies.push_back(enemies3);
	
	cantL=0;cantR=7;x=0;
	
	shoots=2, sTick = 0, enemyCount = 30;
	
	shields.resize(3);
	int c=0;
	for(auto i=0;i<3;i++){
		shields[i]=new Shield(tShield,200.f+c,500.f);
		c+=200;
	}
}

void PlayScene::addEnemyRow(){
	if(rowClock.getElapsedTime().asSeconds() > 11 and enemies.size()<12){
		vector<Enemy*> v;
		v.resize(10);
		
		if(row){
			for(auto i=0;i<v.size();i++){
				if( cRow==4 ) v[i] = new Enemy( t4, c1, (648.f+x), 100.f, (l+(52*cantL)), (r-(52*cantR)), cRow*10, true );
				
				if( cRow==6 ) v[i] = new Enemy( t6, c1, (648.f+x), 100.f, (l+(52*cantL)), (r-(52*cantR)), cRow*10, true );
				
				if( cRow==8 ) v[i] = new Enemy( t8, c1, (648.f+x), 100.f, (l+(52*cantL)), (r-(52*cantR)), cRow*10, true );
				
				if( cRow>8 ) v[i] = new Enemy( t8, c1, (648.f+x), 100.f, (l+(52*cantL)), (r-(52*cantR)), cRow*10, true );
				
				x+=52;
				++cantL;
				--cantR;
			}
			row = false;
			alive += 10;
			cantEnemy += 10;
			cantL = 0; cantR = 7; x = 0;
			
			cRow++;
			enemies.push_back(v);
			rowClock.restart();
		}
		else{
			for(auto i=0; i<v.size(); i++){
				if( cRow==5 ) v[i] = new Enemy( t5, c1, (48.f+x), 100.f, (l+(52*cantL)), (r-(52*cantR)), cRow*10, false );
				
				if( cRow==7 ) v[i] = new Enemy( t7, c1, (48.f+x), 100.f, (l+(52*cantL)), (r-(52*cantR)), cRow*10, false );
				
				if( cRow>8 ) v[i] = new Enemy( t7, c1, (48.f+x), 100.f, (l+(52*cantL)), (r-(52*cantR)), cRow*10, false );
				
				x+=52;
				++cantL;
				--cantR;
			}
			row=true;
			alive+=10;
			cantEnemy+=10;
			cantL=0;cantR=7;x=0;
			
			cRow++;
			enemies.push_back(v);
			rowClock.restart();
		}
	}
}

void PlayScene::update(){
	
	///Mientras el player siga vivo el juego se ejecuta
	if( player->isAlive() == true ){
		
		///UPDATE DEL PLAYERBULLET
		player -> update();
		
		
		///PUNTAJE
		if(score > highScore[2].score){
			
			///Si el jugador supera el 3er puntaje
			stringstream ss;
			ss << "HIGHSCORE 2: " << highScore[1].score << endl;
			highScoreText.setString( ss.str() );
		}
		
		if(score > highScore[1].score){
			
			///Si el jugador supera el 2do puntaje
			stringstream ss;
			ss << "HIGHSCORE 1: " << highScore[0].score << endl;
			highScoreText.setString( ss.str() );
		}
		
		///MANEJO DEL Boost
		if( !showBoost ) boostClock.restart();
		if( showBoost and boostClock.getElapsedTime().asSeconds() > 2 ) showBoost = false;
		
	///BALAS DEL PLAYER	
		///CREACION DE BALAS DEL PLAYER
		if (isPlayerShooting() == true){
			
			///Si devuelve True se crea
			b = new PlayerBullet( player->getSprite().getPosition(), tPB );
			playerBullets.push_back(b);
			
			pShootSound.play();
		}
		
		///ELIMINACION DE PLAYERBULLETS
		auto itPB = playerBullets.begin();
		while( itPB != playerBullets.end() ){
			if( (*itPB) -> isAlive() == true){
				(*itPB)->update();
				itPB++;
			}
			else{
				delete *itPB;
				itPB=playerBullets.erase(itPB);
			}
		}
		
	///ELIMINACIÓN DE ESCUDOS DEL PLAYER
		auto itS = shields.begin();
		while( itS != shields.end() ){
			if( ( *itS ) -> isAlive() == true ){
				( *itS ) -> update();
				itS++;
			}
			else{
				delete *itS;
				itS=shields.erase( itS );
			}
		}
		
	///ENEMIGOS
		///MANEJO DE DISPAROS DE ENEMIGOS
		EnemyManagement();
		
		///SPAWN de filas de enemigos
		addEnemyRow();
		
		///Eliminación de enemigos MUERTOS
		auto itE = enemies.begin();
		while( itE != enemies.end() ){
			
			if(itE -> size() > 0 ){
				
				auto it = itE->begin();
				while( it != itE -> end() ){
					if( (*it) -> isAlive() == true ){
						(*it) -> update();
						it++;
					}
					
					else{
						delete ( *it );
						it = itE -> erase( it );
					}
				}
				
				itE++;
			}
			
			else{
				itE = enemies.erase( itE );
			}
		}
		
	///ASTEROIDES	
		///Creación de Asteroides
		createAsteroid();
		
		///Eliminacion de asteroides destruidos
		auto itA = asteroids.begin();
		while( itA != asteroids.end() ){
			if( (*itA) -> isAlive() == true){
				(*itA)->update();
				itA++;
			}
			else{
				delete *itA;
				itA=asteroids.erase(itA);
			}
		}
		
	///ENEMIGOS TIPO 2	
		///Creación de Enemigos tipo 2
		createEnemy2();
		
		///Eliminacion de enemigos tipo 2 MUERTOS
		auto itE2 = enemiesT2.begin();
		while( itE2 != enemiesT2.end() ){
			if( (*itE2) -> isAlive() == true){
				(*itE2)->update();
				itE2++;
			}
			else{
				delete *itE2;
				itE2=enemiesT2.erase(itE2);
			}
		}
		
		auto itEB = enemyBullets.begin();
		while( itEB != enemyBullets.end() ){
			if( (*itEB) -> isAlive() == true){
				(*itEB)->update();
				itEB++;
			}
			else{
				delete *itEB;
				itEB=enemyBullets.erase(itEB);
			}
		}

		///COLISIONES
		collisionManager();
		
		//VICTORIA
		///SI TODOS LOS ENEMIGOS ESTÁN MUERTOS EL PLAYER GANA LA PARTIDA
		if( Win() ) {
			eShootSound.stop();
			pShootSound.stop();
			enemyDeath.stop();
			playerHitted.stop();
			asteroidSound.stop();
			playTheme.stop();
			
			Game::getInstance().switchScene( new EndGameScene( score, highScore, true ) );
		}
		waitClock.restart();
	}
	else{
		if( waitClock.getElapsedTime().asSeconds() >3 ){ ///CUANDO EL PLAYER PIERDE LA PANTALLA SE CONGELA Y SALTA LA LOSERSCREEN
			///EL PLAYER PERDIO - ELIMINO TODO
			eShootSound.stop();
			pShootSound.stop();
			enemyDeath.stop();
			playerHitted.stop();
			asteroidSound.stop();
			playTheme.stop();
			
			///Como el player perdió voy a la LoserScene
			Game::getInstance().switchScene( new EndGameScene( score, highScore, false ) );
		}
	}
}

bool PlayScene::isPlayerShooting() {
	
	sf::Time shootingTime = shootClock.getElapsedTime();
	float TimeShoot = shootingTime.asSeconds();
	
	///Si se presiona la Space Bar y passan 0.5s retorna true para poder disparar
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) and ( TimeShoot > 0.5 ) ){
	   shootClock.restart();
		return true;
	}
	else return false;
}

void PlayScene::EnemyManagement() {

	for( auto i=0; i<enemies.size(); i++ ){
		for(const auto &e:enemies[i]){
			if(e->isAlive() == true){
				if( e->getSprite().getPosition().y > 500.f ){
				player->isAlive() = false;
			}
		}
	}
	
	if ( enemyClock.getElapsedTime().asSeconds() > .05f ) {
		sTick++;
		shoots = 2 + sTick / 160.f;
		
		bool doShoot = rand() % 25 * ( cantEnemy * 0.9f ) / alive < shoots; ///Dificil: cambio alive/cantEnemy
		if ( doShoot ) {
again:
			int i = rand() % enemies.size();
			auto eV = enemies[i];
			auto en = enemies[i][rand()%eV.size()];
			if ( en->isAlive() ){
				eB = new EnemyBullet( en->getSprite().getPosition() , tEB );
				
				enemyBullets.push_back(eB);
				
				eShootSound.play();
				
			}else{
				goto again;
			}
		}
		
		enemyClock.restart();
	}
}
}

void PlayScene::collisionManager(){ /// Detecta las colisiones entre disparos y los asteroides.
	for(const auto bb: playerBullets){
		for( auto i=0; i<enemies.size(); i++ ){
			for(const auto e:enemies[i]){
				if(e->isAlive()==true){
					if(bb->collidesWith(e)){
						e->isAlive() = false;
						bb->isAlive() = false;
						enemyDeath.play();
						
						boostScore+=1;
						alive--;
						
						score+=(e->getPPH());
						stringstream tmpScore;
						tmpScore<<"SCORE: "<<score<<endl;
						scoreText.setString(tmpScore.str());
					}
				}
			}
		}
		for(const auto e: enemiesT2){
			if( e->isAlive() == true ){
				if( bb->collidesWith( e ) ){
					e->isAlive() = false;
					bb->isAlive() = false;
					enemyDeath.play();
					
					boostScore+=1;
					
					score += ( e->getPPH() );
					stringstream tmpScore;
					tmpScore<<"SCORE: " << score << endl;
					scoreText.setString( tmpScore.str() );
				}
			}
		}
		for(const auto a: asteroids){
			if( a->isAlive() == true ){
				if( bb->collidesWith ( a ) ){
					a->isAlive() = false;
					bb->isAlive() = false;
					asteroidSound.play();
					
					boostScore +=1 ;
					
					score += ( a->getPPH() );
					stringstream tmpScore;
					tmpScore << "SCORE: " << score << endl;
					scoreText.setString( tmpScore.str() );
				}
			}
		}
		for(const auto sh:shields){
			if(sh->isAlive() == true ){
				if( bb->collidesWith( sh ) ){
					bb->isAlive() = false;
					
					sh->getLivesCount() -= 1;
					if( sh->getLivesCount() == 0 ) sh->isAlive() = false; 
				}
			}
		}
		for(const auto eBB: enemyBullets){
			if( eBB->isAlive() == true ){
				if( bb->collidesWith( eBB ) ){
					bb->isAlive() = false;
					eBB->isAlive() = false;
				}
			}
		}
	}
	for(const auto eBB: enemyBullets){
		if(eBB->collidesWith( player )){
			eBB->isAlive() = false;
			
			if(boostScore >= 2){
				stringstream boostS;
				boostS << "BOOST! +" << ( boostScore*10 ) << endl;
				boostScoreText.setString( boostS.str() );
				
				score += ( boostScore * 10 );
				boostScore = 0;
				showBoost = true;
				
				stringstream tmpScore;
				tmpScore << "SCORE: " << score << endl;
				scoreText.setString( tmpScore.str() );
			}
			
			player->getLivesCount()-=1;
			playerHitted.play();
			if( player->getLivesCount() == 0 ) player->isAlive() = false;
		}
		for(const auto sh:shields){
			if( sh->isAlive() == true ){
				
				if( eBB->collidesWith( sh ) ){
					eBB->isAlive() = false;
					sh->getLivesCount() -= 1;
					if( sh->getLivesCount() == 0 ) sh->isAlive() = false; 
				}
			}
		}
	}
	
	for(const auto a: asteroids){
		if( a->collidesWith( player ) ){
			a->isAlive() = false;
			
			if( boostScore >= 2 ){
				stringstream boostS;
				boostS << "BOOST! +" << ( boostScore * 10 ) << endl;
				boostScoreText.setString( boostS.str() );
				
				score +=( boostScore * 10 );
				boostScore = 0;
				showBoost = true;
				
				stringstream tmpScore;
				tmpScore << "SCORE: " << score << endl;
				scoreText.setString( tmpScore.str() );
			}
			
			player->getLivesCount() -= 1;
			playerHitted.play();
			if( player->getLivesCount() == 0 ) player->isAlive() = false;
		}
		for(const auto sh:shields){
			if(sh->isAlive() == true ){
				if( a->collidesWith( sh ) ){
					a->isAlive() = false;
					sh->getLivesCount() -= 1;
					if(sh->getLivesCount() == 0) sh->isAlive() = false;
				}
			}
		}
	}
}
void PlayScene::createAsteroid(){
	sf::Time timeAsteroid = asteroidTime.getElapsedTime();
	if(timeAsteroid.asSeconds() > 3){
		ast = new Asteroid(tAsteroid,player->getSprite().getPosition());
		asteroids.push_back(ast);
		asteroidTime.restart();
	}
}

void PlayScene::createEnemy2(){
	sf::Time timeEnemy2 = enemy2Clock.getElapsedTime();
	if(timeEnemy2.asSeconds() > 7){
		if(enemy2Flag){
			Enemy2* eT2=new Enemy2(tE2,0,50,enemy2Flag);
			enemiesT2.push_back(eT2);
			enemy2Flag=false;
		}
		else{
			Enemy2* eT2=new Enemy2(tE2,800,50,enemy2Flag);
			enemiesT2.push_back(eT2);
			enemy2Flag=true;
		}
		enemy2Clock.restart();
	}
	for(const auto e: enemiesT2){
		if(e->getTime() > 0.5f and e->isAlive() == true){
			eT2Bullet = new EnemyBullet(e->getSprite().getPosition(),tEB);
			enemyBullets.push_back(eT2Bullet);
			eShootSound.play();
			e->getClock().restart();
		}
	}
}

bool PlayScene::Win(){
	bool w = true;
	for( auto i = 0; i < enemies.size(); i++ ){
		for( const auto e : enemies[i] ){ 
			if( e -> isAlive() ){
				w = false;
				break;
			}
		}
	}
	return w;
}

void PlayScene::draw(sf::RenderWindow &w){
	w.draw(spBackground);
	///Todos los personajes se dibujan desde BaseScene
	
	player -> draw( w );
	
	///Dibujo todas las balas del Player
	for( auto i = 0; i < playerBullets.size(); i++ ){
		if(playerBullets[i] -> isAlive() == true) playerBullets[i]->draw(w);
	}	
	
	///Dibujo todos los escudos del Player
	for( auto i = 0; i < shields.size(); i++ ){
		if(shields[i] -> isAlive() == true) shields[i]->draw(w);
	}
	
	///Dibujo todos los asteroides que aparezcan
	for( auto i = 0; i < asteroids.size(); i++ ){
		if(asteroids[i] -> isAlive() == true) asteroids[i]->draw(w);
	}
	
	///Dibujo todos los enemigos
	for(auto i=0;i<enemies.size();i++){
		for(const auto &e : enemies[i]){
			if(e -> isAlive() == true) e->draw( w );
		}
	}
	
	///Dibujo todos los enemigos de tipo 2 (laterales)
	for(auto i=0; i<enemiesT2.size(); i++) {
		if(enemiesT2[i] -> isAlive() == true) enemiesT2[i] -> draw(w); 
	}
	
	///Dibujo todas las balas de los enemigos
	for( auto i = 0; i < enemyBullets.size(); i++ ){
		if(enemyBullets[i] -> isAlive() == true) enemyBullets[i]->draw(w);
	}
	
	///Dibujo los textos
	w.draw(scoreText);
	w.draw(highScoreText);
	if(showBoost) w.draw(boostScoreText);
}
