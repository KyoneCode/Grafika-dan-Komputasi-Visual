#define GLUT_DISABLE_ATEXIT_HACK
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
double rx = 0.0;
double ry = 0.0;
float l[] = { 0.0, 80.0, 0.0 }; // koordinat sumber cahaya
float n[] = { 0.0, -40.0, 0.0 };
float e[] = { 0.0, -60.0, 0.0 };
void help();

// Fungsi untuk menggambar kubus dari 6 persegi (quads)
void drawCube(float size) {
    size = size / 2.0f;  // Setengah dari ukuran, sehingga ukuran total sesuai parameter
    
    // Sisi depan (front) - Z positif
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);  // Normal menghadap ke depan
        glVertex3f(-size, -size, size);  // kiri bawah
        glVertex3f(size, -size, size);   // kanan bawah
        glVertex3f(size, size, size);    // kanan atas
        glVertex3f(-size, size, size);   // kiri atas
    glEnd();
    
    // Sisi belakang (back) - Z negatif
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, -1.0f);  // Normal menghadap ke belakang
        glVertex3f(size, -size, -size);  // kanan bawah
        glVertex3f(-size, -size, -size); // kiri bawah
        glVertex3f(-size, size, -size);  // kiri atas
        glVertex3f(size, size, -size);   // kanan atas
    glEnd();
    
    // Sisi atas (top) - Y positif
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);  // Normal menghadap ke atas
        glVertex3f(-size, size, -size);  // kiri belakang
        glVertex3f(size, size, -size);   // kanan belakang
        glVertex3f(size, size, size);    // kanan depan
        glVertex3f(-size, size, size);   // kiri depan
    glEnd();
    
    // Sisi bawah (bottom) - Y negatif
    glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, 0.0f);  // Normal menghadap ke bawah
        glVertex3f(-size, -size, -size); // kiri belakang
        glVertex3f(size, -size, -size);  // kanan belakang
        glVertex3f(size, -size, size);   // kanan depan
        glVertex3f(-size, -size, size);  // kiri depan
    glEnd();
    
    // Sisi kanan (right) - X positif
    glBegin(GL_QUADS);
        glNormal3f(1.0f, 0.0f, 0.0f);  // Normal menghadap ke kanan
        glVertex3f(size, -size, size);   // depan bawah
        glVertex3f(size, -size, -size);  // belakang bawah
        glVertex3f(size, size, -size);   // belakang atas
        glVertex3f(size, size, size);    // depan atas
    glEnd();
    
    // Sisi kiri (left) - X negatif
    glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f);  // Normal menghadap ke kiri
        glVertex3f(-size, -size, -size); // belakang bawah
        glVertex3f(-size, -size, size);  // depan bawah
        glVertex3f(-size, size, size);   // depan atas
        glVertex3f(-size, size, -size);  // belakang atas
    glEnd();
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
    drawCube(1.0f);
    glPopMatrix();
    
    // Lampu kiri (oranye gelap)
    glColor3f(0.6f, 0.3f, 0.0f); // Warna oranye yang lebih gelap
    glPushMatrix();
    glTranslatef(-0.8f, -0.075f, 0.2f);
    glScalef(0.2f, 0.03f, 0.05f);
    drawCube(1.0f);
    glPopMatrix();
}

void Mobil3D() {
    // Bodi utama mobil (warna putih)
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f, -0.1f, 0.0f);
    glScalef(2.2f, 0.15f, 0.5f); // Lebih panjang dan sedikit lebih lebar
    drawCube(1.0f);
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
	    drawCube(1.0f);
	    glPopMatrix();
	    
	    glPushMatrix();
	    glTranslatef(-1.030f, -0.1f, -0.21f);
	    glScalef(0.15f, 0.05f, 0.1f);
	    drawCube(1.0f);
	    glPopMatrix();
    
    // Lampu belakang (merah, seperti di gambar)
	    glColor3f(1.0f, 0.0f, 0.0f);
	    glPushMatrix();
	    glTranslatef(1.030f, -0.1f, 0.21f);
	    glScalef(0.15f, 0.05f, 0.1f);
	    drawCube(1.0f);
	    glPopMatrix();
	    
	    glPushMatrix();
	    glTranslatef(1.030f, -0.1f, -0.21f);
	    glScalef(0.15f, 0.05f, 0.1f);
	    drawCube(1.0f);
	    glPopMatrix();
}

