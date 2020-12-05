#include "String.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>


int main()
{
	const double x_max = 1960;
	const double y_max = 1080;

	int FileLen(FILE* file)
	{
		assert(file);          
		fseek(file, 0, SEEK_END);
		int lenf = ftell(file);
		fseek(file, 0, SEEK_SET);
		return lenf;
	}

	FILE* code = fopen("Text.txt", "r");
	int sizeCode = FileLen(code);

	String buffer("", sizeCode);
	int p = 0;
	int a = fread(buffer.str, sizeof(char), sizeCode, code);
	fclose(code);

	String Code("", sizeCode);
	sf::Color fillColor = sf::Color(255, 255, 255);
	sf::RenderWindow window(sf::VideoMode(x_max, y_max), "UwU");
	window.setFramerateLimit(60);
	window.clear(fillColor);
	window.display();


	sf::Font font; 
	font.loadFromFile("19901.ttf");
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setOutlineColor(sf::Color::Red);
	text.setPosition(50, 50);

	int strInvisible = -33;
	int s = 0;

	while (window.isOpen())
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
				Code += String(buffer[p]);
				Code += buffer[p];

			
            if (Code.countChar('\n'))
            {
				p += 2;
            }
            
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
			
	}
		
        String newCode = buffer[p] + buffer[p] + 1]; 

        Code += newCode; 


		window.clear(fillColor);
		window.draw(text);
		window.display();
	
	return 0;
}