#include "../headers/HelperFunctions.h"
#include "HelperFunctions.h"

float toRadians(float degrees) {
    return degrees * M_PI / 180;
}

float toDegrees(float radians) {
    return radians * 180 / M_PI;
}

float getVectorMag(sf::Vector2f vec) {
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

sf::Vector2f lerp(sf::Vector2f v1, sf::Vector2f v2, float a) {
    return (1 - a) * v1 + a * v2;
}

sf::Vector2f vectorFromAngle(float a) { // Angle in degrees
    return sf::Vector2f(cos(toRadians(a)), sin(toRadians(a)));
}
float angleFromVector(sf::Vector2f vec) // Returns angle in degrees
{
    return toDegrees(atan2(vec.y, vec.x));
}

bool isFloatBetween(float input, float lower, float upper)
{
    return input >= lower && input <= upper;
}
