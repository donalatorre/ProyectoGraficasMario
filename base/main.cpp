// OpenGL
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include <iostream>


//Reading a PPM file
#include <iostream>
#include <iomanip>
#include <fstream>

#define pi 3.142857
GLfloat angleCubeX = 0.0f;     // Rotational angle for cube
GLfloat angleCubeY = 0.0f;     // Rotational angle for cube
GLfloat angleCubeZ = 0.0f;     // Rotational angle for cube

int refreshMills = 2;

int scaleFactor = 1;
// Positive is to the right, Negative to the left
float TRANSLATE_X = 0.0f;
// Positive is up, negative is down
float TRANSLATE_Y = -2.0f;

float ROT_X=0.0f;
float ROT_Y=0.0f;
float ROT_Z=0.0f;


#define checkImageWidth 626
#define checkImageHeight 417
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

#define doorImageWidth 400
#define doorImageHeight 266
static GLubyte doorImage[checkImageHeight][checkImageWidth][4];

#define windowImageWidth 219
#define windowImageHeight 133
static GLubyte windowImage[checkImageHeight][checkImageWidth][4];


void readImageFile(void) {
  int width,height,colours;
   int i, j, c;
    char keyword[2];
    std::string comment;

   //Reading texture file
    std::ifstream inFile;

    inFile.open("/home/hi/School/8semester/Graphics/Test2/concrete-wall.ppm");
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

    inFile >> keyword;

    std::cout << keyword << " ";
    inFile >> comment;
    std::cout << comment << " ";
    inFile >> comment;
    std::cout << comment << " ";
    inFile >> comment;
    std::cout << comment << ' ';
    inFile >> comment;
    std::cout << comment << std::endl;
    // inFile >> comment;
    // std::cout << comment << " ";

    inFile >> width;
    std::cout << width << ' ';
    inFile >> height;
    std::cout << height << "\n";
    inFile >> colours;
    std::cout << colours;
    std::cout << std::endl;
    for (i = 0; i < height; i++) {
      for (j = 0; j < width; j++) {
         inFile >> c;
         checkImage[height-i][j][0] = (GLubyte) c;
         inFile >> c;
         checkImage[height-i][j][1] = (GLubyte) c;
         inFile >> c;
         checkImage[height-i][j][2] = (GLubyte) c;

         checkImage[height-i][j][3] = (GLubyte) 255;
      }
   }
   inFile.close();

    inFile.open("/home/hi/School/8semester/Graphics/Test2/brown-wood.ppm");
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

    inFile >> keyword;

    std::cout << keyword << " ";
    inFile >> comment;
    std::cout << comment << " ";
    inFile >> comment;
    std::cout << comment << " ";
    inFile >> comment;
    std::cout << comment << ' ';
    inFile >> comment;
    std::cout << comment << std::endl;

    inFile >> width;
    std::cout << width << ' ';
    inFile >> height;
    std::cout << height << "\n";
    inFile >> colours;
    std::cout << colours;
    std::cout << std::endl;
    for (i = 0; i < height; i++) {
      for (j = 0; j < width; j++) {
         inFile >> c;
         doorImage[height-i][j][0] = (GLubyte) c;
         inFile >> c;
         doorImage[height-i][j][1] = (GLubyte) c;
         inFile >> c;
         doorImage[height-i][j][2] = (GLubyte) c;

         doorImage[height-i][j][3] = (GLubyte) 255;
      }
   }
   inFile.close();

    inFile.open("/home/hi/School/8semester/Graphics/Test2/window.ppm");
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

    inFile >> keyword;

    std::cout << keyword << " ";
    inFile >> comment;
    std::cout << comment << " ";
    inFile >> comment;
    std::cout << comment << " ";
    inFile >> comment;
    std::cout << comment << ' ';
    inFile >> comment;
    std::cout << comment << std::endl;

    inFile >> width;
    std::cout << width << ' ';
    inFile >> height;
    std::cout << height << "\n";
    inFile >> colours;
    std::cout << colours;
    std::cout << std::endl;
    for (i = 0; i < height; i++) {
      for (j = 0; j < width; j++) {
         inFile >> c;
         windowImage[height-i][j][0] = (GLubyte) c;
         inFile >> c;
         windowImage[height-i][j][1] = (GLubyte) c;
         inFile >> c;
         windowImage[height-i][j][2] = (GLubyte) c;

         windowImage[height-i][j][3] = (GLubyte) 255;
      }
   }
   inFile.close();
}

