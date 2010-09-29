#include <GL/gl.h>
#include <GL/glu.h>

#include "./ClientShip.hpp"
#include "../Microcosm.hpp"

using namespace Microcosm::Ships;

ClientShip::ClientShip(Ship& ship) 
  : mShip(ship) {
}

ClientShip::~ClientShip() {
}


float ClientShip::getSpeed() {
  return mShip.getBody().GetLinearVelocity().Length();
}

void ClientShip::render() {
  b2Vec2 position = mShip.getBody().GetPosition();
  float angle = mShip.getBody().GetAngle();

  glLoadIdentity();
  glTranslatef(position.x, position.y, 0);
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
