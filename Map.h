#pragma once
#include <vector>
#include <GL/glut.h>
#include "CollisionGun.h"

class Map {
 private:
 public:
  std::vector<HitBox> hitboxes;

  void fromString(char *data){

  }

  void fromString(std::string data){
    fromString((char*)data.c_str());
  }
  
  void fromFile(char *path){
    
  }
};
