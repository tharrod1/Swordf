#include <string.h>
#include <sstream>
#include <vector>
#include <GL/glut.h>
#include "AudioPool.h"
#include "CollisionGun.h"
#include "Light.h"
#include "Object.h"
#include "error.h"
#include "Map.h"

MapToken::MapToken(){}

MapToken *MapToken::clone(){
  MapToken *mt = new MapToken();
  mt->identifier = identifier;
  mt->collidable = collidable;
  mt->isFloor = isFloor;
  mt->path = path; //make sure this stays safe
  mt->hitBox = hitBox.clone();
  mt->rotation = rotation;
  return mt;
}
  
MapToken::~MapToken(){
  free(path);
}

unsigned int Map::nextSpace(char *str, unsigned int start){
  while(str[start++] != ' ');
  return --start;
}

char *Map::slice(char *str, unsigned int start, unsigned int end){
  char *ret = (char*)malloc((end - start) + 1);
  int i = 0;
  while(i < (end - start)){
    str[i] = str[start+i];
    i++;
  }

  return ret;
}
  
Map::Map(AudioPool *ap, LightPool *lp, ObjectPool *op){
  dataSec = false;
  audioPool = ap;
  lightPool = lp;
  objectPool = op;
}

Map::~Map(){
  unsigned int tokss = toks.size();
  for(unsigned int i = 0; i < tokss; i++) delete toks[i];
  tokss = updateToks.size();
  for(unsigned int i = 0; i < tokss; i++) delete updateToks[i];

  toks.clear();
  updateToks.clear();
}
  
void Map::fromString(char *data){
  if(data[0] == '#') return;
    
  if(!dataSec){
    if(data[0] == ':') dataSec = true;
    return; //no data should be placed on this line
  }
    
  unsigned int datalen = strlen(data);
  for(unsigned int i = 0; i < datalen; i++){
    if(dataSec){
      MapToken *mt = new MapToken;
      if(data[2] == '1'){
	mt->collidable = true;
      }else{
	mt->collidable = false;
      }

      if(data[4] == '1'){
	mt->isFloor = true;
      }else{
	mt->isFloor = false;
      }

      unsigned int ns = nextSpace(data, 6);
      char *path = slice(data, 6, ns-1);
      mt->path = path;

      unsigned int ns2 = nextSpace(data, ns+1);
      char *num = slice(data, ns+1, ns2-1);
      ns = ns2;
      mt->hitBox.width = atof(num);

      ns2 = nextSpace(data, ns+1);
      num = slice(data, ns+1, ns2-1);
      ns = ns2;
      mt->hitBox.height = atof(num);

      ns2 = nextSpace(data, ns+1);
      num = slice(data, ns+1, ns2-1);
      ns = ns2;
      mt->hitBox.depth = atof(num);

      ns2 = nextSpace(data, ns+1);
      num = slice(data, ns+1, ns2-1);
      ns = ns2;
      mt->hitBox.y = atof(num);

      ns2 = nextSpace(data, ns+1);
      num = slice(data, ns+1, ns2-1);
      ns = ns2;
      mt->rotation = atof(num);

      toks.push_back(mt);
      free(num);
    }else{
      unsigned int linelen = strlen(data), tokss = toks.size();
      for(int i = 0; i < linelen; i++){
	for(int ti = 0; ti < toks.size(); i++){
	  if(toks[ti]->identifier == data[i]){
	    MapToken *mt = toks[ti]->clone();
	    mt->hitBox.x = x;
	    mt->hitBox.z = z;
	    updateToks.push_back(mt);
	  }
	}
      }
    }
  }
}
  
void Map::fromString(std::string data){
  fromString((char*)data.c_str());
}
  
void Map::fromFile(char *path){
  std::ifstream file(path);
  std::string line;
  while(std::getline(file, line)){
    fromString((char*)line.c_str());
    z += TOKEN_DEPTH;
  }
}

void Map::load(){

}
  
void Map::update(){
    
}
