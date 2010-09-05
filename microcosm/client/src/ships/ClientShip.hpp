#pragma once
#ifndef __MICROCOSM_SHIPS_CLIENTSHIP
#define __MICROCOSM_SHIPS_CLIENTSHIP

#include "reckoner/common/ships/Ship.hpp"


namespace Microcosm {
  namespace Ships {

    class ClientShip {
    public:

      ClientShip();
      ~ClientShip();

      void Init(b2World* world, b2Vec2 position, float angle);

      void tick() { mShip->tick(); }

      void render();
      void handleInput(const sf::Input& Input);

      float getSpeed();

    private:

      Ship* mShip;

    };


  }
}


#endif
