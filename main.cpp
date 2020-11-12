#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <fstream>

static float largura, altura;
static float xMouse = 250, yMouse = 250;
static float rotation = 0;
int marsTexture;

void resize (int w, int h) {
  largura = w;
  altura = h;

  glViewport (0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
	// glOrtho(0, 500, 0, 500, -500, 500);
  gluPerspective(60, (float)w/(float)h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int carregaTextura(const char *textureName) {
  int loadedTexture = SOIL_load_OGL_texture(
		textureName,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
  if(loadedTexture == 0){
    std::cout << "Problema ao carregar textura: " << SOIL_last_result() << std::endl;
  }

  return loadedTexture;
}

void posicionaCamera(int x, int y) {
    xMouse = x;
    yMouse = y;;
    glutPostRedisplay();
}

void setup () {
  glClearColor(1, 1, 1, 1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  marsTexture = carregaTextura("mars-small.jpg");
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

void createPlanet (int radius, int stacks, int columns) {
  
}

void createSphere (int radius, int stacks, int columns) {
  // cria uma quádrica
  GLUquadric* quadObj = gluNewQuadric();
  // estilo preenchido... poderia ser GLU_LINE, GLU_SILHOUETTE
  // ou GLU_POINT
  gluQuadricDrawStyle(quadObj, GLU_FILL);
  // chama 01 glNormal para cada vértice.. poderia ser
  // GLU_FLAT (01 por face) ou GLU_NONE
  gluQuadricNormals(quadObj, GLU_SMOOTH);
  // chama 01 glTexCoord por vértice
  gluQuadricTexture(quadObj, GL_TRUE);
  // cria os vértices de uma esfera
  gluSphere(quadObj, radius, stacks, columns);
  // limpa as variáveis que a GLU usou para criar
  // a esfera
  gluDeleteQuadric(quadObj);
}

void createPlanet(float radius) {
  glRotatef(0, 0, 1, 0);
  glRotatef(90, 1, 0, 0);
  createSphere(radius, 200, 200);
}

void draw () {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(1*(xMouse-largura/2)/(largura/16), -1*(yMouse-altura/2)/(altura/16) + 3, 5,
              0, 0, 0,
              0, 1, 0);

	glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, marsTexture);
  glPushMatrix();
    createPlanet(1.5);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
  glutSwapBuffers();
}

void keyInput (unsigned char key, int x, int y) {
	switch (key) {
    case 27:
			exit(0);
			break;
	}
}

void rotacionaEsfera(){

}

int main (int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition (100, 100);
  glutCreateWindow("Luz e Materiais");
  setup();
  glutDisplayFunc(draw);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyInput);
  glutPassiveMotionFunc(posicionaCamera);
  // glutSpecialFunc(specialKeyInput);
  glutIdleFunc(rotacionaEsfera);
  glutMainLoop();
}