#pragma once
#ifndef __MICROCOSM_FRAMEWORK_SHIP
#define __MICROCOSM_FRAMEWORK_SHIP

#include "reckoner/common/framework/WorldObject.hpp"

#include "ShipMovement.hpp"


namespace Microcosm {

  namespace Ships {

    using namespace Reckoner::Framework;

    class Ship : public WorldObject {
    public:

      Ship(uuid_t uuid, PVR pos);
      virtual ~Ship();

      ShipMovement* mMovement;
      bool mEngineOn;

    };

  }
}


#endif
