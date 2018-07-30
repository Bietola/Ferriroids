#pragma once

#include <cassert>
#include <memory>

#include <SFML/Graphics.hpp>

#include "utils.h"

namespace hb {

//out of bounds type flag
enum OOB_FLAG_T: char {
    OOBF_NONE       = 0,
    OOBF_LEFT       = 1,
    OOBF_RIGHT      = 2,
    OOBF_TOP        = 4,
    OOBF_BOTTOM     = 8
};
using OOBFlags = char;

//forwarding (all classes)
class HitBox;
class Circle;

//factory function to create children
using Ptr = std::unique_ptr<HitBox>;
template <class T, typename... Args>
Ptr create(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

//base class
class HitBox {
    public:
        //clone
        virtual Ptr clone() const = 0;

        //change position
        virtual const sf::Vector2f& getPosition() const = 0;
        virtual void setPosition(const sf::Vector2f& position) = 0;
        void move(const sf::Vector2f& displacement) {setPosition(getPosition() + displacement);}

        //out of bounds
        virtual OOBFlags isOutOfBounds(const sf::FloatRect& bounds) const = 0;
        virtual OOBFlags isCompletelyOutOfBounds(const sf::FloatRect& bounds) const = 0;
        virtual sf::Vector2f bringInsideBounds(const sf::FloatRect& bounds, OOBFlags oobFlags) const = 0;

        //collision with other hitbox
        virtual bool isColliding(const HitBox& other) const = 0;
        //multiple dispatch methods
        virtual bool isCollidingWith(const Circle& other) const = 0;

        //debug draw function
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {assert("draw method not supported in hitbox");}
};

//base class to inherit from
template <class T>
class HitBoxImpl: public HitBox {
    public:
        //automatic override for multiple dispatch
        bool isColliding(const HitBox& other) const override final {
            return other.isCollidingWith(*static_cast<const T*>(this));
        }
};

//children
class Circle: public HitBoxImpl<Circle> {
    private:
        //used in collision
        sf::Vector2f mCenter = {0, 0};
        float mRadius = 0;

        //collision with other hitbox
        bool isCollidingWith(const Circle& other) const override final;

    public:
        //constructor
        Circle(const sf::Vector2f& center, float radius):
            mCenter(center), mRadius(radius) {}

        //getters and setters
        const sf::Vector2f& getCenter() const {return mCenter;}

        //clone
        Ptr clone() const override final {return create<Circle>(*this);}

        //virtual setters and getters
        const sf::Vector2f& getPosition() const override final {return mCenter;}
        void setPosition(const sf::Vector2f& position) override final {mCenter = position;}

        //out of bounds
        OOBFlags isOutOfBounds(const sf::FloatRect& bounds) const override final;
        OOBFlags isCompletelyOutOfBounds(const sf::FloatRect& bounds) const override final;
        sf::Vector2f bringInsideBounds(const sf::FloatRect& bounds, OOBFlags oobFlags) const override final;

        //debug draw method
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        //important geometric points
        float getTop() const {return mCenter.y - mRadius;}
        float getBottom() const {return mCenter.y + mRadius;}
        float getLeft() const {return mCenter.x - mRadius;}
        float getRight() const {return mCenter.x + mRadius;}
};

}
