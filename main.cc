#include <stdio.h>
#include <GL/glut.h>
#include "Swordf.h"

Swordf swordf;
std::vector<HitBox> hbs;

void onClick(int button, int state, int x, int y){
  //check if onclick script exists
}

void onAction(){
  //check if onaction script exists
}

void onMouse(int x, int y){
  //check if onmouse script exists
  swordf.defaultOnMouseMove(x, y);
}

void onKey(Key key, int x, int y){
  swordf.defaultOnKey(key);
}

void offKey(Key key, int x, int y){
  swordf.defaultOffKey(key);
}

void logic(){
  swordf.gravity(hbs, 0.5, 0.1);
  swordf.defaultLogic();
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  logic(); //more optimized if two seperate functions are called, but this makes less weird lag IMO
  swordf.drawCube();
  swordf.drawStr("Test", GLUT_BITMAP_9_BY_15, 2, 1, 1);

  glutSwapBuffers();
}
 
void reshape(GLsizei width, GLsizei height){
  swordf.defaultResize(width, height);
}

int main(int argc, char **argv){
  swordf.initGL(argc, argv, "Swordf");
  hbs.push_back(HitBox(0, -3, 0, 10, 10, 1));
  
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(onKey);
  glutKeyboardUpFunc(offKey);
  glutMouseFunc(onClick);
  glutPassiveMotionFunc(onMouse);
  glutMainLoop();
  return 0;
}
