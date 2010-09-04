#include <Box2D/Box2D.h>

#include "common/B2Util.hpp"
#include "ships/ShipMovement.hpp"
#include "ships/Ship.hpp"
#include "Game.hpp"

using namespace Microcosm::Ships;

ShipMovement::ShipMovement(Ship* obj) 
  : mObj(obj), mState(0),
    mMainThrust(200.0f),
    mTurnThrust(100000.0f),
    mMaxSpeed(80) {}

void ShipMovement::tick() {
  mObj->mEngineOn = false;

  if (getState(SHIP_THRUST)) thrust();
  else if (getState(SHIP_BRAKE)) brake();
  
  int dir = getState(SHIP_TURN_LEFT) - getState(SHIP_TURN_RIGHT);
  if (dir) turn(dir);
  else stopTurn();
}


void ShipMovement::thrust() {
  mObj->mEngineOn = true;
  b2Body* body = mObj->mBody;

  b2Vec2 force = rad2vec(body->GetAngle());
  force *= mMainThrust / body->GetMass();
  b2Vec2 vel = body->GetLinearVelocity();

  b2Vec2 newVel = vel + force;

  if (newVel.Length() > vel.Length()) {
    float b = 1 - vel.LengthSquared() / (mMaxSpeed*mMaxSpeed);
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

void ShipMovement::turn(int dir) {
  b2Body* body = mObj->mBody;
  float vel = body->GetAngularVelocity();
  float force = mTurnThrust * (1 - (fabs(vel) / PI));
  body->ApplyTorque(dir * force);
}

void ShipMovement::stopTurn() {
  b2Body* body = mObj->mBody;
  float vel = body->GetAngularVelocity();
  if (fabs(vel) < 0.05) {
    body->SetAngularVelocity(0);
    return;
  }

  body->SetAngularVelocity(vel * 0.9);
  return;
}


void ShipMovement::brake() {
  b2Body* body = mObj->mBody;
  b2Vec2 vel = body->GetLinearVelocity();
  if (!vel.Length()) return;

  float angle = body->GetAngle();
  float wantAngle = vec2rad(-vel);
  float diff = wantAngle - angle;

  if (diff > PI) diff -= TWOPI;
  while (diff < -PI) diff += TWOPI;

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
