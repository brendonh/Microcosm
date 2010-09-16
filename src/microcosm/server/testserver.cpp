#include <iostream>
#include <string>

#include "reckoner/server/Server.hpp"

int main() {
  std::cout << "Hi" << std::endl;

  Reckoner::Server::run();

  return 0;
}
