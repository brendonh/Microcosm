#include <iostream>
#include <string>
#include <signal.h>
#include <functional>

#include "reckoner/server/Server.hpp"

#include "ClientEndpoint.hpp"

using namespace Microcosm::Server;

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


void handleLogin(Reckoner::Network::ENetEndpoint& endpoint, 
                 const google::protobuf::MessageLite& message) {

  const Reckoner::ProtoBufs::Login* login = 
    static_cast<const Reckoner::ProtoBufs::Login*>(&message);

  new ClientEndpoint(endpoint, login->name());
}


int main() {

  signal (SIGINT, startShutdown);

  if (!Reckoner::Server::initialize()) {
    std::cout << "Reckoner init failed" << std::endl;
    return 1;
  }

  using namespace Reckoner::Framework;

  WorldObject ship1(0, PVR(Vector3(0,0,0),
                           Vector3(0,0,0),
                           PI / 2));

  WorldObject ship2(1, PVR(Vector3(-18, 50, 0),
                           Vector3(0,0,0),
                           0.f));

  server.addObject(ship1);
  server.addObject(ship2);

  using namespace Reckoner::Network;

  ENetEndpoint::registerStaticHandler("Reckoner.ProtoBufs.Login", handleLogin);

  MessageMap::dumpMessageMap();

  server.run();

  return 0;
}
