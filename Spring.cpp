#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include "functions.h"

int main()
{
    int windowx = 1200;
    int windowy = 800;
    int M = 4;
    int F = (M - 1) * M / 2;
    sf::RenderWindow window(sf::VideoMode(windowx, windowy), "UwU");


    Sphere particles[M];
    Spring lines[M][M];

    particles[0] = Sphere{ (200, 200), (0, 0), (0, 0), 10, 10, 255, 255, 255};
	particles[1] = Sphere{ (200, 400), (0, 0), (0, 0), 10, 10, 255, 255, 255};
	particles[2] = Sphere{ (600, 200), (0, 0), (0, 0), 10, 10, 255, 255, 255};
	particles[3] = Sphere{ (600, 600), (0, 0), (0, 0), 10, 10, 255, 255, 255};

    for (int i = 0; i < M; i++ )
    {
        for (int j = 0; j < M; j++ )
        {
            if (i != j)
            {
                Spring lines[i][j] {4, 10};
            }

            else
            {
                Spring lines[i][j] {0, 0};
            }
        }
    }


    const double DT = 0.01;


    while(window.isOpen())
    {
        sf::Event event;

        window.clear();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.display();


        for (int i = 1; i < M; i++)
        {
            particles[i].drawSphere(&window, M);
            for (int j = i + 1; j < M; j++)
            {
                lines[i][j].drawlines(particles[i], particles[j], &window);
            }
        }


        for (int i = 1; i < M; i++)
        {
            for (int j = i + 1; j < M; j++)
            {
                acc(&particles[i], &particles[j], lines[i][j]);
            }
        }

        for (int i = 1; i < M; i++)
        {
            particles[i].speed(DT);
            particles[i].move(DT);
            particles[i].zero_acc();
        }

        for (int i = 1; i < M; i++)
        {
            checkCollision(&particles[i], &window, DT);
        }

    }
    return 0;

}
