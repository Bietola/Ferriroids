#include "MovingEntity.h"

#include "World.h"
#include "Cannon.h"

//constructors
MovingEntity::MovingEntity(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& spriteSize,
                           OOBAction outOfBoundsAction, int collisionDamage, int life,
                           hb::Ptr hitBox):
    Entity(texture, position, spriteSize, collisionDamage, life, std::move(hitBox)), mOutOfBoundsAction(outOfBoundsAction) {
    ;
}
MovingEntity::MovingEntity(const sf::Texture* texture, const sf::Vector2f& position, OOBAction outOfBoundsAction):
    Entity(texture, position), mOutOfBoundsAction(outOfBoundsAction) {
    ;
}
MovingEntity::MovingEntity(const sf::Texture* texture, OOBAction outOfBoundsAction):
    Entity(texture), mOutOfBoundsAction(outOfBoundsAction) {
    ;
}
MovingEntity::MovingEntity():
    Entity() {
    ;
}

//register a cannon
void MovingEntity::registerCannon(const CannonPtr& cannon) {
    mRegisteredCannons.push_back(cannon);
}

//handle border collisions
bool MovingEntity::handleBorderCollisions(const sf::FloatRect& borders) {
    auto center = sf::Vector2f((borders.left + borders.width) / 2.f, (borders.top + borders.height) / 2.f);

    bool dieAtTheEnd = false;
    //do what needs to be done depending on flag
    if(mHitBox) {
        if(mOutOfBoundsAction == OOBAction::Despawn) {
            if(mHitBox->isCompletelyOutOfBounds(borders))
                dieAtTheEnd = true;
        }

        else if(mOutOfBoundsAction == OOBAction::Stop) {
            //get out of bounds type (left, right, bottom or top)
            auto oob = mHitBox->isOutOfBounds(borders);

            //bring hitbox inside bounds again
            setPosition(mHitBox->bringInsideBounds(borders, oob));

            //stop x
            if((oob & hb::OOBF_LEFT) || (oob & hb::OOBF_RIGHT)) {
                mVelocity.x = 0;
                mAcceleration.x = 0;
            }
            //stop y
            if((oob & hb::OOBF_TOP) || (oob & hb::OOBF_BOTTOM)) {
                mVelocity.y = 0;
                mAcceleration.y = 0;
            }
        }

        else if(mOutOfBoundsAction == OOBAction::Reappear) {
            if(mHitBox->isCompletelyOutOfBounds(borders))
                move(2.f * (center - getPosition()));
        }
    }

    return dieAtTheEnd;
}

//move all things contained in entity
void MovingEntity::setPosition(const sf::Vector2f& position) {
    //move graphic transform and hitbox
    Entity::setPosition(position);

    //move cannons
    //!WIP: move cannons to Entity class, there's not reason a non-moving entity cannot have cannons...
    //move entity cannons
    for(auto cannon : mRegisteredCannons) {
        cannon->setOrigin(position);
    }
}

//handle collisions with other entities
void MovingEntity::handleEntityCollisions(COLLISIONS_HANDLED_FLAG_T collHFlag) {
    for(auto collider : sWorld->getEntities()) {
        if(collider && shared_from_this() != collider &&
           !collider->isDead() &&
           collider->getCollisionFaction() != getCollisionFaction() &&
           collider->canCollide() && !collider->collisionsHandled(collHFlag) &&
           collider->isColliding(*this))
            handleEntityCollision(collider);
    }
}

//forced logic (move entity every turn)
void MovingEntity::vHandleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed, COLLISIONS_HANDLED_FLAG_T collHFlag) {
    //accelerate entity
    mVelocity += mAcceleration * timeElapsed.asSeconds();

    //simulate next position
    auto displacement = mVelocity * timeElapsed.asSeconds();

    //move entity
    move(displacement);

    //handle border collisions
    bool dieAtTheEnd = handleBorderCollisions(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

    //handle collisions with other entities
    handleEntityCollisions(collHFlag);

    //custom logic
    vvHandleLogic(window, timeElapsed);

    //despawn entity if necessary
    if(dieAtTheEnd)
        die();
}
