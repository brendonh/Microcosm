#include<stdio.h>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>

#include "reckoner/common/Reckoner.hpp"
#include "reckoner/common/framework/Math2D.hpp"

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

Game::~Game() {}

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

  Ships::Ship* ship1 = new Ships::Ship(0, PVR(Vector3(0,0,0), 
                                              Vector3(0,0,0),
                                              PI / 2));
  pb = new Ships::ClientShip(*ship1);

  Ships::Ship* ship2 = new Ships::Ship(1, PVR(Vector3(-18, 50, 0),
                                              Vector3(0.2f,0,0),
                                              0.f));
  stat = new Ships::ClientShip(*ship2);
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
  pb->handleInput(Input);
  
}

void Game::renderTo(sf::RenderTarget *target) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  char msg[50];
  sprintf(msg, "Speed: %.0f", pb->getSpeed());

  if (speed) {
    speed->SetText(msg);
    target->Draw(*speed);
  }

  pb->render();
  stat->render();
}


void Game::screenshot() {
  sf::Image Screen = window->Capture();
  Screen.SaveToFile("screenshot.jpg");
}
