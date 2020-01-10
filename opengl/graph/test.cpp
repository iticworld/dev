#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"
#include "math.h"

static int year = 0, day = 0;

void display(void)
{
  int temp;
  glClear(GL_COLOR_BUFFER_BIT);
glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE);
      glVertex3f(0.1f, 0.1f, 0.0f);
      glVertex3f(0.8f, 0.1f, 0.0f);
    glEnd();
	  glBegin(GL_POINT);
    for(temp = 0; temp < 360; temp++)
    {
      glVertex3f(0.01f*temp - 2.0f,sin(3.1415927f/180.0f*temp),0);
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
  gluPerspective(60.0f, (GLfloat) w/(GLfloat) h, 1.0f, 80.0f);

  glMatrixMode(GL_MODELVIEW); //GL_PROJECTION
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  // glShadeModel(GL_SMOOTH); //GL_SMOOTH

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}
