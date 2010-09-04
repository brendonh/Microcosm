#include "Ship.hpp"

using namespace Microcosm::Ships;

Ship::Ship() : mBody(NULL), mMovement(NULL), mEngineOn(false) {}

Ship::~Ship() {
  cleanup();
}

void Ship::cleanup() {
  if (mBody) {
    mBody->GetWorld()->DestroyBody(mBody);
    mBody = NULL;
  }
  if (mMovement) {
    delete mMovement;
    mMovement = NULL;
  }
}

void Ship::Init(b2World* world, b2Vec2 position, float angle) {
  cleanup();

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

