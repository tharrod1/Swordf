#include "Light.h"
#include <vector>
#include <GL/glut.h>

Light::Light(){
  pos[0] = 1.0f;
  pos[1] = 1.0f;
  pos[2] = 1.0f;
}

Light::Light(GLfloat ix, GLfloat iy, GLfloat iz){
  pos[0] = ix;
  pos[1] = iy;
  pos[2] = iz;
}

void Light::set(GLfloat ix, GLfloat iy, GLfloat iz){
  pos[0] = ix;
  pos[1] = iy;
  pos[2] = iz;
}

void Light::update(){
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
}

Light::~Light(){
  //test if light is autoremoved
}

unsigned int LightPool::addLight(GLfloat x, GLfloat y, GLfloat z){
  pool.push_back(Light(x, y, z));
  return pool.size();
}
  
void LightPool::update(){
  unsigned int pools = pool.size();
  for(unsigned int i = 0; i < pools; i++){
    pool[i].update();
  }
}

LightPool::~LightPool(){
  pool.clear();
}
