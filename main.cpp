#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/freeglut.h>

#include <iostream>
#include <fstream>
#include <cmath>

static float largura, altura;
static float xMouse = 250, yMouse = 250;
static float rotation = 0;
static float eyeX, eyeY, eyeZ = 1500, centerX = 0, centerY = 0;
static float translationSpeed = 100;
static float rotationSpeed = 2;
int sunTexture;
int mercuryTexture;
int venusTexture;
int earthTexture;
int marsTexture;
int jupiterTexture;
int saturnTexture;
int uranusTexture;
int neptuneTexture;
int saturnRingsTexture;
static bool biggerPlanets = false;
static bool orbits = false;
Mix_Music *music;

const double pi = 3.14159265;

static double rotationMercurio = 0, rotationVenus = 0, rotationTerra = 0, rotationMarte = 0, rotationJupiter = 0;
static double rotationSaturno = 0, rotationUrano = 0, rotationNetuno = 0;

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

  Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,4096);
	music=Mix_LoadMUS("songs/universe.mp3");

  sunTexture = carregaTextura("imgs/solzin.jpg");
  mercuryTexture = carregaTextura("imgs/mercurio.png");
  venusTexture = carregaTextura("imgs/2k_venus_surface.jpg");
  earthTexture = carregaTextura("imgs/earth.png");
  marsTexture = carregaTextura("imgs/2k_mars.jpg");
  jupiterTexture = carregaTextura("imgs/2k_jupiter.jpg");
  saturnTexture = carregaTextura("imgs/2k_saturn.jpg");
  uranusTexture = carregaTextura("imgs/2k_uranus.jpg");
  neptuneTexture = carregaTextura("imgs/2k_neptune.jpg");
  saturnRingsTexture = carregaTextura("imgs/2k_saturn_ring.png");

  Mix_PlayMusic(music,-1);
	Mix_VolumeMusic(32);

  // glEnable(GL_CULL_FACE);
  // glCullFace(GL_BACK);
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

void drawOrbit (float distanceFromSun, double angulo) {
  double numSides = 500;
  glBegin(GL_LINE_LOOP);
  glLineWidth(30.0f);
    for (int i=0; i<=numSides; i++) {
			double t=2*pi*i/numSides;
      glVertex3d(distanceFromSun*cos(t), 0 ,distanceFromSun*sin(t));
    }
  glEnd();
}

