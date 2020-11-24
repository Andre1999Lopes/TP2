static float width, height;
static float xMouse = 250, yMouse = 250;
static float rotation = 0;
static float eyeX, eyeY = 100, eyeZ = 400, centerX = 0, centerY = 0, centerZ = 0;
static float translationSpeed = 100;
static float rotationSpeed = 2;
static bool sideLook = true;
static bool splash = true;

float matShine[] = { 50 }; 

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
static bool light = false;
static bool animation = true;

const double pi = 3.14159265;

static double rotationMercurio = 0, rotationVenus = 0, rotationTerra = 0, rotationMarte = 0, rotationJupiter = 0;
static double rotationSaturno = 0, rotationUrano = 0, rotationNetuno = 0, rotationSun = 0;

static double anguloMercurio = 0, anguloVenus = 0, anguloTerra = 0, anguloMarte = 0, JupiterAngle = 0;
static double anguloSaturno = 0, anguloUrano = 0, anguloNetuno = 0;