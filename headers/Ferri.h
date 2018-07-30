#pragma once

#include <cmath>

#include "MovingEntity.h"
#include "Cannon.h"

#include "utils.h"
#include "media.h"

class Ferri: public MovingEntity {
    private:
        //kinematics
        float mSpeed;

        //cannon
        CannonPtr mCannon;

    public:
        //constructor
        Ferri(float speed);

        //destructor
        ~Ferri() {}

        //clone
        ClonePtr clone() const override final {return std::make_shared<Ferri>(*this);}

        //logic
        void handleEvent(sf::RenderWindow& window, const sf::Event& event) override final;
        void vvHandleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed) override final;
        void vDraw(sf::RenderTarget& target, sf::RenderStates states) const override final {}
};
