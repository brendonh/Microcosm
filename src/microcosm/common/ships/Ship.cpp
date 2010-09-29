#include "./Ship.hpp"

using namespace Microcosm::Ships;

Ship::Ship(uuid_t uuid, b2World& world, b2Vec2 position, float angle)
  : Reckoner::Framework::WorldObject(uuid, createBody(world, position, angle)),
    mMovement(NULL), 
    mEngineOn(false) {

  mBody.SetUserData(this);

  // XXX TODO: Something more abstract?
  mMovement = new ShipMovement(this);
  mTickListeners.push_back(mMovement);
}

Ship::~Ship() {
  delete mMovement;
}


b2Body& Ship::createBody(b2World& world, 
                         b2Vec2 position, 
                         float angle) {

  b2BodyDef *bodyDef = new b2BodyDef();
  bodyDef->type = b2_dynamicBody;
  bodyDef->position.Set(position.x, position.y);
  bodyDef->angle = angle;
      
  bodyDef->linearDamping = 0;
  bodyDef->angularDamping = 0;
      
  b2Body* body = world.CreateBody(bodyDef);

  b2PolygonShape *dynamicBox = new b2PolygonShape();
  dynamicBox->SetAsBox(10.f, 10.f);
  b2FixtureDef *fixtureDef = new b2FixtureDef();
  fixtureDef->shape = dynamicBox;
  fixtureDef->density = 1.0f;
  body->CreateFixture(fixtureDef);

  return *body;
}
