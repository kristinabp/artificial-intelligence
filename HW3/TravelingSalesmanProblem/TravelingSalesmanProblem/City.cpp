#include "City.h"

City::City(double _x, double _y): x(_x), y(_y)
{
}

double City::distance(const City& other)
{
    double xDist = abs(this->x - other.x);
    double yDist = abs(this->y - other.y);
    return sqrt(pow(xDist, 2) + pow(yDist, 2));
}

void City::print() const
{
    std::cout << "(" << this->x << ", " << this->y << ")\n";
}
