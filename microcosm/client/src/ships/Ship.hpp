#pragma once
#ifndef __MICROCOSM_FRAMEWORK_SHIP
#define __MICROCOSM_FRAMEWORK_SHIP

#include <Box2D/Box2D.h>

#include "common/Microcosm.hpp"
#include "common/B2Util.hpp"

#include "framework/WorldObject.hpp"
#include "ships/ShipMovement.hpp"


namespace Microcosm {
  
  namespace Ships {

    class Ship : public Microcosm::Framework::WorldObject {
    public:
      
      Ship();
      ~Ship();

      void Init(b2World* world, b2Vec2 position, float angle);

      void render();
      void handleInput(const sf::Input& Input);

      float getSpeed();

    private:

      friend class ShipMovement;

      b2Body*  mBody;
      bool mEngineOn;

      ShipMovement* mMovement;

    };

  }
}


#endif
