#pragma once
#ifndef __MICROCOSM_SHIPS_SHIPDISPATCH
#define __MICROCOSM_SHIPS_SHIPDISPATCH


#include "reckoner/common/framework/WorldObject.hpp"
#include "reckoner/common/framework/Component.hpp"

#include "reckoner/common/ENetEndpoint.hpp"
#include "reckoner/common/Region.hpp"
#include "reckoner/server/PacketQueue.hpp"
#include "reckoner/server/UpdateBuilder.hpp"


namespace Microcosm {
  namespace Ships {

    class ShipDispatch : public Reckoner::Framework::Component {
    public:

      ShipDispatch(Reckoner::Framework::WorldObject& obj);

      //ShipDispatch(Reckoner::Region& region, uuid_t uuid, PVR pvr);

      virtual void tick();

      virtual void queueUpdate(Reckoner::Server::PacketQueue& queue,
                               bool force);

    private:
      //Reckoner::Region& mRegion;

      Reckoner::Server::UpdateBuilder mUpdateBuilder;

    };

  }
}

#endif
