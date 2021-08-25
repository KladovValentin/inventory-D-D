#pragma once
#include "mainHeader.h"

class Button
{
public:
	sf::RectangleShape background;
	sf::Text text;

	Button(string tytle, Font font, double posx, double posy) :background(), text() {
		background.setPosition(posx, posy);
		text.setPosition(sf::Vector2f(background.getPosition().x + 5, background.getPosition().y + 2));
		text.setString(tytle);
		background.setSize(Vector2f(text.getGlobalBounds().width + 10, text.getGlobalBounds().height + 10));
		background.setFillColor(Color::Green);
		text.setFont(font);
		text.setCharacterSize(14); // in pixels, not points!
		text.setFillColor(sf::Color::Black);
	}
	Button(string tytle, Font font, double posx, double posy, double width, double height) : Button(tytle,font,posx,posy) {
		background.setSize(Vector2f(width, height));
	}

};
