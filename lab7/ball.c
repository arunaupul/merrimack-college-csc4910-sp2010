/* Bouncing Ball - JDP Nov 2007 */
/* Bugs: 
   Ball is a small and simple box 
 */

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

ball cp;

/* We assume that a color is set before this is called */
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
    initBall(&cp);

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    /* Draw the balls */
    setBallColor();
    updateBall(&cp);
    glFlush();

    /* call back again after elapsedUSecs have passed */ 
    glutTimerFunc (value, timerCallback, value); 
} 

/* Handle keyboard input */
void key(unsigned char k, int x, int y)
{
    if (k == 27)  exit(0);
}


/* Main routine */
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
