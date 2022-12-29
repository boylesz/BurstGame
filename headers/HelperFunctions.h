#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#define _USE_MATH_DEFINES

#include <math.h>
#include <SFML/System/Vector2.hpp>

float toRadians(float degrees);
float toDegrees(float radians);

float getVectorMag(sf::Vector2f vec);
sf::Vector2f lerp(sf::Vector2f v1, sf::Vector2f v2, float a);
sf::Vector2f vectorFromAngle(float a);
float angleFromVector(sf::Vector2f vec);

bool isFloatBetween(float input, float lower, float upper);

#endif