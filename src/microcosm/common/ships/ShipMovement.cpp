#include "reckoner/common/Reckoner.hpp"
#include "./ShipMovement.hpp"
#include "./Ship.hpp"

using namespace Microcosm::Ships;

ShipMovement::ShipMovement(Ship* obj) 
  : mObj(obj), mState(0),
    mMainThrust(0.01f),
    mTurnSpeed(0.05f),
    mMaxSpeed(1.0f) {}

void ShipMovement::tick() {
  mObj->mEngineOn = false;

  if (getState(SHIP_THRUST)) thrust();
  else if (getState(SHIP_BRAKE)) brake();
  
  int dir = getState(SHIP_TURN_LEFT) - getState(SHIP_TURN_RIGHT);
  if (dir) turn(dir);

  PVR& pos = mObj->mPos;
  pos.position += pos.velocity;
}


void ShipMovement::thrust() {
  mObj->mEngineOn = true;

  PVR& pos = mObj->mPos;
  Vector3 forceVec = rad2vec(pos.rotation) * mMainThrust;
  Vector3 vel = pos.velocity;

  Vector3 newVel = vel + forceVec;

  if (lengthSqr(newVel) > lengthSqr(vel)) {
    float b = 1 - lengthSqr(vel) / (mMaxSpeed*mMaxSpeed);
    if (b <= 0) b = 0;

    double lorentz_factor_reciprocal = sqrt(b);
    forceVec *= lorentz_factor_reciprocal;
  }

  vel += forceVec;

  if (lengthSqr(vel) > 0) {
    newVel = normalize(newVel);
    newVel *= length(vel);
    vel = newVel;
  }

  pos.velocity = vel;
}


void ShipMovement::turn(int dir) {
  PVR& pos = mObj->mPos;
  pos.rotation += mTurnSpeed * dir;
}


void ShipMovement::brake() {
  PVR& pos = mObj->mPos;
  
  Vector3 vel = Vector3(pos.velocity);

  if (!length(vel)) return;

  float angle = pos.rotation;
  float wantAngle = vec2rad(-vel);
  float diff = wantAngle - angle;

  if (diff > PI) diff -= TWOPI;
  while (diff < -PI) diff += TWOPI;

  if (fabs(diff) < mTurnSpeed) {
    pos.rotation = wantAngle;
    thrust();

    Vector3& newVel = pos.velocity;

    if (dot(newVel, vel) <= 0) {
      newVel.setX(0);
      newVel.setY(0);
    }

    return;
  }

  turn(diff < 0 ? -1 : 1);
}
