#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <fstream>

static float largura, altura;
static float xMouse = 250, yMouse = 250;
static float rotation = 0;
static float posX, posY, posZ = 5;
int marsTexture;
int sunTexture;

void resize (int w, int h) {
  largura = w;
  altura = h;

  glViewport (0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
	// glOrtho(0, 500, 0, 500, -500, 500);
  gluPerspective(45, (float)w/(float)h, 1, 1000);
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
  glClearColor(0, 0, 0, 1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  marsTexture = carregaTextura("mars-small.jpg");
  sunTexture = carregaTextura ("solzin.jpg");
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
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

void createPlanet(float radius, int textura) {
  glBindTexture(GL_TEXTURE_2D, textura);
  glRotatef(rotation, 0, 1, 0);
  glRotatef(90, 1, 0, 0);
  createSphere(radius, 200, 200);
}

void draw () {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(posX, posY, posZ,
            posX, posY, 0,
            0, 1, 0);

	glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
    glTranslatef(0, 0, -10);
    createPlanet(1.5, sunTexture);

    glTranslatef(0, -10, 2);
    createPlanet(1.5, marsTexture);

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

void specialKeyInput (int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      posY += 0.1;
      break;

    case GLUT_KEY_DOWN:
      posY -= 0.1;
      break;
    
    case GLUT_KEY_LEFT:
      posX -= 0.1;
      break;

    case GLUT_KEY_RIGHT:
      posX += 0.1;
      break;
  }
}

void rodinha(int button, int dir, int x, int y) {
  if (button == 3) {
    posZ -= 0.1;
  }

  else if (button == 4) {
    posZ += 0.1;
  }
}

void rotacionaEsfera() {
  rotation += .1f;
  glutPostRedisplay();
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
  glutSpecialFunc(specialKeyInput);
  glutMouseFunc(rodinha);
  glutIdleFunc(rotacionaEsfera);
  glutMainLoop();
}