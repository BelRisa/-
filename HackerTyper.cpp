#include "String.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>

int handlingEvent(sf::RenderWindow* window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
			return 0;
		}
		if (event.type == sf::Event::KeyReleased)
		{
			return 1;
		}
	}
}

int FileLen(FILE* file)
{
	assert(file);          
	fseek(file, 0, SEEK_END);
	int lenf = ftell(file);
	fseek(file, 0, SEEK_SET);
	return lenf;
}


int main()
{
	const double x_max = 1960;
	const double y_max = 1080;

	FILE* code = fopen("Text.txt", "r");
	int sizeCode = FileLen(code);


	String buffer("", sizeCode);
	int pointer = 0;
	int a = fread(buffer.str, sizeof(char), sizeCode, code);
	fclose(code);

	String visCode("", sizeCode);
	sf::Color fillColor = sf::Color(255, 255, 255);
	sf::RenderWindow window(sf::VideoMode(x_max, y_max), "UwU");
	window.setFramerateLimit(60);
	window.clear(fillColor);
	window.display();


	sf::Font font; 

	sf::Text visible;
	visible.setFont(font);
	visible.setFillColor(sf::Color::Red);
	visible.setOutlineColor(sf::Color::Red);
	visible.setPosition(50, 50);

	int strInvisible = -33;
	int bies = 0;

	while (true)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyReleased)
			{
				visCode += buffer[pointer];
				visCode += buffer[pointer + 1];
				visCode += buffer[pointer + 2];

			
				if (buffer[pointer] == '\n')
					strInvisible += 1;
				if (buffer[pointer + 1] == '\n')
					strInvisible += 1;
				if (buffer[pointer + 2] == '\n')
					strInvisible += 1;

				pointer += 3;
			}
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					int a = event.mouseWheelScroll.delta;
				
					strInvisible -= a;
				
				}
			}
		}
		
		if (strInvisible > 0)
		{
			int n = strInvisible;
			for (int i = 0; i < visCode.strSize; ++i)
			{
				if (visCode[i] == '\n')
					n -= 1;
				if (n == 0)
				{
					bies = i;
					break;
				}
				if (i == visCode.strSize - 1)
					bies = i;
			}
		}
		else
		{
			bies = 0;
		}

		//std::cout << numberOfFirstStrInVisible << ' ' << bies << std::endl;
		visible.setString(visCode.str + sizeof(char) * bies);
		//std::cout << visCode << std::endl;
		//std::cout << std::endl;

		window.clear(fillColor);
		window.draw(visible);
		window.display();
	}
	return 0;
}