#include "PlayerCharacter.h"

// Private Functions
void PlayerCharacter::initVariables() {
    this->radius = 25.f;
    this->rotationSpeed = 4.f;
    this->movementSpeed = 2.f;
    this->laserCooldown = 20;
    this->laserCooldownTimer = laserCooldown;
    this->HIT_POINTS = 10u;
    this->shieldRadius = radius * 2.5f;
    this->damageCooldownTimer = 0;
    this->damageCooldown = 60;
    this->isInvulnerable = false;
    this->bulletCount = 0;
}

void PlayerCharacter::initShape() {
    // Set character shapes
    this->shape.setPointCount(3);
    this->shape.setPoint(0, sf::Vector2f(-0.67f * radius, 0.67f * radius));
    this->shape.setPoint(1, sf::Vector2f(0.67f * radius, 0.67f * radius));
    this->shape.setPoint(2, sf::Vector2f(0, -radius));
    this->shape.setOutlineColor(sf::Color::White);
    this->shape.setOutlineThickness(3);

    this->ring.setRadius(shieldRadius);
    this->ring.setHole(0.9);
    this->ring.setColor(sf::Color::White);
    this->ring.setSectorSize(0.4);
    this->ring.setSectorOffset(0.55);
}

// Constructor / Destructor

PlayerCharacter::PlayerCharacter(float x, float y) {
    this->shape.setPosition(x, y);
    this->ring.setPosition(x, y);
    
    this->initVariables();
    this->initShape();
    
}

PlayerCharacter::~PlayerCharacter() {

}

// Accessors

sf::Vector2f PlayerCharacter::getPosition() {
    return this->shape.getPosition();
}

float PlayerCharacter::getHeading()
{
    return this->shape.getRotation();
}

float PlayerCharacter::getX()
{
    return this->shape.getPosition().x;
}

float PlayerCharacter::getY()
{
    return this->shape.getPosition().y;
}

sf::ConvexShape PlayerCharacter::getShape() {
    return this->shape;
}

float PlayerCharacter::getRadius()
{
    return this->radius;
}

float PlayerCharacter::getShieldRadius()
{
    return this->shieldRadius;
}

bool PlayerCharacter::getInvulnerable()
{
    return this->isInvulnerable;
}

unsigned short PlayerCharacter::getHitPoints()
{
    return this->HIT_POINTS;
}

unsigned short PlayerCharacter::getBulletCount()
{
    return this->bulletCount;
}

void PlayerCharacter::addBullet()
{
    this->bulletCount++;
}

// Public Functions

void PlayerCharacter::updateInput() {
    // Keyboard Input
    //Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->shape.rotate(-rotationSpeed);
        this->ring.rotate(-rotationSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->shape.rotate(rotationSpeed);
        this->ring.rotate(rotationSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        float rotation = shape.getRotation() - 90;
        sf::Vector2f force = sf::Vector2f(cos(toRadians(rotation)), sin(toRadians(rotation)));
        vel += force;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && laserCooldownTimer == 0 && bulletCount > 0) {
        pendingLasers.push_back(Laser(this->shape.getPosition(), this->shape.getRotation() - 90, BulletType::Player, rotationSpeed));
        laserCooldownTimer = laserCooldown;
        bulletCount--;
    }
}

void PlayerCharacter::damage(unsigned short dmgAmnt) {
    this->HIT_POINTS -= dmgAmnt;

    // Check for death
    if (HIT_POINTS <= 0u) {
        // Die
        std::cout << "Dead!\n";
    }

    // Apply invulnerability
    this->isInvulnerable = true;
    this->damageCooldownTimer = damageCooldown;
}

void PlayerCharacter::pollLasers(std::vector<Laser> &larr)
{
    for (unsigned short i = 0; i < pendingLasers.size(); i++) {
        larr.push_back(pendingLasers[i]);
    }
    pendingLasers.clear();
}

void PlayerCharacter::update()
{
    // Update movement inputs
    this->updateInput();

    // Check wrapping bounds
    sf::Vector2f pos = shape.getPosition();
    if (pos.x > RESOLUTION_WIDTH + radius) {
        shape.setPosition(-radius, pos.y);
        ring.setPosition(-radius, pos.y);
    } else if (pos.x < -radius) {
        shape.setPosition(RESOLUTION_WIDTH + radius, pos.y);
        ring.setPosition(RESOLUTION_WIDTH + radius, pos.y);
    }
    if (pos.y > RESOLUTION_HEIGHT + radius) {
        shape.setPosition(pos.x, -radius);
        ring.setPosition(pos.x, -radius);
    } else if (pos.y < -radius) {
        shape.setPosition(pos.x, RESOLUTION_HEIGHT + radius);
        ring.setPosition(pos.x, RESOLUTION_HEIGHT + radius);
    }

    // Update movement physics
    vel *= 0.95f;
    shape.move(vel);
    ring.move(vel);

    if (laserCooldownTimer > 0) laserCooldownTimer--;

    if (damageCooldownTimer > 0) damageCooldownTimer--;
    else this->isInvulnerable = false;
}

void PlayerCharacter::render(sf::RenderTarget* target) {
    if (!this->isInvulnerable || (this->isInvulnerable && this->damageCooldownTimer % 5 == 0)) target->draw(this->shape);
    target->draw(this->ring);
}