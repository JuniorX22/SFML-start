// SFML start.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);
	sf::RectangleShape player(sf::Vector2f(100.0f, 150.0f));
	player.setPosition(206.0f, 206.0f);
	sf::Texture playerTexture;
	playerTexture.loadFromFile("randomdude.png");
	player.setTexture(&playerTexture);

	Animation animation(&playerTexture, sf::Vector2u(3, 4), 0.3f);

	/*sf::Vector2u textureSize = playerTexture.getSize();
	textureSize.x /= 3;
	textureSize.y /= 4;
	player.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 3, textureSize.x, textureSize.y));
	*/

	float deltaTime = 0.0f;
	sf::Clock clock;


	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}

			animation.Update(0, deltaTime);
			player.setTextureRect(animation.uvRect);

			window.clear(sf::Color(150, 150, 150));
			window.draw(player);
			window.display();
		}

	}
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
