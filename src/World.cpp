#include "World.h"

void World::handleEvent(sf::RenderWindow& window, const sf::Event& event) {
    for(const auto& entity : mEntities) {
        if(entity)
            entity->handleEvent(window, event);
    }
}

void World::handleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed) {
    //handle entity logic
    for(const auto& entity : mEntities) {
        if(entity)
            entity->handleLogic(window, timeElapsed, mCurrentCollisionsHandledFlag);
    }
    Entity::advanceCollisionsHandledFlag(mCurrentCollisionsHandledFlag);

    //despawn entities that need to be despawned
    despawnAll();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(const auto& entity : mEntities) {
        if(entity)
            target.draw(*entity);
    }
}
