#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "AlienCharacter.h"
#include "GlobalVariables.h"
#include <vector>
#include <string>
#include <math.h>
#include <iostream>

/*
    Game engine wrapper class
*/

class Game {
    private:
        // Variables
        // Window
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event ev;

        sf::Font font;
        sf::Text hpDisplay;
        sf::Text bulletCountDisplay;

        // Game objects
        PlayerCharacter player;

        std::vector<AlienCharacter> aliens;
        float spawnTimerMax;
        float spawnTimer;
        int maxAliens;

        std::vector<Laser> lasers;

        // Private Functions
        void initVariables();
        void initWindow(int resolutionWidth, int resolutionHeight);
        void handleEntityCollisions();
        void updateUI();
        void cleanupEnemies();

    public:
        // Constructors / Destructors
        Game();
        virtual ~Game();

        // Accessors
        const bool isRunning() const;

        // Public Functions
        void spawnAliens();
        void pollEvents();
        void pollLasers();
        void update();
        void render();
        sf::VideoMode getWindowResolution();
};

#endif