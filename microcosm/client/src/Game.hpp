#ifndef __MICROCOSM_GAME
#define __MICROCOSM_GAME

#include <SFML/Graphics.hpp>

#include <Box2D/Box2D.h>

#include "ships/Ship.hpp"

namespace Microcosm {

  class Game {
  public:

    Game(bool f);
    ~Game();

    void mainloop();
    void screenshot();

    float timeStep;

  private:

    bool fullscreen;

    float unrenderedTime;

    sf::RenderWindow* window;
    sf::Clock* clock;
    sf::Text* speed;

    b2World *world;

    Ships::Ship* pb;
    Ships::Ship* stat;

    void init();

    void initOpenGL();
    void initSFML();
    void initBox2D();

    void handleEvents();

    void renderTo(sf::RenderTarget *target);
  };


}

#endif
