#include <stdio.h>
#include <iostream>
#include <sstream>

#include "Game.hpp"

int main(int argc, char** argv) {

  bool fullscreen = false;

  for (int i = 0; i < argc; i++) {
    if (std::string(argv[i]) == "--fullscreen") {
      fullscreen = true;
      break;
    }
  }

  Microcosm::Game *game = new Microcosm::Game(fullscreen);
  game->mainloop();
  return EXIT_SUCCESS;
}
