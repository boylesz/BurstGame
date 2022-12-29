#ifndef ALIEN_CHARACTER_H
#define ALIEN_CHARACTER_H

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "SelbaWard/Ring.hpp"
#include "PlayerCharacter.h"
#include <math.h>
#include <iostream>
#include <memory>

class AlienCharacter : std::enable_shared_from_this<AlienCharacter> {
    private:
        sw::Ring shape; // The shape of the enemy. Also holds the position, rotation, scale and radius of the enemy
        sw::Ring eye;
        sf::Vector2f vel; // The velocity of the enemy
        sf::Vector2f acc; // The acceleration of the enemy

        // Movement variables
        sf::Vector2f startLocation;
        sf::Vector2f targetLocation;
        bool reachedLocation;
        float speed; // Speed of the enemy
        float lerpAlpha;
        float lerpIncrement;
        unsigned int movementCooldownLength; // Length of cooldown timer in frames
        unsigned int movementCooldownTimer;

        // Attack variables
        unsigned short hitpoints;
        unsigned int attackCooldownLength;
        unsigned int attackCooldownTimer;
        unsigned int attackVariation;

        std::vector<Laser> pendingLasers;

        void initVariables();
        void initShape(sf::RenderTarget* window);
        void getNewTargetLocation(sf::RenderTarget* window);
        void checkBounds(sf::RenderTarget* window);
        void moveToTargetLocation();
        void updateEyeLocation(PlayerCharacter& player);

    public:
        AlienCharacter(sf::RenderTarget* window);
        virtual ~AlienCharacter();

        // Accessors
        sf::Vector2f getPosition();
        float getX();
        float getY();
        sw::Ring getShape();
        float getRadius();
        unsigned short getHitpoints();

        // Functions
        void damage(unsigned short dmgAmnt);
        void attackPlayer();
        void pollLasers(std::vector<Laser>& larr);
        void update(sf::RenderTarget* window, PlayerCharacter& player);
        void render(sf::RenderTarget* target);
};

#endif