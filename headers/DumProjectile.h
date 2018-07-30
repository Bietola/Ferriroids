#pragma once

#include <cmath>

#include "MovingEntity.h"

#include "utils.h"

class DumProjectile: public MovingEntity {
    private:

    public:
        //constructor
        DumProjectile(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& hitBox);
        DumProjectile(const sf::Texture* texture, const sf::Vector2f& position);
        DumProjectile(const sf::Texture* texture);

        //destructor
        ~DumProjectile() {}

        //clone
        ClonePtr clone() const override final {return std::make_shared<DumProjectile>(*this);}

        //logic
        void handleEvent(sf::RenderWindow& window, const sf::Event& event) override final {}
        void vvHandleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed) override final {}
        void vDraw(sf::RenderTarget& target, sf::RenderStates states) const override final {}
};
