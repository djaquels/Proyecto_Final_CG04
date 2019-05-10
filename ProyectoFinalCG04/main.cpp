#include "Main.h"
#include "imageloader.hpp"
#include "cmodel/CModel.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <math.h>	
#include <Windows.h>


// VARIABLE GLOBALES
#ifdef GL_VERSION_1_1
static GLuint texName;
#endif
//texturas
#define    checkImageWidth 64
#define    checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
GLuint _textgrass,_textsky,_textbambu,_textroof;
float camina_x = 0, camina_z = 0;
// TEXTURAS
float px=0, py=1.0, pz=20, x1=0.0,y2=1.0,z1=0;
//funciones de texturizado

void makeCheckImage(void)
{
	int i, j, c;

	for (i = 0; i < checkImageHeight; i++) {
		for (j = 0; j < checkImageWidth; j++) {
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}
}
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
		//as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}
// OBJ 3D
// carga de texturas
void cargaPasto() {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textgrass);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glEnd();
	glPopMatrix();
}
void cargaCielo() {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textsky);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glEnd();
	glPopMatrix();

}
void cargaBambu() {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textbambu);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glEnd();
	glPopMatrix();

}
void cargaRoof() {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textroof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glEnd();
	glPopMatrix();
}
//dibujo
void pisocasa() {
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-5, 0.0, 15);
	glTexCoord3f(0.0, 2.0, 0.0); glVertex3f(5, 0.0, 15);
	glTexCoord3f(2.0, 2.0, 0.0); glVertex3f(5, 0.0, -15);
	glTexCoord3f(2.0, 0.0, 0.0); glVertex3f(-5, 0.0, -15);
	glEnd();

}
void dibujacuarto() {
	//pared1
	cargaBambu();
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-5, 0.0, 15);
	glTexCoord3f(0.0, 4.0, 0.0); glVertex3f(-5, 2.0, 15);
	glTexCoord3f(8.0, 4.0, 0.0); glVertex3f(-5, 2.0, 0);
	glTexCoord3f(8.0, 0.0, 0.0); glVertex3f(-5, 0.0, 0);
	glEnd();
	//pared2
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(5, 0.0, 15);
	glTexCoord3f(0.0, 4.0, 0.0); glVertex3f(5, 2.0, 15);
	glTexCoord3f(8.0, 4.0, 0.0); glVertex3f(5, 2.0, 0);
	glTexCoord3f(8.0, 0.0, 0.0); glVertex3f(5, 0.0, 0);
	glEnd();
	//fachada1
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-5, 0.0, 15);
	glTexCoord3f(0.0, 4.0, 0.0); glVertex3f(-5, 2.0, 15);
	glTexCoord3f(8.0, 4.0, 0.0); glVertex3f(-4.5, 2.0, 15);
	glTexCoord3f(8.0, 0.0, 0.0); glVertex3f(-4.5, 0.0, 15);
	glEnd();
	//fachada2
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-5, 1.5, 15);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-5, 2.0, 15);
	glTexCoord3f(8.0, 1.0, 0.0); glVertex3f(5, 2.0, 15);
	glTexCoord3f(8.0, 0.0, 0.0); glVertex3f(5, 1.5, 15);
	glEnd();
	//fachada3
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-3, 0.0, 15);
	glTexCoord3f(0.0, 4.0, 0.0); glVertex3f(-3, 2.0, 15);
	glTexCoord3f(8.0, 4.0, 0.0); glVertex3f(5, 2.0, 15);
	glTexCoord3f(8.0, 0.0, 0.0); glVertex3f(5, 0.0, 15);
	glEnd();
	//fachada4
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-3, 0.0, 0);
	glTexCoord3f(0.0, 4.0, 0.0); glVertex3f(-3, 2.0, 0);
	glTexCoord3f(8.0, 4.0, 0.0); glVertex3f(5, 2.0, 0);
	glTexCoord3f(8.0, 0.0, 0.0); glVertex3f(5, 0.0, 0);
	glEnd();
	//fachada5
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-5, 0.0, 0);
	glTexCoord3f(0.0, 4.0, 0.0); glVertex3f(-5, 2.0, 0);
	glTexCoord3f(8.0, 4.0, 0.0); glVertex3f(-4.5, 2.0, 0);
	glTexCoord3f(8.0, 0.0, 0.0); glVertex3f(-4.5, 0.0, 0);
	glEnd();
	//fachada6
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-5, 1.5, 0);
	glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-5, 2.0, 0);
	glTexCoord3f(8.0, 1.0, 0.0); glVertex3f(5, 2.0, 0);
	glTexCoord3f(8.0, 0.0, 0.0); glVertex3f(5, 1.5, 0);
	glEnd();
}
void piso() {
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 0.0, 0.11); glVertex3f(-10, 0, 20);
	glTexCoord3f(0.0, 1, 0.1); glVertex3f(10,0,20);
	glTexCoord3f(1.0, 1.0, 0.1); glVertex3f(10,0,-20);
	glTexCoord3f(1.0, 0.0, 0.1); glVertex3f(-10,0,-20);
	glEnd();
}

