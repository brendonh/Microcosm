#pragma once
#ifndef __MICROCOSM_SHIPS_SHIPMOVEMENT
#define __MICROCOSM_SHIPS_SHIPMOVEMENT

#include <SFML/Window.hpp>

#include "reckoner/common/framework/WorldObject.hpp"
#include "reckoner/common/framework/Component.hpp"

namespace Microcosm {
  namespace Ships {

    class ShipMovement : public Reckoner::Framework::Component {
    public:

      ShipMovement(Reckoner::Framework::WorldObject& obj);

      virtual void tick();

    private:

      // XXX TODO: These should be in the ShipState
      float mMainThrust;
      float mTurnSpeed;
      float mMaxSpeed;

      void thrust();
      void turn(int dir);
      void brake();

    };

  }
}

#endif
