#include "./Ship.hpp"

using namespace Microcosm::Ships;

Ship::Ship(b2World* world, b2Vec2 position, float angle)
  : Reckoner::Framework::WorldObject(),
    mMovement(NULL), 
    mEngineOn(false) {

  b2BodyDef *bodyDef = new b2BodyDef();
  bodyDef->type = b2_dynamicBody;
  bodyDef->position.Set(position.x, position.y);
  bodyDef->angle = angle;
      
  bodyDef->linearDamping = 0;
  bodyDef->angularDamping = 0;
      
  b2Body* body = world->CreateBody(bodyDef);
  b2PolygonShape *dynamicBox = new b2PolygonShape();
  dynamicBox->SetAsBox(10.f, 10.f);

  b2FixtureDef *fixtureDef = new b2FixtureDef();
  fixtureDef->shape = dynamicBox;
  fixtureDef->density = 1.0f;
      
  body->CreateFixture(fixtureDef);

  setBody(body);

  // XXX TODO: Something more abstract?
  mMovement = new ShipMovement(this);
  mTickListeners.push_back(mMovement);
}

Ship::~Ship() {
  mBody->GetWorld()->DestroyBody(mBody);
  delete mMovement;
}
