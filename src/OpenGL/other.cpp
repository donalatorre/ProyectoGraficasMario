#include <GL/glew.h>
#include <GLUT/glut.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <GLFW/glfw3.h>
#include "matrix.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define POINT_COUNT 24
#define MAX_PRISM 50

using namespace std;

GLfloat marioPoints[MAX_PRISM][POINT_COUNT * 3];
int prismCount = 0;

/**/
void drawCube2(GLfloat vertices[POINT_COUNT * 3], GLubyte *color);

void setAllPoints() {
//glLoadIdentity();
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glColor3f(0.5f, 0.0f, 1.0f); // sets color to black.
       glBegin(GL_QUADS);
		glVertex3f(-2, -1, 0);
		glVertex3f(-2, 1, 0);
		glVertex3f(0, 1, 0);
		glVertex3f(0, -1, 0);
       glEnd();
return;*/
    for(int i = 0; i < prismCount; i++) {
        drawCube2(marioPoints[i], colors[i]);
    }
}

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init(void) {
    glEnable(GL_DEPTH_TEST);
    return;
    raul::makeCheckImage();
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
                 checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 raul::checkImage);
    gluBuild2DMipmaps(GL_TEXTURE_2D,1,checkImageWidth,checkImageHeight,GL_RGBA,GL_UNSIGNED_BYTE,raul::checkImage);
}

int main(int argc, char** argv) {
    GLFWwindow *window;
    raul::makeCheckImage();
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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(setAllPoints);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(setAllPoints);
    glutMainLoop();
return 0;    
    
    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }
    
    // Create a window mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario model", NULL, NULL);
    
    /**/
    glfwSetKeyCallback( window, keyCallback );
    glfwSetInputMode( window, GLFW_STICKY_KEYS, 1 );
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );
    /**/
    
    if(!window){
        glfwTerminate();
        return -1;
    }
    
    // Make the window's context current
    glfwMakeContextCurrent(window);
    
    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    /**/
    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;
    /**/
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
    //      checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
    //             raul::checkImage);
    //gluBuild2DMipmaps(GL_TEXTURE_2D,1,checkImageWidth,checkImageHeight,GL_RGBA,GL_UNSIGNED_BYTE,raul::checkImage);
    // Loop until window closes
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
        
        glEnable(GL_DEPTH_TEST);
        
        /**/
        glPushMatrix( );
        glTranslatef( halfScreenWidth, halfScreenHeight, -500 );
        glScalef(scaleX, scaleY, scaleZ);
        scaleX = scaleY = scaleZ = 1;
        glRotatef( rotationX, 1, 0, 0 );
        glRotatef( rotationY, 0, 1, 0 );
        glTranslatef( -halfScreenWidth + traslationX, -halfScreenHeight + traslationY, 500  + traslationZ);
        /**/
        
        setAllPoints();
        
        // Swap front and back buffers
        glfwSwapBuffers(window);
        
        // Poll for and process events
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void drawCube2(GLfloat vertices[POINT_COUNT * 3], GLubyte *color){
/*for(int i = 0; i < POINT_COUNT; i += 4) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glColor3f(1.0f, 1.0f, 1.0f); // sets color to black.
       glBegin(GL_QUADS);
	for(int j = i; j < i + 4; j++)
		glVertex3f(vertices[j * 3 + 0], vertices[j * 3 + 1], vertices[j * 3 + 2]);
       glEnd();
       glutSwapBuffers();
}
return;*/
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer( 4, GL_UNSIGNED_BYTE, 0, color );
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

