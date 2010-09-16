#pragma once
#ifndef __MICROCOSM_FRAMEWORK_SHIP
#define __MICROCOSM_FRAMEWORK_SHIP

#include <Box2D/Box2D.h>

#include "reckoner/common/B2Util.hpp"
#include "reckoner/common/framework/WorldObject.hpp"

#include "ShipMovement.hpp"


namespace Microcosm {

  namespace Ships {

    class Ship : public Reckoner::Framework::WorldObject {
    public:

      Ship(b2World* world, b2Vec2 position, float angle);
      ~Ship();

      ShipMovement* mMovement;
      bool mEngineOn;

    private:
    };

  }
}


#endif
