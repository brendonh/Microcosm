#pragma once

#include "reckoner/common/framework/WorldObject.hpp"
#include "microcosm/client/framework/Renderer.hpp"

namespace Microcosm {
  namespace Ships {

    class ShipRenderer : public Microcosm::Client::Renderer {
    public:

      ShipRenderer(Reckoner::Framework::WorldObject& obj)
        : Microcosm::Client::Renderer(obj) {}

      virtual void render();

    };

  }
}