// function to initialize
void initGL (void) {

  // making background color black as first
  glClearColor(0.0, 0.0, 0.0, 0.0);
  // glClearDepth(1.0); // Set background depth to farthest
  glEnable(GL_DEPTH_TEST);
  // glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
  // glShadeModel(GL_SMOOTH);
  // glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

   readImageFile();
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
   //              checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
   //              checkImage);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 1,checkImageWidth,checkImageHeight,GL_RGBA,GL_UNSIGNED_BYTE,checkImage);
}



void grayBase();
void redRoof();
void orangeBanner();
void orangeColumn();
void blueWindow();
void brownDoor();
void secondBlueWindow();
void thirdBlueWindow();
void signboard();

void display (void) {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // siempre limpiamos antes
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // We fix Z to -10.0f, so the figure is far from the camera
  glTranslatef(TRANSLATE_X, TRANSLATE_Y, -10.0f);

  glRotatef(angleCubeX, 1, 0, 0);
  glRotatef(angleCubeY, 0, 1, 0);
  glRotatef(angleCubeZ, 0, 0, 1);

  glScalef(scaleFactor, scaleFactor, scaleFactor);

  grayBase();
  redRoof();
  orangeBanner();
  orangeColumn();
  blueWindow();
  brownDoor();
  secondBlueWindow();
  thirdBlueWindow();
  signboard();

  glutSwapBuffers();
  angleCubeX += 1.0;
}
void keyboardListener(int key, int x, int y){
    switch(key)
    {
    case GLUT_KEY_UP:
        TRANSLATE_Y++;
        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN:
        TRANSLATE_Y--;
        glutPostRedisplay();
        break;

    case GLUT_KEY_LEFT:
        TRANSLATE_X--;
        glutPostRedisplay();
        break;

    case GLUT_KEY_RIGHT:
        TRANSLATE_X++;
        glutPostRedisplay();
        break;

    case GLUT_KEY_F3:
        scaleFactor++;
        glutPostRedisplay();
        break;
    case GLUT_KEY_F4:
        if(scaleFactor>1){
        scaleFactor--;
        glutPostRedisplay();
        }
        break;
    case GLUT_KEY_F5:
        angleCubeX--;
        glutPostRedisplay();
        break;
    case GLUT_KEY_F6:
        angleCubeX++;
        glutPostRedisplay();
        break;
    case GLUT_KEY_F7:
        angleCubeY--;
        glutPostRedisplay();
        break;
    case GLUT_KEY_F8:
        angleCubeY++;
        glutPostRedisplay();
        break;
    case GLUT_KEY_F9:
        angleCubeZ--;
        glutPostRedisplay();
        break;
    case GLUT_KEY_F10:
        angleCubeZ++;
        glutPostRedisplay();
        break;
    }
}

