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
  std::vector<char> keys;
  
 public:
  GLfloat x, y, z, c, rotation, distance;
  CameraMode cameraMode;
  Camera(GLfloat ix, GLfloat iy, GLfloat iz, GLfloat r);
  Camera();
  void switchMode();
  void setDims(int width, int height);
  GLfloat getXLook();
  GLfloat getZLook();
  void down(char key);
  void up(char key);
  void update();
};
