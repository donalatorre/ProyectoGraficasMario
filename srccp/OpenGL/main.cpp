#include<stdio.h>
#include<GLUT/glut.h>
#include<math.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "matrix.h"

#define POINT_COUNT 24
#define MAX_PRISM 50
#define SCREEN_WIDTH 1280
#define ENTR 1000
#define SCREEN_HEIGHT 720
GLfloat marioPoints[MAX_PRISM][POINT_COUNT * 3];
int prismCount = 0;

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

GLfloat traslationX = 0.0f;
GLfloat traslationY = 0.0f;
GLfloat traslationZ = 0.0f;

GLfloat scaleX = 1.0f;
GLfloat scaleY = 1.0f;
GLfloat scaleZ = 1.0f;

#define checkImageWidth 627
#define checkImageHeight 418
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

void readAllFiles(void) {
    std::string inp;
    std::ifstream in("points.txt");
    for(prismCount = 0; std::getline(in, inp); prismCount++) {
        std::stringstream stringst(inp);
        
        for(int i = 0; i < POINT_COUNT; i++) {
            for(int j = 0; j < 3; j++) {
                stringst >> marioPoints[prismCount][i * 3 + j];
            }
        }
    }
    in.close();
    int width,height,colours;
    int i, j, c;
    char keyword[2];
    std::string comment;
    
    //Reading texture file
    std::ifstream inFile;
    
    inFile.open("/Users/adanlopezalatorre/Documents/SemestresTec/Septimo/ComputerGraphics/ProyectoGraficasMario/base/concrete-wall.ppm");
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
            checkImage[height-i][j][0] = (GLubyte) c;
            inFile >> c;
            checkImage[height-i][j][1] = (GLubyte) c;
            inFile >> c;
            checkImage[height-i][j][2] = (GLubyte) c;
            
            checkImage[height-i][j][3] = (GLubyte) 255;
        }
    }
    inFile.close();
}

void init (void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    readAllFiles();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 1,checkImageWidth,checkImageHeight,GL_RGBA,GL_UNSIGNED_BYTE,checkImage);
}

void display (void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    glScalef(scaleX, scaleY, scaleZ);
    glRotatef( rotationX, 1, 0, 0 );
    glRotatef( rotationY, 0, 1, 0 );
    glTranslatef( traslationX, traslationY, traslationZ);
    
    /*gluBuild2DMipmaps(GL_TEXTURE_2D,
                      1,
                      checkImageWidth,
                      checkImageHeight,
                      GL_RGBA,
                      GL_UNSIGNED_BYTE,
                      checkImage);
    
    glEnable(GL_TEXTURE_2D);*/
    glBegin(GL_QUADS);
    
    
    GLfloat halfScreenWidth = SCREEN_WIDTH / 2.0 / ENTR;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2.0 / ENTR;
    for(int u = 0; u < prismCount; u++) {
        glColor3f(colors[u][0], colors[u][1], colors[u][2]);    // Gray
        for(int i = 0; i < POINT_COUNT; i += 4) {
            
            GLfloat arg1[] = {0.0, 0.0, 1.0, 1.0};
            GLfloat arg2[] = {0.0, 1.0, 1.0, 0.0};
            for(int j = i; j < i + 4; j++) {
                //glTexCoord2f(arg1[j - i], arg2[j - i]);
                glVertex3f( marioPoints[u][j * 3]/ENTR - halfScreenWidth, marioPoints[u][j * 3 + 1]/ENTR - halfScreenHeight, marioPoints[u][j * 3 + 2]/ENTR - 0.5);
            }
        }
    }
    
    glEnd();
    
    //glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard (unsigned char key, int x, int y) {
    const GLfloat scaleSpeed = 1.1;
    const GLfloat translationSpeed = 0.1;
    bool redisp = 1;
    switch (key) {
        case '0':
            scaleX *= 1/scaleSpeed;
            break;
        case '1':
            scaleX *= scaleSpeed;
            break;
        case '2':
            scaleY *= 1/scaleSpeed;
            break;
        case '3':
            scaleY *= scaleSpeed;
            break;
        case '4':
            scaleZ *= 1/scaleSpeed;
            break;
        case '5':
            scaleZ *= scaleSpeed;
            break;
        case 'h':
            traslationX -= translationSpeed;
            break;
        case 'l':
            traslationX += translationSpeed;
            break;
        case 'k':
            traslationY += translationSpeed;
            break;
        case 'j':
            traslationY -= translationSpeed;
            break;
        case 'e':
            traslationZ += translationSpeed;
            break;
        case 'f':
            traslationZ -= translationSpeed;
            break;
        
        default:
            redisp = 0;
            break;
    }
    if(redisp) glutPostRedisplay();
}

void SpecialInput(int key, int x, int y){
    const GLfloat rotationSpeed = 0.5;
    bool redisp = 1;
    switch(key) {
        case GLUT_KEY_DOWN:
            rotationX -= rotationSpeed;
            break;
        case GLUT_KEY_UP:
            rotationX += rotationSpeed;
            break;
        case GLUT_KEY_LEFT:
            rotationY += rotationSpeed;
            break;
        case GLUT_KEY_RIGHT:
            rotationY -= rotationSpeed;
            break;
        default:
            redisp = 0;
            break;
    }
    if(redisp) glutPostRedisplay();
}

int main (int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(60, 60);
    glutCreateWindow("Mario Bros");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialInput);
    glutMainLoop();
}

