#include <GL/glut.h>

#include <iostream>
#include <map>
#include <cmath>

const double step = 0.01f;
const double ratio = 1.0f /2.0f;
std::map<double, double> results[3];

double f(double x)
{
  return sqrt((x / ratio) + (2.0f / ratio));
}

double f2(double x)
{
  return 1.0f / (x * x - x);
}

void calculate()
{
  for(double i = -40.0f; i < 0.0f; i = i + 0.01f)
  {
    double x = i * step;
    double y = f2(i) * step;
    if(-0.9f <= x && x <= 0.9f)
    {
      if(-0.9f <= y && y <= 0.9f)
      {
        results[0].insert(std::map<double, double>::value_type(x, y));
      }
    }
  }
  for(double i = 0.01f; i < 1.0f; i = i + 0.01f)
  {
    double x = i * step;
    double y = f2(i) * step;
    if(-0.9f <= x && x <= 0.9f)
    {
      if(-0.9f <= y && y <= 0.9f)
      {
        results[1].insert(std::map<double, double>::value_type(x, y));
      }
    }
  }
  for(double i = 1.01f; i < 40.0f; i = i + 0.01f)
  {
    double x = i * step;
    double y = f2(i) * step;
    if(-0.9f <= x && x <= 0.9f)
    {
      if(-0.9f <= y && y <= 0.9f)
      {
        results[2].insert(std::map<double, double>::value_type(x, y));
      }
    }
  }
  // for(double i = -10.0f; i < 10.0f; i = i + 0.1f)
  // {
  //   double x = i * step;
  //   double y = f2(i) * step;
  //   if(x / ratio == 0 || x / ratio == 1) continue;
  //
  //   if(-0.9f <= x && x <= 0.9f)
  //   {
  //     if(-0.9f <= y && y <= 0.9f)
  //     {
  //       results.insert(std::map<double, double>::value_type(x, y));
  //     }
  //   }
  // }
}

void display()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_LINE_SMOOTH);

  glPushMatrix();
    glLineWidth(1.0f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
      glVertex2f( 0.0f, -80.0f);
      glVertex2f( 0.0f,  80.0f);

      glVertex2f(-180.0f, 0.0f);
      glVertex2f( 180.0f, 0.0f);
    glEnd();
    glLineWidth(2.5f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for(std::map<double, double>::iterator it = results[0].begin(); it != results[0].end(); ++it)
    {
      glVertex3f(it->first, it->second, 0.0f);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for(std::map<double, double>::iterator it = results[1].begin(); it != results[1].end(); ++it)
    {
      glVertex3f(it->first, it->second, 0.0f);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for(std::map<double, double>::iterator it = results[2].begin(); it != results[2].end(); ++it)
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
  gluPerspective(1.5f, (GLfloat) w/(GLfloat) h, 1.0f, 100.0f);

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
  glutInitWindowSize(400, 800);
  glutCreateWindow("graph");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  glutMainLoop();

  return 0;
}
