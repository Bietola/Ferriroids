#include <iostream>
#include <cstdlib>
#include <ctime>

#include "states.h"
#include "media.h"

int main()
{
    //seed random
    srand(time(NULL));

    //load media
    load_media();

    //set up window
    sf::RenderWindow window(sf::VideoMode(750,750),"hello sfml");
    window.setFramerateLimit(30);

    //set up game state
    state::GameState* currentState = new state::Asteroids(window);

    //game loop
    sf::Clock gameClock;
    sf::Event e;
    while(window.isOpen() && currentState){
        //handle events
        while(window.pollEvent(e)){
            if(e.type == sf::Event::Closed)
                window.close();
            currentState->handleEvent(window, e);
        }

        //handle game logic
        currentState->handleLogic(window, gameClock.getElapsedTime());
        gameClock.restart();

        //render
        window.clear();
        currentState->draw(window);
        window.display();

        //change game state if necessary
        state::change(currentState);
    }

    //exit
    return 0;
}
