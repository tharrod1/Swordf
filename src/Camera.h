#pragma once
#include <math.h>
#include <GL/glut.h>
#define PI 3.14159265
#define RUN 2.8

enum CameraMode {
  first, third
};

class Camera {
 private:
  int w, h;
  bool fwd, bwd, lwd, rwd;
  std::vector <char> keys;
  
 public:
  GLfloat x, y, z, c, rotation, distance;
  CameraMode cameraMode;
  
  Camera(GLfloat ix, GLfloat iy, GLfloat iz, GLfloat r){
    x = ix;
    y = iy;
    z = iz;
    rotation = r;
    distance = 5.0;
    c = 2.0;
    cameraMode = first;
    fwd = bwd = lwd = rwd = false;
  }

  Camera(){
    x = 0.0;
    y = 1.0;
    z = 0.0;
    rotation = 0.0;
    distance = 5.0;
    c = 2.0;
    cameraMode = first;
    fwd = bwd = lwd = rwd = false;
  }

  void switchMode(){
    cameraMode = (cameraMode == first) ? third : first;
  }

  void setDims(int width, int height){
    w = width;
    h = height;
  }
  
  GLfloat getXLook(){
    return x+distance*sin(rotation);
  }

  GLfloat getZLook(){
    return z-distance*cos(rotation);
  }

  void down(char key){
    keys.push_back(key);
  }
  
  void up(char key){
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

  void update(){
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
};
