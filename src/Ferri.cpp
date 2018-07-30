#include "Ferri.h"

#include "DumProjectile.h"

//constructor
Ferri::Ferri(float speed):
    MovingEntity(gTextureProvider.getMediaPtr("ferri"), OOBAction::Stop),
    mSpeed(speed),
    mCannon(std::make_shared<Cannon>(
        sf::Vector2f(0, 0),
        std::make_shared<DumProjectile>(gTextureProvider.getMediaPtr("proton"), sf::Vector2f(0, 0), sf::Vector2f(50, 50)),
        0.5
    )) {
    //life
    setLife(10);

    //set collision damage
    setCollisionDamage(1);

    //collision faction
    setCollisionFaction(COLLFACT_FRIEND);

    //initialize hitbox
    mHitBox = hb::create<hb::Circle>(getPosition(), std::max(mSprite.getSize().x, mSprite.getSize().y) / 2.f);

    //initialize cannons
    registerCannon(mCannon);

    //set up transform
    setOrigin(getSpriteSize().x / 2.f + getPosition().x, getSpriteSize().y / 2.f + getPosition().y);
}

//event handling
void Ferri::handleEvent(sf::RenderWindow& window, const sf::Event& event) {
    if(event.type == sf::Event::KeyReleased)
        mVelocity = {0, 0};
}

//logic
void Ferri::vvHandleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed) {
    //move Ferri
    if(utils::areKeysPressed(sf::Keyboard::W, sf::Keyboard::D, sf::Keyboard::S, sf::Keyboard::A)) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            mVelocity.y = -1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            mVelocity.x = 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            mVelocity.y = 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            mVelocity.x = -1;
        //mVelocity *= mSpeed;
        mVelocity = utils::normalize(mVelocity, mSpeed);
    }
    else {
        mVelocity = {0, 0};
    }

    //get mouse information
    auto mousePosition = sf::Mouse::getPosition(window);
    auto mouseDistance = sf::Vector2f(mousePosition) - getPosition();

    //make the great Ferri face follow the mouse
    auto angle = std::atan(mouseDistance.y / mouseDistance.x);
    if(mouseDistance.x > 0) setRotation(angle / PI * 180);
    else setRotation(180 + angle / PI * 180);

    //shoot if the mouse is clicked
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        mCannon->shoot(utils::normalize(mouseDistance, 500.f));
    }
}
