#pragma once
#include <math.h>
#include <GL/glut.h>
#define PI 3.14159265

enum Direction {
  fwd, bwd, lwd, rwd, none
};

enum CameraMode {
  first, third
};

class Camera {
 private:
  Direction dir;
  int w, h;
  
 public:
  GLfloat x, y, z, c, rotation;
  CameraMode cameraMode;
  
  Camera(GLfloat ix, GLfloat iy, GLfloat iz, GLfloat r){
    x = ix;
    y = iy;
    z = iz;
    rotation = r;
    dir = none;
    cameraMode = first;
  }

  Camera(){
    x = 0.0;
    y = 1.0;
    z = 0.0;
    rotation = 0.0;
    dir = none;
    cameraMode = first;
  }

  void switchMode(){
    cameraMode = (cameraMode == first) ? third : first;
  }

  void setDims(int width, int height){
    w = width;
    h = height;
  }
  
  GLfloat getXLook(){
    return x+sin(rotation);
  }

  GLfloat getZLook(){
    return z-cos(rotation);
  }

  void forward(GLfloat ic){
    dir = fwd;
    c = ic;
  }

  void backward(GLfloat ic){
    dir = bwd;
    c = ic;
  }

  void left(GLfloat ic){
    dir = lwd;
    c = ic;
  }

  void right(GLfloat ic){
    dir = rwd;
    c = ic;
  }

  void up(){
    dir = none;
  }

  void update(){
    switch(dir){
    case fwd:
      x += c * sin(rotation) * 0.01;
      z -= c * cos(rotation) * 0.01;
      break;
    case bwd:
      x -= c * sin(rotation) * 0.01;
      z += c * cos(rotation) * 0.01;
      break;
    case lwd:
      x -= c * sin(rotation+PI/2) * 0.01;
      z += c * cos(rotation+PI/2) * 0.01;
      break;
    case rwd:
      x -= c * sin(rotation-PI/2) * 0.01;
      z += c * cos(rotation-PI/2) * 0.01;
      break;
    default:
      break;
    }

    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(w/2, h/2);
  }
};
