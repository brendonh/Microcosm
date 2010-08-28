#include<stdio.h>

#include "microcosm.hpp"
#include "game.hpp"

using namespace Microcosm;

Game::Game(bool f) : fullscreen(f) { 
  timeStep = 1.0f / 60.0f;
  unrenderedTime = 0;
  init(); 
}

Game::~Game() {}

void Game::init() {
  initSFML();
  initOpenGL();
  initBox2D();
}

void Game::mainloop() {
  while (window->IsOpened()) {

    unrenderedTime += clock->GetElapsedTime();
    clock->Reset();

    handleEvents();

    while(unrenderedTime > timeStep) {
      pb->update();
      world->Step(timeStep, 10, 10);
      unrenderedTime -= timeStep;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    window->SaveGLStates();

    char msg[50];
    sprintf(msg, "Speed: %.2f", pb->body->GetLinearVelocity().Length());

    speed->SetString(msg);
    window->Draw(*speed);
    window->RestoreGLStates();

    pb->render();
    stat->render();

    window->Display();
  }
}

void Game::initSFML() {
  if (fullscreen) {
    sf::VideoMode vm = sf::VideoMode::GetDesktopMode();
    window = new sf::RenderWindow(vm, "Box2D Sandbox", sf::Style::None);
  } else {
    window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Box2D Sandbox");
  }

  window->UseVerticalSync(true);
  window->SetFramerateLimit(100);

  clock = new sf::Clock();

  speed = new sf::Text("Hello World");
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

void Game::initBox2D() {
  b2Vec2 gravity(0.0f, 0.0f);
  world = new b2World(gravity, true);

  pb = new PushBox(world, 0, 0);
  stat = new PushBox(world, -18, 50);
}


void Game::handleEvents() {
  sf::Event Event;
  while (window->GetEvent(Event)) {
    if (Event.Type == sf::Event::Closed)
      window->Close();

    if (Event.Type == sf::Event::KeyPressed || Event.Type == sf::Event::KeyReleased) {
      switch(Event.Key.Code) {
      case sf::Key::Escape:
        window->Close(); 
        break;
      }
    }
  }

  const sf::Input& Input = window->GetInput();

  pb->setState(SHIP_THRUST,     Input.IsKeyDown(sf::Key::Up));
  pb->setState(SHIP_BRAKE,      Input.IsKeyDown(sf::Key::Down));
  pb->setState(SHIP_TURN_LEFT,  Input.IsKeyDown(sf::Key::Left));    
  pb->setState(SHIP_TURN_RIGHT, Input.IsKeyDown(sf::Key::Right));
  
}
