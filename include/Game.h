#pragma once

#include"map"
#include"string"
#include"sstream"
#include"D:\MakeFileTemplate-main\C++\_SFML\include\Player.h"
#include"D:\MakeFileTemplate-main\C++\_SFML\include\Pelor.h"
#include"D:\MakeFileTemplate-main\C++\_SFML\include\Londo.h"

class Game
{
private:
	//Window
	sf::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<pelor*> pelorakeh;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Player
	Player* player;

	//londoakeh
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Londo*> londoakeh;

	//Private functions
	void initWindow();
	void initTextures();
	void initWorld();

	void initPlayer();
	void initLondoakeh();

public:
	Game();
	virtual ~Game();

	//Functions
	void run();
	void updatePollEvents();
	void updateInput();
	void updateWorld();
	void updateCollision();
	void updatepelorakeh();
	void updateLondoakeh();
	void updateCombat();
	void update();
	void renderWorld();
	void render();
};

