#include "Entity.h"

#include "World.h"

#include <iostream>

//statics
World* Entity::sWorld = nullptr;
bool Entity::sDebugMode = false;

//constructors
Entity::Entity(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& spriteSize,
               int collisionDamage, int life,
               hb::Ptr hitBox):
    mTexture(texture),
    mSprite(spriteSize),
    mHitBox(std::move(hitBox)),
    mCollisionDamage(collisionDamage),
    mLife(life)
{
    //set position
    setPosition(position);

    //set up sprite
    mSprite.setTexture(texture);
    mSprite.setOutlineColor(sf::Color::Red);
}
Entity::Entity(const sf::Texture* texture, const sf::Vector2f& position):
    Entity(texture, position, {0, 0}, -1, -1, nullptr) {
    if(texture)
        mSprite.setSize(sf::Vector2f(texture->getSize()));
}
Entity::Entity(const sf::Texture* texture):
    Entity(texture, {0, 0})
{
    ;
}
Entity::Entity():
    Entity(nullptr) {
    ;
}

//copy constructor
Entity::Entity(const Entity& other):
    mTexture(other.mTexture),
    mSprite(other.mSprite),
    mHitBox(other.mHitBox->clone()),
    mCollisionDamage(other.mCollisionDamage),
    mLife(other.mLife),
    mCollisionsHandledFlag(other.mCollisionsHandledFlag),
    mCollisionFaction(other.mCollisionFaction)
{
    setOrigin(other.getOrigin());
    setPosition(other.getPosition());
    setRotation(other.getRotation());
    setScale(other.getScale());
}

//set position of entity and all of its things
void Entity::setPosition(const sf::Vector2f& position) {
    //set position for graphic transformation
    sf::Transformable::setPosition(position);

    //move hitbox
    if(mHitBox) mHitBox->setPosition(position);
}

//move entity and all of its things
void Entity::move(const sf::Vector2f& displacement) {
    setPosition(getPosition() + displacement);
}

//die
void Entity::die() {
    //perform custom logic before dying
    vDie();

    //remove from world
    mToDespawn = true;
}

//collisions
void Entity::handleEntityCollision(const BasePtr& collider) {
    //advance collision handled flag
    advanceCollisionsHandledFlag(mCollisionsHandledFlag);

    //damage both entities
    setLife(getLife() - collider->getCollisionDamage());
    collider->setLife(collider->getLife() - getCollisionDamage());
}

//handle entity specific forces logic
void Entity::handleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed, COLLISIONS_HANDLED_FLAG_T collHFlag) {
    //custom logic
    vHandleLogic(window, timeElapsed, collHFlag);

    //make entity die when life reaches 0
    if(mLife <= 0)
        die();
}

//draw
void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    //draw sprite (and its bounds if in debug mode)
    if(sDebugMode) const_cast<Entity*>(this)->mSprite.setOutlineThickness(3);
    else const_cast<Entity*>(this)->mSprite.setOutlineThickness(0);
    states.transform = getTransform();
    target.draw(mSprite, states);

    //draw hitbox if in debug mode
    if(sDebugMode && mHitBox)
        mHitBox->draw(target, states);

    //custom drawing
    vDraw(target, states);
}
