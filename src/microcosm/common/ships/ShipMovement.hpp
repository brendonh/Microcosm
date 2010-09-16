#pragma once
#ifndef __MICROCOSM_SHIPS_SHIPMOVEMENT
#define __MICROCOSM_SHIPS_SHIPMOVEMENT

#include <stdint.h>

#include <SFML/Window.hpp>

#include "reckoner/common/framework/WorldObject.hpp"
#include "reckoner/common/framework/Listeners.hpp"

namespace Microcosm {
  namespace Ships {

    class Ship;

    enum MOVEMENT_STATES { 
      SHIP_THRUST = 0, 
      SHIP_BRAKE = 1, 
      SHIP_TURN_LEFT = 2, 
      SHIP_TURN_RIGHT = 3
    };

    class ShipMovement : public Reckoner::Framework::TickListener {
    private:
      Ship* mObj;

    public:

      ShipMovement(Ship* obj);

      void tick();

      uint32_t mState;

      bool getState(int s) { return mState & (1 << s); }
      void setState(int s) { mState |= (1 << s); }
      void clearState(int s) { mState &= ~(1 << s); }
      
      void setState(int s, bool v) {
        if (v) setState(s);
        else clearState(s);
      }

    private:

      float mMainThrust;
      float mTurnThrust;
      float mMaxSpeed;

      void thrust();
      void turn(int dir);
      void stopTurn();
      void brake();

    };

  }
}

#endif
