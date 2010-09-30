#ifndef __MICROCOSM_GAME
#define __MICROCOSM_GAME

#include <SFML/Graphics.hpp>

#include <Box2D/Box2D.h>

#include "ships/ClientShip.hpp"

namespace Microcosm {

  class Game {
  public:

    Game(bool fullscreen);
    ~Game();

    bool tick();
    void screenshot();

    float timeStep;

  private:

    bool fullscreen;

    float unrenderedTime;

    sf::RenderWindow* window;
    sf::Clock* clock;

    sf::String* speed;

    b2World mWorld;

    Ships::ClientShip* pb;
    Ships::ClientShip* stat;

    void init();

    void initOpenGL();
    void initSFML();
    void initBox2D();

    void handleEvents();

    void renderTo(sf::RenderTarget *target);
  };


}

#endif
