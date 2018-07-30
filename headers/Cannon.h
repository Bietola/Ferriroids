#pragma once

#include <cmath>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Shooter.h"

class World;

class Cannon {
    public:
        using ProjectilePtr = Shooter::ProjectilePtr;

    private:
        //shooter info
        Shooter mShooter;
        sf::Clock mShootClock;
        float mRechargeTime;

    public:
        //constructor
        Cannon(const sf::Vector2f& origin, const ProjectilePtr& projectile, float rechargeTime):
            mShooter(origin, projectile), mRechargeTime(rechargeTime) {}

        //destructor
        ~Cannon() {}

        //getters and setters
        const sf::Vector2f& getOrigin() const {return mShooter.getOrigin();}
        void setOrigin(const sf::Vector2f& origin) {mShooter.setOrigin(origin);}

        //shoot
        void shoot(const sf::Vector2f& velocity);
        void shoot(float angle, float speed);
};
