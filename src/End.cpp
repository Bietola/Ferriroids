#include "states.h"

#include <sstream>

#include "media.h"
#include "Meteor.h"

//constructor
state::End::End(const sf::RenderWindow& window, int levelOfDeath):
    mLevelOfDeath(levelOfDeath),
    mAchievementsText("score: 000", gFontProvider.getMedia("kenvector_future_thin"), 30)
{
    //adjust achievement text
    std::stringstream endMessage;
    endMessage << "Alas," << std::endl << "The Great Ferri has been stricken down." << std::endl;
    endMessage << "Before dying an awesome death, he:" << std::endl;
    endMessage << "Made it to level " << mLevelOfDeath << "," << std::endl;
    endMessage << "Obliterated " << Meteor::countBigDestroyed() << " big asteroids and" << std::endl;
    endMessage << Meteor::countDestroyed() - Meteor::countBigDestroyed() << " others." << std::endl;
    if(mLevelOfDeath < 3)
        endMessage << "All in all, he did ok..." << std::endl;
    else if(mLevelOfDeath < 5)
        endMessage << "He was as awesome as his accent." << std::endl;
    else if(mLevelOfDeath < 7)
        endMessage << "His quest will forever be remembered." << std::endl;
    else
        endMessage << "Legends will tell of his innumerable achievements." << std::endl;
    mAchievementsText.setString(endMessage.str());
    //mAchievementsText.setString("hello");
    mAchievementsText.setPosition({0, window.getSize().y / 2.f - 200.f});
}

//handle events
void state::End::handleEvent(sf::RenderWindow& window, const sf::Event& event) {
    //close window and shut down state engine when key is pressed
    if(event.type == sf::Event::Closed)
        window.close();
    setNext(nullptr);
}
void state::End::handleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed) {
    //nothing...
    ;
}
void state::End::draw(sf::RenderWindow& window) {
    //draw achievements
    window.draw(mAchievementsText);
}
