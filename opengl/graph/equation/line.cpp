#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <iostream>
#include <map>

const double step = 0.2f;
std::map<double, double> results;

int f(int x)
{
  return x * 2 - 1;
}

void calculate()
{
  for(int i = -20; i < 20; i++)
  {
    double x = i * step;
    double y = f(i) * step;

    if(-0.9f <= x && x <= 0.9f)
    {
      if(-0.9f <= y && y <= 0.9f)
      {
        results.insert(std::map<double, double>::value_type((double) x, y));
      }
    }
  }
}

void display()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  //
  glLineWidth(1.0);
  //
  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_LINES);
    // X AXIS
    glVertex2f( 0.0f, -0.9f);
    glVertex2f( 0.0f,  0.9f);
    // Y AXIS
    glVertex2f(-0.9f,  0.0f);
    glVertex2f( 0.9f,  0.0f);
  glEnd();
  glBegin (GL_TRIANGLES);
    // X ARROW
    glVertex2f(0.9f ,  0.0f);
    glVertex2f(0.88f,  0.02f);
    glVertex2f(0.88f, -0.02f);
    // Y ARROW
    glVertex2f( 0.0f,  0.9f);
    glVertex2f( 0.02f, 0.88f);
    glVertex2f(-0.02f, 0.88f);
  glEnd();

  glRasterPos2f(0.86f, -0.07f);
  glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *) "x");

  glRasterPos2f(-0.055f, 0.86f);
  glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *) "y");

  glColor3f(1.0f, 0.0f, 0.0f);
  glBegin (GL_LINE_LOOP);
  for(std::map<double, double>::iterator it = results.begin(); it != results.end(); ++it)
  {
    glVertex2f(it->first, it->second);
  }
  glEnd();

  glPopMatrix();

  glFlush();
}

int main(int argc, char** argv)
{
  calculate();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 800);
  glutCreateWindow("graph");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  glutMainLoop();

  return 0;
}
