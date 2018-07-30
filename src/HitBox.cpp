#include "HitBox.h"

#include "utils.h"

#include <iostream> //!DB

///Circle
//circle-circle collision
bool hb::Circle::isCollidingWith(const Circle& other) const {
    float distance = utils::intensity(getCenter() - other.getCenter());
    return distance < mRadius * 2.f;
}

//out of bounds
hb::OOBFlags hb::Circle::isOutOfBounds(const sf::FloatRect& bounds) const {
    OOBFlags retVal = 0;
    if(getTop() < bounds.top)
        retVal |= OOBF_TOP;
    if(getBottom() > bounds.top + bounds.height)
        retVal |= OOBF_BOTTOM;
    if(getLeft() < bounds.left)
        retVal |= OOBF_LEFT;
    if(getRight() > bounds.left + bounds.width)
        retVal |= OOBF_RIGHT;

    return retVal;
}

//completely out of bounds
hb::OOBFlags hb::Circle::isCompletelyOutOfBounds(const sf::FloatRect& bounds) const {
    OOBFlags retVal = 0;
    if(getBottom() < bounds.top)
        retVal |= OOBF_TOP;
    if(getTop() > bounds.top + bounds.height)
        retVal |= OOBF_BOTTOM;
    if(getRight() < bounds.left)
        retVal |= OOBF_LEFT;
    if(getLeft() > bounds.left + bounds.width)
        retVal |= OOBF_RIGHT;

    return retVal;
}

//bring object inside bounds (considering give out of bounds flags)
sf::Vector2f hb::Circle::bringInsideBounds(const sf::FloatRect& bounds, OOBFlags oobFlags) const {
    if(!oobFlags) return getPosition();

    auto insidePosition = getPosition();

    auto lowerBorders = sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height);
    auto upperBorders = sf::Vector2f(bounds.left, bounds.top);

    if(oobFlags & OOBF_LEFT)
        insidePosition.x = upperBorders.x + mRadius;

    if(oobFlags & OOBF_RIGHT)
        insidePosition.x = lowerBorders.x - mRadius;

    if(oobFlags & OOBF_TOP)
        insidePosition.y = upperBorders.y + mRadius;

    if(oobFlags & OOBF_BOTTOM)
        insidePosition.y = lowerBorders.y - mRadius;

    return insidePosition;
}

//debug draw function
void hb::Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Transform translation = sf::Transform::Identity;
    translation.translate(mCenter);
    states.transform = translation;

    sf::CircleShape circleShape(mRadius);
    circleShape.setOrigin({mRadius, mRadius});
    circleShape.setFillColor(sf::Color(0, 255, 0, 122));

    target.draw(circleShape, states);
}
