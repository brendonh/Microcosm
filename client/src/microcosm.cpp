#include <SFML/Window.hpp>

#include "microcosm.h"

void gl_setup();
void gl_cube(sf::Clock Clock);

int main(int UNUSED(argc), char** UNUSED(argv)) {

  sf::Window App(sf::VideoMode(800, 600, 32), "Microcosm");
  bool running = true;
  sf::Clock Clock;

  gl_setup();

  while (App.IsOpened()) {

    sf::Event Event;
    while (App.GetEvent(Event)) {

      if (Event.Type == sf::Event::Closed) 
        App.Close();

      if ((Event.Type == sf::Event::KeyPressed) && 
          (Event.Key.Code == sf::Key::Escape))
        App.Close();

      if (Event.Type == sf::Event::Resized)
        glViewport(0, 0, Event.Size.Width, Event.Size.Height);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    gl_cube(Clock);

    App.Display();

  }

  return EXIT_SUCCESS;
}


void gl_setup() {
  // Set color and depth clear value
  glClearDepth(1.f);
  glClearColor(0.f, 0.f, 0.f, 0.f);
  
  // Enable Z-buffer read and write
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  
  // Setup a perspective projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.f, 1.f, 1.f, 500.f);
}


void gl_cube(sf::Clock Clock) {

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.f, 0.f, -200.f);
  glRotatef(Clock.GetElapsedTime() * 50, 1.f, 0.f, 0.f);
  glRotatef(Clock.GetElapsedTime() * 30, 0.f, 1.f, 0.f);
  glRotatef(Clock.GetElapsedTime() * 90, 0.f, 0.f, 1.f);

  glBegin(GL_QUADS);

  glVertex3f(-50.f, -50.f, -50.f);
  glVertex3f(-50.f,  50.f, -50.f);
  glVertex3f( 50.f,  50.f, -50.f);
  glVertex3f( 50.f, -50.f, -50.f);

  glVertex3f(-50.f, -50.f, 50.f);
  glVertex3f(-50.f,  50.f, 50.f);
  glVertex3f( 50.f,  50.f, 50.f);
  glVertex3f( 50.f, -50.f, 50.f);

  glVertex3f(-50.f, -50.f, -50.f);
  glVertex3f(-50.f,  50.f, -50.f);
  glVertex3f(-50.f,  50.f,  50.f);
  glVertex3f(-50.f, -50.f,  50.f);

  glVertex3f(50.f, -50.f, -50.f);
  glVertex3f(50.f,  50.f, -50.f);
  glVertex3f(50.f,  50.f,  50.f);
  glVertex3f(50.f, -50.f,  50.f);

  glVertex3f(-50.f, -50.f,  50.f);
  glVertex3f(-50.f, -50.f, -50.f);
  glVertex3f( 50.f, -50.f, -50.f);
  glVertex3f( 50.f, -50.f,  50.f);

  glVertex3f(-50.f, 50.f,  50.f);
  glVertex3f(-50.f, 50.f, -50.f);
  glVertex3f( 50.f, 50.f, -50.f);
  glVertex3f( 50.f, 50.f,  50.f);

  glEnd();
}
