#pragma once
#include <SFML/Graphics.hpp>
class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();


	void Move(float dx, float dy) { body.move(dx, dy); } //we moeten body geen public variabelen maken

	bool CheckCollision(Collider other, float push); //float kijkt of een object gaat uit ge duwd worden
	sf::Vector2f GetPosition() { return body.getPosition(); }  //function zodat je de positie van de andere body kan detecteren
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; } 

private:
	sf::RectangleShape& body;//dit zorgt ervoor dat je de body kan aanpassen
};

