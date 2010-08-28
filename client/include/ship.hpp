#ifndef __MICROCOSM_PUSHBOX
#define __MICROCOSM_PUSHBOX

#include <Box2D/Box2D.h>

#include "microcosm.hpp"

namespace Microcosm {
  
  enum ship_states { 
    SHIP_THRUST = 0, 
    SHIP_BRAKE = 1, 
    SHIP_TURN_LEFT = 2, 
    SHIP_TURN_RIGHT = 3
  };

  class Ship {
  public:
    Ship(b2World* world, float x, float y);

    void setState(int s, bool v);

    bool getState(int s);
    void setState(int s);
    void clearState(int s);

    void update();
    void render();

    float getSpeed();

  private:
    b2World* world;
    b2Body*  body;

    b2Vec2 position;
    float32 angle;

    float mainThrust;
    float turnThrust;

    float maxSpeed;
    float maxTurn;

    char state;

    bool engine;

    void init();

    void thrust();
    void turn(int dir);
    void brake();
    void stopTurn();

  };

  inline void Ship::setState(int s, bool v) {
    if (v) setState(s);
    else clearState(s);
  }

  inline bool Ship::getState(int s) { return state & (1 << s); }
  inline void Ship::setState(int s) { state |= (1 << s); }
  inline void Ship::clearState(int s) { state &= ~(1 << s); }

}
#endif
