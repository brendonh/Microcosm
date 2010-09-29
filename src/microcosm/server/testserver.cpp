#include <iostream>
#include <string>
#include <signal.h>
#include <functional>

#include "reckoner/common/ENetEndpoint.hpp"
#include "reckoner/server/Server.hpp"

#include "microcosm/common/ships/Ship.hpp"


Reckoner::Server::Server server;

void forceShutdown(int UNUSED(param)) {
  std::cout << "\rForcing shutdown" << std::endl;
  exit(1);
}

void startShutdown(int UNUSED(param)) {
  std::cout << "\rShutting down..." << std::endl;
  server._shutdown = true;
  signal(SIGINT, forceShutdown);
}


class TestClient {
public:
  
  Reckoner::Network::ENetEndpoint& mClient;
  std::string mName;
  std::string mIdentifier;

  TestClient(Reckoner::Network::ENetEndpoint& client,
             std::string name) : 
    mClient(client),
    mName(name),
    mIdentifier(client.getIdentifier() + " [" + name + "]") {
    LOG("Logged in");

#define ATTACH(MSG, METHOD) \
    client.registerHandler(MSG, \
      std::bind(&TestClient::METHOD, *this,  \
                std::placeholders::_1, \
                std::placeholders::_2))

    ATTACH("Reckoner.ProtoBufs.Login", repeatedLogin);

#undef attach

    Reckoner::ProtoBufs::LoggedIn msg;
    client.send(&msg, ENET_PACKET_FLAG_RELIABLE);
  }

  void repeatedLogin(Reckoner::Network::ENetEndpoint& UNUSED(endpoint), 
                     const google::protobuf::MessageLite& UNUSED(message)) {
    LOG("HAHA NICE TRY");
  }

};


void handleLogin(Reckoner::Network::ENetEndpoint& endpoint, 
                 const google::protobuf::MessageLite& message) {

  const Reckoner::ProtoBufs::Login* login = 
    static_cast<const Reckoner::ProtoBufs::Login*>(&message);

  TestClient* tc = new TestClient(endpoint, login->name());
}


int main() {
  signal (SIGINT, startShutdown);

  if (!Reckoner::Server::initialize()) {
    std::cout << "Reckoner init failed" << std::endl;
    return 1;
  }

  using namespace Microcosm::Ships;

  Ship* ship1 = new Ship(0, server.mRegion.mWorld, b2Vec2(0.f, 0.f), PI / 2);
  Ship* ship2 = new Ship(1, server.mRegion.mWorld, b2Vec2(-18, 50), 0.f);

  Reckoner::Network::ENetEndpoint::dumpMessageMap();

  Reckoner::Network::ENetEndpoint::registerStaticHandler("Reckoner.ProtoBufs.Login", handleLogin);

  //TestClient tc("Testy");
  // Reckoner::Network::ENetEndpoint::registerHandler("Reckoner.ProtoBufs.Login", 
  //                                                  std::bind(&TestClient::memHandleLogin, tc, 
  //                                                            std::placeholders::_1));

  server.run();

  return 0;
}
