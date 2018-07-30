#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "utils.h"

class Cannon;

class MovingEntity: public Entity {
    public:
        //aliases
        using CannonPtr = std::shared_ptr<Cannon>;

        //what to do when out of bounds
        enum class OOBAction {
            Despawn,
            Stop,
            Reappear
        };

    protected:
        //position
        sf::Vector2f mVelocity = {0, 0};
        sf::Vector2f mAcceleration = {0, 0};

        //what to do when out of bounds
        OOBAction mOutOfBoundsAction = OOBAction::Despawn;

        //cannons
        std::vector<CannonPtr> mRegisteredCannons;

        //custom logic
        virtual void handleEvent(sf::RenderWindow& window, const sf::Event& event) override {}
        virtual void vvHandleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed) {}

    public:
        //constructor
        MovingEntity(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& spriteSize,
                     OOBAction outOfBoundsAction, int collisionDamage, int life,
                     hb::Ptr hitBox);
        MovingEntity(const sf::Texture* texture, const sf::Vector2f& position, OOBAction despawnWhenOutOfBounds);
        MovingEntity(const sf::Texture* texture, OOBAction despawnWhenOutOfBounds);
        MovingEntity();

        //destructor
        virtual ~MovingEntity() {}

        //getters and setters
        void setPosition(const sf::Vector2f& position) override final;

        const sf::Vector2f& getVelocity() const {return mVelocity;}
        void setVelocity(const sf::Vector2f& velocity) {mVelocity = velocity;}

        void setOutOfBoundsAction(OOBAction action) {mOutOfBoundsAction = action;}

        //cannon stuff
        void registerCannon(const CannonPtr& cannon);

        //handle border collisions - *
        bool handleBorderCollisions(const sf::FloatRect& borders);

        //handle collisions with other entities
        void handleEntityCollisions(COLLISIONS_HANDLED_FLAG_T collHFlag);

        //forced logic
        void vHandleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed, COLLISIONS_HANDLED_FLAG_T collHFlag) override final;
};

//(*) return if entity has to die at the end
