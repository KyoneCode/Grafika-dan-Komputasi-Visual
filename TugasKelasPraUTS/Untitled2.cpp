#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>

float angleX = 0.0f;
float angleY = 0.0f;
bool keyW = false, keyS = false, keyA = false, keyD = false;
void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
}
void KotakBantu(float panjang, float lebar, float tinggi, float r, float g, float b) {
    float px = panjang / 2.0f;
    float py = lebar / 2.0f;
    float pz = tinggi / 2.0f;

    glColor3f(r, g, b);
    glBegin(GL_LINES);

    // 8 titik sudut balok
    float x0 = -px, x1 = px;
    float y0 = -py, y1 = py;
    float z0 = -pz, z1 = pz;

    // 12 edges (garis) dari balok/kubus

    // Depan
    glVertex3f(x0, y0, z1); glVertex3f(x1, y0, z1);
    glVertex3f(x1, y0, z1); glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1, z1); glVertex3f(x0, y1, z1);
    glVertex3f(x0, y1, z1); glVertex3f(x0, y0, z1);

    // Belakang
    glVertex3f(x0, y0, z0); glVertex3f(x1, y0, z0);
    glVertex3f(x1, y0, z0); glVertex3f(x1, y1, z0);
    glVertex3f(x1, y1, z0); glVertex3f(x0, y1, z0);
    glVertex3f(x0, y1, z0); glVertex3f(x0, y0, z0);

    // Sisi sambung depan-belakang
    glVertex3f(x0, y0, z0); glVertex3f(x0, y0, z1);
    glVertex3f(x1, y0, z0); glVertex3f(x1, y0, z1);
    glVertex3f(x1, y1, z0); glVertex3f(x1, y1, z1);
    glVertex3f(x0, y1, z0); glVertex3f(x0, y1, z1);

    glEnd();
}

void balok3D(float panjang, float lebar, float tinggi, float r, float g, float b) {
    float px = panjang / 2.0f;
    float py = lebar / 2.0f;
    float pz = tinggi / 2.0f;

    glColor3f(r, g, b);
    glBegin(GL_QUADS);

    // DEPAN
    glVertex3f(-px, -py,  pz);
    glVertex3f( px, -py,  pz);
    glVertex3f( px,  py,  pz);
    glVertex3f(-px,  py,  pz);

    // BELAKANG
    glVertex3f(-px, -py, -pz);
    glVertex3f(-px,  py, -pz);
    glVertex3f( px,  py, -pz);
    glVertex3f( px, -py, -pz);

    // ATAS
    glVertex3f(-px,  py, -pz);
    glVertex3f(-px,  py,  pz);
    glVertex3f( px,  py,  pz);
    glVertex3f( px,  py, -pz);

    // BAWAH
    glVertex3f(-px, -py, -pz);
    glVertex3f( px, -py, -pz);
    glVertex3f( px, -py,  pz);
    glVertex3f(-px, -py,  pz);

    // KIRI
    glVertex3f(-px, -py, -pz);
    glVertex3f(-px, -py,  pz);
    glVertex3f(-px,  py,  pz);
    glVertex3f(-px,  py, -pz);

    // KANAN
    glVertex3f( px, -py, -pz);
    glVertex3f( px,  py, -pz);
    glVertex3f( px,  py,  pz);
    glVertex3f( px, -py,  pz);

    glEnd();
}
void laptop(){
	glPushMatrix();//frame bawah
	glTranslatef(0.0f, -1.5f, 0.0f);
	balok3D(5.0f, 0.3f, 0.09f, 0.3f, 0.3f, 0.3f);
	glPopMatrix();
	
	glPushMatrix();//frame atas
	glTranslatef(0.0f, 1.5f, 0.0f);
	balok3D(5.0f, 0.3f, 0.09f, 0.3f, 0.3f, 0.3f);
	glPopMatrix();
	
	glPushMatrix();//frame kanan
	glTranslatef(2.5f, 0.0f, 0.0f);
	balok3D(0.2f, 3.15f, 0.09f, 0.3f, 0.3f, 0.3f);
	glPopMatrix();
	
	glPushMatrix();//frame kiri
	glTranslatef(-2.5f, 0.0f, 0.0f);
	balok3D(0.2f, 3.15f, 0.09f, 0.3f, 0.3f, 0.3f);
	glPopMatrix();
	
	glPushMatrix();//layar ( sebenernya gaperlu push pop sih, biar tebel aja :"v
	balok3D(5.0f, 3.15f, 0.01f, 0.1f, 0.8f, 1.0f);
	glPopMatrix();
	
	glPushMatrix();//layarbelakang
	glTranslatef(0.0f, 0.0f, -0.01f);
	balok3D(5.0f, 3.15f, 0.01f, 0.3f, 0.3f, 0.3f);
	glPopMatrix();
	
	glPushMatrix();//Logo belakang
	glTranslatef(0.0f, 0.0f, -0.01f);
	glRotatef(45, 0.0f, 0.0f, 1.0f);
	balok3D(1.0f, 1.0f, 0.0101f, 0.9f, 0.3f, 0.9f);//ini biar mengkilat kaya hologram gitu :"v
	balok3D(1.0f, 1.0f, 0.01011f, 0.9f, 0.25f, 0.25f);
	glPopMatrix();
	
	glPushMatrix();//logo keyboard
	glTranslatef(2.3f, -1.63f, 2.35f);
	glRotatef(45, 0.0f, 1.0f, 0.0f);
	balok3D(0.25f, 0.1f, 0.25f, 0.9f, 0.3f, 0.9f);//ini biar mengkilat kaya hologram gitu :"v
	balok3D(0.25f, 0.11f, 0.25f, 0.9f, 0.25f, 0.25f);
	glPopMatrix();
	
	glPushMatrix();//keyboard base
	glTranslatef(0.0f, -1.7f, 1.65f);
	balok3D(5.2f, 0.20f, 3.2f, 0.33f, 0.33f, 0.33f);
	glPopMatrix();
	
	glPushMatrix();//keyboard
	glTranslatef(0.0f, -1.69f, 1.26f);
	balok3D(4.9f, 0.2f, 1.5f, 0.6f, 0.6f, 0.6f);
	glPopMatrix();
	
	glPushMatrix();//touchpad
	glTranslatef(-0.3f, -1.69f, 2.6f);
	balok3D(1.4f, 0.2f, 0.8f, 0.6f, 0.6f, 0.6f);
	glPopMatrix();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);       // Geser ke belakang agar terlihat
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // rotasi atas-bawah
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // rotasi kiri-kanan
    // Gambar 
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.48f);
    glScalef(0.3f, 0.3f, 0.3f);
	laptop();
    glPopMatrix();
    KotakBantu(1.6f, 1.07f, 1.0f, 1.0f, 0.7f, 0.2f);
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void keyboardDown(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': keyW = true; break;
        case 's': keyS = true; break;
        case 'a': keyA = true; break;
        case 'd': keyD = true; break;
        case 27: exit(0); break; // Esc
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': keyW = false; break;
        case 's': keyS = false; break;
        case 'a': keyA = false; break;
        case 'd': keyD = false; break;
    }
}
void update(int value) {
    if (keyW) angleX -= 1.0f;
    if (keyS) angleX += 1.0f;
    if (keyA) angleY -= 1.0f;
    if (keyD) angleY += 1.0f;

    glutPostRedisplay(); // refresh tampilan
    glutTimerFunc(16, update, 0); // panggil ulang tiap 16ms (~60 FPS)
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Kubus 3D - OpenGL GLUT");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}

