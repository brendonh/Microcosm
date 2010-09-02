#ifndef __MICROCOSM_GAME
#define __MICROCOSM_GAME

#include <SFML/Graphics.hpp>

#include <GL/gl.h>
#include <GL/glu.h>

#include <Box2D/Box2D.h>

#include "ship.hpp"

namespace Microcosm {

  class Game {
  public:

    Game(bool f);
    ~Game();

    void mainloop();
    void screenshot();

  private:

    bool fullscreen;

    float timeStep;
    float unrenderedTime;

    sf::RenderWindow* window;
    sf::Clock* clock;
    sf::Text* speed;

    b2World *world;

    Ship* pb;
    Ship* stat;

    void init();

    void initOpenGL();
    void initSFML();
    void initBox2D();

    void handleEvents();

    void renderTo(sf::RenderTarget *target);
  };


}

#endif
