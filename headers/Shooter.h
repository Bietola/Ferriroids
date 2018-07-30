#pragma once

#include <cmath>
#include <memory>

#include <SFML/Graphics.hpp>

class MovingEntity;

class Shooter {
    public:
        using ProjectilePtr = std::shared_ptr<MovingEntity>;

    private:
        sf::Vector2f mOrigin;
        ProjectilePtr mProjectile;

    public:
        //constructor
        Shooter(const sf::Vector2f& origin, const ProjectilePtr& projectile):
            mOrigin(origin), mProjectile(projectile) {}

        //destructor
        ~Shooter() {}

        //getters and setters
        const sf::Vector2f& getOrigin() const {return mOrigin;}
        void setOrigin(const sf::Vector2f& origin) {mOrigin = origin;}

        //shoot
        void shoot(const sf::Vector2f& velocity);
        void shoot(float angle, float speed);
};
