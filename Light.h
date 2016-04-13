#include <vector>
#include <GL/glut.h>

class Light {
private:
  GLfloat pos[3];
public:  
  Light(){
    pos[0] = 1.0f;
    pos[1] = 1.0f;
    pos[2] = 1.0f;
  }

  Light(GLfloat ix, GLfloat iy, GLfloat iz){
    pos[0] = ix;
    pos[1] = iy;
    pos[2] = iz;
  }

  void set(GLfloat ix, GLfloat iy, GLfloat iz){
    pos[0] = ix;
    pos[1] = iy;
    pos[2] = iz;
  }
  
  void update(){
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
  }

  ~Light(){
    //test if light is autoremoved
  }
};

class LightPool {
private:
public:
  std::vector<Light> pool;

  unsigned int addLight(GLfloat x, GLfloat y, GLfloat z){
    pool.push_back(Light(x, y, z));
    return pool.size();
  }
  
  void update(){
    unsigned int pools = pool.size();
    for(unsigned int i = 0; i < pools; i++){
      pool[i].update();
    }
  }
  
  ~LightPool(){
    pool.clear();
  }
};
