#ifndef LASER_H
#define LASER_H

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "SelbaWard/Ring.hpp"
#include "GlobalVariables.h"
#include "HelperFunctions.h"
#include <math.h>

class Laser : std::enable_shared_from_this<Laser> {
    private:
        // Variables
            sw::Ring shape;
            sf::Vector2f vel;
            BulletType type;

        // Private Functions
            void initVariables(float angle, BulletType type, float rotVel);
            void initShape(sf::Vector2f startPos);


    public:
        // Constructor / Destructor
            Laser(sf::Vector2f startPos, float angle, BulletType t, float rotVel = 0.f);
            virtual ~Laser();

        // Accessors
            BulletType getType();
            sf::Vector2f getPosition();
            float getX();
            float getY();

        // Public Functions
            bool isOffscreen();
            void update();
            void render(sf::RenderTarget* window);

};

#endif