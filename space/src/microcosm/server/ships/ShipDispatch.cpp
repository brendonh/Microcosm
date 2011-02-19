#include "ShipDispatch.hpp"

#include <vector>
#include <set>

#include "reckoner/common/ReckonerTypes.hpp"


using namespace Microcosm::Ships;

ShipDispatch::ShipDispatch(Reckoner::Framework::WorldObject& obj) 
  : Reckoner::Framework::Component(obj, "dispatch"),
    mUpdateBuilder(obj) {
}


// ShipDispatch::ShipDispatch(Reckoner::Region& region, uuid_t uuid, PVR pos) 
//   : Ship(uuid, pos),
//     mRegion(region),
//     mUpdateBuilder(*this) {
// }

void ShipDispatch::tick() {
  // Ship::tick();
  // mRegion.dirtyObject(this);
}

void ShipDispatch::queueUpdate(Reckoner::Server::PacketQueue& queue, bool force) {
  mUpdateBuilder.updatePackedObj();
  const Reckoner::Network::ENetPacketBuffer& buffer = mUpdateBuilder.buffer();

  // XXX TODO: Not all of them
  // And maybe memoize it?

  //Reckoner::Region& region = static_cast<&>(mObj.getComponent("state"));

  // std::vector<ClientID> clients;
  // Reckoner::ObjectMap_t objects = mRegion.objects();
  // for (auto it = objects.begin(); it != objects.end(); ++it) {
  //   std::vector<ClientID> watchers = (*it).second->watchers();
  //   clients.insert(clients.end(), watchers.begin(), watchers.end());
  // }

  // std::set<ClientID> uniqueClients(clients.begin(), clients.end());

  // for (auto sit = uniqueClients.begin(); sit != uniqueClients.end(); ++sit) {
  //   ClientID cid = *sit;
  //   std::cout << "YO" << std::endl;
  //   queue.queue(cid, &buffer);
  // }
}