void grayBase() {

  gluBuild2DMipmaps(GL_TEXTURE_2D,
                    1,
                    checkImageWidth,
                    checkImageHeight,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    checkImage);

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);

  glColor3f(0.4f, 0.4f, 0.4f);	// Gray


  // Top face
  glTexCoord2f(0.0, 0.0);
  glVertex3f( 1.0f, 1.0f, -1.0f);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-1.0f, 1.0f,  1.0f);
  glTexCoord2f(1.0, 0.0);
  glVertex3f( 1.0f, 1.0f,  1.0f);

  // Bottom face
  glTexCoord2f(0.0, 0.0);
  glVertex3f( 1.0f, -0.5f,  1.0f);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1.0f, -0.5f,  1.0f);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-1.0f, -0.5f, -1.0f);
  glTexCoord2f(1.0, 0.0);
  glVertex3f( 1.0f, -0.5f, -1.0f);

  // Front face
  glTexCoord2f(0.0, 0.0);
  glVertex3f( 1.0f,  1.0f, 1.0f);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1.0f,  1.0f, 1.0f);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-1.0f, -0.5f, 1.0f);
  glTexCoord2f(1.0, 0.0);
  glVertex3f( 1.0f, -0.5f, 1.0f);

  // Back face
  glTexCoord2f(0.0, 0.0);
  glVertex3f( 1.0f, -0.5f, -1.0f);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1.0f, -0.5f, -1.0f);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-1.0f,  1.0f, -1.0f);
  glTexCoord2f(1.0, 0.0);
  glVertex3f( 1.0f,  1.0f, -1.0f);

  // Left face
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-1.0f,  1.0f,  1.0f);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1.0f,  1.0f, -1.0f);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-1.0f, -0.5f, -1.0f);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(-1.0f, -0.5f,  1.0f);

  // Right face
  glTexCoord2f(0.0, 0.0);
  glVertex3f(1.0f,  1.0f, -1.0f);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(1.0f,  1.0f,  1.0f);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(1.0f, -0.5f,  1.0f);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(1.0f, -0.5f, -1.0f);

  glEnd();

  glDisable(GL_TEXTURE_2D);
}

void redRoof() {
  glBegin(GL_QUADS);

  glColor3f(1.0f, 0.0f, 0.0f);	// Red
  //Top Face
  glVertex3f( 1.3f, 1.3f, -1.3f);
  glVertex3f(-1.3f, 1.3f, -1.3f);
  glVertex3f(-1.3f, 1.3f,  1.3f);
  glVertex3f( 1.3f, 1.3f,  1.3f);

  // Bottom face
  glVertex3f( 1.3f, 1.0f, -1.3f);
  glVertex3f(-1.3f, 1.0f, -1.3f);
  glVertex3f(-1.3f, 1.0f,  1.3f);
  glVertex3f( 1.3f, 1.0f,  1.3f);

  // Front face
  glVertex3f( 1.3f, 1.3f, 1.3f);
  glVertex3f(-1.3f, 1.3f, 1.3f);
  glVertex3f(-1.3f, 1.0f, 1.3f);
  glVertex3f( 1.3f, 1.0f, 1.3f);

  // Back face
  glVertex3f( 1.3f, 1.0f, -1.3f);
  glVertex3f(-1.3f, 1.0f, -1.3f);
  glVertex3f(-1.3f, 1.3f, -1.3f);
  glVertex3f( 1.3f, 1.3f, -1.3f);

  // Left face
  glVertex3f(-1.3f, 1.3f,  1.3f);
  glVertex3f(-1.3f, 1.3f, -1.3f);
  glVertex3f(-1.3f, 1.0f, -1.3f);
  glVertex3f(-1.3f, 1.0f,  1.3f);

  // Right face (x = 1.0f)
  glVertex3f(1.3f, 1.3f, -1.3f);
  glVertex3f(1.3f, 1.3f,  1.3f);
  glVertex3f(1.3f, 1.0f,  1.3f);
  glVertex3f(1.3f, 1.0f, -1.3f);

  glEnd();
}

