#pragma once
#include <vector>
#include <GL/glut.h>

class Script {
 private:
  std::vector<GLfloat> fVars;
  std::vector<int> iVars;
  std::vector<unsigned int> uiVars, labelLines;
  std::vector<char*> strVars, labels;
  unsigned int line;
  
 public:
  Script(){
    line = 0;
  }

  ~Script(){
    iVars.clear();
    uiVars.clear();
    labelLines.clear();

    unsigned int s = strVars.size();
    for(unsigned int i = 0; i < s; i++) free(strVars[i]);
    s = labels.size();
    for(unsigned int i = 0; i < s; i++) free(labels[i]);
    
    strVars.clear();
    labels.clear();
  }
  
  void evalStr(char *data){
    switch(data[0]){
    case '#':
      return;
    case ':':
      unsigned int datalen = strlen(data);
      char *lab = (char*)malloc(datalen);
      for(unsigned int i = 0; i < datalen - 1; i++) lab[i] = data[i+1];
      labels.push_back(lab);
      labelLines.push_back(line);
      break;
    default:
      //parse
      break;
    }
  }
  
  void evalFile(char *path){
    std::ifstream file(path);
    std::string lineData;
    while(std::getline(file, lineData)){
      evalStr((char*)line.c_str());
      ++line;
    }
  }
};
