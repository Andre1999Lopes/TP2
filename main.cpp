#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/freeglut.h>

#include <iostream>
#include <fstream>
#include <cmath>

#include "global.h"
#include "utility.h"
#include "functions.cpp"

int main (int argc, char *argv[]) {
  glutInit(&argc, argv);
  SDL_Init(SDL_INIT_AUDIO);
	Mix_Init(MIX_INIT_MP3);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(1920, 1080);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Universe Sandbox³");
  setup();
  glutDisplayFunc(draw);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyInput);
  glutPassiveMotionFunc(posicionaCamera);
  glutSpecialFunc(specialKeyInput);
  glutMouseFunc(rodinha);
  glutIdleFunc(atualizaCena);
  glutMainLoop();
}