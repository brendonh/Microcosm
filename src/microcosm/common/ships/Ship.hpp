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

      Ship(uuid_t uuid, b2World& world, b2Vec2 position, float angle);
      virtual ~Ship();

      ShipMovement* mMovement;
      bool mEngineOn;

      const b2Body& getBody() { return mBody; }

    private:

      friend class ShipMovement;

      static b2Body& createBody(b2World& world, 
                                b2Vec2 position, 
                                float angle);


    };

  }
}


#endif
