#include "D:\MakeFileTemplate-main\C++\_SFML\include\Game.h"

//Private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800,600), "Kisah Musim Panas", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["pelor"] = new sf::Texture();
	this->textures["pelor"]->loadFromFile("Textures/Pelor.png");
}

void Game::initWorld()
{	if (!this->worldBackgroundTex.loadFromFile("Textures/map.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initLondoakeh()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

//Con/Des
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initWorld();

	this->initPlayer();
	this->initLondoakeh();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto &i : this->textures)
	{
		delete i.second;
	}

	//Delete pelorakeh
	for (auto *i : this->pelorakeh)
	{
		delete i;
	}

	//Delete Londoakeh
	for (auto *i : this->londoakeh)
	{
		delete i;
	}
}

//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();

		if(this->player->getHp() > 0)
			this->update();

		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->pelorakeh.push_back(
			new pelor(
			this->textures["pelor"], 
			this->player->getPos().x + this->player->getBounds().width/2.f, 
			this->player->getPos().y, 
			0.f, 
			-1.f, 
			5.f
			)
		);
	}
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//Left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Right world collison
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updatepelorakeh()
{
	unsigned counter = 0;
	for (auto *pelor : this->pelorakeh)
	{
		pelor->update();

		//pelor culling (top of screen)
		if (pelor->getBounds().top + pelor->getBounds().height < 0.f)
		{
			//Delete pelor
			delete this->pelorakeh.at(counter);
			this->pelorakeh.erase(this->pelorakeh.begin() + counter);
		}

		++counter;
	}
}

void Game::updateLondoakeh()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->londoakeh.push_back(new Londo(rand() % this->window->getSize().x-20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto *londo : this->londoakeh)
	{
		londo->update();

		//pelor culling (top of screen)
		if (londo->getBounds().top > this->window->getSize().y)
		{
			//Delete londo
			delete this->londoakeh.at(counter);
			this->londoakeh.erase(this->londoakeh.begin() + counter);
		}
		//londo player collision
		else if(londo->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->londoakeh.at(counter)->getDamage());
			delete this->londoakeh.at(counter);
			this->londoakeh.erase(this->londoakeh.begin() + counter);
		}

		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->londoakeh.size(); ++i)
	{
		bool londo_deleted = false;
		for (size_t k = 0; k < this->pelorakeh.size() && londo_deleted == false; k++)
		{	
			if (this->londoakeh[i]->getBounds().intersects(this->pelorakeh[k]->getBounds()))
			{

				delete this->londoakeh[i];
				this->londoakeh.erase(this->londoakeh.begin() + i);

				delete this->pelorakeh[k];
				this->pelorakeh.erase(this->pelorakeh.begin() + k);

				londo_deleted = true;
			}
		}
	}
}

void Game::update()
{
	this->updateInput();
	this->player->update();
	this->updateCollision();
	this->updatepelorakeh();
	this->updateLondoakeh();
	this->updateCombat();
	this->updateWorld();
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();

	//Draw world
	this->renderWorld();

	//Draw semuanya
	this->player->render(*this->window);

	for (auto *pelor : this->pelorakeh)
	{
		pelor->render(this->window);
	}

	for (auto *londo : this->londoakeh)
	{
		londo->render(this->window);
	}

	this->window->display();
}