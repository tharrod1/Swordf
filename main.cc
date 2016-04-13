#include <stdio.h>
#include <GL/glut.h>
#include "Swordf.h"
#include "gravity.h"

Swordf swordf;
std::vector<HitBox> hbs;
int fallTime;

void onClick(){

}

void onClick(int button, int state, int x, int y){

}

void onAction(){

}

void onMouse(int x, int y){
  swordf.camera.rotation += (x-swordf.mousePosition.x) * 0.001;
  swordf.mousePosition.x = x;
}

void onKey(Key key, int x, int y){
  switch(key){
  case KEY_A:
  case KEY_a:
    swordf.camera.left(1.0);
    break;
  case KEY_D:
  case KEY_d:
    swordf.camera.right(1.0);
    break;
  case KEY_W:
    swordf.camera.forward(2.5);
    break;
  case KEY_w:
    swordf.camera.forward(1.0);
    break;
  case KEY_S:
  case KEY_s:
    swordf.camera.backward(0.5);
    break;
  case KEY_e:
    onAction();
    break;
  case KEY_f:
    glutFullScreen();
    break;
  case KEY_SPACE:
    swordf.camera.y += 8;
      break;
  case KEY_ESCAPE:
    exit(0); // FIXME: change to exit menu unless in config
    break;
  default:
    break;
  }
}

void offKey(Key key, int x, int y){
  switch(key){
  case KEY_A:
  case KEY_a:
  case KEY_D:
  case KEY_d:
  case KEY_W:
  case KEY_w:
  case KEY_S:
  case KEY_s:
    swordf.camera.up();
    break;
  default:
    break;
  }
}

void logic(){
  swordf.camera.y = gravity(swordf.camera, hbs, 0.5, 0.1, &fallTime);
  swordf.camera.update();
  swordf.mainLight.update();
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);  
  glLoadIdentity();

  logic(); //more optimized if two seperate functions are called, but this makes less weird lag IMO
  
  gluLookAt(swordf.camera.x, swordf.camera.y, swordf.camera.z,
	    swordf.camera.getXLook(), swordf.camera.y, swordf.camera.getZLook(),
	    0.0, swordf.camera.y, 0.0);
  swordf.drawCube();
  glutSwapBuffers();
}
 
void reshape(GLsizei width, GLsizei height){
  swordf.defaultResize(width, height);
}

int main(int argc, char **argv){
  swordf.initGL(argc, argv, "Swordf");
  fallTime = 0;
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
