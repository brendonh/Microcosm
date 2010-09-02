#include <stdio.h>

#include <GL/gl.h>

#include "ship.hpp"

using namespace Microcosm;

inline b2Vec2 rad2vec(float r) {
  return b2Vec2(cos(r), sin(r));
}

inline float vec2rad(b2Vec2 v) {
   return atan2(v.y, v.x);
}

Ship::Ship(b2World* world, float x, float y) 
  : world(world),
    mainThrust(200.0f),
    turnThrust(100000.0f),
    maxSpeed(80) { 

  position.x = x;
  position.y = y;
  angle = 90 * DEG2RAD;

  init();
}

void Ship::init() {
  b2BodyDef *bodyDef = new b2BodyDef();
  bodyDef->type = b2_dynamicBody;
  bodyDef->position.Set(position.x, position.y);
  bodyDef->angle = angle;

  bodyDef->linearDamping = 0;
  bodyDef->angularDamping = 0;

  body = world->CreateBody(bodyDef);
  b2PolygonShape *dynamicBox = new b2PolygonShape();
  dynamicBox->SetAsBox(10.f, 10.f);

  b2FixtureDef *fixtureDef = new b2FixtureDef();
  fixtureDef->shape = dynamicBox;
  fixtureDef->density = 1.0f;

  body->CreateFixture(fixtureDef);

  mainThrust /= body->GetMass();
}

void Ship::update() {

  engine = false;

  if (getState(SHIP_THRUST)) thrust();
  else if (getState(SHIP_BRAKE)) brake();

  int dir = getState(SHIP_TURN_LEFT) - getState(SHIP_TURN_RIGHT);
  if (dir) turn(dir);
  else stopTurn();

}

void Ship::thrust() {
  engine = true;
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

void Ship::turn(int dir) {
  float vel = body->GetAngularVelocity();
  float force = turnThrust * (1 - (fabs(vel) / PI));
  body->ApplyTorque(dir * force);
}

void Ship::stopTurn() {
  float vel = body->GetAngularVelocity();
  if (fabs(vel) < 0.05) {
    body->SetAngularVelocity(0);
    return;
  }

  body->SetAngularVelocity(vel * 0.9);
  return;
}

void Ship::brake() {
  b2Vec2 vel = body->GetLinearVelocity();
  if (!vel.Length()) return;

  float angle = body->GetAngle();
  float wantAngle = vec2rad(-vel);
  float diff = wantAngle - angle;

  if (fabs(diff) < 0.01) {
    body->SetAngularVelocity(0);
    body->SetTransform(body->GetPosition(), wantAngle);
    thrust();

    b2Vec2 newVel = body->GetLinearVelocity();
    float component = b2Dot(newVel, vel);
    if (component < 0) body->SetLinearVelocity(b2Vec2(0, 0));
    return;
  }

  float mod = sqrt(fabs(diff)) * (500 / body->GetMass());
  if (diff < 0) mod = -mod;

  body->SetAngularVelocity(mod);
}

void Ship::render() {
  position = body->GetPosition();
  angle = body->GetAngle();

  glLoadIdentity();
  glTranslatef(position.x, position.y, 0);
  glRotatef(angle * RAD2DEG, 0, 0, 1);
  glBegin(GL_QUADS);
  if (engine) glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-10.f, -10.f, 0);
  glVertex3f(-10.f,  10.f, 0);
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f( 10.f,  7.f, 0);
  glVertex3f( 10.f, -7.f, 0);
  glEnd();
}


float Ship::getSpeed() {
  return body->GetLinearVelocity().Length();
}
