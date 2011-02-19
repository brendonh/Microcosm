#include<stdio.h>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>

#include "reckoner/common/Reckoner.hpp"
#include "reckoner/common/framework/Math2D.hpp"

#include "microcosm/common/ships/ShipState.hpp"
#include "microcosm/common/ships/ShipMovement.hpp"


#include "ships/ShipInput.hpp"
#include "ships/ShipRenderer.hpp"
#include "Game.hpp"

using namespace Microcosm;


Game::Game(bool full)
  : fullscreen(full),
    window(NULL), 
    clock(NULL),
    speed(NULL),
    pb(NULL), 
    stat(NULL) { 

  // XXX TODO: Use own clock here instead
  timeStep = TIMESTEP / 1000.f;
  unrenderedTime = 0;
  init();
}

Game::~Game() {
  delete pb;
  delete stat;
}

void Game::init() {
  initSFML();
  initOpenGL();
  initWorld();
}

bool Game::tick() {
  if (!window->IsOpened()) return false;

  unrenderedTime += clock->GetElapsedTime();
  clock->Reset();

  handleEvents();

  while(unrenderedTime > timeStep) {
    pb->tick();
    stat->tick();
    unrenderedTime -= timeStep;
  }

  renderTo(window);
  window->Display();

  return true;
}

void Game::initSFML() {
  if (fullscreen) {
    sf::VideoMode vm = sf::VideoMode::GetDesktopMode();
    window = new sf::RenderWindow(vm, "Microcosm", sf::Style::None);
  } else {
    window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Microcosm");
  }

  window->UseVerticalSync(true);
  window->PreserveOpenGLStates(true);

  clock = new sf::Clock();

  speed = new sf::String();
  speed->SetFont(sf::Font::GetDefaultFont());
  speed->SetColor(sf::Color(0,255,0)); 
}


void Game::initOpenGL() {
  glClearDepth(1.f);
  glClearColor(0.f, 0.f, 0.f, 0.f);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.f, ((float)window->GetWidth() / window->GetHeight()), 1.f, 500.f);
  glTranslatef(0, 0, -150.f);

  glMatrixMode(GL_MODELVIEW);
}

void Game::initWorld() {

  using namespace Reckoner::Framework;
  using namespace Microcosm::Ships;

  pb = new WorldObject(0, PVR(Vector3(0,0,0), 
                              Vector3(0,0,0),
                              PI / 2));

  ShipInput* input = new ShipInput(*pb);
  pb->addComponent(*input);

  ShipState* state = new ShipState(*pb);
  pb->addComponent(*state);

  ShipRenderer* renderer = new ShipRenderer(*pb);
  pb->addComponent(*renderer);

  ShipMovement* movement = new ShipMovement(*pb);
  pb->addComponent(*movement);

  stat = new WorldObject(1, PVR(Vector3(-18, 50, 0),
                                Vector3(0.2f,0,0),
                                0.f));

  state = new ShipState(*stat);
  stat->addComponent(*state);

  renderer = new ShipRenderer(*stat);
  stat->addComponent(*renderer);

  movement = new ShipMovement(*stat);
  stat->addComponent(*movement);


}


void Game::handleEvents() {
  sf::Event Event;
  while (window->GetEvent(Event)) {
    if (Event.Type == sf::Event::Closed)
      window->Close();

    if (Event.Type == sf::Event::KeyPressed) {
      switch(Event.Key.Code) {
      case sf::Key::Escape:
        window->Close(); 
        break;

      case sf::Key::F1:
        screenshot();
        break;

      default: break;
      }
    }
  }

  const sf::Input& Input = window->GetInput();

  using Microcosm::Ships::ShipInput;
  ShipInput& si = static_cast<ShipInput&>(pb->getComponent("input"));
  si.handleInput(Input);
  
}

void Game::renderTo(sf::RenderTarget *target) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  char msg[50];

  using Microcosm::Ships::ShipState;
  ShipState& state = static_cast<ShipState&>(pb->getComponent("state"));
  sprintf(msg, "Speed: %.0f", state.getSpeed());

  if (speed) {
    speed->SetText(msg);
    target->Draw(*speed);
  }

  using Microcosm::Ships::ShipRenderer;
  static_cast<ShipRenderer&>(pb->getComponent("renderer")).render();
  static_cast<ShipRenderer&>(stat->getComponent("renderer")).render();
}


void Game::screenshot() {
  sf::Image Screen = window->Capture();
  Screen.SaveToFile("screenshot.jpg");
}
