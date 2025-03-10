#include <gl/glut.h>
#include <math.h>

void gedung(){
//base gedung nya banh
	glBegin(GL_QUADS);
	glColor3f(0.1f, 0.1f, 0.1f);  
    glVertex2f(-0.8f, 0.7f); // Kiri atas
    glVertex2f(-0.55f, 0.7f);  // Kanan atas
    glVertex2f(-0.55f, 0.0f);  // Kanan bawah
    glVertex2f(-0.8f, 0.0f); // Kiri bawah

//jendela di 1,1
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);  
    glVertex2f(-0.75f, 0.55f); // Kiri atas
    glVertex2f(-0.70f, 0.55f);  // Kanan atas
    glVertex2f(-0.70f, 0.50f);  // Kanan bawah
    glVertex2f(-0.75f, 0.50f); // Kiri bawah
//1,2
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);  
    glVertex2f(-0.65f, 0.55f); // Kiri atas
    glVertex2f(-0.60f, 0.55f);  // Kanan atas
    glVertex2f(-0.60f, 0.50f);  // Kanan bawah
    glVertex2f(-0.65f, 0.50f); // Kiri bawah
//jendela bawahnya 2,2
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);  
    glVertex2f(-0.65f, 0.45f); // Kiri atas
    glVertex2f(-0.60f, 0.45f);  // Kanan atas
    glVertex2f(-0.60f, 0.40f);  // Kanan bawah
    glVertex2f(-0.65f, 0.40f); // Kiri bawah	
// sebelahnya yang bawahnya 2,1
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);  
    glVertex2f(-0.75f, 0.45f); // Kiri atas
    glVertex2f(-0.70f, 0.45f);  // Kanan atas
    glVertex2f(-0.70f, 0.40f);  // Kanan bawah
    glVertex2f(-0.75f, 0.40f); // Kiri bawah
//bawahnya 3,1
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);  
    glVertex2f(-0.65f, 0.35f); // Kiri atas
    glVertex2f(-0.60f, 0.35f);  // Kanan atas
    glVertex2f(-0.60f, 0.30f);  // Kanan bawah
    glVertex2f(-0.65f, 0.30f); // Kiri bawah
//kanannya 3,2
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);  
    glVertex2f(-0.75f, 0.35f); // Kiri atas
    glVertex2f(-0.70f, 0.35f);  // Kanan atas
    glVertex2f(-0.70f, 0.30f);  // Kanan bawah
    glVertex2f(-0.75f, 0.30f); // Kiri bawah
//4,1
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);  
    glVertex2f(-0.75f, 0.25f); // Kiri atas
    glVertex2f(-0.70f, 0.25f);  // Kanan atas
    glVertex2f(-0.70f, 0.20f);  // Kanan bawah
    glVertex2f(-0.75f, 0.20f); // Kiri bawah	
//4,2
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);  
    glVertex2f(-0.65f, 0.25f); // Kiri atas
    glVertex2f(-0.60f, 0.25f);  // Kanan atas
    glVertex2f(-0.60f, 0.20f);  // Kanan bawah
    glVertex2f(-0.65f, 0.20f); // Kiri bawah		
	glEnd();
    glFlush();
}

void drawGradientBackground() {
    glBegin(GL_QUADS);
    // Warna langit keemasan di bagian atas
    glColor3f(1.0f, 0.5f, 0.0f);  // Jingga
    glVertex2f(-1.0f, 1.0f); // Kiri atas
    glVertex2f(1.0f, 1.0f);  // Kanan atas
    // Warna merah keunguan di bagian bawah
    glColor3f(0.8f, 0.2f, 0.2f);  // Merah sunset
    glVertex2f(1.0f, 0.0f);  // Kanan bawah
    glVertex2f(-1.0f, 0.0f); // Kiri bawah
    glEnd();
    glFlush();
}

void Marka() {
    // Membuat satu garis marka
    glColor3f(1.0f, 1.0f, 1.0f); // Warna putih
    glBegin(GL_QUADS);
    glVertex2f(-0.15f, -0.7f); // Kiri atas
    glVertex2f(0.15f, -0.7f);  // Kanan atas
    glVertex2f(0.15f, -0.75f);  // Kanan bawah
    glVertex2f(-0.15f, -0.75f); // Kiri bawah
    glEnd();
}

void Tanah() {
	//ini rumah paling kanan
	glPushMatrix();
    glTranslatef(1.5f, -0.40f, 0.0f);
    gedung();
    glPopMatrix();
    glFlush();
    
    	glBegin(GL_QUADS);
	glColor3f(0.1f, 0.1f, 0.1f);  
    glVertex2f(0.7f, 0.3f); // Kiri atas
    glVertex2f(0.95f, 0.3f);  // Kanan atas
    glVertex2f(0.99f, 0.2f);  // Kanan bawah
    glVertex2f(0.665f, 0.2f); // Kiri bawah
    
	// Menggambar jalan (bagian hitam)
    glBegin(GL_QUADS);
    // Warna abu-abu di bagian atas jalan
    glColor3f(0.0f, 0.0f, 0.0f);  // Hitam
    glVertex2f(-1.0f, 0.0f); // Kiri tengah
    glVertex2f(1.0f, 0.0f);  // Kanan tengah
    // Warna hitam di bagian bawah jalan
    glColor3f(0.6f, 0.6f, 0.6f);  // Abu
    glVertex2f(1.0f, -3.0f);  // Kanan bawah
    glVertex2f(-1.0f, -3.0f); // Kiri bawah
    glEnd();
    
    // Menggambar garis putus-putus menggunakan translasi
    // Menggunakan stack untuk translasi marka jalan
    for (float x = -1.0f; x <= 1.0f; x += 0.5f) {
        glPushMatrix(); // Mulai stack
        glTranslatef(x, 0.0f, 0.0f); // Translasi ke posisi x
        Marka(); // Gambar satu garis marka
        glPopMatrix(); // Akhir stack
    }
    
    gedung();
    glPushMatrix();
    glTranslatef(0.3f, -0.10f, 0.0f);
    gedung();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6f, 0.0f, 0.0f);
    gedung();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.9f, -0.04f, 0.0f);
    gedung();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.3f, -0.2f, 0.0f);
    gedung();
    glPopMatrix();

	glPushMatrix();
    glTranslatef(1.2f, -0.10f, 0.0f);
    gedung();
    glPopMatrix();
    

}

