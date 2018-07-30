#include "states.h"

///Intro state
void state::Intro::draw(sf::RenderWindow& window) {
    window.draw(sf::Sprite(mIntroTexture));
}
