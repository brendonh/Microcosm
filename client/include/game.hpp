#ifndef __MICROCOSM_GAME
#define __MICROCOSM_GAME

#include <SFML/Graphics.hpp>

#include <GL/gl.h>
#include <GL/glu.h>

#include <Box2D/Box2D.h>

#include "pushbox.hpp"

namespace Microcosm {

  class Game {
  public:

    bool fullscreen;

    float timeStep;
    float unrenderedTime;

    sf::RenderWindow* window;
    sf::Clock* clock;
    sf::Text* speed;

    b2World *world;

    PushBox* pb;
    PushBox* stat;

    Game(bool f);
    ~Game();

    void init();
    void mainloop();

    void initOpenGL();
    void initSFML();
    void initBox2D();

    void handleEvents();

  };


}

#endif
