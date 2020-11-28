#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#define ARRAYDOUBLE_H

const float DT = 0.01;

void circleMove(float* x, float vx, float* y, float vy)
{
    *x += vx * DT;
    *y += vy * DT;
}

void checkCollision(float* x, float* vx, float* y, float* vy, int windowx, int windowy, float radius)
{
    if ((*x >= windowx - 2 * radius) or (*x <= 0))
    {
         *vx = - *vx;
    }

    if ((*y >= windowy - 2 * radius) or (*y <= 0))
    {
        *vy = - *vy;
    }
}

void resolveWallCollision(float* x, float* vx, float* y, float* vy, float radius, int windowx, int windowy)
{
    if (*x < 0)
    {
        *x += *x + radius;
    }

    if (*x + 2 * radius > windowx)
    {
        *x -= - windowx + *x + radius;
    }

    if (*y < 0)
    {
        *y += -*y + radius;
    }

    if (*y + 2 * radius > windowy)
    {
        *y -= - windowy + *y + radius;
    }
}

int main()
{
    float windowx = 1000;
    float windowy = 800;
    float radius = 10;
    float vx = -50;
    float vy = -50;
    float sticklx = 100;
    float stickly = 10; 
    float stickx = windowx / 2 - sticklx / 2;
    float sticky = windowy - (50 + stickly); 
    
    float y = windowy - (50 + stickly + 2 * radius);
    float x = windowx / 2 - radius;

    sf::RenderWindow window(sf::VideoMode(windowx, windowy), "UwU");

    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({ x, y });

    sf::RectangleShape rectangle(sf::Vector2f(100.f, 10.f));
    rectangle.setPosition({ stickx, sticky });
    rectangle.setFillColor(sf::Color::Blue); 

    sf::RectangleShape rectangle1(sf::Vector2f(80.f, 30.f));
    rectangle1.setPosition({ stickx, sticky });
    rectangle1.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        shape.setPosition({ x, y });
        rectangle.setPosition({ stickx, sticky });
        window.draw(rectangle);
        window.draw(shape);
        int k = 0;
        int j = 0;
        int m = 0;
        for (int i = 0; i < 40; i++)
        {   
            m = k % 2;
            rectangle1.setPosition({ 100 - 40 * m + 83 * j, 100 + 35 * k });
            window.draw(rectangle1);            
            j += 1;
            if (j >= 10)
            {
                j = 0;
                k += 1;
            }

        }
        checkCollision(&x, &vx, &y, &vy, windowx, windowy, radius);
        resolveWallCollision(&x, &vx, &y, &vy, radius, windowx, windowy);
        circleMove(&x, vx, &y, vy);
        float mousex = sf::Mouse::getPosition(window).x;

        if (mousex <= (windowx - sticklx / 2 ) and mousex >= (sticklx / 2))
        {
            stickx = mousex - sticklx / 2;
        }
        
        window.display();
        /*if (y >= 780)
        {
            std::cout << "YOU LOSE!";
            break;
        }*/
    }

    return 0;
}