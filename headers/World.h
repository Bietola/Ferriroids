#pragma once

#include <memory>
#include <vector>

#include "Entity.h"

#include "MovingEntity.h"

#include <iostream>

class World: public sf::Drawable, public sf::Transformable {
    public:
        using EntityPtr = std::shared_ptr<Entity>;

    private:
        //entities
        std::vector<EntityPtr> mEntities;

        //current collisions handled flag (for collision optimization)
        Entity::COLLISIONS_HANDLED_FLAG_T mCurrentCollisionsHandledFlag = Entity::COLLHANDLEDF_1;

    public:
        //constructor
        World() {}

        //destructor
        ~World() {}

        //getters and setters
        std::vector<EntityPtr> getEntities() {return mEntities;}

        Entity::COLLISIONS_HANDLED_FLAG_T getCurrentCollisionsHandledFlag() const {return mCurrentCollisionsHandledFlag;}

        //game logic handling
        void handleEvent(sf::RenderWindow& window, const sf::Event& event);
        void handleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

        //spawning
        void spawn(const EntityPtr& entity) {
            //add entity to world
            mEntities.emplace_back(entity);

            //custom entity spawn logic
            entity->onSpawn();
        }
        template<class EntityType, typename... Args>
        void spawn(Args&&... args) {
            spawn(std::make_shared<EntityType>(std::forward<Args>(args)...));
        }

        //despawning
        void despawnAll() {
            mEntities.erase(std::remove_if(mEntities.begin(), mEntities.end(), [](const auto& entity) {
                return entity->mToDespawn;
            }), mEntities.end());
        }
};
