#pragma once
#include <sstream>
#include <fstream>
#include <vector>
#include <GL/glut.h>
#include "CollisionGun.h"
#include "error.h"

typedef struct point_t {
  GLfloat x, y, z;
} Point;

class Object {
private:
  std::vector<Point> verts, uvs, norms;
  std::vector<unsigned int*> faces;
  std::vector<HitBox> hitBoxes;
  bool collidable;
  
public:
  GLfloat x, y, z, yr, xr, zr;
  
  Object();
  bool isCollidable();
  void setBoxes(std::vector<HitBox> boxes);
  std::vector<HitBox> getBoxes();
  bool load(char *objPath, char *mtlPath);
  void draw();
};