void orangeBanner() {
  glBegin(GL_QUADS);

  glColor3f(1.0f, 0.5f, 0.0f);	// Orange
  // Top Face
  glVertex3f( 1.1f, 0.93f, -1.1f);
  glVertex3f(-1.1f, 0.93f, -1.1f);
  glVertex3f(-1.1f, 0.93f,  1.1f);
  glVertex3f( 1.1f, 0.93f,  1.1f);

  // Bottom face
  glVertex3f( 1.1f, 0.45f, -1.1f);
  glVertex3f(-1.1f, 0.45f, -1.1f);
  glVertex3f(-1.1f, 0.45f,  1.1f);
  glVertex3f( 1.1f, 0.45f,  1.1f);

  // Front face
  glVertex3f( 1.1f, 0.93f, 1.1f);
  glVertex3f(-1.1f, 0.93f, 1.1f);
  glVertex3f(-1.1f, 0.45f, 1.1f);
  glVertex3f( 1.1f, 0.45f, 1.1f);

  // Back face
  glVertex3f( 1.1f, 0.45f, -1.1f);
  glVertex3f(-1.1f, 0.45f, -1.1f);
  glVertex3f(-1.1f, 0.93f, -1.1f);
  glVertex3f( 1.1f, 0.93f, -1.1f);

  // Left face
  glVertex3f(-1.1f, 0.93f,  1.1f);
  glVertex3f(-1.1f, 0.93f, -1.1f);
  glVertex3f(-1.1f, 0.45f, -1.1f);
  glVertex3f(-1.1f, 0.45f,  1.1f);

  // Right face
  glVertex3f(1.1f, 0.93f, -1.1f);
  glVertex3f(1.1f, 0.93f,  1.1f);
  glVertex3f(1.1f, 0.45f,  1.1f);
  glVertex3f(1.1f, 0.45f, -1.1f);
  glEnd();
}

void orangeColumn() {
  glBegin(GL_QUADS);
  //Top Face
  glColor3f(1.0f, 0.5f, 0.0f);     // Orange

  glVertex3f(-0.5f, 0.45f, 0.80f);
  glVertex3f(-1.1f, 0.45f, 0.80f);
  glVertex3f(-1.1f, 0.45f, 1.1f);
  glVertex3f( 1.1f, 0.45f, 1.1f);

  // Bottom face
  glVertex3f(-0.7f, -0.5f, 0.8f);
  glVertex3f(-1.1f, -0.5f, 0.8f);
  glVertex3f(-1.1f, -0.5f,  1.1f);
  glVertex3f(-0.7f, -0.5f,  1.1f);

  // Front face
  glVertex3f(-0.7f, 0.45f, 1.1f);
  glVertex3f(-1.1f, 0.45f, 1.1f);
  glVertex3f(-1.1f, -0.5f, 1.1f);
  glVertex3f(-0.7f, -0.5f, 1.1f);

  // Back face
  glVertex3f(-0.7f, -0.5f, 0.8f);
  glVertex3f(-1.1f, -0.5f, 0.8f);
  glVertex3f(-1.1f, 0.45f, 0.8f);
  glVertex3f(-0.7f, 0.45f, 0.8f);

  // Left face
  glVertex3f(-1.1f, 0.45f, 0.8f);
  glVertex3f(-1.1f, 0.45f, 1.1f);
  glVertex3f(-1.1f, -0.5f, 1.1f);
  glVertex3f(-1.1f, -0.5f, 0.8f);

  // Right face
  glVertex3f(-0.7f, 0.45f, 0.8f);
  glVertex3f(-0.7f, 0.45f,  1.1f);
  glVertex3f(-0.7f, -0.5f,  1.1f);
  glVertex3f(-0.7f, -0.5f, 0.8f);

  glEnd();
}