void createPlanet (float radius, int textura, double angulo, double rotation, float distanceFromSun) {
  glPushMatrix();
    distanceFromSun *= 10;
    glBindTexture(GL_TEXTURE_2D, textura);
    if (orbits)
      drawOrbit(distanceFromSun, angulo);
    glTranslatef(distanceFromSun*cos(-angulo), 0, distanceFromSun*sin(-angulo));
    glRotatef(rotation, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    if (biggerPlanets)
      createSphere(20*radius, 200, 200);
    else
      createSphere(radius, 200, 200);
  glPopMatrix();
}

void createRings (int distanceFromSun, double angulo, float red, float green, float blue, float inner, float outer, int anguloAnel) {
  glPushMatrix();
    distanceFromSun *= 10;
    glTranslatef(distanceFromSun*cos(-angulo), 0, distanceFromSun*sin(-angulo));
    glRotatef(-anguloAnel, 1, 0, 0);
    glColor3f(red, green, blue);
    GLUquadric *disk;
    disk = gluNewQuadric();
    if(biggerPlanets)
      gluDisk(disk, 20*inner, 20*outer, 600, 600);
    else
      gluDisk(disk, inner, outer, 600, 600);
  glPopMatrix();
}

void draw () {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(eyeX, eyeY, eyeZ,
            centerX, centerY, 0,
            0, 1, 0);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glEnable(GL_TEXTURE_2D);

    createSun(109, sunTexture);

    createPlanet(0.376, mercuryTexture, anguloMercurio, rotationMercurio, 38);
    createPlanet(0.949, venusTexture, anguloVenus, rotationVenus, 72);
    createPlanet(1, earthTexture, anguloTerra, rotationTerra, 100);
    createPlanet(0.563, marsTexture, anguloMarte, rotationMarte, 152);
    createPlanet(11.2, jupiterTexture, anguloJupiter, rotationJupiter, 520);
    createPlanet(9.46, saturnTexture, anguloSaturno, rotationSaturno, 958);
    createPlanet(4.06, uranusTexture, anguloUrano, rotationUrano, 1914);
    createPlanet(3.88, neptuneTexture, anguloNetuno, rotationNetuno, 3020);
    
  glDisable(GL_TEXTURE_2D);

  createRings(520, anguloJupiter, 0.32, 0.26, 0.20, 17.5, 18, 90);

  createRings(958, anguloSaturno, 0.52, 0.46, 0.39, 12, 15.5, 75);
  createRings(958, anguloSaturno, 0.52, 0.46, 0.39, 16, 20, 75);

  createRings(1914, anguloUrano, 0.63, 0.63, 0.63, 9.5, 9.8, 0);
  createRings(1914, anguloUrano, 0.63, 0.63, 0.63, 8.7, 8.9, 0);
  createRings(1914, anguloUrano, 0.63, 0.63, 0.63, 8, 8.2, 0);

  createRings(3020, anguloNetuno, 0.24, 0.24, 0.24, 8.1, 8.3, 20);
  createRings(3020, anguloNetuno, 0.24, 0.24, 0.24, 7.4, 7.8, 20);
  createRings(3020, anguloNetuno, 0.24, 0.24, 0.24, 5.5, 6.3, 20);

  glutSwapBuffers();
}

void keyInput (unsigned char key, int x, int y) {
	switch (key) {
    case 27:
			exit(0);
			break;

    case 'b':
    case 'B':
      if(biggerPlanets)
        biggerPlanets = false;
      else
        biggerPlanets = true;
      break;

    case 'o':
    case 'O':
      if (orbits)
        orbits = false;
      else
        orbits = true;
      break;

      case 43:
        if(translationSpeed > 10)
          translationSpeed -= 15;
        break;
      case 45:
        translationSpeed += 15;
        break;
        //não existe polígono com menos de 3 lados
        
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
      eyeY += 50;
      centerY += 50;
      break;

    case GLUT_KEY_DOWN:
      eyeY -= 50;
      centerY -= 50;
      break;
    
    case GLUT_KEY_LEFT:
      eyeX -= 50;
      centerX -= 50;
      break;

    case GLUT_KEY_RIGHT:
      eyeX += 50;
      centerX += 50;
      break;
  }
}

void rodinha (int button, int dir, int x, int y) {
  if (button == 3) {
    eyeZ -= 30;
    if (eyeZ <= 0) {
      eyeZ = 0.000000001;
    }
  }

  else if (button == 4) {
    eyeZ += 30;
  }
}

void rotacionaEsfera () {
  rotation += .1f;
  anguloMercurio += 4.419/translationSpeed;
  anguloVenus += 1.624/translationSpeed;
  anguloTerra += 1/translationSpeed;
  anguloMarte += 0.532/translationSpeed;
  anguloJupiter += 0.084/translationSpeed;
  anguloSaturno += 0.034/translationSpeed;
  anguloUrano += 0.012/translationSpeed;
  anguloNetuno += 0.006/translationSpeed;

  rotationMercurio += 0.01706/rotationSpeed;
  rotationVenus += 0.00411/rotationSpeed;
  rotationTerra += 1/rotationSpeed;
  rotationMarte += 0.97087/rotationSpeed;
  rotationJupiter += 2.43902/rotationSpeed;
  rotationSaturno += 2.22222/rotationSpeed;
  rotationUrano += 1.38888/rotationSpeed;
  rotationNetuno += 1.49253/rotationSpeed;

  glutPostRedisplay();
}

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
  glutIdleFunc(rotacionaEsfera);
  glutMainLoop();
}