#include <GL/glut.h>
#include "Camera.h"
#include "CollisionGun.h"

GLfloat gravity(Camera cam, std::vector<HitBox> boxes, GLfloat lowest,
	       GLfloat gc, int *fallTime){
  HitBox hb;
  hb.x = cam.x;
  hb.y = cam.y - gc;
  hb.z = cam.z;
  hb.width = 0.0;
  hb.height = 0.0;
  hb.depth = 0.0;
  
  CollisionGun cg;
  unsigned int nbox = boxes.size() - 1;
  while(nbox > -1){
    if(cg.boxCollision(hb, boxes[nbox])){
      fallTime = 0;
      return cam.y;
    }
  }

  ++*fallTime;
  GLfloat gv = (gc * ((GLfloat)*fallTime) * ((GLfloat)*fallTime)) / (60*60*60*60);

  if(gv > 195000) gv = 195000;
  
  cam.y -= gv;
  if(cam.y < lowest){
    cam.y = lowest;
    *fallTime = 0;
  }
  
  return cam.y;
}

void gravity(std::vector<HitBox> boxes, GLfloat lowest,
	       GLfloat gc, int *fallTime){
  //make boxes stack and/or fall
  //add center of gravity
}
