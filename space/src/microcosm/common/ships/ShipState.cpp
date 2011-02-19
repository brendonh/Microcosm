#include "ShipState.hpp"

using namespace Microcosm::Ships;

ShipState::ShipState(Reckoner::Framework::WorldObject& obj) 
  : Reckoner::Framework::Component(obj, "state"),
    mState(0) {}


void ShipState::tick() {}