void lampu() {
    //lampu
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(0.90f, -0.1f, 0.0f);//kanan bawah
    glVertex3f(0.70f, -0.08f, 0.0f);//kiri bawah
    glVertex3f(0.70f, -0.05f, 0.0f);//kiri atas
    glVertex3f(0.90f, -0.05f, 0.0f);//kanan atas
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.50f, 0.0f);
    glVertex3f(-0.90f, -0.1f, 0.0f);//kanan bawah
    glVertex3f(-0.70f, -0.08f, 0.0f);//kiri bawah
    glVertex3f(-0.70f, -0.05f, 0.0f);//kiri atas
    glVertex3f(-0.90f, -0.05f, 0.0f);//kanan atas
    glEnd();
    
    glFlush();
}

// Fungsi untuk menggambar lingkaran (roda)
void drawCircle(float cx, float cy, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);  // Titik pusat lingkaran
    
    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)segments;
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    
    glEnd();
}

// Fungsi untuk menggambar roda dengan jari-jari
void drawWheel(float x, float y, float radius) {
    // Simpan status matriks saat ini
    glPushMatrix();
    
    // Translasi ke posisi roda
    glTranslatef(x, y, 0.0f);
    
    // Rotasi roda (contoh penggunaan glRotated dengan sudut 0 - tidak berputar)
    glRotated(0.0, 0.0, 0.0, 1.0);
    
    // Gambar ban luar (hitam)
    glColor3f(0.2f, 0.2f, 0.2f);
    drawCircle(0.0f, 0.0f, radius, 30);
    
    // Gambar velg roda (abu-abu)
    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(0.0f, 0.0f, radius * 0.7f, 30);
    
    // Gambar jari-jari roda
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 8; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / 8.0f;
        float x = radius * 0.9f * cosf(theta);
        float y = radius * 0.9f * sinf(theta);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(x, y);
    }
    glEnd();
    
    // Pusat roda (lingkaran kecil)
    glColor3f(0.4f, 0.4f, 0.4f);
    drawCircle(0.0f, 0.0f, radius * 0.2f, 20);
    
    // Kembalikan status matriks
    glPopMatrix();
}

void Badan(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawGradientBackground();
    Tanah();
    
    // Menggunakan stack untuk mobil
    glPushMatrix();
    
    //atap
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(0.90f, 0.0f, 0.0f);//kanan bawah
    glVertex3f(-0.90f, 0.0f, 0.0f);//kiri bawah
    glVertex3f(-0.50f, 0.20f, 0.0f);//kiri atas
    glVertex3f(0.60f, 0.20f, 0.0f);//kanan atas
    glEnd();
    
    //jendela depan
    glColor3f(0.7f, 0.9f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-0.50f, 0.02f, 0.0f);//kanan bawah
    glVertex3f(-0.90f, 0.01f, 0.0f);//kiri bawah
    glVertex3f(-0.55f, 0.17f, 0.0f);//kiri atas
    glVertex3f(-0.45f, 0.17f, 0.0f);//kanan atas
    glEnd();
    
    //bodi
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(0.90f, -0.2f, 0.0f);//kanan bawah
    glVertex3f(-0.90f, -0.2f, 0.0f);//kiri bawah
    glVertex3f(-0.90f, 0.0f, 0.0f);//kiri atas
    glVertex3f(0.90f, 0.0f, 0.0f);//kanan atas
    glEnd();
    
    // Jendela kiri
    glColor3f(0.7f, 0.9f, 1.0f); // Warna biru muda
    glBegin(GL_QUADS);
    glVertex3f(-0.45f, 0.02f, 0.0f); // kiri bawah
    glVertex3f(-0.40f, 0.17f, 0.0f); // kiri atas
    glVertex3f(0.0f, 0.17f, 0.0f);   // kanan atas
    glVertex3f(0.05f, 0.02f, 0.0f);  // kanan bawah
    glEnd();
    
    // jendela kanan 
    glColor3f(0.7f, 0.9f, 1.0f); // Warna biru muda
    glBegin(GL_QUADS);
    glVertex3f(0.55f, 0.02f, 0.0f); // kiri bawah
    glVertex3f(0.50f, 0.17f, 0.0f); // kiri atas
    glVertex3f(0.10f, 0.17f, 0.0f); // kanan atas
    glVertex3f(0.15f, 0.02f, 0.0f); // kanan bawah
    glEnd();

    
    lampu();
    
    drawWheel(-0.6f, -0.2f, 0.12f);  // Roda depan
    drawWheel(0.6f, -0.2f, 0.12f);   // Roda belakang
    
    glPopMatrix();
    
    glutSwapBuffers();
    
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Mobil dengan Roda dan Jendela");
    glutDisplayFunc(Badan);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Latar belakang biru
    glutMainLoop();
    return 0;
}
