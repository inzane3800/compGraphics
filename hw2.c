#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#ifndef RES
#define RES 1
#endif
#include <GLUT/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
int numVtc = 200000;
double th=0;
float vertice[200000][3];
int colors[200000][3];
static GLfloat view_rotx = 25.0, view_roty = 50.0, view_rotz = 35.0;
static GLfloat view_posz = 60.0;
double s  = 10;
double b  = 2.6666;
double r  = 28;
GLint colorIndex;
int iter = 0;
int iterInc = 10;
int axes = 1;
#define LEN 8192
int scale = 1;

void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
        
    glRotatef(view_rotx, 1.0, 0.0, 0.0);
    
    glRotatef(view_roty, 0.0, 1.0, 0.0);
    
    glRotatef(view_rotz, 0.0, 0.0, 1.0);
    
    if (axes)
    {
    const double len=55;
    glBegin(GL_LINES);
           
    glVertex3d(0.0,0.0,0.0);
            
    glVertex3d(len,0.0,0.0);
           
    glVertex3d(0.0,0.0,0.0);
        
    glVertex3d(0.0,len,0.0);
        
    glVertex3d(0.0,0.0,0.0);
           
    glVertex3d(0.0,0.0,len);
           
    glEnd();
        
    glRasterPos3d(len,0.0,0.0);
        
    Print("X");
        
    glRasterPos3d(0.0,len,0.0);
    Print("Y");
           
    glRasterPos3d(0.0,0.0,len);
    Print("Z");
    }
    
    glBegin(GL_LINE_STRIP);
    int i = 0;
    int i2 = 0;
    while( i < iter && i < numVtc ) {
        glColor3f(colors[i2][0], colors[i2][1], colors[i2++][2]);
        glVertex3fv(vertice[i++]);
    }
    glEnd();
    
    if( iter < numVtc ) {
        if( iter + iterInc > numVtc ) iter = numVtc;
        
        else iter+=iterInc;
    }
    
    glFlush();
    
    glutSwapBuffers();
    
    glPopMatrix();
    
}

static void reshape(int width, int height) {
  GLfloat h = (GLfloat) height / (GLfloat) width;
  glViewport(0, 0, (GLint) width, (GLint) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-5.0, 5.0, -h*2, h*2, 1.0, 300.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -60.0);
}

static void keyfunc(unsigned char k, int x, int y) {
    switch (k) {
        case 'a':
            view_rotx += 5.0;
            break;
        case 'd':
            view_rotx -= 5.0;
            break;
        case 'w':
            view_roty += 5.0;
            break;
        case 's':
            view_roty -= 5.0;
            break;
        case 'q':
            view_rotz += 5.0;
            break;
        case 'z':
            view_rotz -= 5.0;
            break;
        case 'r':
            iter = 0;
            break;
        case 'f':
            iter = numVtc;
            break;
        case 't':
            iterInc += 5;
            break;
        case 'g':
            if( iterInc - 5 >- 0 ) iterInc -= 5;
            break;
        case 'c':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            view_posz -= 1;
            gluLookAt(view_posz,0,0,0.0,0.0,0.0,0.0,1.0,0.0);
            break;
        case 'v':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            view_posz += 1;
            gluLookAt(view_posz,0,0,0.0,0.0,0.0,0.0,1.0,0.0);
            break;
        default:
            return;
    }
    glutPostRedisplay();
}

static void idle(void) {
    iter+=iterInc;
    glutPostRedisplay();
}

static void lorenzPopulation(void) {
    int i;
    float x = vertice[0][0] = 1;
    float y = vertice[0][1] = 1;
    float z = vertice[0][2] = 1;
    float dt = 0.001;
    

    for (i=0;i<numVtc-1;i++)
    {
        float dx = s*(y-x);
        float dy = x*(r-z)-y;
        float dz = x*y - b*z;
        x += dt*dx;
        y += dt*dy;
        z += dt*dz;
        
        vertice[i+1][0] = x;
        vertice[i+1][1] = y;
        vertice[i+1][2] = z;
        
        
    }
}

static void rainbowColors(void) {
colorIndex=0;
for (int colorIndex=0; colorIndex<33332; colorIndex++)
{
    colors[colorIndex][0]=1;
    colors[colorIndex][1]=0;
    colors[colorIndex][2]=0;
}
for (int colorIndex=33333; colorIndex<66664; colorIndex++)
{
    colors[colorIndex][0]=1;
    colors[colorIndex][1]=1;
    colors[colorIndex][2]=0;
}
for (int colorIndex=66665; colorIndex<99996; colorIndex++)
{
    colors[colorIndex][0]=0;
    colors[colorIndex][1]=1;
    colors[colorIndex][2]=0;
}
for (int colorIndex=99997; colorIndex<133328; colorIndex++)
{
    colors[colorIndex][0]=0;
    colors[colorIndex][1]=1;
    colors[colorIndex][2]=1;
}
for (int colorIndex=133329; colorIndex<166660; colorIndex++)
{
    colors[colorIndex][0]=0;
    colors[colorIndex][1]=0;
    colors[colorIndex][2]=1;
}
for (int colorIndex=166661; colorIndex<200000; colorIndex++)
{
    colors[colorIndex][0]=1;
    colors[colorIndex][1]=0;
    colors[colorIndex][2]=1;
}
}
int main(int argc,char* argv[]) {
    rainbowColors();
    lorenzPopulation();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(25, 25);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Rainbow Lorenz Curve");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyfunc);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
