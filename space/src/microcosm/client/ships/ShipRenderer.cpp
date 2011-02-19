#include <GL/gl.h>
#include <GL/glu.h>

#include "reckoner/common/Reckoner.hpp"
#include "reckoner/common/framework/Math2D.hpp"

#include "microcosm/common/ships/ShipState.hpp"

#include "ShipRenderer.hpp"

using namespace Microcosm::Ships;

void ShipRenderer::render() {
  Reckoner::Framework::PVR pos = mObj.mPos;

  using Microcosm::Ships::ShipState;
  ShipState& state = static_cast<ShipState&>(mObj.getComponent("state"));

  Reckoner::Framework::Vector3 position = pos.position;
  float angle = pos.rotation;

  glLoadIdentity();
  glTranslatef(position.getX(), position.getY(), 0);
  glRotatef(angle * RAD2DEG, 0, 0, 1);

  glBegin(GL_QUADS);

  if (state.getState(ShipState::ENGINE_ON)) glColor3f(1.0, 0.0, 0.0);

  glVertex3f(-10.f, -10.f, 0);
  glVertex3f(-10.f,  10.f, 0);

  glColor3f(1.0, 1.0, 1.0);

  glVertex3f( 10.f,  7.f, 0);
  glVertex3f( 10.f, -7.f, 0);

  glEnd();

}
