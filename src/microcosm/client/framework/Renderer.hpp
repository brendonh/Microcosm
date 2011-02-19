#pragma once

#include "reckoner/common/framework/WorldObject.hpp"
#include "reckoner/common/framework/Component.hpp"

namespace Microcosm {
  namespace Client {

    class Renderer : public Reckoner::Framework::Component {
    public:

      Renderer(Reckoner::Framework::WorldObject& obj) 
        : Reckoner::Framework::Component(obj, "renderer")
      {}

      virtual void tick() {}
      virtual void render() = 0;

    };

  }
}
