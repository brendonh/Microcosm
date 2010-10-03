#include "./Ship.hpp"

using namespace Microcosm::Ships;

Ship::Ship(uuid_t uuid, PVR pos)
  : Reckoner::Framework::WorldObject(uuid, pos),
    mMovement(NULL), 
    mEngineOn(false) {

  // XXX TODO: Something more abstract?
  mMovement = new ShipMovement(this);
  mTickListeners.push_back(mMovement);
}

Ship::~Ship() {
  delete mMovement;
}
