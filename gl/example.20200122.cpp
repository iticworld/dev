/**
 * g++ -std=c++14 -o example.20200122.out example.20200122.cpp -I/usr/local/include -L/usr/local/lib -lglut -lGL -lGLU
 */
#include <GL/glut.h>

void draw(void)
{
  // clear display window
  glClear(GL_COLOR_BUFFER_BIT);
  // set line segment color to green
  glColor3f(0.0f, 0.4f, 0.2f);
  // specify line segment geometry
  glBegin(GL_LINES);
    glVertex2i(180,  15);
    glVertex2i( 10, 145);
  glEnd();
  // process all OpenGL routines as quickly as possible
  glFlush();
}

int main(int argc, char ** argv)
{
  // initialize glut
  glutInit(&argc, argv);
  // set display mode
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  // set top left display window position
  glutInitWindowPosition(50, 100);
  // set display window width and height_
  glutInitWindowSize(400, 300);
  // create display window
  glutCreateWindow("An Example OpenGL Program");
  // set display window color to white
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  // set projection parameters
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0f, 200.0f, 0.0f, 150.0f);
  // send graphics to display window
  glutDisplayFunc(draw);
  // display everything and wait
  glutMainLoop();
  return 0;
}
