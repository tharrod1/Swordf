//hoi racherd it's tomas
#include <vector>
#include <algorithm>
#include <math.h>
#include <GL/glut.h>
#include "CollisionGun.h"

HitBox::HitBox(){}
HitBox::HitBox(GLfloat ix, GLfloat iy, GLfloat iz,
	       GLfloat iw, GLfloat ih, GLfloat id){
  x = ix;
  y = iy;
  z = iz;
  width = iw;
  height = ih;
  depth = id;
}

HitBox HitBox::clone(){
  HitBox hb(x, y, z, width, height, depth);
  return hb;
}

bool CollisionGun::boxCollision(HitBox hb1, HitBox hb2){
  if(hb1.x <= hb2.x <= hb1.x + hb1.width){
    if(hb1.y <= hb2.y <= hb1.y + hb1.height){
      if(hb1.z <= hb2.z <= hb1.z + hb1.depth){
	return true;
      }else if(hb2.z <= hb1.z <= hb2.z + hb2.depth){
	return true;
      }
    }else if(hb2.y <= hb1.y <= hb2.y + hb2.height){
      if(hb1.z <= hb2.z <= hb1.z + hb1.depth){
	return true;
      }else if(hb2.z <= hb1.z <= hb2.z + hb2.depth){
	return true;
      }
    }
  }else if(hb2.x <= hb1.x <= hb2.x + hb2.width){
    if(hb1.y <= hb2.y <= hb1.y + hb1.height){
      if(hb1.z <= hb2.z <= hb1.z + hb1.depth){
	return true;
      }else if(hb2.z <= hb1.z <= hb2.z + hb2.depth){
	return true;
      }
    }else if(hb2.y <= hb1.y <= hb2.y + hb2.height){
      if(hb1.z <= hb2.z <= hb1.z + hb1.depth){
	return true;
      }else if(hb2.z <= hb1.z <= hb2.z + hb2.depth){
	return true;
      }
    }
  }
    
  return false;
}

bool CollisionGun::linearShot(HitBox hb){
  const GLfloat x1 = hb.x;
  const GLfloat z1 = hb.z;
  const GLfloat y1 = hb.y;
    
  const GLfloat x2 = hb.x+hb.width;
  const GLfloat z2 = hb.z+hb.depth;
  const GLfloat y2 = hb.y+hb.height;

  double distx, distz;
  double testAngle;
  
  //check if will hit horizontally
  //may need to use % math.pi/2
  distx = x1 - x;
  distz = z1 - z;
  testAngle = atan(distx/distz);
  if(yr < testAngle) return false;
    
  distx = x2 - x;
  distz = z2 - z;
  testAngle = atan(distx/distz);
  if(yr > testAngle) return false;

  if(y < y1 || y > y2) return false;
    
  return true;
}

bool CollisionGun::linearShot(HitBox hb, Bullet b){
  const GLfloat x1 = hb.x;
  const GLfloat z1 = hb.z;
  const GLfloat y1 = hb.y;
    
  const GLfloat x2 = hb.x+hb.width;
  const GLfloat z2 = hb.z+hb.depth;
  const GLfloat y2 = hb.y+hb.height;

  double distx, distz;
  double testAngle;
  
  //check if will hit horizontally
  //may need to use % math.pi/2
  distx = x1 - x;
  distz = z1 - z;
  testAngle = atan(distx/distz);
  if(yr < testAngle) return false;
    
  distx = x2 - x;
  distz = z2 - z;
  testAngle = atan(distx/distz);
  if(yr > testAngle) return false;

  if(y < y1 || y > y2) return false;
    
  return true;
}

void CollisionGun::bulletShot(GLfloat v, GLfloat g){
  Bullet b;
  b.x = x;
  b.y = y;
  b.z = z;
  b.yr = yr;
  b.v = v;
  b.g = g;
  bulletPool.push_back(b);
}

std::vector<unsigned int> CollisionGun::update(std::vector<HitBox> boxes){
  unsigned int bullets = bulletPool.size() - 1;
  unsigned int lbox = boxes.size() - 1;
  unsigned int lboxc = lbox;
  unsigned int lbh;
  std::vector<unsigned int> boxHit, boxHitT, boxHitC, boxHitB, boxHitR;
  GLfloat oldyr;
#pragma loop(hint_parallel(0))
  while(bullets > -1){
    Bullet cb = bulletPool[bullets];
    while(lbox > -1){
      if(linearShot(boxes[lbox], cb)){
	boxHit.push_back(lbox);
      }

      --lbox;
    }

      
    lbox = lboxc;
    cb.x += cb.v*sin(cb.yr);
    cb.y -= cb.g;
    cb.z -= cb.v*cos(cb.yr);
      
    while(lbox > -1){
      if(linearShot(boxes[lbox], cb)){
	boxHitT.push_back(lbox);
      }

      --lbox;
    }

    boxHitC = (boxHit.size() < boxHitT.size()) ? boxHit : boxHitT;
    boxHitB = (boxHit.size() > boxHitT.size()) ? boxHit : boxHitT;
    lbh = boxHitC.size() - 1;
    while(lbh > -1){
      if(std::find(boxHitC.begin(), boxHitC.end(), boxHitB[lbh]) != boxHitC.end()){
	boxHitR.push_back(boxHitB[lbh]);
      }

      --lbh;
    }
      
    lbox = lboxc;
    --bullets;
  }

  return boxHitR;
}
