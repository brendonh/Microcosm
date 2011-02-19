#include "microcosm/common/ships/ShipState.hpp"

#include "ShipInput.hpp"

using namespace Microcosm::Ships;

ShipInput::ShipInput(Reckoner::Framework::WorldObject& obj)
  : Reckoner::Framework::Component(obj, "input")
{}


void ShipInput::tick() {}

void ShipInput::handleInput(const sf::Input& Input) {
  ShipState& state = static_cast<ShipState&>(mObj.getComponent("state"));
  
  state.setState(ShipState::THRUST,     Input.IsKeyDown(sf::Key::Up));
  state.setState(ShipState::BRAKE,      Input.IsKeyDown(sf::Key::Down));
  state.setState(ShipState::TURN_LEFT,  Input.IsKeyDown(sf::Key::Left));    
  state.setState(ShipState::TURN_RIGHT, Input.IsKeyDown(sf::Key::Right));
}
