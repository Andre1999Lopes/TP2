void resize (int w, int h);
int carregaTextura (const char *textureName);
void posicionaCamera (int x, int y);
void setup ();
void createSphere (int radius, int stacks, int columns);
void createSun (float radius, float textura, float rotation);
void drawOrbit (float distanceFromSun, double angulo);
void createPlanet (float radius, int textura, double angulo, double rotation, float distanceFromSun);
void createRings (int distanceFromSun, double angulo, float red, float green, float blue, float inner, float outer, int anguloAnel);
void draw ();
void keyInput (unsigned char key, int x, int y);
void specialKeyInput (int key, int x, int y);
void rodinha (int button, int dir, int x, int y);
void rotacionaEsfera ();
void atualizaCena ();
