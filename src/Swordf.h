#pragma once
#include <vector>
#include <GL/glut.h>
#include "Camera.h"
#include "AudioPool.h"
#include "CollisionGun.h"
#include "Light.h"
#include "Object.h"
#include "Map.h"

#define KEY_A 65
#define KEY_a 97

#define KEY_d 100
#define KEY_D 68

#define KEY_e 101
#define KEY_E 69

#define KEY_f 102
#define KEY_F 70

#define KEY_S 83
#define KEY_s 115

#define KEY_W 87
#define KEY_w 119

#define KEY_T 84
#define KEY_t 116

#define KEY_SPACE 32
#define KEY_ESCAPE 27

#define NEAR 0.1
#define FAR 1000.0

typedef unsigned char Key;

void swordf_defaultOnPause();

class Swordf {
 private:
  int fallTime; //used for camera
  bool paused;
  void (*pauseFunc)(void);
  
 public:
  Camera camera;
  AudioPool audioPool;
  Light mainLight;
  LightPool lightPool;
  CollisionGun collisionGun;
  ObjectPool objectPool;
  int windowWidth, windowHeight; //makes sense to be unsigned, but glutGet returns and int
  unsigned int gameState;
  char *pausePath;

  Swordf();
  ~Swordf();
  void calcDims();
  void togglePause();
  void setOnPause(void (*func)(void));
  void menu(char *path);
  void initGL(int argc, char **argv, char *title);
  void drawStr(char *str, void *font,
	       GLfloat x, GLfloat y, GLfloat z);
  void defaultOnMouseMove(int x, int y);
  void defaultScroll(int delt);
  void defaultOnAction();
  void defaultOnKey(Key key);
  void defaultOffKey(Key key);
  void defaultResize(GLsizei width, GLsizei height);
  void defaultLogic();
  void drawCube();
  void gravity(std::vector<HitBox> boxes, GLfloat lowest, GLfloat gc);
};
