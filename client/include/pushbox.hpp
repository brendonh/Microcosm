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

  class PushBox {
  public:

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

    PushBox(b2World* world, float x, float y);

    void setState(int s, bool v);

    bool getState(int s);
    void setState(int s);
    void clearState(int s);

    void thrust();
    void turn(int dir);
    void brake();

    void stopTurn();

    void update();
    void render();

  };

  inline void PushBox::setState(int s, bool v) {
    if (v) setState(s);
    else clearState(s);
  }

  inline bool PushBox::getState(int s) { return state & (1 << s); }
  inline void PushBox::setState(int s) { state |= (1 << s); }
  inline void PushBox::clearState(int s) { state &= ~(1 << s); }

}
#endif
