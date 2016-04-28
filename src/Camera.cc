#include <vector>
#include <math.h>
#include <GL/glut.h>
#include "Camera.h"

Camera::Camera(GLfloat ix, GLfloat iy, GLfloat iz, GLfloat r){
  x = ix;
  y = iy;
  z = iz;
  rotation = r;
  distance = 5.0;
  c = 2.0;
  cameraMode = first;
  fwd = bwd = lwd = rwd = false;
}

Camera::Camera(){
  x = 0.0;
  y = 1.0;
  z = 0.0;
  rotation = 0.0;
  distance = 5.0;
  c = 2.0;
  cameraMode = first;
  fwd = bwd = lwd = rwd = false;
}

void Camera::switchMode(){
  cameraMode = (cameraMode == first) ? third : first;
}

void Camera::setDims(int width, int height){
  w = width;
  h = height;
}
  
GLfloat Camera::getXLook(){
  return x+distance*sin(rotation);
}

GLfloat Camera::getZLook(){
  return z-distance*cos(rotation);
}

void Camera::down(char key){
  keys.push_back(key);
}
  
void Camera::up(char key){
  unsigned int lkeys = keys.size();
  for(unsigned int i = 0; i < lkeys; i++){
    if(key == 'w' || key == 'W'){
      if(keys[i] == 'w' || keys[i] == 'W'){
	keys.erase(keys.begin()+i);
      }
    }else{
      if(keys[i] == key){
	keys.erase(keys.begin()+i);
      }
    }
  }
}

void Camera::update(){
  glutSetCursor(GLUT_CURSOR_NONE);
  glutWarpPointer(w/2, h/2);
    
  if(keys.empty()) return;
  char curKey = keys.back();

  if(cameraMode == third) c = -c;
    
  switch(curKey){
  case 'W':
    x += RUN * c * sin(rotation) * 0.01;
    z -= RUN * c * cos(rotation) * 0.01;
  case 'w':
    x += c * sin(rotation) * 0.01;
    z -= c * cos(rotation) * 0.01;
    break;
  case 's':
    x -= c * sin(rotation) * 0.01;
    z += c * cos(rotation) * 0.01;
    break;
  case 'a':
    x -= c * sin(rotation+PI/2) * 0.01;
    z += c * cos(rotation+PI/2) * 0.01;
    break;
  case 'd':
    x -= c * sin(rotation-PI/2) * 0.01;
    z += c * cos(rotation-PI/2) * 0.01;
    break;
  }

  if(cameraMode == third) c = -c;
}
