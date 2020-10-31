#include "TXLib.h"
#include <cmath>
#include <cstdlib>
#include "functions.h"

int main()
{
    int windowx = 1000;
    int windowy = 600;
    int M = 4;
    int F = (M - 1) * M / 2;

    struct Sphere particles[M];
    int k = 1;
    int j = 0;
    for (int i = 0; i < M; i++)
    {
        particles[i].radius = 30;
        particles[i].x = particles[i].radius* (2 * j + 1) + 5 * (j + 1);
        particles[i].y = k * (5 + 2 * particles[i].radius + 30*(i%2));
        particles[i].N = 20;
        particles[i].vx = 0;
        particles[i].vy = 0;
        particles[i].ax = 0;
        particles[i].ay = 0;
        particles[i].r = 255;
        particles[i].g = 255;
        particles[i].b = 255;
        particles[i].m = 100000;

        j += 1;
        if (particles[i].x > windowx - 3 * particles[i].radius - 10)
        {
            k += 1;
            j = 0;
        }
        if (particles[i].y > windowy - 3 * particles[i].radius - 10)
        {
            break;
        }
    }

    struct Spring lines[3][3];

    lines[0][0].k = 0;
    lines[0][0].length = 0;
    lines[0][1].k = 400;
    lines[0][1].length = 10;
    lines[0][2].k = 400;
    lines[0][2].length = 15;
    lines[1][0].k = 400;
    lines[1][0].length = 10;
    lines[1][1].k = 0;
    lines[1][1].length = 0;
    lines[1][2].k = 400;
    lines[1][2].length = 20;
    lines[2][0].k = 400;
    lines[2][0].length = 25;
    lines[2][1].k = 400;
    lines[2][1].length = 20;
    lines[2][2].k = 0;
    lines[2][2].length = 0;

    const double DT = 0.01;
    txCreateWindow(windowx, windowy);
    txSetFillColor(RGB(0, 0, 0));

    while(true)
    {

        txBegin();
        txClear();

        for (int i = 1; i < M; i++)
        {
            draw(particles[i]);
            for (int j = i + 1; j < M; j++)
            {
                drawlines(particles[i], particles[j], lines[i][j]);
            }
        }

        txEnd();

        for (int i = 1; i < M; i++)
        {
            for (int j = i + 1; j < M; j++)
            {
                acc(&(particles[i]), &(particles[j]), lines[i][j]);
            }
            move(&(particles[i]), DT);
        }
        for (int i = 1; i < M; i++)
        {
            speed(&(particles[i]), DT);
            move(&(particles[i]), DT);
        }
        for (int i = 1; i < M; i++)
        {
            checkCollision(&(particles[i]), windowx, windowy);
        }

    }
    return 0;

}
