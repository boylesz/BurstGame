#include "Laser.h"

// Private Functions

void Laser::initVariables(float angle, BulletType t, float rotVel) {
    vel = vectorFromAngle(angle);
    vel = vel * 30.f + sf::Vector2f(-vel.y, vel.x) * rotVel;
    type = t;
}

void Laser::initShape(sf::Vector2f startPos) {
    this->shape.setRadius(8.f);
    this->shape.setHole(0.f);
    this->shape.setNumberOfSides(10u);
    if (type == BulletType::Enemy) this->shape.setColor(sf::Color::Red);
    else this->shape.setColor(sf::Color::Blue);
    this->shape.setPosition(startPos);
}

// Constructor / Destructor

Laser::Laser(sf::Vector2f startPos, float angle, BulletType t, float rotVel) {
    this->initVariables(angle, t, rotVel);
    this->initShape(startPos);
}

Laser::~Laser() {

}

// Accessors

BulletType Laser::getType()
{
    return this->type;
}

sf::Vector2f Laser::getPosition()
{
    return this->shape.getPosition();
}

float Laser::getX()
{
    return this->shape.getPosition().x;
}

float Laser::getY()
{
    return this->shape.getPosition().y;
}

// Public Functions

bool Laser::isOffscreen() {
    // Offscreen
    if (this->shape.getPosition().x > RESOLUTION_WIDTH + this->shape.getRadius() ||
        this->shape.getPosition().y > RESOLUTION_HEIGHT + this->shape.getRadius() ||
        this->shape.getPosition().x < -this->shape.getRadius() ||
        this->shape.getPosition().y < -this->shape.getRadius()) {
        return true;
    }
    return false;
}

void Laser::update()
{
    this->shape.move(vel);

    
}

void Laser::render(sf::RenderTarget* window) {
    window->draw(this->shape);
}