void blueWindow() {

  glBegin(GL_QUADS);
  glColor3f(0.7f, 0.9f, 1.0f);     // Blue
  //Top Face
  glVertex3f(-0.2f, 0.25f, 0.80f);
  glVertex3f(-0.8f, 0.25f, 0.80f);
  glVertex3f(-0.8f, 0.25f, 1.05f);
  glVertex3f(-0.2f, 0.25f, 1.05f);
  // Bottom face
  glVertex3f(-0.2f, -0.2f, 0.8f);
  glVertex3f(-0.8f, -0.2f, 0.8f);
  glVertex3f(-0.8f, -0.2f,  1.05f);
  glVertex3f(-0.2f, -0.2f,  1.05f);

  // Front face
  glVertex3f(-0.8f, 0.25f, 1.05f);
  glVertex3f(-0.2f, 0.25f, 1.05f);
  glVertex3f(-0.2f, -0.2f, 1.05f);
  glVertex3f(-0.8f, -0.2f, 1.05f);

  // Left face
  glVertex3f(-0.8f, 0.25f, 0.8f);
  glVertex3f(-0.8f, 0.25f, 1.05f);
  glVertex3f(-0.8f, -0.2f, 1.05f);
  glVertex3f(-0.8f, -0.2f, 0.8f);

  // Right face
  glVertex3f(-0.2f, 0.25f, 0.8f);
  glVertex3f(-0.2f, 0.25f, 1.05f);
  glVertex3f(-0.2f, -0.2f, 1.05f);
  glVertex3f(-0.2f, -0.2f, 0.8f);

  glEnd();

  glDisable(GL_TEXTURE_2D);
}

void brownDoor() {

  gluBuild2DMipmaps(GL_TEXTURE_2D,
                    1,
                    doorImageWidth,
                    doorImageHeight,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    doorImage);

  glEnable(GL_TEXTURE_2D);


  glBegin(GL_QUADS);

  glColor3f(0.65, 0.50, 0.39);     // Browm

  //Top Face
  glTexCoord2f(0.0, 0.0);
  glVertex3f(0.3f, 0.25f, 0.80f);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-0.1f, 0.25f, 0.80f);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-0.1f, 0.25f, 1.05f);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(0.3f, 0.25f, 1.05f);

  // Bottom face
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-0.1f, -0.5f, 0.8f);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(0.3f, -0.5f, 0.8f);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(0.3f, -0.5f,  1.05f);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(-0.1f, -0.5f,  1.05f);

  // Front face
  glTexCoord2f(0.0, 0.0);
  glVertex3f(0.3f, 0.25f, 1.05f);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-0.1f, 0.25f, 1.05f);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-0.1f, -0.5f, 1.05f);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(0.3f, -0.5f, 1.05f);

  // Left face
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-0.1f, 0.25f, 0.8f);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-0.1f, 0.25f, 1.05f);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-0.1f, -0.5f, 1.05f);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(-0.1f, -0.5f, 0.8f);

  // Right face
  glTexCoord2f(0.0, 0.0);
  glVertex3f(0.3f, 0.25f, 0.8f);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(0.3f, 0.25f, 1.05f);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(0.3f, -0.5f, 1.05f);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(0.3f, -0.5f, 0.8f);
  glEnd();

  glDisable(GL_TEXTURE_2D);

}

void secondBlueWindow() {

  glBegin(GL_QUADS);

  glColor3f(0.7f, 0.9f, 1.0f);     // Blue

  //Top Face
  glVertex3f(0.4f, 0.25f, 0.80f);
  glVertex3f(0.9f, 0.25f, 0.80f);
  glVertex3f(0.9f, 0.25f, 1.05f);
  glVertex3f(0.4f, 0.25f, 1.05f);

  // Bottom face
  glVertex3f(0.4f, -0.2f, 0.8f);
  glVertex3f(0.9f, -0.2f, 0.8f);
  glVertex3f(0.9f, -0.2f, 1.05f);
  glVertex3f(0.4f, -0.2f, 1.05f);

  // Front face
  glVertex3f(0.9f, 0.25f, 1.05f);
  glVertex3f(0.4f, 0.25f, 1.05f);
  glVertex3f(0.4f, -0.2f, 1.05f);
  glVertex3f(0.9f, -0.2f, 1.05f);

  // Left face
  glVertex3f(0.9f, 0.25f, 0.8f);
  glVertex3f(0.9f, 0.25f, 1.05f);
  glVertex3f(0.9f, -0.2f, 1.05f);
  glVertex3f(0.9f, -0.2f, 0.8f);

  // Right face
  glVertex3f(0.4f, 0.25f, 0.8f);
  glVertex3f(0.4f, 0.25f, 1.05f);
  glVertex3f(0.4f, -0.2f, 1.05f);
  glVertex3f(0.4f, -0.2f, 0.8f);

  glEnd();
}

