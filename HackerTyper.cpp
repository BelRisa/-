#include "String.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>

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
	const double windowx = 1300;
	const double windowy = 800;



	FILE* code = fopen("Text.txt", "r");
	int sizeCode = FileLen(code);

	char* buf = new char[sizeCode];
	int p = 0;
	int allString = 0;
	int a = fread(buf, sizeof(char), sizeCode, code);
	fclose(code);
	String buffer = String(buf).split(a)[0];
	delete[] buf;

	sf::Color fillColor = sf::Color(255, 255, 255);
	sf::RenderWindow window(sf::VideoMode(windowx, windowy), "UwU");
	sf::View view = window.getView();
	window.setFramerateLimit(60);
	window.clear(fillColor);
	window.display();

	String Code = new char[sizeCode + 1];
	sf::Font font; 
	font.loadFromFile("19901.ttf");
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setPosition(50, 50);
    text.setCharacterSize(15); 

	while (window.isOpen())
	{
		sf::Event event;
		while (window.isOpen())
    	{
			sf::Event evnt;
			while (window.pollEvent(evnt))
			{
				switch (evnt.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (evnt.key.code == sf::Keyboard::Space)
						window.close();
					break;
				}
        	}
		}

		window.clear();
		window.draw(text);
		window.setView(view);
		window.display();

		if (event.type == sf::Event::MouseWheelScrolled)
		{
			view.move(0, -20 * event.mouseWheelScroll.delta);
		}

		if (event.type == sf::Event::KeyReleased)
		{
			text.setString((buffer.split(p)[0]));
			
			Code += String(buffer[p]);
			p += 2;

			Code += String(buffer[p] + buffer[p + 1]);
			if (allString == 1)
            {
                for (int i = 0; i < 4; i++)
                {
                    if ( buffer.str[p + i] == '\n' && p < (a - 5))
                    {
                        view.move(0, 30); 
                    }
                }
            }
            else
            {
                sf::Vector2f pos = text.findCharacterPos((size_t)p);
                if (pos.y > windowy / 1.2)
                    allString = 1;    	
            }

			if (p > a - 3)
				p -= 2;
			break;			
            
		}

        window.display();    
			
	}
	
	return 0;
}