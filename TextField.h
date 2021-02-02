#ifndef TXTFIELD_H
#define TXTFIELD_H

#include <string>

#include <SFML/Graphics.hpp>


const int GUI_TEXT_MAX = 24;

const int GUI_TEXT_BACKSPACE = 8;
const int GUI_TEXT_ESCAPE = 13;

const sf::Color GUI_TEXT_GRAY = sf::Color(105, 105, 105);

class TextField {
public:
	TextField();

	TextField(sf::Vector2f vec, sf::Font& f, int arg, std::string str);

	void setPosition(sf::Vector2f vec);

	void regen();

	bool input(sf::Event ev);

	void setFont(sf::Font& f);

	const sf::String& getText();

	void setPlaceholder(std::string str);

	void render(sf::RenderWindow& window);

	void setLength(int arg);

	int getTextLength();

	bool isActive();

	bool is_button, dk;

	std::string second_text, first_text;

	void open();
private:
	sf::Text txt;
	sf::RectangleShape box;

	int size;

	bool was_clicked;

	int length;

	bool renderPlaceholder;

	void setActive(bool arg);

	bool active;

	sf::Vector2f pos;

	std::string placeholder;
};

#endif
