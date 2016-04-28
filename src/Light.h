#pragma once
#include <vector>
#include <GL/glut.h>

class Light {
 private:
  GLfloat pos[3];
 public:
  Light();
  Light(GLfloat ix, GLfloat iy, GLfloat iz);
  void set(GLfloat ix, GLfloat iy, GLfloat iz);
  void update();
  ~Light();
};

class LightPool {
public:
  std::vector<Light> pool;
  unsigned int addLight(GLfloat x, GLfloat y, GLfloat z);
  void update();
  ~LightPool();
};
