#include <GL/gl.h>
#include <GL/glu.h>

#include "Ship.hpp"

using namespace Microcosm::Ships;

Ship::Ship() {}

Ship::~Ship() {
  
}

void Ship::Init(b2World* world, b2Vec2 position, float angle) {
  b2BodyDef *bodyDef = new b2BodyDef();
  bodyDef->type = b2_dynamicBody;
  bodyDef->position.Set(position.x, position.y);
  bodyDef->angle = angle;
      
  bodyDef->linearDamping = 0;
  bodyDef->angularDamping = 0;
      
  mBody = world->CreateBody(bodyDef);
  b2PolygonShape *dynamicBox = new b2PolygonShape();
  dynamicBox->SetAsBox(10.f, 10.f);
      
  b2FixtureDef *fixtureDef = new b2FixtureDef();
  fixtureDef->shape = dynamicBox;
  fixtureDef->density = 1.0f;
      
  mBody->CreateFixture(fixtureDef);

  // XXX TODO: Something more abstract?
  mMovement = new ShipMovement(this);
  mTickListeners.push_back(mMovement);
}


#include <stdio.h>

void Ship::render() {
  b2Vec2 position = mBody->GetPosition();
  float angle = mBody->GetAngle();

  glLoadIdentity();
  glTranslatef(position.x, position.y, 0);
  glRotatef(angle * RAD2DEG, 0, 0, 1);

  glBegin(GL_QUADS);

  if (mEngineOn) glColor3f(1.0, 0.0, 0.0);

  glVertex3f(-10.f, -10.f, 0);
  glVertex3f(-10.f,  10.f, 0);

  glColor3f(1.0, 1.0, 1.0);

  glVertex3f( 10.f,  7.f, 0);
  glVertex3f( 10.f, -7.f, 0);

  glEnd();
}
    
void Ship::handleInput(const sf::Input& Input) {
  mMovement->handleInput(Input);
}


float Ship::getSpeed() {
  return mBody->GetLinearVelocity().Length();
}
