#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <fstream>
#include <cmath>

static float largura, altura;
static float xMouse = 250, yMouse = 250;
static float rotation = 0;
static float eyeX, eyeY, eyeZ = 150, centerX = 0, centerY = 0;
const float translationSpeed = 30;
int sunTexture;
int mercuryTexture;
int venusTexture;
int earthTexture;
int marsTexture;
int jupiterTexture;
int saturnTexture;
int uranusTexture;
int neptuneTexture;

const double pi = 3.14159265;
static double anguloMercurio = 0, anguloVenus = 0, anguloTerra = 0, anguloMarte = 0, anguloJupiter = 0;
static double anguloSaturno = 0, anguloUrano = 0, anguloNetuno = 0;

void resize (int w, int h) {
  largura = w;
  altura = h;

  glViewport (0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, (float)w/(float)h, 0.1, 2147483647);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int carregaTextura (const char *textureName) {
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

void posicionaCamera (int x, int y) {
    xMouse = x;
    yMouse = y;
    glutPostRedisplay();
}

void setup () {
  glClearColor(0, 0, 0, 1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  sunTexture = carregaTextura("imgs/solzin.jpg");
  mercuryTexture = carregaTextura("imgs/mercurio.png");
  venusTexture = carregaTextura("imgs/2k_venus_surface.jpg");
  earthTexture = carregaTextura("imgs/earth.png");
  marsTexture = carregaTextura("imgs/2k_mars.jpg");
  jupiterTexture = carregaTextura("imgs/2k_jupiter.jpg");
  saturnTexture = carregaTextura("imgs/2k_saturn.jpg");
  uranusTexture = carregaTextura("imgs/2k_uranus.jpg");
  neptuneTexture = carregaTextura("imgs/2k_neptune.jpg");

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

void planetTranslation () {

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

void createSun (float radius, float textura) {
  glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textura);
    glRotatef(rotation, 0, 1, 0);
    createSphere(radius, 200, 200);
  glPopMatrix();
}

void createPlanet (float radius, int textura, double angulo, float distanceFromSun) {
  glPushMatrix();
    // glTranslated(radius*cos(angulo),0,radius*sin(angulo));
    glBindTexture(GL_TEXTURE_2D, textura);
    glRotatef(rotation, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    glTranslatef(distanceFromSun*cos(angulo), 0, distanceFromSun*sin(angulo));
    createSphere(radius, 200, 200);
  glPopMatrix();

  // 360.0*diaAtual / 365.0
}

void draw () {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(eyeX, eyeY, eyeZ,
            centerX, centerY, 0,
            0, 1, 0);

	glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);

    createSun(50, sunTexture);

    createPlanet(1.5, mercuryTexture, anguloMercurio, 100);
    createPlanet(1, venusTexture, anguloVenus, 150);
    createPlanet(4, earthTexture, anguloTerra, 200);
    createPlanet(1.5, marsTexture, anguloMarte, 250);
    createPlanet(10, jupiterTexture, anguloJupiter, 350);
    createPlanet(8, saturnTexture, anguloSaturno, 450);
    createPlanet(5, uranusTexture, anguloUrano, 600);
    createPlanet(5.5, neptuneTexture, anguloNetuno, 750);

  glDisable(GL_TEXTURE_2D);
  glutSwapBuffers();
}

void keyInput (unsigned char key, int x, int y) {
	switch (key) {
    case 27:
			exit(0);
			break;

    // em teoria, era pra virar a camera ao redor do undo

    // case 'd':
    // case 'D':
    //   centerX += 0.1;
    //   break;

    // case 'a':
    // case 'A':
    //   centerX -= 0.1;
    //   break;
  }
}

void specialKeyInput (int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      eyeY += 1;
      centerY += 0.5;
      break;

    case GLUT_KEY_DOWN:
      eyeY -= 1;
      centerY -= 0.5;
      break;
    
    case GLUT_KEY_LEFT:
      eyeX -= 1;
      centerX -= 1;
      break;

    case GLUT_KEY_RIGHT:
      eyeX += 1;
      centerX += 1;
      break;
  }
}

void rodinha (int button, int dir, int x, int y) {
  if (button == 3) {
    eyeZ -= 1;
    if (eyeZ <= 0) {
      eyeZ = 0.000000001;
    }
  }

  else if (button == 4) {
    eyeZ += 1;
  }
}

void rotacionaEsfera () {
  rotation += .5f;
  anguloMercurio += 4.419/translationSpeed;
  anguloVenus += 1.624/translationSpeed;
  anguloTerra += 1/translationSpeed;
  anguloMarte += 0.532/translationSpeed;
  anguloJupiter += 0.084/translationSpeed;
  anguloSaturno += 0.034/translationSpeed;
  anguloUrano += 0.012/translationSpeed;
  anguloNetuno += 0.06/translationSpeed;

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