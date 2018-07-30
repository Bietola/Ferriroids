#include "Cannon.h"

//shoot
void Cannon::shoot(const sf::Vector2f& velocity) {
    if(mShootClock.getElapsedTime().asSeconds() > mRechargeTime) {
        mShootClock.restart();
        mShooter.shoot(velocity);
    }
}
void Cannon::shoot(float angle, float speed) {
    shoot(sf::Vector2f(std::cos(angle), std::sin(angle)) * speed);
}
