#include <iostream>
#include <string>
#include <signal.h>

#include "reckoner/client/Connection.hpp"

#include "Game.hpp"

bool running = true;
bool _shutdown = false;

void forceShutdown(int UNUSED(param)) {
  std::cout << "\rForcing shutdown..." << std::endl;
  running = false;
}

void startShutdown(int UNUSED(param)) {
  _shutdown = true;
  signal(SIGINT, forceShutdown);
  std::cout << "\r" << std::flush;
}


bool fullscreen = false;
Reckoner::Client::Connection* conn = NULL;
Microcosm::Game* game = NULL;


void handleLoggedIn(Reckoner::Network::ENetEndpoint& UNUSED(endpoint), 
                    const google::protobuf::MessageLite& UNUSED(message)) {
  game = new Microcosm::Game(fullscreen);
}


int main(int argc, char** argv) {

  signal(SIGINT, startShutdown);

  for (int i = 0; i < argc; i++) {
    if (std::string(argv[i]) == "--fullscreen") {
      fullscreen = true;
      break;
    }
  }

  if (enet_initialize () != 0) {
    fprintf (stderr, "An error occurred while initializing ENet.\n");
    return EXIT_FAILURE;
  }

  using namespace Reckoner::Client;
  conn = Connection::connect("localhost", 8101);

  if (NULL == conn) {
    std::cout << "Abandoning!" << std::endl;
    return EXIT_FAILURE;
  }

  Reckoner::Network::ENetEndpoint::registerStaticHandler("Reckoner.ProtoBufs.LoggedIn", 
                                                         handleLoggedIn);

  while (running) {
    if (_shutdown) {
      conn->startDisconnect();
      // Just start disconnecting once.
      _shutdown = false;
    }

    // XXX TODO: Close the window cleanly here.
    if (conn->isDisconnected()) break;

    conn->service(0);

    if (NULL == game) continue;

    if (!game->tick()) break;
  }

  if (!conn->isDisconnected()) {
    conn->startDisconnect();
    conn->service(500);
  }

  delete game;

  atexit(enet_deinitialize);

  return EXIT_SUCCESS;
}