// obyek yang akan digambar
void draw()
{
glPushMatrix();
glScalef(50.0, 50.0, 50.0);
Mobil3D();
glPopMatrix();
//glutSolidTeapot(30.0); //Isi dengan salah satu saja, dan
//berilah obyek yang selain dalam tabel ini
//glutSolidTorus(20, 40, 20,10);
//glutWireSphere(60,10,10);
//glutSolidCube (40);
//glutSolidCone(20,50,40,50);
}
//membuat proyeksi bayangan
void glShadowProjection(float * l, float * e, float * n)
{
float d, c;
float mat[16];
d = n[0]*l[0] + n[1]*l[1] + n[2]*l[2];
c = e[0]*n[0] + e[1]*n[1] + e[2]*n[2] - d;

mat[0] = l[0]*n[0]+c; // membuat matrik. OpenGLmenggunakan kolom matrik
mat[4] = n[1]*l[0];
mat[8] = n[2]*l[0];
mat[12] = -l[0]*c-l[0]*d;
mat[1] = n[0]*l[1];
mat[5] = l[1]*n[1]+c;
mat[9] = n[2]*l[1];
mat[13] = -l[1]*c-l[1]*d;
mat[2] = n[0]*l[2];
mat[6] = n[1]*l[2];
mat[10] = l[2]*n[2]+c;
mat[14] = -l[2]*c-l[2]*d;
mat[3] = n[0];
mat[7] = n[1];
mat[11] = n[2];
mat[15] = -d;
glMultMatrixf(mat); // kalikan matrik
}
void render()
{
glClearColor(0.0,0.6,0.9,0.0);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glLightfv(GL_LIGHT0, GL_POSITION, l);
glDisable(GL_CULL_FACE);
glDisable(GL_LIGHTING);
glColor3f(1.0,1.0,0.0);
glBegin(GL_POINTS);
glVertex3f(l[0],l[1],l[2]);
glEnd();
glColor3f(0.8,0.8,0.8);
glBegin(GL_QUADS);
glNormal3f(0.0,1.0,0.0);
glVertex3f(-1300.0,e[1]-0.1, 1300.0);
glVertex3f( 1300.0,e[1]-0.1, 1300.0);
glVertex3f( 1300.0,e[1]-0.1,-1300.0);
glVertex3f(-1300.0,e[1]-0.1,-1300.0);
glEnd();
// gambar bayangan

glPushMatrix();
glRotatef(ry,0,1,0);
glRotatef(rx,1,0,0);
glEnable(GL_LIGHTING);
glColor3f(0.0,0.0,0.8);
draw();
glPopMatrix();
//sekarang gambar bayangan yang muncul
glPushMatrix();
glShadowProjection(l,e,n);
glRotatef(ry,0,1,0);
glRotatef(rx,1,0,0);
glDisable(GL_LIGHTING);
glColor3f(0.4,0.4,0.4);
draw();
glPopMatrix();
glutSwapBuffers();
}

void keypress(unsigned char c, int a, int b)
{
if ( c==27 ) exit(0);
else if ( c=='s' ) l[1]-=5.0;
else if ( c=='w' ) l[1]+=5.0;
else if ( c=='a' ) l[0]-=5.0;
else if ( c=='d' ) l[0]+=5.0;
else if ( c=='q' ) l[2]-=5.0;
else if ( c=='e' ) l[2]+=5.0;
else if ( c=='h' ) help();
}
void help()
{
printf("proyeksi contoh bayangan sebuah obyek teapot\n");
}
void idle()
{
rx+=0.1;
ry+=0.1;
render();
}
void resize(int w, int h)
{
glViewport(0, 0, w, h);

}
int main(int argc, char * argv[])
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowPosition(300,30);
glutCreateWindow("proyeksi bayangan");
glutReshapeFunc(resize);
glutReshapeWindow(400,400);
glutKeyboardFunc(keypress);
glutDisplayFunc(render);
glutIdleFunc(idle);
glEnable(GL_NORMALIZE);
glEnable(GL_LIGHTING);
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_DEPTH_TEST);
glEnable(GL_LIGHT0);
glEnable(GL_TEXTURE_2D);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60.0f, 1.0, 1.0, 400.0);
// Reset koordinat sebelum dimodifikasi/diubah
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0.0, 0.0, -150.0);
glutMainLoop();
return 0;
}
