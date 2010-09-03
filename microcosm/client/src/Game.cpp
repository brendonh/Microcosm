#include<stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "common/Microcosm.hpp"
#include "Game.hpp"


using namespace Microcosm;



Game::Game(bool f)
  : fullscreen(f) { 
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
      pb->tick();
      world->Step(timeStep, 10, 10);
      unrenderedTime -= timeStep;
    }

    renderTo(window);
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
  window->SetFramerateLimit(60);

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

  pb = new Ships::Ship();
  pb->Init(world, b2Vec2(0, 0), PI / 2);

  stat = new Ships::Ship();
  stat->Init(world, b2Vec2(-18, 50), 0.f);
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

  target->SaveGLStates();

  char msg[50];
  sprintf(msg, "Speed: ???");
  sprintf(msg, "Speed: %.0f", pb->getSpeed());

  speed->SetString(msg);
  target->Draw(*speed);
  target->RestoreGLStates();

  pb->render();
  stat->render();
  
}

/* Not actually working. */
void Game::screenshot() {
  sf::RenderImage *image = new sf::RenderImage();
  if (!image->Create(window->GetWidth(), window->GetHeight())) {
    printf("Image not available\n");
    return;
  }
  image->SetActive(true);
  renderTo(image);
  image->Display();
  image->GetImage().SaveToFile("screenshot.jpg");
  printf("Done.\n");
}
