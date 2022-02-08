#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "BaseScene.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Music.hpp>
#include "Player.h"
#include <vector>
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Enemy2.h"
#include "Asteroid.h"
#include "Shield.h"

using namespace std;

class PlayScene: public BaseScene{
private:
	
	///SCORE
	vector<Score> highScore;
	int score;								///Puntaje
	sf::Text highScoreText,scoreText;		///texto para mostrar el puntaje
	sf::Font fontScoreText;					///fuente del texto
	
	int shoots, sTick, enemyCount, alive = 30,cantEnemy=30;
	float x,l,r,cantL,cantR;
	sf::Clock rowClock;
	bool row=true;
	int cRow=4;
	
	///BONIFICACIÓN DE SCORE
	int boostScore;							///Puntaje Bonus
	sf::Text boostScoreText;				///Texto
	bool showBoost;							///Booleano que muestra el bonus
	sf::Clock boostClock;
	
	sf::Texture texBackground;				///Fondo de pantalla
	sf::Sprite spBackground;
	
	Player *player;							///El Player
	PlayerBullet *b;						///Bala
	vector<PlayerBullet*> playerBullets; 	///Balas del Player
	sf::Texture tPB;						///Textura de la Bala
	
	Shield* sh;								///Escudo
	vector<Shield*> shields;				///Vector de Escudos
	sf::Texture tShield;					///Textura del Escudo
	
	///ENEMIGOS CONTADOS DE ARRIBA HACIA ABAJO
	vector<vector<Enemy*>> enemies;
	sf::Texture t1,t2,t3,t4,t5,t6,t7,t8;	///Texturas de las filas
	EnemyBullet* eB;						///Bala enemiga
	sf::Texture tEB;						///Textura de la Bala
	vector<EnemyBullet*> enemyBullets; 		///Balas de los enemigos
	
	Enemy2* eT2;							///Enemigo tipo 2
	bool enemy2Flag=true;					///Bandera
	vector<Enemy2*> enemiesT2;				///Vector de Enemigos tipo 2
	EnemyBullet* eT2Bullet;					///Bala de Enemigo tipo 2
	sf::Texture tE2;						///Textura del Enemigo tipo 2
	
	Asteroid* ast;							///Asteroide
	vector<Asteroid*> asteroids;			///Vector de Asteroides
	sf::Texture tAsteroid;					///Textura del Asteroide
	
/**/sf::Music playTheme;
/**/sf::SoundBuffer pShootBuff, eShootBuff, enemyDeathBuffer,asteroidBuffer,phBuffer;
/**/sf::Sound pShootSound,eShootSound,enemyDeath,asteroidSound,playerHitted;
	
	sf::Clock c1,enemy2Clock,e2shootClock,shootClock,enemyClock, waitClock;
	sf::Clock asteroidTime;					///reloj de aparicion de Asteroides.
	sf::Clock enemy2Time;					///Reloj de aparicion de enemigos tipo 2
	bool moreRows=true;

public:

	///CONSTRUCTORES Y DESTRUCTOR
	PlayScene();
	PlayScene(vector<Score> &HS);
	~PlayScene();
	
	///FUNCIONES HEREDADAS DE BASESCENE
	void update();
	void windowEvents(sf::Event &E,sf::RenderWindow &w); ///TOMA  DE LA PANTALLA
	void draw(sf::RenderWindow &w);
	
	///FUNCIONES PROPIAS DE LA CLASE
	bool isPlayerShooting(); 							///Detecta si se dispara una bala.
	
	void addEnemyRow();
	
	void collisionManager(); 							///Detecta las colisiones entre Entidades (Player,Enemigos, 
														///Enemigos tipo 2, Balas, Escudos y  asteroides).
	
	void createAsteroid(); 								///Crea un nuevo Asteroide.
	void createEnemy2(); 								///Crea un nuevo Enemigo tipo 2 y controla la creación de sus balas.
	void EnemyManagement();								///Controla la creación de las Balas enemigas
	
	bool Win();											///Verifica si el Player ganó
};

#endif

