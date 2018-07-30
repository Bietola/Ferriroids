#pragma once

#include <cmath>

#include "MovingEntity.h"

#include "utils.h"

class Meteor: public MovingEntity {
    public:
        //min and max spawn velocity components
        const float MIN_VELOCITY_COMP = 50;
        const float MAX_VELOCITY_COMP = 100;

        //sizes
        enum SIZE_T {
            SIZE_NONEXISTENT = 0,
            SIZE_TINY,
            SIZE_SMALL,
            SIZE_MEDIUM,
            SIZE_BIG
        };

        //colors
        enum COLOR_T {
            COLOR_GREY,
            COLOR_BROWN,
            COLOR_MAX
        };

    private:
        //meteors stats
        static int sNumLiving;
        static int sNumDestroyed;
        static int sNumBigDestroyed;

        //size
        SIZE_T mSize;

        //color
        COLOR_T mColor;

        //custom logic
        void vvHandleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed) override final {}
        void vDraw(sf::RenderTarget& target, sf::RenderStates states) const override final {}
        void vDie() override final;
        void onSpawn() override final;

    public:
        //constructor
        Meteor(const sf::Vector2f& position, SIZE_T size, COLOR_T color);
        Meteor(const sf::RenderWindow& window);

        //destructor
        ~Meteor() {}

        //clone
        ClonePtr clone() const override final {return std::make_shared<Meteor>(*this);}

        //logic
        void handleEvent(sf::RenderWindow& window, const sf::Event& event) override final {}

        //get static meteor info
        static int count() {return sNumLiving;}
        static int countDestroyed() {return sNumDestroyed;}
        static int countBigDestroyed() {return sNumBigDestroyed;}

};
