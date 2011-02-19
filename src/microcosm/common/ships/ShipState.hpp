#pragma once

#include <stdint.h>

#include "reckoner/common/framework/WorldObject.hpp"
#include "reckoner/common/framework/Component.hpp"

namespace Microcosm {
  namespace Ships {

    class ShipState : public Reckoner::Framework::Component {
    public:

      enum STATES { 
        THRUST = 0, 
        BRAKE = 1, 
        TURN_LEFT = 2, 
        TURN_RIGHT = 3,

        ENGINE_ON = 4
      };

      ShipState(Reckoner::Framework::WorldObject& obj);

      virtual void tick();

      bool getState(int s) { return mState & (1 << s); }
      void setState(int s) { mState |= (1 << s); }
      void clearState(int s) { mState &= ~(1 << s); }
      
      void setState(int s, bool v) {
        if (v) setState(s);
        else clearState(s);
      }

      float getSpeed() {
        return length(mObj.mPos.velocity) * 10;
      }

    private:

      uint32_t mState;

    };

  }
}

