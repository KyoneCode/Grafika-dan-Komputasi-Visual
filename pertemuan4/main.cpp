// Template untuk mainan objek 3D
// Kamera bisa maju mundur kiri kanan
// Sudah dilengkapi pencahayaan
// Sekarang pake texture
#include <math.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
float angle=0.0, deltaAngle = 0.0, ratio;
float x=0.0f,y=1.75f,z=15.0f; // posisi awal kamera
float lx=0.0f,ly=0.0f,lz=-1.0f;
float deltaMove = 0.0f;
int h, w;
int bitmapHeight=12;
void Reshape(int w1, int h1)
{
// Fungsi reshape
if(h1 == 0) h1 = 1;
w = w1;
h = h1;
ratio = 1.0f * w / h;
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glViewport(0, 0, w, h);
gluPerspective(45,ratio,0.1,1000);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(
x, y, z,
x + lx,y + ly,z + lz,
0.0f,1.0f,0.0f);
}
void orientMe(float ang)
{
// Fungsi ini untuk memutar arah kamera (tengok kiri/kanan)
lx = sin(ang);
lz = -cos(ang);
glLoadIdentity();
gluLookAt(x, y, z,
x + lx,y + ly,z + lz,
0.0f,1.0f,0.0f);
}
void moveMeFlat(float i) {
    // Fungsi ini untuk maju mundur kamera
    x = x + i * lx * 0.1f;  // Pergerakan di sumbu X
    z = z + i * lz * 0.1f;  // Pergerakan di sumbu Z

    glLoadIdentity();  // Reset transformasi modelview
    gluLookAt(x, y, z,       // Posisi kamera
              x + lx, y + ly, z + lz, // Titik yang dilihat kamera
              0.0f, 1.0f, 0.0f);  // Vektor atas (up)
}

void Rumput() {
    glColor3f(0.0f, 1.0f, 0.0f);  // Mengatur warna menjadi hijau

    // Menggambar bidang datar (plane) dengan ukuran besar untuk rumput
    glBegin(GL_QUADS);
    
    glVertex3f(-50.0f, 0.0f, -50.0f);
    glVertex3f(50.0f, 0.0f, -50.0f);
    glVertex3f(50.0f, 0.0f, 50.0f);
    glVertex3f(-50.0f, 0.0f, 50.0f);
    
    glEnd();  // Selesai menggambar bidang
}
// Fungsi untuk menggambar silinder 3D (untuk roda)
void drawCylinder(float radius, float height, int slices) {
    GLUquadricObj *quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluCylinder(quadObj, radius, radius, height, slices, 4);
    gluDeleteQuadric(quadObj);
}

// Fungsi untuk menggambar roda 3D
void drawWheel3D(float x, float y, float z, float radius, float thickness) {
    // Simpan status matriks saat ini
    glPushMatrix();
    
    // Translasi ke posisi roda
    glTranslatef(x, y, z);
    
    // Rotasi roda untuk posisi yang benar (roda menghadap ke samping)
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    
    // Ban luar (hitam)
    glColor3f(0.2f, 0.2f, 0.2f);
    drawCylinder(radius, thickness, 20);
    
    // Velg roda (abu-abu) - sisi depan
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    GLUquadricObj *frontDisk = gluNewQuadric();
    gluDisk(frontDisk, radius * 0.2f, radius, 20, 3);
    gluDeleteQuadric(frontDisk);
    glPopMatrix();
    
    // Velg roda (abu-abu) - sisi belakang
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, thickness);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    GLUquadricObj *backDisk = gluNewQuadric();
    gluDisk(backDisk, radius * 0.2f, radius, 20, 3);
    gluDeleteQuadric(backDisk);
    glPopMatrix();
    
    // Pusat roda (lingkaran kecil)
    glColor3f(0.4f, 0.4f, 0.4f);
    
    // Kembalikan status matriks
    glPopMatrix();
}

