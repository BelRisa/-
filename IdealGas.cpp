#include "math.h"
#include <SFML/Graphics.hpp>
#include <cassert>

const float DT = 0.01;
const int windowx = 1200;
const int windowy = 800;
const int M = 10;


struct Vector2f
{
    float x;
    float y;
};

struct Sphere
{
    Vector2f coord;
    Vector2f velocity;
    int radius;
    int red;
    int green;
    int blue;
};

void drawSphere(sf::RenderWindow* window, Sphere sphere, const int M)
{
    sf::CircleShape circle(sphere.radius, 10);
    assert((sphere.coord.x > sphere.radius) & (sphere.coord.x + sphere.radius< windowx) & (sphere.coord.y > sphere.radius) & (sphere.coord.y + sphere.radius < windowy));
    for (int i = 0; i < M; i++)
    {
        circle.setRadius(sphere.radius - sphere.radius * i / M);
        circle.setPosition(sphere.coord.x - sphere.radius + 1.4 * sphere.radius * i / M, sphere.coord.y - sphere.radius + 0.6 * sphere.radius * i / M);
        circle.setFillColor(sf::Color(sphere.red, sphere.green, sphere.blue));
        window->draw(circle);
    }
}

void moveSphere(Sphere* sphere)
{
    sphere->coord.x += sphere->velocity.x * DT;
    sphere->coord.y += sphere->velocity.y * DT;
}


void checkCollision(Sphere* sphere)
{
    if (sphere->coord.x + sphere->velocity.x * DT + sphere->radius > windowx)
    {
        sphere->velocity.x *= -1;
        sphere->coord.x = 2 * windowx - sphere->coord.x - 2 * sphere->radius;
    }
    if (sphere->coord.x + sphere->velocity.x * DT - sphere->radius < 0)
    {
        sphere->velocity.x *= -1;
        sphere->coord.x = -sphere->coord.x + 2 * sphere->radius;
    }
    if (sphere->coord.y + sphere->velocity.y * DT + sphere->radius > windowy)
    {
        sphere->velocity.y *= -1;
        sphere->coord.y = 2 * windowy - sphere->coord.y - 2 * sphere->radius;
    }
    if (sphere->coord.y + sphere->velocity.y * DT - sphere->radius < 0)
    {
        sphere->velocity.y *= -1;
        sphere->coord.y = -sphere->coord.y + 2 * sphere->radius;
    }
}

bool checkCollisionTwoSpheres(const Sphere* sphere1, const Sphere* sphere2)
{
    if (pow (sphere1->radius + sphere2->radius, 2) > pow(sphere1->coord.x - sphere2->coord.x, 2)+ pow(sphere1->coord.y - sphere2->coord.y, 2))
    {
        return true;
    }
    return false;
}

void collideSpheres(Sphere* sphere1, Sphere* sphere2)
{
    double distx = sphere1->coord.x - sphere2->coord.x;
    double disty = sphere1->coord.y - sphere2->coord.y;

    double hypotenuse = sqrt(distx * distx + disty * disty);

    double sin = distx / hypotenuse;
    double cos = disty / hypotenuse;
        if (hypotenuse < sphere1->radius + sphere2->radius)
        {
            double Vn1 = sphere2->velocity.x * sin + sphere2->velocity.y * cos;
      		double Vn2 = sphere1->velocity.x * sin + sphere1->velocity.y * cos;
      		double Vt1 = - sphere2->velocity.x * cos +sphere2->velocity.y * sin;
            double Vt2 = - sphere1->velocity.x * cos + sphere1->velocity.y * sin;
      		double dt = (sphere2->radius + sphere1->radius - hypotenuse) / (Vn1 - Vn2);

      		if (dt > 0.5)
      		{
                dt = 0.5;
            }
      		if (dt < - 0.5)
      		{
                dt = - 0.5;
            }
            sphere1->coord.x = sphere1->coord.x - sphere1->velocity.x * dt;
      		sphere1->coord.y = sphere1->coord.y - sphere1->velocity.y * dt;
      		sphere2->coord.x = sphere2->coord.x - sphere2->velocity.x * dt;
      		sphere2->coord.y = sphere2->coord.y - sphere2->velocity.y * dt;

      		distx = sphere1->coord.x - sphere2->coord.x;
      		disty = sphere1->coord.y - sphere2->coord.y;

      		double back = Vn2;
      		Vn2 = Vn1;
      		Vn1 = back;


      		sphere1->velocity.x = Vn2 * sin - Vt2 * cos;
      		sphere1->velocity.y = Vn2 * cos + Vt2 * sin;
      		sphere2->velocity.x = Vn1 * sin - Vt1 * cos;
      		sphere2->velocity.y = Vn1 * cos + Vt1 * sin;
        }

}


int main()
{
    sf::RenderWindow window(sf::VideoMode(windowx, windowy), "Ideal_Gas");

    Sphere particles[100];
    for (int i = 0; i < 100; i++)
    {
        particles[i] = { float(20 * i % (windowx - 100) + 50), float(100 * (20 * i - 30 * i % (windowx - 100)) / (windowx- 100) + 50), float(0.8 * i), float(0.5 * i), 3, 255, 255, 255};
    }

    while (window.isOpen())
    {
        sf::Event event;
        window.clear();
        for (int i = 0; i < 100; i++)
        {
            drawSphere(&window, particles[i], M);
        }
        window.display();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
                break;
            }
        }

        for (int i = 0; i < 100; i++)
        {
            for (int j = i + 1; j < 100; j++)
            {
                if (checkCollisionTwoSpheres(&particles[i], &particles[j]))
                {
                    collideSpheres(&particles[i], &particles[j]);
                }
            }
        }

        for (int i = 0; i < 100; i++)
        {
            checkCollision(&particles[i]);
        }

        for (int i = 0; i < 100; i++)
        {
            moveSphere(&particles[i]);
        }
    }
    return 0;
}