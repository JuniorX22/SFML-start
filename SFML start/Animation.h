#pragma once
#include <SFML/Graphics.hpp>

class Animation
{

public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime); //dit is hoeveel images wij hebben en hoelang het duurt voor het veranderen van een image
	~Animation();

	void Update(int row, float deltaTime,bool faceRight);

public:
	sf::IntRect uvRect;

private:

	sf::Vector2u imageCount;     
	sf::Vector2u currentImage;    

	float totalTime;
	float switchTime;
};