void cielo() {
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glTranslatef(0,-5,0);
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(0, -20, -10);
	glTexCoord3f(0.0, 1, 0.0); glVertex3f(10, -20, -10);
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(10, 20, -10);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(0, 20, -10);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-10, -10, 0);
	glTexCoord3f(0.0, 1, 0.0); glVertex3f(-10, -10, 10);
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(-10, 10, 10);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(-10, 10, 0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(10, -10, 0);
	glTexCoord3f(0.0, 1, 0.0); glVertex3f(10, -10, 10);
	glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(10, 10, 10);
	glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(10, 10, 0);
	glEnd();
	glPopMatrix();
}

void dibuja(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();             /* clear the matrix */
	/* viewing transformation  */
	gluLookAt(px, py, pz, x1, y2, z1, 0.0, 1.0, 0.0);
	glScalef(1.0, 2.0, 1.0);      /* modeling transformation */
	//cargaCielo();
	//cielo()
	glTranslatef(camina_x, 0, camina_z);
	glPushMatrix();
	//textura de piso
	cargaPasto();
	piso();//piso
	glPushMatrix();
	cargaRoof();
	pisocasa();
	//cuarto1
	glPushMatrix();
	dibujacuarto();
	glPopMatrix();
	//cuarto2

	glPopMatrix();
	/*EJES CORDENADOS   */
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(10, 0, 0);
	glEnd();
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 10, 0);
	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 10);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glFlush();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	makeCheckImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

#ifdef GL_VERSION_1_1
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
#endif

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#ifdef GL_VERSION_1_1
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
#else
	glTexImage2D(GL_TEXTURE_2D, 0, 4, checkImageWidth, checkImageHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
#endif
	// carga de texturas
	Image* image = loadBMP("grass.bmp");
	_textgrass = loadTexture(image);
	 image = loadBMP("sky.bmp");
    _textsky = loadTexture(image);
	image = loadBMP("roof.bmp");
	_textroof = loadTexture(image);
	image = loadBMP("bambu.bmp");
	_textbambu = loadTexture(image);


	delete image;

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'j':
		camina_x += 0.1;
		glutPostRedisplay();
		break;
	case 'l':
		camina_x -= 0.1;
		glutPostRedisplay();
		break;
	case 'i':
		camina_z += 0.1;
		glutPostRedisplay();
		break;
	case 'k':
		camina_z -= 0.1;
		glutPostRedisplay();
		break;
	case 'a':
		x1 -= 0.5;
		glutPostRedisplay();
	break;
	case 'A':
		x1 += 0.5;
		glutPostRedisplay();
	break;
	case 'd':
		y2 -= 0.5;
		glutPostRedisplay();
		break;
	case 'D':
		y2 += 0.5;
		glutPostRedisplay();
		break;
	case 'x':
		px -= 0.5;
		glutPostRedisplay();
		break;
	case 'X':
		px += 0.5;
		glutPostRedisplay();
		break;
	case 'y':
		py -= 0.5;
		glutPostRedisplay();
		break;
	case 'Y':
		py += 0.5;
		glutPostRedisplay();
		break;
	case 'z':
		pz -= 0.5;
		glutPostRedisplay();
		break;
	case 'Z':
		pz += 0.5;
		glutPostRedisplay();
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 650);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Proyecto Final");
	init();
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutDisplayFunc(dibuja); // Esta madre es la que dibuja en la pantalla
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}