#pragma once
#include <GL/glut.h>
#include "Camera.h"
#include "AudioPool.h"
#include "CollisionGun.h"
#include "Light.h"

#define KEY_A 65
#define KEY_a 97
#define KEY_d 100
#define KEY_D 68
#define KEY_W 87
#define KEY_w 119
#define KEY_S 83
#define KEY_s 115
#define KEY_e 101
#define KEY_f 102
#define KEY_SPACE 32
#define KEY_ESCAPE 27

typedef unsigned char Key;

typedef struct mousepos_t {
  int x, y;
}MousePosition;

class Swordf {
 private:

 public:
  Camera camera;
  AudioPool audioPool;
  MousePosition mousePosition;
  Light mainLight;
  LightPool lightPool;
  
  void initGL(int argc, char **argv, char *title){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(800, 600);  
    glutInitWindowPosition(50, 50); 
    glutCreateWindow(title);
  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glClearDepth(1.0f);                   
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);  
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  }

  void defaultResize(GLsizei width, GLsizei height){
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    
    glViewport(0.0f, 0.0f, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
  }

  void drawCube(){
    glBegin(GL_QUADS);
    const GLfloat cyan[] = {0.0f, 0.8f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, cyan);
    
    glVertex3f( 1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f,  1.0f);
 
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
 
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);
 
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
 
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
 
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();
  }
};
