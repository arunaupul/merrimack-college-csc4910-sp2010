/* 
 * trans.c - Name collision with Nate Robbin's transformation.c
 *
 * Illustrate transformations using gl calls.  
 * Draw three shapes by translating a standard disc.
 *
 * Jeff Parker    Sept 2009
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define STEPS 16.0

void init()
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
}

void setColorRed()
{
    glColor3f(1.0, 0.0, 0.0);
}

void setColorYellow()
{
    glColor3f(1.0, 1.0, 0.0);
}

void setColorBlue()
{
    glColor3f(0.0, 0.0, 1.0);
}

void setColorGreen()
{
    glColor3f(0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
        switch (tolower(key)) 
        {
                case 'q':
                case 27:                        /* Escape key */
                        exit(0);
                        break;
        }
}

void drawDisc()
{
    int count;
        
    glBegin(GL_POLYGON);
        for (count = 0; count <= STEPS*2; count++)
        {
            float theta = (float)(count * M_PI)/STEPS;
            glVertex2f(sin(theta), cos(theta));        
        }
    glEnd();
}

void drawAxes()
{
    setColorYellow();
    glBegin(GL_LINES);
        glVertex2f(-2.0, 0.0);
        glVertex2f(10.0, 0.0);
        glVertex2f(0.0, -2.0);
        glVertex2f(0.0, 10.0);
    glEnd();
}
    
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();

    setColorBlue();
    drawDisc();

    setColorRed();
    glTranslated(8,0,0);
    drawDisc();
    
    setColorGreen();
    glTranslated(-3,2,0);
    glScaled(1,4,0);
    drawDisc();
    glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D (-2.0, 10.0, -2.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

/* main loop */ int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Transformation");
   glutKeyboardFunc(keyboard);
   init ();
   glutReshapeFunc (reshape);
   glutDisplayFunc(display);
   glutMainLoop();

   return 0;
}
