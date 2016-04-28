#pragma once
#include <vector>
#include <GL/glut.h>

typedef struct bullet_t {
  GLfloat x, y, z, yr, v, g;
} Bullet;

//could be a struct, but idk if I'll change it yet
class HitBox {
public:
  GLfloat x, y, z, width, height, depth;
  int fallTime;
  HitBox();
  HitBox(GLfloat ix, GLfloat iy, GLfloat iz,
	 GLfloat iw, GLfloat ih, GLfloat id);
  HitBox clone();
};

class CollisionGun {
 private:
  GLfloat x, y, z, yr;
  std::vector<Bullet> bulletPool;
 public:
  
  //number of boxes that need to be checked is n(n-1) / 2, so I will allow for specific game optimizations than bloat this with all the various methods
  bool boxCollision(HitBox hb1, HitBox hb2);
  bool linearShot(HitBox hb);
  bool linearShot(HitBox hb, Bullet b);
  void bulletShot(GLfloat v, GLfloat g);
  std::vector<unsigned int> update(std::vector<HitBox> boxes);
};
