#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "World.h"

namespace state {

class GameState {
    private:
        GameState* mNext = nullptr;

    public:
        //game logic
        virtual void handleEvent(sf::RenderWindow& window, const sf::Event& event) {}
        virtual void handleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed) {}
        virtual void draw(sf::RenderWindow& window) {}

        //set next state
        void setNext(GameState* next) {
            mNext = next;
        }
        template <class T, typename... Args>
        void setNext(Args&&... args) {
            setNext(new T(std::forward<Args>(args)...));
        }

        //change to next state if there is one
        friend void change(GameState*& state);
};

void change(GameState*& state);

class Intro: public GameState {
    private:
        sf::Texture mIntroTexture;

    public:
        //constructor
        Intro() {
            mIntroTexture.loadFromFile("art/ferri.png");
        }

        //game logic
        void draw(sf::RenderWindow& window) override;
};

class Asteroids: public GameState {
    private:
        //pointer to player
        std::weak_ptr<Entity> mPlayer;

        //level info
        int mCurrentLevel = 1;
        sf::Clock mLevelClock;

        //static interface
        sf::Text mLifeText;
        sf::Text mCurrentLevelText;
        sf::Text mLevelTimeLeftText;

        //level interface
        static double calcLevelTime(int currentLevel);
        void nextLevel();

        //update interface
        void updatePlayerInterface();

    public:
        //constructor
        Asteroids(const sf::RenderWindow& window);

        //game logic handling
        void handleEvent(sf::RenderWindow& window, const sf::Event& event) override final;
        void handleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed) override final;
        void draw(sf::RenderWindow& window) override final;
};

class End: public GameState {
    private:
        //level on which the player died
        int mLevelOfDeath;

        //text to show the player's achievements
        sf::Text mAchievementsText;

    public:
        //constructor
        End(const sf::RenderWindow& window, int levelOfDeath);

        //game logic handling
        void handleEvent(sf::RenderWindow& window, const sf::Event& event) override final;
        void handleLogic(sf::RenderWindow& window, const sf::Time& timeElapsed) override final;
        void draw(sf::RenderWindow& window) override final;
};

}
