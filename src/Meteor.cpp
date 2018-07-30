#include "Meteor.h"

#include <sstream>

#include "World.h"
#include "media.h"

//static
int Meteor::sNumLiving = 0;
int Meteor::sNumDestroyed = 0;
int Meteor::sNumBigDestroyed = 0;

//constructor
Meteor::Meteor(const sf::Vector2f& position, SIZE_T size, COLOR_T color):
    MovingEntity(), mSize(size), mColor(color) {
    //set life
    setLife(1);

    //set position
    setPosition(position);

    //set collision damage
    setCollisionDamage(1);

    //set collision faction
    setCollisionFaction(COLLFACT_ENEMY);

    //set oob action to reappear
    setOutOfBoundsAction(OOBAction::Reappear);

    //load corresponding texture
    std::stringstream txtrSS;
    txtrSS << "meteor";

    //color
    switch(color) {
        case COLOR_GREY:
            txtrSS << "Grey";
            break;
        default:
            txtrSS << "Brown";
    }
    txtrSS << "_";

    //size
    int numRandVar;
    switch(size) {
        case SIZE_TINY:
            txtrSS << "tiny";
            numRandVar = 2;
            break;
        case SIZE_SMALL:
            txtrSS << "small";
            numRandVar = 2;
            break;
        case SIZE_MEDIUM:
            txtrSS << "med";
            numRandVar = 2;
            break;
        case SIZE_BIG:
            txtrSS << "big";
            numRandVar = 4;
            break;
        default:
            assert(false && "invalid asteroid size while constructing one");
    }

    //pick random variant
    txtrSS << (rand() % numRandVar + 1);

    //set selected texture
    setTexture(gTextureProvider.getMediaPtr(txtrSS.str()));

    //adjust sprite size and hitbox
    auto spriteSize = sf::Vector2f(getTexture()->getSize());
    setSpriteSize(spriteSize);
    setOrigin(spriteSize.x / 2.f, spriteSize.y / 2.f);
    mHitBox = hb::create<hb::Circle>(getPosition(), std::min(spriteSize.x, spriteSize.y) / 2.f);

    //set random initial velocity
    setVelocity({float(rand()) / RAND_MAX * (MAX_VELOCITY_COMP - MIN_VELOCITY_COMP) + MIN_VELOCITY_COMP,
                 float(rand()) / RAND_MAX * (MAX_VELOCITY_COMP - MIN_VELOCITY_COMP) + MIN_VELOCITY_COMP});
    if(rand() % 2)
        setVelocity({-getVelocity().x, getVelocity().y});
    if(rand() % 2)
        setVelocity({getVelocity().x, -getVelocity().y});
}
Meteor::Meteor(const sf::RenderWindow& window):
    Meteor(utils::randBorderVec2(sf::Vector2f(window.getSize())),
           SIZE_BIG,
           COLOR_T(rrange(int(COLOR_MAX))))
{
    ;
}

//split before dying
void Meteor::vDie() {
    //spawn two smaller asteroids
    SIZE_T spawnSize = SIZE_T(mSize - 1);
    if(spawnSize != SIZE_NONEXISTENT) {
        Entity::sWorld->spawn<Meteor>(getPosition(), spawnSize, mColor);
        Entity::sWorld->spawn<Meteor>(getPosition(), spawnSize, mColor);
    }

    //decrement spawn counter
    sNumLiving--;
    sNumDestroyed++;
    if(mSize == SIZE_BIG)
        sNumBigDestroyed++;
}

//augment spawn counter when spawning
void Meteor::onSpawn() {
    sNumLiving++;
}
