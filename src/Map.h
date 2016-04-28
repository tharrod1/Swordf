#pragma once
#include <string.h>
#include <sstream>
#include <vector>
#include <GL/glut.h>
#include "AudioPool.h"
#include "CollisionGun.h"
#include "Light.h"
#include "Object.h"
#include "error.h"

#define TOKEN_WIDTH 10.0
#define TOKEN_DEPTH 10.0

// TODO: smallmap files (number <char to repeat>)

typedef std::vector<Object> ObjectPool;

class MapToken {
 public:
  char identifier;
  bool collidable, isFloor;
  char *path;
  HitBox hitBox;
  GLfloat rotation;

  MapToken();
  ~MapToken();
  MapToken *clone();
};

//this is for the easy to read/write map file format
class Map {
 private:
  bool dataSec;
  AudioPool *audioPool;
  LightPool *lightPool;
  ObjectPool *objectPool;
  std::vector<MapToken*> toks, updateToks;
  GLfloat x, z;

  unsigned int nextSpace(char *str, unsigned int start);
  char *slice(char *str, unsigned int start, unsigned int end);
  
 public:
  std::vector<HitBox> hitboxes;
  Map(AudioPool *ap, LightPool *lp, ObjectPool *op);
  ~Map();
  void fromString(char *data);
  void fromString(std::string data);
  void fromFile(char *path);
  void load();
  void update();
};
