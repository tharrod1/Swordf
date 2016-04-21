#pragma once
#include <vector>
#include <GL/glut.h>

class Script {
 private:
  std::vector<GLfloat> fVars;
  std::vector<int> iVars;
  std::vector<unsigned int> uiVars, labelLines;
  std::vector<char*> strVars, labels;
  
 public:
  Script(){
    
  }

  ~Script(){
    //clear vectors
  }
  
  void evalStr(char *data){
    switch(data[0]){
    case '#':
      return;
    case ':':
      //set label
      break;
    default:
      //parse
      break;
    }
  }
  
  void evalFile(char *file){
    
  }
};