void thirdBlueWindow() {
  glBegin(GL_QUADS);

  glColor3f(0.7f, 0.9f, 1.0f);     // Blue
  //Top Face
  glVertex3f(1.0f, 0.25f, -0.80f);
  glVertex3f(1.05f, 0.25f, -0.80f);
  glVertex3f(1.05f, 0.25f, 0.8f);
  glVertex3f(1.0f, 0.25f, 0.8f);

  // Bottom face
  glVertex3f(1.0f, -0.2f, 0.8f);
  glVertex3f(1.05f, -0.2f, 0.8f);
  glVertex3f(1.05f, -0.2f, -0.8f);
  glVertex3f(1.0f, -0.2f, -0.8f);

  // Front face
  glVertex3f(1.05f, 0.25f, 0.8f);
  glVertex3f(1.0f, 0.25f, 0.8f);
  glVertex3f(1.0f, -0.2f, 0.8f);
  glVertex3f(1.05f, -0.2f, 0.8f);

  // Back face
  glVertex3f(1.0f, -0.2f, -0.8f);
  glVertex3f(1.05f, -0.2f, -0.8f);
  glVertex3f(1.05f, 0.25f, -0.8f);
  glVertex3f(1.0f, 0.25f, -0.8f);

  // Right face
  glVertex3f(1.05f, 0.25f, -0.8f);
  glVertex3f(1.05f, 0.25f, 0.8f);
  glVertex3f(1.05f, -0.2f, 0.8f);
  glVertex3f(1.05f, -0.2f, -0.8f);

  glEnd();
}

void signboardGray() {
  glBegin(GL_QUADS);

  glColor3f(0.4f, 0.4f, 0.4f);     // Gray

  //Top Face
  glVertex3f( 0.5f, 1.35f, 1.1f);
  glVertex3f(-0.5f, 1.35f, 1.1f);
  glVertex3f(-0.5f, 1.35f, 1.4f);
  glVertex3f( 0.5f, 1.35f, 1.4f);

  // Bottom face
  glVertex3f( 0.5f, 0.90f, 1.1f);
  glVertex3f(-0.5f, 0.90f, 1.1f);
  glVertex3f(-0.5f, 0.90f, 1.4f);
  glVertex3f( 0.5f, 0.90f, 1.4f);

  // Front face
  glVertex3f( 0.5f, 1.35f, 1.4f);
  glVertex3f(-0.5f, 1.35f, 1.4f);
  glVertex3f(-0.5f, 0.90f, 1.4f);
  glVertex3f( 0.5f, 0.90f, 1.4f);

  // Back face
  glVertex3f( 0.5f, 0.90f, 1.1f);
  glVertex3f(-0.5f, 0.90f, 1.1f);
  glVertex3f(-0.5f, 1.35f, 1.1f);
  glVertex3f( 0.5f, 1.35f, 1.1f);

  // Left face
  glVertex3f(-0.5f, 1.35f, 1.4f);
  glVertex3f(-0.5f, 1.35f, 1.1f);
  glVertex3f(-0.5f, 0.90f, 1.1f);
  glVertex3f(-0.5f, 0.90f, 1.4f);

  // Right face
  glVertex3f(0.5f, 1.35f, 1.1f);
  glVertex3f(0.5f, 1.35f, 1.4f);
  glVertex3f(0.5f, 0.90f, 1.4f);
  glVertex3f(0.5f, 0.90f, 1.1f);

  glEnd();
}

