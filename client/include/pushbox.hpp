#ifndef __MICROCOSM_PUSHBOX
#define __MICROCOSM_PUSHBOX

#include <Box2D/Box2D.h>

#include "microcosm.hpp"

namespace Microcosm {

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

    PushBox(b2World* world, float x, float y);

    void thrust();
    void turn(int sign);
    void stopTurn();
    void brake(int on);

    void update();
    void render();

  };

}
#endif
