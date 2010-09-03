#pragma once
#ifndef __MICROCOSM_FRAMEWORK_LISTENERS
#define __MICROCOSM_FRAMEWORK_LISTENERS

#include "framework/WorldObject.hpp"

namespace Microcosm {
  namespace Framework {

    class WorldObject;

    class TickListener {
    public:      
      virtual void tick() = 0;

    };

  }
}

# endif
