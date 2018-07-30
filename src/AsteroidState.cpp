#include "states.h"

#include "Ferri.h"
#include "Meteor.h"

///Asteroids state
state::Asteroids::Asteroids(const sf::RenderWindow& window):
    mLifeText("lives: 00", gFontProvider.getMedia("kenpixel_future"), 40),
    mCurrentLevelText("level: 00", gFontProvider.getMedia("kenpixel_future"), 40),
    mLevelTimeLeftText("lv.time: 00", gFontProvider.getMedia("kenpixel_future"), 40)
{
    //set up world
    Entity::sWorld = new World;

    //set up player interface
    mLifeText.setColor(sf::Color::Green);
    mLifeText.setPosition(window.getSize().x - mLifeText.getGlobalBounds().width ,0);
    mCurrentLevelText.setColor(sf::Color::White);
    mCurrentLevelText.setPosition(window.getSize().x - mCurrentLevelText.getGlobalBounds().width,
                                  mLifeText.getGlobalBounds().height + 10);
    mLevelTimeLeftText.setColor(sf::Color::White);
    mLevelTimeLeftText.setPosition(window.getSize().x - mLevelTimeLeftText.getGlobalBounds().width,
                                   mLifeText.getGlobalBounds().height +
                                   mCurrentLevelText.getGlobalBounds().height + 20);

    //spawn the great Ferri (player)
    auto ferri = std::make_shared<Ferri>(300);
    mPlayer = ferri;
    ferri->setPosition({100, 100});
    Entity::sWorld->spawn(ferri);
}

//calculates the time that the given level should last
double state::Asteroids::calcLevelTime(int currentLevel) {
    return double(currentLevel * 30);
}

//goes up a level
void state::Asteroids::nextLevel() {
    mCurrentLevel++;
    mLevelClock.restart();
}

//update interface
void state::Asteroids::updatePlayerInterface() {
    //check if player is still alive
    auto player = mPlayer.lock();
    if(!player)
        return;

    //life
    if(player->getLife() <= 3)
        mLifeText.setColor(sf::Color::Red);
    else if(player->getLife() <= 5)
        mLifeText.setColor(sf::Color::Yellow);
    mLifeText.setString("lives: " + utils::intToFixedDigitsString(player->getLife(), 2));

    //level
    mCurrentLevelText.setString("level: " + utils::intToFixedDigitsString(mCurrentLevel, 2));

    //level time left
    int timeToDisplay = int(mLevelClock.getElapsedTime().asSeconds());
    std::string stringToDisplay;
    if(timeToDisplay > calcLevelTime(mCurrentLevel))
        stringToDisplay = "!!";
    else
        stringToDisplay = utils::intToFixedDigitsString(calcLevelTime(mCurrentLevel) - timeToDisplay, 2);
    mLevelTimeLeftText.setString("lv.time: " + stringToDisplay);
}

//handle events
void state::Asteroids::handleEvent(sf::RenderWindow& window, const sf::Event& event) {
    //handle debug overlay event
    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::T)
            Entity::sDebugMode = !Entity::sDebugMode;
    }

    //handle world event
    Entity::sWorld->handleEvent(window, event);
}

//handle drawing
void state::Asteroids::draw(sf::RenderWindow& window) {
    //draw world
    window.draw(*Entity::sWorld);

    //draw player interface
    window.draw(mLifeText);
    window.draw(mCurrentLevelText);
    window.draw(mLevelTimeLeftText);
}

//handle logic
void state::Asteroids::handleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed) {
    //switch to end state if player is dead
    if(mPlayer.expired()) {
        setNext<End>(window, mCurrentLevel);
        return;
    }

    //level logic
    if(mLevelClock.getElapsedTime().asSeconds() < calcLevelTime(mCurrentLevel)) {
        if(perc(0.3 * mCurrentLevel))
            Entity::sWorld->spawn<Meteor>(window);
    }
    else {
        nextLevel();
    }

    //update player interface
    updatePlayerInterface();

    //handle world logic
    Entity::sWorld->handleLogic(window, timeElapsed);
}
