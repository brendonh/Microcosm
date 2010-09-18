#include <iostream>
#include <string>
#include <signal.h>
#include <functional>

#include "reckoner/server/Server.hpp"

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

void handleLogin(const google::protobuf::MessageLite& message) {
  const Reckoner::ProtoBufs::Login* login = static_cast<const Reckoner::ProtoBufs::Login*>(&message);
  std::cout << "Yo yo whattup: " << login->name() << std::endl;
}


class TestClient {
public:
  
  std::string mName;

  TestClient(std::string name) : mName(name) {}

  void memHandleLogin(const google::protobuf::MessageLite& message) {
    const Reckoner::ProtoBufs::Login* login = static_cast<const Reckoner::ProtoBufs::Login*>(&message);
    std::cout << mName << ": " << login->name() << std::endl;
  }

  void foo() {

  }

};

int main() {
  signal (SIGINT, startShutdown);

  if (!Reckoner::Server::initialize()) {
    std::cout << "Reckoner init failed" << std::endl;
    return 1;
  }

  Reckoner::Network::ENetEndpoint::dumpMessageMap();

  Reckoner::Network::ENetEndpoint::registerHandler("Reckoner.ProtoBufs.Login", handleLogin);

  //TestClient tc("Testy");
  // Reckoner::Network::ENetEndpoint::registerHandler("Reckoner.ProtoBufs.Login", 
  //                                                  std::bind(&TestClient::memHandleLogin, tc, 
  //                                                            std::placeholders::_1));

  server.run();

  return 0;
}
