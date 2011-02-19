#ifndef __MICROCOSM_GAME
#define __MICROCOSM_GAME

#include <SFML/Graphics.hpp>

#include "reckoner/common/framework/WorldObject.hpp"

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

    Reckoner::Framework::WorldObject* pb;
    Reckoner::Framework::WorldObject* stat;

    void init();

    void initOpenGL();
    void initSFML();
    void initWorld();

    void handleEvents();

    void renderTo(sf::RenderTarget *target);
  };


}

#endif
