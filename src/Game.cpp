#include "Game.h"

const int RESOLUTION_WIDTH = 2560;
const int RESOLUTION_HEIGHT = 1440;

sf::Font font;

// Private Functions

void Game::initVariables() {
    this->window = nullptr;
    this->spawnTimerMax = 30.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxAliens = 1;
}

void Game::initWindow(int resolutionWidth, int resolutionHeight) {
    this->videoMode = sf::VideoMode(resolutionWidth, resolutionHeight);
    this->window = new sf::RenderWindow(this->videoMode, "Burst", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);

    this->hpDisplay.setFont(font);
    this->hpDisplay.setFillColor(sf::Color::White);
    this->hpDisplay.setPosition(50.f, 50.f);

    this->bulletCountDisplay.setFont(font);
    this->bulletCountDisplay.setFillColor(sf::Color::White);
    this->bulletCountDisplay.setPosition(50.f, 80.f);
}

void Game::handleEntityCollisions() {
    // Check collisions between the player and enemies
    for (AlienCharacter& a : aliens) {
        if (getVectorMag(a.getPosition() - player.getPosition()) <= a.getShape().getRadius() + player.getRadius()) {
            if (!player.getInvulnerable()) {
                player.damage(1u);
            }
        }
    }

    // Check collisions between the bullets and the player and enemies
    unsigned short index = 0;
    for (Laser& l : lasers) {
        if (l.getType() == BulletType::Enemy && !player.getInvulnerable()) {
            if (getVectorMag(l.getPosition() - player.getPosition()) <= player.getShieldRadius()) {
                if (isFloatBetween(angleFromVector(l.getPosition() - player.getPosition()) - player.getHeading() + 90.f, -72.f, 72.f)) {
                    player.addBullet();
                } else {
                    player.damage(1u);
                }
                // Erase laser
                lasers.erase(lasers.begin() + index);
                index--;
            }
        }
        else if (l.getType() == BulletType::Player) {
            for (AlienCharacter& a : aliens) {
                if (getVectorMag(l.getPosition() - a.getPosition()) <= a.getRadius()) {
                    a.damage(1u);
                    lasers.erase(lasers.begin() + index);
                    index--;
                }
            }
        }
        index++;
    }

}

void Game::updateUI() {
    this->hpDisplay.setString("HP: " +  std::to_string(player.getHitPoints()));
    this->bulletCountDisplay.setString("Bullets: " + std::to_string(player.getBulletCount()));
}

void Game::cleanupEnemies()
{
    for (unsigned short i = 0; i < aliens.size(); i++) {
        if (aliens[i].getHitpoints() <= 0) aliens.erase(aliens.begin() + i);
    }
}

// Constructor / Destructor

Game::Game() {
    this->font.loadFromFile("/Users/zavierboyles/Documents/Coding/C++/BurstGame/assets/Neon.ttf");
    this->initVariables();
    this->initWindow(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
}

Game::~Game() {
    delete this->window;
}

// Accessors

const bool Game::isRunning() const {
    return this->window->isOpen();
}

// Public Functions

void Game::spawnAliens() {
    // Timer
    if (this->spawnTimer > this->spawnTimerMax) {
        this->spawnTimer += 0.1f;
    }
    else {
        if (this->aliens.size() < this->maxAliens) {
            this->aliens.push_back(AlienCharacter(this->window));
            this->spawnTimer = 0.f;
        }
    }
}

void Game::pollEvents() {
    // Event Polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape) {
                this->window->close();
            }
            break;
        
        default:
            break;
        }
    }
}

void Game::pollLasers() {
    player.pollLasers(lasers);
    for (AlienCharacter& a : aliens) {
        a.pollLasers(lasers);
    }
}

void Game::update() {
    this->pollEvents();
    this->pollLasers();

    for (unsigned short i = 0; i < lasers.size(); i++) {
        lasers[i].update();
        if (lasers[i].isOffscreen()) {
            lasers.erase(i + lasers.begin());
        }
    }
    this->spawnAliens();
    for (AlienCharacter& i : this->aliens) {
        i.update(this->window, player);
    }
    this->player.update();

    this->handleEntityCollisions();
    this->cleanupEnemies();
    this->updateUI();
}

void Game::render() {
    /*
        Render game objects to window
    */

    this->window->clear();

    for (Laser& l : this->lasers) {
        l.render(this->window);
    }

    this->player.render(this->window);
    for (AlienCharacter& i : this->aliens) {
        i.render(this->window);
    }

    this->window->draw(this->hpDisplay);
    this->window->draw(this->bulletCountDisplay);

    this->window->display();
}

sf::VideoMode Game::getWindowResolution() {
    return videoMode;
}