void signboardRed() {
  glBegin(GL_QUADS);

  glColor3f(1.0f, 0.0f, 0.0f);     // Gray

  //Top Face
  glVertex3f( 0.4f, 1.3f, 1.0f);
  glVertex3f(-0.4f, 1.3f, 1.0f);
  glVertex3f(-0.4f, 1.3f, 1.46f);
  glVertex3f( 0.4f, 1.3f, 1.46f);

  // Bottom face
  glVertex3f( 0.4f, 1.0f, 1.0f);
  glVertex3f(-0.4f, 1.0f, 1.0f);
  glVertex3f(-0.4f, 1.0f, 1.46f);
  glVertex3f( 0.4f, 1.0f, 1.46f);

  // Front face
  glVertex3f( 0.4f, 1.3f, 1.46f);
  glVertex3f(-0.4f, 1.3f, 1.46f);
  glVertex3f(-0.4f, 1.0f, 1.46f);
  glVertex3f( 0.4f, 1.0f, 1.46f);

  // Left face
  glVertex3f(-0.4f, 1.3f, 1.46f);
  glVertex3f(-0.4f, 1.3f, 1.0f);
  glVertex3f(-0.4f, 1.0f, 1.0f);
  glVertex3f(-0.4f, 1.0f, 1.46f);

  // Right face
  glVertex3f(0.4f, 1.3f, 1.0f);
  glVertex3f(0.4f, 1.3f, 1.46f);
  glVertex3f(0.4f, 1.0f, 1.46f);
  glVertex3f(0.4f, 1.0f, 1.0f);

  glEnd();
}
void signboardNumber() {
  glBegin(GL_QUADS);
glColor3f(1.0f, 1.0f, 1.0f);     // White
      glVertex3f(-0.08f, 1.27f, 1.462f);
      glVertex3f(-0.16f, 1.27f, 1.462f);
      glVertex3f(-0.16f, 1.03f, 1.462f);
      glVertex3f(-0.08f, 1.03f, 1.462f);

      glVertex3f( 0.05f, 1.27f, 1.462f);
      glVertex3f(-0.05f, 1.27f, 1.462f);
      glVertex3f(-0.05f, 1.03f, 1.462f);
      glVertex3f( 0.05f, 1.03f, 1.462f);

      glVertex3f( 0.08f, 1.27f, 1.462f);
      glVertex3f( 0.16f, 1.27f, 1.462f);
      glVertex3f( 0.16f, 1.03f, 1.462f);
      glVertex3f( 0.08f, 1.03f, 1.462f);

      glVertex3f(-0.19f, 1.28f, 1.462f);
      glVertex3f( 0.19f, 1.28f, 1.462f);
      glVertex3f( 0.19f, 1.24f, 1.462f);
      glVertex3f(-0.19f, 1.24f, 1.462f);

      glVertex3f(-0.19f, 1.07f, 1.462f);
      glVertex3f( 0.19f, 1.07f, 1.462f);
      glVertex3f( 0.19f, 1.03f, 1.462f);
      glVertex3f(-0.19f, 1.03f, 1.462f);

  glEnd();
}
void signboard() {
  signboardGray();
  signboardRed();
  signboardNumber();
}

void timer(int value) {
  glutPostRedisplay();
  glutTimerFunc(refreshMills, timer, 0);
}

void reshape (GLsizei width, GLsizei height) {
  if (height == 0) height = 1;
  GLfloat aspect = (GLfloat)width / (GLfloat)height;

  // Set the viewport to cover the new window
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();             // Reset
  gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main (int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("III");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  initGL();
  //glutTimerFunc(0, timer, 0);
  glutSpecialFunc(keyboardListener);
  glutMainLoop();
  return 0;
}
