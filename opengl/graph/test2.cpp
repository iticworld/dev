#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <iostream>
#include <map>

const double step = 0.2f;
std::map<double, double> results;

const double ratio = 1.0f / 4.0f;

double f(double x)
{
  return (x / ratio) * (x / ratio);
}

void calculate()
{
  for(double i = -1.0f; i < 1.0f; i += 0.01f)
  {

    results.insert(std::map<double, double>::value_type(i, f(i)));

  }
}

void display()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // glColor3f(0.0f, 0.0f, 0.0f);
  // glBegin(GL_LINES);
  //   // X AXIS
  //   glVertex2f( 0.0f, -0.9f);
  //   glVertex2f( 0.0f,  0.9f);
  //   // Y AXIS
  //   glVertex2f(-0.9f,  0.0f);
  //   glVertex2f( 0.9f,  0.0f);
  // glEnd();
  // glBegin (GL_TRIANGLES);
  //   // X ARROW
  //   glVertex2f(0.9f ,  0.0f);
  //   glVertex2f(0.88f,  0.02f);
  //   glVertex2f(0.88f, -0.02f);
  //   // Y ARROW
  //   glVertex2f( 0.0f,  0.9f);
  //   glVertex2f( 0.02f, 0.88f);
  //   glVertex2f(-0.02f, 0.88f);
  // glEnd();
  //
  // glRasterPos2f(0.86f, -0.07f);
  // glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *) "x");
  //
  // glRasterPos2f(-0.055f, 0.86f);
  // glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *) "y");

  glEnable(GL_LINE_SMOOTH);
  glPushMatrix();
    glLineWidth(1.0);

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);
    for(std::map<double, double>::iterator it = results.begin(); it != results.end(); ++it)
    {
      glVertex3f(it->first, it->second, 0.0f);
    }
    glEnd();

  glPopMatrix();

  glutSwapBuffers();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(10.0f, (GLfloat) w/(GLfloat) h, 1.0f, 100.0f);

  glMatrixMode(GL_MODELVIEW); //GL_PROJECTION
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
