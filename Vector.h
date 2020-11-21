#include <math.h>
#include <cassert>

struct Vector
{
    double x;
    double y;

    Vector(double x, double y) 
    {
        this->x = x;
        this->y = y;
    };

    Vector(double x, double y)
    {
        this->x = x;
        this->y = y;
    };

    Vector(sf::Vector vector)
    {
        this->x = vector.x;
        this->y = vector.y;
    };

    Vector(sf::Vector vector)
    {
        this->x = vector.x;
        this->y = vector.y;
    };

    Vector operator + (Vector v)
    {
        return Vector(x + v.x, y + v.y);
    }

    Vector& operator += (Vector v)
    {
        x += v.x;
        y += v.y;

        return *this;
    }

    Vector operator - (Vector v)
    {
        return Vector(x - v.x, y - v.y);
    }

    Vector& operator -= (Vector v)
    {
        x -= v.x;
        y -= v.y;

        return *this;
    }

    Vector operator * (double v)
    {
        return Vector(x * v, y * v);
    }

    Vector& operator *= (double v)
    {
        x = x * v;
        y = y * v;

        return *this;
    }

    Vector operator / (double v)
    {
        assert(v);

        return Vector(x / v, y / v);
    }

    Vector& operator /= (double v)
    {
        assert(v);
        x = x / v;
        y = y / v;

        return *this;
    }

    double operator * (Vector v)
    {
        return x * v.x + y * v.y;
    }

    double dist()
    {
        return pow(x * x + y * y, 0.5);
    }

};

