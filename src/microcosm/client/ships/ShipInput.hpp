#pragma once

#include "reckoner/common/framework/WorldObject.hpp"
#include "reckoner/common/framework/Component.hpp"

#include <SFML/Window.hpp>

namespace Microcosm {
  namespace Ships {

    class ShipInput : public Reckoner::Framework::Component {
    public:

      ShipInput(Reckoner::Framework::WorldObject& obj);

      virtual void tick();

      void handleInput(const sf::Input& Input);

    };

  }
}
