#include <GL/gl.h>
#include <GL/glu.h>

#include "reckoner/common/Reckoner.hpp"
#include "./ClientShip.hpp"

using namespace Microcosm::Ships;

ClientShip::ClientShip(Ship& ship) 
  : mShip(ship) {
}

ClientShip::~ClientShip() {
}


float ClientShip::getSpeed() {
  return length(mShip.mPos.velocity) * 10;
}

void ClientShip::render() {
  Vector3 position = mShip.mPos.position;
  float angle = mShip.mPos.rotation;

  glLoadIdentity();
  glTranslatef(position.getX(), position.getY(), 0);
  glRotatef(angle * RAD2DEG, 0, 0, 1);

  glBegin(GL_QUADS);

  if (mShip.mEngineOn) glColor3f(1.0, 0.0, 0.0);

  glVertex3f(-10.f, -10.f, 0);
  glVertex3f(-10.f,  10.f, 0);

  glColor3f(1.0, 1.0, 1.0);

  glVertex3f( 10.f,  7.f, 0);
  glVertex3f( 10.f, -7.f, 0);

  glEnd();
}
    
void ClientShip::handleInput(const sf::Input& Input) {
  ShipMovement* movement = mShip.mMovement;
  movement->setState(SHIP_THRUST,     Input.IsKeyDown(sf::Key::Up));
  movement->setState(SHIP_BRAKE,      Input.IsKeyDown(sf::Key::Down));
  movement->setState(SHIP_TURN_LEFT,  Input.IsKeyDown(sf::Key::Left));    
  movement->setState(SHIP_TURN_RIGHT, Input.IsKeyDown(sf::Key::Right));
}
