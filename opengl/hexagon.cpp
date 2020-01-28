#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

const double TWO_PI = 6.2831853f;

// Initial display window size
GLsizei winWidth = 400;
GLsizei winHeight = 400;
GLuint regHex;

class screenPt
{
private:
  GLint x, y;
public:
  // Default Constructor: initializes coordinate position to (0, 0)
  screenPt() {
    x = y = 0;
  }
  void setCoords(GLint xCoord, GLint yCoord) {
    x = xCoord;
    y = yCoord;
  }
  GLint getx() const {
    return x;
  }
  GLint gety() const {
    return y;
  }
};

static void init(void)
{
  screenPt hexVertex;
  screenPt circCtr;
  GLdouble theta;
  GLint k;
  // set circle center coordinates.
  circCtr.setCoords(winWidth/2, winHeight/2);
  // display window color = white
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  // set up a display list for a red regular hexagon.
  // vertices for the hexagon are six equally spaced
  // points around the circumference of a circle.
  // get an identifier for the display list
  regHex = glGenLists(1);
  glNewList(regHex, GL_COMPILE);
    // set fill color for hexagon to red.
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
      for(k = 0; k < 6; k++)
      {
        theta = TWO_PI * k / 6.0f;
        hexVertex.setCoords(circCtr.getx() + 150 * cos(theta),
                            circCtr.gety() + 150 * sin(theta));
        glVertex2i(hexVertex.getx(), hexVertex.gety());

      }
    glEnd();
  glEndList();
}

void regHexagon(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glCallList(regHex);
  glFlush();
}

void winReshapeFcn(int newWidth, int newHeight)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0f, (GLdouble) newWidth, 0.0f, (GLdouble) newHeight);
  glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char ** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(winWidth, winHeight);
  glutCreateWindow("Reshape Function & Display List Example");

  init();
  glutDisplayFunc(regHexagon);
  glutReshapeFunc(winReshapeFcn);
  glutMainLoop();
  return 0;
}
