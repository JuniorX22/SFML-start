#include "player.h"


Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)  //hier maak je een initialiser list hier kan je een membervariable toe wijzen
{
	this->speed = speed;
	faceRight = true;
	body.setSize(sf::Vector2f(100.0f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 206.0f);
	body.setTexture(texture);
}

Player::~Player() 
{

}

void::Player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);  //movement als je op de keys drukt

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		movement.x -= speed * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += speed * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		movement.y -= speed * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += speed * deltaTime;

	if (movement.x == 0.0f) 
	{
		row = 0;
	}
	else
	{
		row = 1;

		if (movement.x > 0.0f) //hier check je of de movement .x groter is dan nul dan kijk je rechts
			faceRight = true;     
		else
			faceRight = false; 
	}
	animation.Update(row, deltaTime, faceRight); 
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}