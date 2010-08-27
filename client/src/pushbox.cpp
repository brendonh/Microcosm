#include <GL/gl.h>

#include "pushbox.hpp"

using namespace Microcosm;

inline b2Vec2 rad2vec(float r) {
  return b2Vec2(cos(r), sin(r));
}

PushBox::PushBox(b2World* world, float x, float y) 
  : world(world),
    mainThrust(200.0f),
    turnThrust(40000.0f) { 

  position.x = x;
  position.y = y;
  angle = 90 * DEG2RAD;

  b2BodyDef *bodyDef = new b2BodyDef();
  bodyDef->type = b2_dynamicBody;
  bodyDef->position.Set(x, y);
  bodyDef->angle = angle;
  bodyDef->linearDamping = 0;

  body = world->CreateBody(bodyDef);
  b2PolygonShape *dynamicBox = new b2PolygonShape();
  dynamicBox->SetAsBox(10.f, 10.f);

  b2FixtureDef *fixtureDef = new b2FixtureDef();
  fixtureDef->shape = dynamicBox;
  fixtureDef->density = 1.0f;

  body->CreateFixture(fixtureDef);

  mainThrust /= body->GetMass();
  maxSpeed = 50;

  brake(false);
}

void PushBox::update() {
  position = body->GetPosition();
  angle = body->GetAngle();
}

void PushBox::thrust() {
  b2Vec2 force = rad2vec(angle);
  force *= mainThrust;
  b2Vec2 vel = body->GetLinearVelocity();
  b2Vec2 newVel = vel + force;
    
  if (newVel.Length() > vel.Length()) {
    float b = 1 - vel.LengthSquared() / (maxSpeed*maxSpeed);
    if (b <= 0) b = 0;

    double lorentz_factor_reciprocal = sqrt(b);
    force *= lorentz_factor_reciprocal;
  }

  vel += force;

  if (vel.Length() > 0) {
    newVel.Normalize();
    newVel *= vel.Length();
    vel = newVel;
  }

  body->SetLinearVelocity(vel);
}

void PushBox::turn(int sign) {
  float vel = body->GetAngularVelocity();
  float force = 100000.0f * (1 - (fabs(vel) / 6.0f));
  body->ApplyTorque(sign * force);
}

void PushBox::stopTurn() {
  float vel = body->GetAngularVelocity();
  if (fabs(vel) < 0.1) {
    body->SetAngularVelocity(0);
    return;
  }
  float prop = (fabs(vel) / 6.0f);
  float force = 500000.0f * prop;
  if (force < 1000.f) force = 1000.f;
  if (vel > 0) force = -force;
  body->ApplyTorque(force);
}

void PushBox::brake(int on) {
  if (on) body->SetLinearDamping(0.3f);
  else body->SetLinearDamping(0);
}

void PushBox::render() {
  glLoadIdentity();
  glTranslatef(position.x, position.y, 0);
  glRotatef(angle * RAD2DEG, 0, 0, 1);
  glBegin(GL_QUADS);
  glVertex3f(-10.f, -10.f, 0);
  glVertex3f(-10.f,  10.f, 0);
  glVertex3f( 10.f,  10.f, 0);
  glVertex3f( 10.f, -10.f, 0);
  glEnd();
}
