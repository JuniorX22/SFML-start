#include "Animation.h"

	

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
	{
	    //deze code laat zien welke image genomen word en hoelang het duurt om te switchen van image

		this->imageCount = imageCount;
		this->switchTime = switchTime;
		totalTime = 0.0f;
		currentImage.x = 0;

		uvRect.width = texture->getSize().x / float(imageCount.x);
		uvRect.height = texture->getSize().y / float(imageCount.y);
	}

	Animation::~Animation()
	{

	}

	void Animation::Update(int row, float deltaTime,bool faceRight) //dit zorgt dat de foto update en een animation krijgt
																	

	{
		currentImage.y = row;
		totalTime += deltaTime;
		
		if (totalTime >= switchTime)
		{
			totalTime -= switchTime;
			currentImage.x++;

			if (currentImage.x >= imageCount.x) 
			{
				currentImage.x = 0;
			}
		}

		
		uvRect.top = currentImage.y * uvRect.height;

		if (faceRight)
		{
			uvRect.left = currentImage.x * uvRect.width;
			uvRect.width = abs(uvRect.width);
		}
		else
		{
			uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
			uvRect.width = -abs(uvRect.width); //negatief omdat de image niet tussen positief en negatief blijft veranderen             
		}
		
	}
