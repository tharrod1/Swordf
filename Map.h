#pragma once
#include <vector>
#include <GL/glut.h>
#include "CollisionGun.h"
#include "error.h"

class Map {
 private:
  bool dataSec;
  
 public:
  std::vector<HitBox> hitboxes;

  Map(){
    dataSec = false;
  }
  
  void fromString(char *data){
    if(!dataSec){
      if(data[0] == ':') dataSec = true;
    }
    
    unsigned int datalen = strlen(data);
    for(unsigned int i = 0; i < datalen; i++){
      if(dataSec){

      }else{
	
      }
    }
  }

  void fromString(std::string data){
    fromString((char*)data.c_str());
  }
  
  void fromFile(char *path){
    //fromstring each line
  }
};
