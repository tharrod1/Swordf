#pragma once
#include <stdio.h>
#include <vector>
#include <GL/glut.h>
#include "CollisionGun.h"
#include "error.h"

typedef struct point_t {
  GLfloat x, y, z;
} Point;

class Object {
private:
  std::vector<Point> verts, uvs, normals;
  std::vector<HitBox> hitBoxes;
  bool collidable;
  
public:
  GLfloat x, y, z, yr, xr, zr;
  
  Object(){
    collidable = false;
  }

  bool isCollidable(){
    return collidable;
  }
  
  void setBoxes(std::vector<HitBox> boxes){
    hitBoxes = boxes;
    collidable = true;
  }

  std::vector<HitBox> getBoxes(){
    return hitBoxes;
  }
  
  bool load(char *objPath, char *mtlPath){
    FILE *objFile = fopen(objPath, "r");
    if(objFile == NULL){
      return false;
    }
    
    FILE *mtlFile = fopen(mtlPath, "r");
    if(mtlFile == NULL){
      return false;
    }

    char buf[1024];
    
    while(true){
      if(fgets(buf, sizeof(buf), objFile) == NULL) break;
      switch(buf[0]){
      case 'v':
	//vertex data
	switch(buf[1]){
	case 't':
	  //texture vert
	  break;
	case 'n':
	  //normal vert
	  break;
	case 'p':
	  //parameter
	  break;
	default:
	  msg("Invalid obj file format.\n", __DATE__, __TIME__, __FILE__, __LINE__);
	  break;
	}
	break;
      case '#':
	break;
      case 'g':
	//group
	break;
      case 's':
	//surface
	break;
      case 'f':
	//face
	break;
      default:
	msg("Invalid obj file format.\n", __DATE__, __TIME__, __FILE__, __LINE__);
	break;
      }
    }

    //similar method for mtl
    
    fclose(objFile);
    fclose(mtlFile);
  }

  void draw(){
    //draw at [x, y, z] rotated xr, yr, and zr
  }
};
