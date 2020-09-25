#include "TXLib.h"
#include "math.h"
#include <cstdlib>

const float DT = 0.1;

struct Sphere
{
    int x;
    int y;
    int radius;
    int N;
    float vx;
    float vy;
    int r;
    int g;
    int b;
};

float projectionVector( float vectorX, float vectorY, float distx, float disty)
{
    float scalarComposition = vectorX * distx + vectorY * disty;
    float moduleDist = pow (distx * distx + disty * disty, 0.5 );
    float projection = scalarComposition / moduleDist;
    return projection;
}

void draw(Sphere sphere)
{
    COLORREF a = txGetFillColor();

    for (int i = 1; i < sphere.N; i++)
    {
        txSetFillColor(RGB(i * sphere.r / sphere.N, i * sphere.g / sphere.N, i * sphere.b / sphere.N));
        txSetColor    (RGB(i * sphere.r / sphere.N, i * sphere.g / sphere.N, i * sphere.b / sphere.N));
        txCircle(sphere.x, sphere.y, sphere.radius - sphere.radius * i / sphere.N);
    }

    txSetFillColor(a);
}

void move(Sphere* sphere)
{
    (*sphere).x += (*sphere).vx * DT;
    (*sphere).y += (*sphere).vy * DT;
}

void checkCollision (Sphere* sphere)
{

    if (((*sphere).x > 800 - (*sphere).radius) or ((*sphere).x < (*sphere).radius))
    {
        (*sphere).vx = - (*sphere).vx;
    }

    if (((*sphere).y > 600 - (*sphere).radius) or ((*sphere).y < (*sphere).radius))
    {
        (*sphere).vy = - (*sphere).vy;
    }
}

bool checkCollisionTwoSpheres(Sphere* sphere1, Sphere* sphere2)
{
    if ((*sphere1).radius + (*sphere2).radius > sqrt(pow((*sphere1).x - (*sphere2).x, 2)+ pow((*sphere1).y - (*sphere2).y, 2)))
    {
        return true;
    }
    return false;
}

void collisionTwoSpheres(Sphere* sphere1,  Sphere* sphere2)
{
    float distx = (*sphere1).x - (*sphere2).x;
    float disty = (*sphere1).y - (*sphere2).y;
    float moduleDist = sqrt(distx * distx + disty * disty);
    float projectionV1 = projectionVector((*sphere1).vx, (*sphere1).vy, distx, disty);
    float projectionV2 = projectionVector((*sphere2).vx, (*sphere2).vy, distx, disty);
    float dv = projectionV1 - projectionV2;

    if (dv < 0)
    {
        (*sphere2).vx +=   dv * distx / moduleDist;
        (*sphere2).vy +=   dv * disty / moduleDist;
        (*sphere1).vx += - dv * distx / moduleDist;
        (*sphere1).vy += - dv * disty / moduleDist;
    }

}


int main()
{
    Sphere s1 = { 200, 200, 50, 100, 56, 90, 255, 0, 0 };
    Sphere s2 = { 510, 410, 50, 100, 100, 98, 255, 255, 255 };
    Sphere s3 = { 100, 200, 50, 100, 40, 30, 255, 0, 255};

    txCreateWindow(800, 600);
    txSetFillColor(RGB(0, 0, 0));

    double mousex = 0;
    double mousey = 0;
    double mouseOldx = 0;
    double mouseOldy = 0;

    while (true)
    {

        mouseOldx = mousex;
        mouseOldy = mousey;
        mousex = txMouseX();
        mousey = txMouseY();

        if (txMouseButtons() > 0 )
        {
            s1.x = mousex;
            s1.y = mousey;
            s1.vx = (mousex - mouseOldx) / DT;
            s1.vy = (mousey - mouseOldy) / DT;
        }

        txClear();

        txBegin();

        draw(s1);
        draw(s2);
        draw(s3);

        txEnd();

        checkCollision(&s1);
        checkCollision(&s2);
        checkCollision(&s3);

        move(&s1);
        move(&s2);
        move(&s3);

        if (checkCollisionTwoSpheres(&s1, &s2))
        {
            collisionTwoSpheres(&s1, &s2);
        }
        if (checkCollisionTwoSpheres(&s1, &s3))
        {
            collisionTwoSpheres(&s1, &s3);
        }
        if (checkCollisionTwoSpheres(&s2, &s3))
        {
            collisionTwoSpheres(&s2, &s3);
        }
    }

    return 0;

}
