#include <GL/glut.h>
// #include <GL/freeglut_std.h>

GLsizei winWidth = 400;
GLsizei winHeight = 300;
GLint xRaster = 25;
GLint yRaster = 150;

GLubyte label[36] = { 'J', 'a', 'n',  'F', 'e', 'b',  'M', 'a', 'r',
                      'A', 'p', 'r',  'M', 'a', 'y',  'J', 'u', 'n',
                      'J', 'u', 'l',  'A', 'u', 'g',  'S', 'e', 'p',
                      'O', 'c', 't',  'N', 'o', 'v',  'D', 'e', 'c' };
GLint dataValue[12] = { 420, 342, 324, 310, 262, 185, 190, 196, 217, 312, 438 };

void init(void)
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0f, 200.0f, 0.0f, 150.0f);
}

class scrPt {
public:
GLint x, y;
};

// void pieChart(void)
// {
//   srcPt circCtr;
//   srcPt piePt;
//   GLint radius = winWidth / 4;
//
//   GLdouble sliceAngle;
//   GLdouble previousSliceAngle = 0.0f;
//   GLint k;
//   GLint nSlices = 12;
//   GLfloat dataValues[12] = {
//     10.0f, 7.0f, 13.0f, 5.0f, 13.0f, 14.0f, 3.0f, 16.0f, 5.0f, 3.0f, 17.0f, 8.0f
//   };
//
//   GLfloat dataSum = 0.0f;
//
//   circCtr.x = winWidth / 2;
//   circCtr.y = winHeight / 2;
//   circleMidPoint(circCtr, radius);
// }

void barChart(void)
{
  GLint month, k;
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0f, 0.0f, 0.0f);
  for(k = 0; k < 12; k++)
  {
    glRecti(20 + k * 50, 165, 40 + k*50, dataValue[k]);
  }
  glFlush();
}

void lineGraph(void)
{
  GLint month;
  GLint k;
  GLint x = 30;

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_LINE_STRIP);
  for(k = 0; k < 12; k++)
  {
    glVertex2i (x + k*50, dataValue[k]);
  }
  glEnd();

  glColor3f(1.0f, 0.0f, 0.0f);
  for(k = 0; k < 12; k++)
  {
    glRasterPos2i(xRaster + k + 50, dataValue[k] - 4);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
  }

  glColor3f(0.0f, 0.0f, 0.0f);
  xRaster = 20;
  for(month = 0; month < 12; month ++)
  {
    glRasterPos2i(xRaster, yRaster);
    for(k = 3 * month; k < 3*month + 3; k++)
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
      xRaster += 50;
    }
  }
  glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
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
  glutCreateWindow("Line Chart Data Plot");

  init();
  // glutDisplayFunc(lineGraph);
  glutDisplayFunc(barChart);
  glutReshapeFunc(winReshapeFcn);
  glutMainLoop();
  return 0;
}
