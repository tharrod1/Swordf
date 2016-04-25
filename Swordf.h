#pragma once
#include <vector>
#include <GL/glut.h>
#include "Camera.h"
#include "AudioPool.h"
#include "CollisionGun.h"
#include "Light.h"
#include "Object.h"
#include "Map.h"
#include "Physics.h"
#include "error.h"

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

void swordf_defaultOnPause(){
  //add escape option menu
}

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

  Swordf(){
    gameState = 0;
    paused = false;
    fallTime = 0;
    pauseFunc = swordf_defaultOnPause;
    pausePath = "pics/pause.png";
  }
  
  void calcDims(){
    windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
  }

  void togglePause(){
    paused = !paused;
    if(paused) pauseFunc();
  }

  void setOnPause(void (*func)(void)){
    pauseFunc = func;
  }

  void menu(char *path){
    togglePause();
    //set a background image
  }
  
  void initGL(int argc, char **argv, char *title){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(800, 600);  
    glutInitWindowPosition(50, 50); 
    glutCreateWindow(title);
  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);  
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    gluPerspective(45.0f, (GLfloat)windowWidth/(GLfloat)windowHeight, NEAR, FAR);
    msg("Swordf game initialized.\n", __DATE__, __TIME__, __FILE__, __LINE__);
  }

  void drawStr(char *str, void *font,
	       GLfloat x, GLfloat y, GLfloat z){
    char *c;
    glRasterPos3f(x, y, z);
    for(c=str; *c != '\0'; c++){
      glutBitmapCharacter(font, *c);
    }
  }

  void defaultOnMouseMove(int x, int y){
    camera.rotation += (x-windowWidth/2) * 0.001;
    fmod(camera.rotation, 2*PI);
  }

  void defaultOnAction(){

  }

  void defaultOnKey(Key key){
    switch(key){
    case KEY_A:
    case KEY_a:
      camera.down('a');
      break;
    case KEY_D:
    case KEY_d:
      camera.down('d');
      break;
    case KEY_W:
      camera.down('W');
      break;
    case KEY_w:
      camera.down('w');
      break;
    case KEY_S:
    case KEY_s:
      camera.down('s');
      break;
    case KEY_E:
    case KEY_e:
      defaultOnAction();
      break;
    case KEY_F:
    case KEY_f:
      glutFullScreen();
      break;
    case KEY_T:
    case KEY_t:
      camera.switchMode();
      break;
    case KEY_SPACE:
      camera.y += 8;
      break;
    case KEY_ESCAPE:
      menu(pausePath);
      break;
    default:
      break;
    }
  }

  void defaultOffKey(Key key){
    switch(key){
    case KEY_A:
    case KEY_a:
      camera.up('a');
      break;
    case KEY_D:
    case KEY_d:
      camera.up('d');
      break;
    case KEY_W:
      camera.up('W');
      break;
    case KEY_w:
      camera.up('w');
      break;
    case KEY_S:
    case KEY_s:
      camera.up('s');
      break;
    }
  }

  void defaultResize(GLsizei width, GLsizei height){
    if (height <= 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    
    glViewport(0.0f, 0.0f, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, NEAR, FAR);
    calcDims();
  }

  void defaultScroll(int delt){
    GLfloat dist = camera.distance;
    dist -= delt * 0.5;
    if(dist > 50 || dist < 1) return;
    camera.distance = dist;
  }

  void defaultLogic(){
    camera.setDims(windowWidth, windowHeight);
    camera.update();
    mainLight.update();

    if(camera.cameraMode == first){
      gluLookAt(camera.x, camera.y, camera.z,
		camera.getXLook(), camera.y, camera.getZLook(),
		0.0, camera.y, 0.0);
    }else{
      //scroll mouse weel changes distance
      gluLookAt(camera.getXLook(), camera.y, camera.getZLook(),
		camera.x, camera.y, camera.z,
		0.0, camera.y, 0.0);
    }
  }

  void drawCube(){
    glBegin(GL_QUADS);
    const GLfloat cyan[] = {0.0f, 0.8f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, cyan);
    
    glVertex3f( 1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f,  1.0f);
 
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
 
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);
 
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
 
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
 
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();
  }

  void gravity(std::vector<HitBox> boxes, GLfloat lowest, GLfloat gc){
    HitBox hb;
    hb.x = camera.x;
    hb.y = camera.y - gc;
    hb.z = camera.z;
    hb.width = 0.0;
    hb.height = 0.0;
    hb.depth = 0.0;
  
    unsigned int nbox = boxes.size() - 1;
    while(nbox > -1){
      if(collisionGun.boxCollision(hb, boxes[nbox])){
	fallTime = 0;
	return;
      }
    }

    ++fallTime;
    GLfloat gv = (gc * ((GLfloat)fallTime) * ((GLfloat)fallTime)) / (60*60*60*60);

    if(gv > 195000) gv = 195000;
  
    camera.y -= gv;
    if(camera.y < lowest){
      camera.y = lowest;
      fallTime = 0;
    }
  }
};
