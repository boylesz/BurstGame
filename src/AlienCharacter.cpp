#include "AlienCharacter.h"

// Private Functions

void AlienCharacter::initVariables() {
    this->speed = 6.f;
    this->reachedLocation = true;
    this->movementCooldownTimer = 0;
    this->movementCooldownLength = 90;
    this->attackCooldownLength = 150;
    this->attackVariation = 60;
    this->attackCooldownTimer = this->attackCooldownLength + (rand() % this->attackVariation * 2 - this->attackVariation);
    this->hitpoints = 1u;
}

void AlienCharacter::initShape(sf::RenderTarget* window) {
    this->shape.setRadius(35.f);
    this->shape.setHole(0.6);
    this->shape.setColor(sf::Color::White);
    this->shape.setPosition(
        static_cast<float>(rand() % window->getSize().x),
        static_cast<float>(rand() % window->getSize().y)
    );
    this->shape.setSectorSize(0.8);
    this->shape.setSectorOffset(0.1);

    this->eye.setRadius(4.f);
    this->eye.setHole(0.f);
    this->eye.setNumberOfSides(10);
    this->eye.setColor(sf::Color::Red);
    this->eye.setPosition(28.5f * cos(toRadians(this->shape.getRotation())), 28.5f * sin(toRadians(this->shape.getRotation())));
}

void AlienCharacter::getNewTargetLocation(sf::RenderTarget* window) {
    this->startLocation = this->shape.getPosition();
    this->targetLocation = this->shape.getPosition() + vectorFromAngle(rand() % 360) * (rand() % 400 + 100.f);
    this->checkBounds(window);
    this->lerpAlpha = 0.f;
    const float scaleFactor = getVectorMag(targetLocation - startLocation) / speed;
    this->lerpIncrement = 1 / scaleFactor;
    reachedLocation = false;
}

void AlienCharacter::checkBounds(sf::RenderTarget* window) {
    const sf::FloatRect screenBounds(0.f, 0.f, window->getSize().x, window->getSize().y);
    if (!screenBounds.contains(this->targetLocation)) {
        this->targetLocation = this->shape.getPosition() + vectorFromAngle(rand() % 360) * (rand() % 400 + 100.f);
        this->checkBounds(window);
    }
}

void AlienCharacter::moveToTargetLocation() {
    lerpAlpha += lerpIncrement;
    this->shape.setPosition(lerp(startLocation, targetLocation, lerpAlpha));
}

void AlienCharacter::updateEyeLocation(PlayerCharacter& player) {
    const float angleToPlayer = atan2(player.getPosition().y - this->shape.getPosition().y, player.getPosition().x - this->shape.getPosition().x);
    this->shape.setRotation(toDegrees(angleToPlayer));
    this->eye.setPosition(28.5f * cos(angleToPlayer) + this->shape.getPosition().x, 28.5f * sin(angleToPlayer) + this->shape.getPosition().y);
}

// Constructor / Destructor

AlienCharacter::AlienCharacter(sf::RenderTarget* window) {
    this->initVariables();
    this->initShape(window);
}

AlienCharacter::~AlienCharacter() {

}

sf::Vector2f AlienCharacter::getPosition()
{
    return this->shape.getPosition();
}

float AlienCharacter::getX()
{
    return this->shape.getPosition().x;
}

float AlienCharacter::getY()
{
    return this->shape.getPosition().y;
}

sw::Ring AlienCharacter::getShape()
{
    return this->shape;
}

float AlienCharacter::getRadius()
{
    return this->shape.getRadius();
}

unsigned short AlienCharacter::getHitpoints()
{
    return this->hitpoints;
}

// Accessors



// Public Functions

void AlienCharacter::damage(unsigned short dmgAmnt)
{
    this->hitpoints -= dmgAmnt;
}

void AlienCharacter::attackPlayer()
{
    pendingLasers.push_back(Laser(this->shape.getPosition(), this->shape.getRotation(), BulletType::Enemy));
}

void AlienCharacter::pollLasers(std::vector<Laser> &larr)
{
    for (unsigned short i = 0; i < pendingLasers.size(); i++) {
        larr.push_back(pendingLasers[i]);
    }
    pendingLasers.clear();
}

void AlienCharacter::update(sf::RenderTarget* window, PlayerCharacter& player) {
    // Check if enemy has reached its target location
    if (this->lerpAlpha >= 1.f) reachedLocation = true;

    // Move
    if (!this->reachedLocation) {
        this->moveToTargetLocation();
    }
    else {
        if (this->movementCooldownTimer < this->movementCooldownLength) {
            this->movementCooldownTimer++;
        }
        else {
            this->getNewTargetLocation(window);
            this->movementCooldownTimer = 0;
        }
    }

    // Update rotation
    this->updateEyeLocation(player);

    // Attack player
    if (this->attackCooldownTimer > 0) {
        this->attackCooldownTimer--;
    }
    else {
        this->attackPlayer();
        this->attackCooldownTimer = this->attackCooldownLength + (rand() % this->attackVariation * 2 - this->attackVariation);
    }
}

void AlienCharacter::render(sf::RenderTarget* target) {
    target->draw(this->shape);
    target->draw(this->eye);
}