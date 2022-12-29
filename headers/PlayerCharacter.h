#ifndef PLAYER_CHARACTER_HPP
#define PLAYER_CHARACTER_HPP

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "SelbaWard/Ring.hpp"
#include "GlobalVariables.h"
#include "HelperFunctions.h"
#include "Laser.h"
#include <iostream>

class AlienCharacter; // Forward declaration

class PlayerCharacter {
    private:
        // Variables
        sf::ConvexShape shape; // The shape of the player. Also holds the position, rotation and scale of the player
        sw::Ring ring;
        sf::Vector2f vel; // The velocity of the player
        sf::Vector2f acc; // The acceleration of the player
        float radius; // Radius of the player box;
        float shieldRadius;

        unsigned int laserCooldown;
        unsigned int laserCooldownTimer;
        std::vector<Laser> pendingLasers;
        unsigned short bulletCount;

        float rotationSpeed;
        float movementSpeed;

        unsigned short HIT_POINTS;
        unsigned short damageCooldown;
        unsigned short damageCooldownTimer; // A brief period of time after taking damage when the player is invulnerable
        bool isInvulnerable;

        // Private Functions
        void initVariables();
        void initShape();

    public:
        // Constructors / Destructors
        PlayerCharacter(float x = RESOLUTION_WIDTH / 2, float y = RESOLUTION_HEIGHT / 2);
        virtual ~PlayerCharacter();

        // Accessors
        sf::Vector2f getPosition();
        float getHeading();
        float getX();
        float getY();
        sf::ConvexShape getShape();
        float getRadius();
        float getShieldRadius();
        bool getInvulnerable();
        unsigned short getHitPoints();
        unsigned short getBulletCount();
        void addBullet();

        // Public Functions
        void damage(unsigned short dmgAmnt);
        void pollLasers(std::vector<Laser>& larr);
        void update();
        void updateInput();
        void render(sf::RenderTarget* target);
};

#endif