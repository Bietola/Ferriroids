#include "DumProjectile.h"

#include <cassert>

//constructor
DumProjectile::DumProjectile(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& spriteSize):
    MovingEntity(texture, position, spriteSize, OOBAction::Despawn, 1, 1,
                 nullptr)
{
    //needs texture
    assert(texture && "dum projectile needs texture");

    //set collision faction
    setCollisionFaction(COLLFACT_FRIEND);

    //set up origin and hitbox
    float radius = float(std::max(spriteSize.x, spriteSize.y)) / 2.f;
    setOrigin(radius, radius);
    mHitBox = hb::create<hb::Circle>(getPosition(), radius);
}
DumProjectile::DumProjectile(const sf::Texture* texture, const sf::Vector2f& position):
    DumProjectile(texture, position, {0, 0}) {}
DumProjectile::DumProjectile(const sf::Texture* texture):
    DumProjectile(texture, {0, 0}) {}
