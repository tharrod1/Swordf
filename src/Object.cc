#include <sstream>
#include <fstream>
#include <vector>
#include <GL/glut.h>
#include "CollisionGun.h"
#include "error.h"
#include "Object.h"

Object::Object(){
  collidable = false;
}

bool Object::isCollidable(){
  return collidable;
}
  
void Object::setBoxes(std::vector<HitBox> boxes){
  hitBoxes = boxes;
  collidable = true;
}

std::vector<HitBox> Object::getBoxes(){
  return hitBoxes;
}
  
bool Object::load(char *objPath, char *mtlPath){
  std::ifstream objFile, mtlFile;
  objFile.open(objPath);
  if(!objFile){
    msg("Failed to open obj file.", ERRSTAMP); //no new line if person wants to add what file or other info
    return false;
  }

  mtlFile.open(mtlPath);
  if(!mtlFile){
    msg("Failed to open mtl file.", ERRSTAMP);
    return false;
  }

  std::string line, op;
    
  while(std::getline(objFile, line)){
    if(line == "" || line[0] == '#') continue;
    std::istringstream lineStream(line);
    lineStream >> op;
    Point p;
      
    if(op == "v"){
      sscanf(line.c_str(), "%*s %f %f %f", &p.x, &p.y, &p.z);
      verts.push_back(p);
    }else if(op == "vt"){
      sscanf(line.c_str(), "%*s %f %f", &p.x, &p.y);
      norms.push_back(p);
    }else if(op == "vn"){
      sscanf(line.c_str(), "%*s %f %f", &p.x, &p.y);
      uvs.push_back(p);
    }else if(op == "f"){
      unsigned int vals[8];
      sscanf(line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d",
	     &vals[0], &vals[1], &vals[2],
	     &vals[3], &vals[4], &vals[5],
	     &vals[6], &vals[7]);
      faces.push_back(vals);
    }else{
      //just going to treat as a comment
    }
  }
}

void Object::draw(){
  unsigned int sfaces = faces.size();
  glBegin(GL_TRIANGLES);
    
  for(int i = 0; i < sfaces; i++){
    //glColor3f for uv
    glVertex3f(verts[i].x, verts[i].y, verts[i].z);
  }

  glEnd();
}
