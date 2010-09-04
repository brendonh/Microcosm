#pragma once
#ifndef __MICROCOSM_FRAMEWORK_WORLDOBJECT
#define __MICROCOSM_FRAMEWORK_WORLDOBJECT

#include <vector>

#include <SFML/Window.hpp>

#include "Listeners.hpp"

namespace Microcosm {
  namespace Framework {

    typedef std::vector<TickListener*> ListenerList;

    class WorldObject {
    public:
      
      WorldObject() {};

      void tick() {
        ListenerList::const_iterator i;
        for (i = mTickListeners.begin(); i != mTickListeners.end(); ++i) {
          (*i)->tick();
        }
      }

      ~WorldObject() {
        TickListener* tl;
        while(!mTickListeners.empty()) {
          tl = mTickListeners.back();
          mTickListeners.pop_back();
          delete tl;
        }
      };


    protected:

      ListenerList mTickListeners;

    };

  }
}

#endif
