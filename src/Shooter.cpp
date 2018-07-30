#include "Shooter.h"

#include <cassert>

#include "Entity.h"
#include "MovingEntity.h"
#include "World.h"

//shoot
void Shooter::shoot(const sf::Vector2f& velocity) {
    //asserts
    assert(Entity::sWorld && "shooter needs Entity::sWorld to shoot (projectile needs to be spawned on it");

    //prepare projectile
    mProjectile->setPosition(mOrigin);
    mProjectile->setVelocity(velocity);
    mProjectile->setCollisionsHandledFlag(Entity::sWorld->getCurrentCollisionsHandledFlag());

    //shoot it
    Entity::sWorld->spawn(mProjectile->clone());
}
void Shooter::shoot(float angle, float speed) {
    shoot(sf::Vector2f(std::cos(angle), std::sin(angle)) * speed);
}