// Fungsi untuk menggambar lampu 3D (tidak menyala)
void lampu3D() {
    // Lampu kanan (merah gelap)
    glColor3f(0.6f, 0.0f, 0.0f); // Warna merah yang lebih gelap
    glPushMatrix();
    glTranslatef(0.8f, -0.075f, 0.2f);
    glScalef(0.2f, 0.03f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Lampu kiri (oranye gelap)
    glColor3f(0.6f, 0.3f, 0.0f); // Warna oranye yang lebih gelap
    glPushMatrix();
    glTranslatef(-0.8f, -0.075f, 0.2f);
    glScalef(0.2f, 0.03f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void Mobil3D() {
    // Bodi utama mobil (warna putih)
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f, -0.1f, 0.0f);
    glScalef(2.2f, 0.15f, 0.5f); // Lebih panjang dan sedikit lebih lebar
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Bagian atas mobil (atap) - bentuk trapesium (warna abu-abu)
    glColor3f(0.6f, 0.6f, 0.6f);
    glPushMatrix();
    glScalef(0.93f, 0.93f, 0.93f);
    glTranslatef(0.0f, -0.024f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.05f, 0.0f);
    glPopMatrix();
    // Gambar trapesium untuk atap mobil
    glBegin(GL_QUADS);
        // Sisi bawah trapesium
        glVertex3f(-0.9f, 0.0f, -0.24f);
        glVertex3f(0.9f, 0.0f, -0.24f);
        glVertex3f(0.9f, 0.0f, 0.24f);
        glVertex3f(-0.9f, 0.0f, 0.24f);
        
        // Sisi atas trapesium (lebih kecil untuk membentuk trapesium)
        glVertex3f(-0.8f, 0.15f, -0.22f);
        glVertex3f(0.8f, 0.15f, -0.22f);
        glVertex3f(0.8f, 0.15f, 0.22f);
        glVertex3f(-0.8f, 0.15f, 0.22f);
        
        // Sisi depan trapesium
        glVertex3f(-0.9f, 0.0f, -0.24f);
        glVertex3f(-0.9f, 0.0f, 0.24f);
        glVertex3f(-0.8f, 0.15f, 0.22f);
        glVertex3f(-0.8f, 0.15f, -0.22f);
        
        // Sisi belakang trapesium
        glVertex3f(0.9f, 0.0f, -0.24f);
        glVertex3f(0.9f, 0.0f, 0.24f);
        glVertex3f(0.8f, 0.15f, 0.22f);
        glVertex3f(0.8f, 0.15f, -0.22f);
        
        // Sisi kiri trapesium
        glVertex3f(-0.9f, 0.0f, 0.24f);
        glVertex3f(0.9f, 0.0f, 0.24f);
        glVertex3f(0.8f, 0.15f, 0.22f);
        glVertex3f(-0.8f, 0.15f, 0.22f);
        
        // Sisi kanan trapesium
        glVertex3f(-0.9f, 0.0f, -0.24f);
        glVertex3f(0.9f, 0.0f, -0.24f);
        glVertex3f(0.8f, 0.15f, -0.22f);
        glVertex3f(-0.8f, 0.15f, -0.22f);
    glEnd();
    
    glPopMatrix();
    
    // Jendela - warna biru muda (seperti di gambar)
    glColor3f(-0.5f, 0.7f, 0.8f);
    
    // Jendela depan (bentuk trapesium)
    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex3f(-0.85f, -0.05f, -0.23f);   // bawah kiri
        glVertex3f(-0.85f, -0.05f, 0.23f);    // bawah kanan
        glVertex3f(-0.8f, 0.05f, 0.22f);      // atas kanan
        glVertex3f(-0.8f, 0.05f, -0.22f);     // atas kiri
    glEnd();
    glPopMatrix();
    
    // Jendela belakang (bentuk trapesium)
    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex3f(0.85f, -0.05f, -0.23f);    // bawah kiri
        glVertex3f(0.85f, -0.05f, 0.23f);     // bawah kanan
        glVertex3f(0.8f, 0.05f, 0.22f);       // atas kanan
        glVertex3f(0.8f, 0.05f, -0.22f);      // atas kiri
    glEnd();
    glPopMatrix();
    
    // Jendela samping kiri depan (bentuk trapesium)
    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex3f(-0.7f, -0.05f, 0.24f);     // bawah kiri
        glVertex3f(-0.2f, -0.05f, 0.24f);     // bawah kanan
        glVertex3f(-0.25f, 0.05f, 0.22f);     // atas kanan
        glVertex3f(-0.7f, 0.05f, 0.22f);      // atas kiri
    glEnd();
    glPopMatrix();
    
    // Jendela samping kiri belakang (bentuk jajargenjang)
    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex3f(-0.1f, -0.05f, 0.24f);     // bawah kiri
        glVertex3f(0.7f, -0.05f, 0.24f);      // bawah kanan
        glVertex3f(0.65f, 0.05f, 0.22f);      // atas kanan
        glVertex3f(-0.15f, 0.05f, 0.22f);     // atas kiri
    glEnd();
    glPopMatrix();
    
    // Jendela samping kanan depan (bentuk trapesium)
    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex3f(-0.7f, -0.05f, -0.24f);    // bawah kiri
        glVertex3f(-0.2f, -0.05f, -0.24f);    // bawah kanan
        glVertex3f(-0.25f, 0.05f, -0.22f);    // atas kanan
        glVertex3f(-0.7f, 0.05f, -0.22f);     // atas kiri
    glEnd();
    glPopMatrix();
    
    // Jendela samping kanan belakang (bentuk jajargenjang)
    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex3f(-0.1f, -0.05f, -0.24f);    // bawah kiri
        glVertex3f(0.7f, -0.05f, -0.24f);     // bawah kanan
        glVertex3f(0.65f, 0.05f, -0.22f);     // atas kanan
        glVertex3f(-0.15f, 0.05f, -0.22f);    // atas kiri
    glEnd();
    glPopMatrix();
    
    // Roda-roda
   // Roda depan kanan
		glPushMatrix();
		    glTranslatef(-0.7f, -0.175f, 0.2495f);  // Pindah ke posisi roda
		    glRotatef(90, 0, 1, 0);               // Rotasi 90° di sumbu Y
		    drawWheel3D(0, 0, 0, 0.12f, 0.05f);   // Gambar roda di pusat koordinat lokal
		glPopMatrix();
		
		// Roda depan kiri
		glPushMatrix();
		    glTranslatef(-0.7f, -0.175f, -0.2495f);
		    glRotatef(90, 0, 1, 0);
		    drawWheel3D(0, 0, 0, 0.12f, 0.05f);
		glPopMatrix();
		
		// Roda belakang kanan
		glPushMatrix();
		    glTranslatef(0.7f, -0.175f, 0.2495f);
		    glRotatef(90, 0, 1, 0);
		    drawWheel3D(0, 0, 0, 0.12f, 0.05f);
		glPopMatrix();
		
		// Roda belakang kiri
		glPushMatrix();
		    glTranslatef(0.7f, -0.175f, -0.2495f);
		    glRotatef(90, 0, 1, 0);
		    drawWheel3D(0, 0, 0, 0.12f, 0.05f);
		glPopMatrix();
    // Lampu depan (oranye, seperti di gambar)
	    glColor3f(1.0f, 0.5f, 0.0f); 
	    glPushMatrix();
	    glTranslatef(-1.030f, -0.1f, 0.21f);
	    glScalef(0.15f, 0.05f, 0.1f);
	    glutSolidCube(1.0f);
	    glPopMatrix();
	    
	    glPushMatrix();
	    glTranslatef(-1.030f, -0.1f, -0.21f);
	    glScalef(0.15f, 0.05f, 0.1f);
	    glutSolidCube(1.0f);
	    glPopMatrix();
    
    // Lampu belakang (merah, seperti di gambar)
	    glColor3f(1.0f, 0.0f, 0.0f);
	    glPushMatrix();
	    glTranslatef(1.030f, -0.1f, 0.21f);
	    glScalef(0.15f, 0.05f, 0.1f);
	    glutSolidCube(1.0f);
	    glPopMatrix();
	    
	    glPushMatrix();
	    glTranslatef(1.030f, -0.1f, -0.21f);
	    glScalef(0.15f, 0.05f, 0.1f);
	    glutSolidCube(1.0f);
	    glPopMatrix();
}
void Grass() {
    // Fungsi untuk membuat rumput berupa segitiga yang menonjol dengan posisi acak
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float grassHeight = 0.3; // Tinggi rumput yang lebih rendah
    const int totalGrassBlades = 1000; // Jumlah total rumput
    
    // Warna hijau untuk rumput
    glColor3f(0.0, 0.6, 0.0);
    
    // Inisialisasi seed untuk random
    srand(12345); // Seed tetap agar posisi rumput konsisten antar frame
    
    // Membuat segitiga rumput dengan posisi acak
    for (int i = 0; i < totalGrassBlades; i++) {
        // Generate posisi acak dalam rentang area
        float x = X_MIN + ((float)rand() / RAND_MAX) * (X_MAX - X_MIN);
        float z = Z_MIN + ((float)rand() / RAND_MAX) * (Z_MAX - Z_MIN);
        
        // Variasi kecil untuk lebar rumput
        float width = 0.1 + ((float)rand() / RAND_MAX) * 0.1;
        
        // Menggambar segitiga rumput sederhana
        glBegin(GL_TRIANGLES);
            glVertex3f(x - width, 0, z);
            glVertex3f(x + width, 0, z);
            glVertex3f(x, grassHeight, z);
        glEnd();
    }
    
    // Tambahkan warna hijau gelap untuk "tanah"
    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(X_MIN, 0, Z_MIN);
        glVertex3f(X_MAX, 0, Z_MIN);
        glVertex3f(X_MAX, 0, Z_MAX);
        glVertex3f(X_MIN, 0, Z_MAX);
    glEnd();
}

void display() {
// Kalau move dan angle tidak nol, gerakkan kamera...
if (deltaMove)
moveMeFlat(deltaMove);
if (deltaAngle) {
angle += deltaAngle;
orientMe(angle);
}
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
Rumput();
Grass();
glColor3f(0.8f, 0.52f, 0.25f);

    glPushMatrix();
    glTranslatef(0.0f, 1.8f, 0.0f);  // Posisi lebih tinggi
    glScalef(6.0f, 6.0f, 6.0f);     // Make car bigger
    Mobil3D();
    glPopMatrix();
glutSwapBuffers();
glFlush();
}
void pressKey(int key, int x, int y) {
// Fungsi ini akan dijalankan saat tombol keyboard ditekan danbelum dilepas
// Selama tombol ditekan, variabel angle dan move diubah => kamerabergerak
switch (key) {
case GLUT_KEY_LEFT : deltaAngle = -0.0007f;break;
case GLUT_KEY_RIGHT : deltaAngle = 0.0007f;break;
case GLUT_KEY_UP : deltaMove = 0.07f;break;
case GLUT_KEY_DOWN : deltaMove = -0.07f;break;
}
}
void releaseKey(int key, int x, int y) {
// Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas
// Saat tombol dilepas, variabel angle dan move diset nol =>kamera berhenti
switch (key) {
case GLUT_KEY_LEFT :
if (deltaAngle < 0.0f)
deltaAngle = 0.0f;
break;
case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f)
deltaAngle = 0.0f;
break;
case GLUT_KEY_UP : if (deltaMove > 0.0f)
deltaMove = 0.0f;
break;
case GLUT_KEY_DOWN : if (deltaMove < 0.0f)
deltaMove = 0.0f;
break;
}
}
// Variable untuk pencahayaan

const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
void lighting(){
// Fungsi mengaktifkan pencahayaan
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
glEnable(GL_LIGHT0);
glEnable(GL_NORMALIZE);
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_LIGHTING);
glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}
void init(void)
{
glEnable (GL_DEPTH_TEST);
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
}
int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(100,100);
glutInitWindowSize(640,480);
glutCreateWindow("3D Lighting");
glutIgnoreKeyRepeat(1); // Mengabaikan key repeat (saat tombolkeyboard dipencet terus)
glutSpecialFunc(pressKey);
glutSpecialUpFunc(releaseKey);
glutDisplayFunc(display);

glutIdleFunc(display); // Fungsi display-nya dipanggil terus-menerus

glutReshapeFunc(Reshape);
lighting();
init();
glutMainLoop();
return(0);
}
