/* Bouncing Ball 2 - JDP Nov 2007 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* globals */

GLsizei wh = 300, ww = 300; /* initial window size */ 

#define        MAG        (GLfloat)(5.0)        /* Size of ball */
int size = 3;

/* Keep track of ball's position (x, y) and velocity (deltax, deltay) */
typedef struct ball
{
    int x;
    int y;
    GLfloat deltax;
    GLfloat deltay;
} ball;

#define NUM_BALLS        4
ball *cp[NUM_BALLS];

void tic();

/* A color must be called before this */
void drawBall(ball *b)
{
   int  y = wh - b->y;
   int  x = b->x;
   glBegin(GL_POLYGON);
      glVertex2f(x+size, y+size);
      glVertex2f(x-size, y+size);
      glVertex2f(x-size, y-size);
      glVertex2f(x+size, y-size);
   glEnd();
}

/* reshaping routine called whenever window is resized or moved */
void myReshape(GLsizei w, GLsizei h) 
{
    /* adjust clipping box */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* adjust viewport and clear */
    glViewport(0,0,w,h);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    /* set global size for use by drawing routine */
    ww = w;
    wh = h;
}

/* Background */
void setBackGroundColor()
{
   glColor3ub(0, 0, 0);
}

/* Ball color */
void setBallColor()
{
   glColor3ub(0, 0, 255);
}

/* Color of line */
void setLineColor()
{
   glColor3ub(0, 255, 0);
}

/* Start the ball rolling... */
void initBall(ball *b)
{
    /* Pick a random direction */
    GLfloat theta = (GLfloat)(rand() % 256)/255;
    b->deltax = MAG * cos(theta);
    b->deltay = MAG * sin(theta);

    /* Pick the starting spot */
    b->x = (rand() % ww)/2;        /* Ugly hack: ww gets reset to 300 ?!? */
    b->y = (rand() % wh)/2;
}

/* Initialize */
void myinit() 
{
    int i;

    for (i = 0; i < NUM_BALLS; i++)
    {
        cp[i] = malloc(sizeof(struct ball));
        initBall(cp[i]);
    }

    glClearColor (0.0, 0.0, 0.0, 1.0);
    glViewport(0, 0, ww, wh);

   /* Pick 2D clipping window to match
      size of screen window. This choice avoids having to scale object
      coordinates each time window is resized. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble) ww , 0.0, (GLdouble) wh , -1.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

/* move one ball */
void updateBall(ball *b)
{
    /* Update x and y value */
    b->x = b->x + b->deltax;
    b->y = b->y + b->deltay;
    
    /* Did we hit the edge? */
    if ((b->x < 2) || (b->x > ww))
    {
        b->deltax = -1.0 * b->deltax;
        b->x = b->x + b->deltax;
        /* Provide for resize */
        if (b->x > ww)
            b->x = b->x % ww;
    }
    
    /* Did we hit the edge? */
    if ((b->y < 2) || (b->y > wh))
    {
        b->deltay = -1.0 * b->deltay;
        b->y = b->y + b->deltay;
        /* Provide for resize */
        if (b->y > wh)
            b->y = b->y % wh;
    }

    /* Plot the point */
    drawBall(b);
}

/* display callback required by GLUT */
/* This one does nothing */
void display() 
{}

/* The timer callback */
static void timerCallback (int value) 
{ 
   /* Tmer processing */ 
   tic();

   /* call back again after elapsedUSecs have passed */ 
   glutTimerFunc (value, timerCallback, value); 
} 

/* Handle keyboard input */
void key(unsigned char k, int x, int y)
{
    if (k == 27)  exit(0);
}

void drawCurve()
{
    int i;
    GLfloat pts[4][3];
    /* Copy the coordinates from balls to array */
    for (i = 0; i < 4; i++)
    {
        pts[i][0] = (GLfloat)cp[i]->x;
        pts[i][1] = (GLfloat)wh - (GLfloat)cp[i]->y;
        pts[i][2] = (GLfloat)0.0;
    }

    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &pts[0][0]);
    /* type, u_min, u_max, stride, num points, points */

    glEnable(GL_MAP1_VERTEX_3);

    setLineColor();
    glBegin(GL_LINE_STRIP);
    for (i = 0; i <= 30; i++)
        /* Evaluate the curve when u = i/30 */
        glEvalCoord1f((GLfloat) i/ 30.0);
    glEnd();

    /* Draw lines between the control points */
    setBallColor();
    glBegin(GL_LINE_STRIP);
        for (i = 0; i < 4; i++)
            glVertex2f(pts[i][0], pts[i][1]);
    glEnd();
    glShadeModel(GL_FLAT);
}

/* Advance things one tic */
void tic()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    setBallColor();
    /* Update the balls */
    /* XXX Fill in logic to move the balls */

    /* Draw the curve */
    drawCurve(cp);
    glFlush();
}

/* display callback required by GLUT */


int main(int argc, char** argv) 
{
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ww, wh); 
    glutCreateWindow("bounce");
    myinit ();

    /* Register callback functions */
    glutReshapeFunc (myReshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutTimerFunc (100, timerCallback, 40); 

    glutMainLoop();

    return 0;        /* Never reached */
}
