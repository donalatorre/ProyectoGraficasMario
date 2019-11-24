#include <GL/glew.h>
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

void init(void);
/**/
void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods );
/**/
void drawCube2(GLfloat vertices[POINT_COUNT * 3], GLubyte *color);
/**/
void drawCube3(GLfloat vertices[POINT_COUNT * 3]);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

GLfloat traslationX = 0.0f;
GLfloat traslationY = 0.0f;
GLfloat traslationZ = 0.0f;

GLfloat scaleX = 1.0f;
GLfloat scaleY = 1.0f;
GLfloat scaleZ = 1.0f;

void setAllPoints() {
    for(int i = 0; i < prismCount; i++) {
        drawCube2(marioPoints[i], colors[i]);
//        drawCube3(marioPoints[i]);
    }
}

int main() {
    GLFWwindow *window;
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
//        GLfloat vert[] = {563.000, 195.000, -470.000, 613.000, 195.000, -470.000, 613.000, 165.000, -470.000, 563.000, 165.000, -470.000, 563.000, 195.000, -570.000, 613.000, 195.000, -570.000, 613.000, 165.000, -570.000, 563.000, 165.000, -570.000, 563.000, 195.000, -470.000, 563.000, 195.000, -570.000, 563.000, 165.000, -570.000, 563.000, 165.000, -470.000, 613.000, 195.000, -470.000, 613.000, 195.000, -570.000, 613.000, 165.000, -570.000, 613.000, 165.000, -470.000, 563.000, 195.000, -470.000, 563.000, 195.000, -570.000, 613.000, 195.000, -570.000, 613.000, 195.000, -470.000, 563.000, 195.000, -570.000, 563.000, 195.000, -570.000, 613.000, 195.000, -570.000, 613.000, 195.000, -570.000};
//        drawCube3(vert);
        
        // Swap front and back buffers
        glfwSwapBuffers(window);
        
        // Poll for and process events
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void drawCube2(GLfloat vertices[POINT_COUNT * 3], GLubyte *color){
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer( 4, GL_UNSIGNED_BYTE, 0, color );
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void drawCube3(GLfloat vertices[POINT_COUNT * 3]) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    glLoadIdentity();                 // Reset the model-view matrix

    
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
         int i = 0;
         // Top face (y = 1.0f)
         // Define vertices in counter-clockwise (CCW) order with normal pointing out
         glColor3f(0.0f, 1.0f, 0.0f);     // Green
         glVertex3f(vertices[i + 0], vertices[i + 1], vertices[i + 2]);
         glVertex3f(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
         glVertex3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
         glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
    
         i+=12;
         // Bottom face (y = -1.0f)
         glColor3f(1.0f, 0.5f, 0.0f);     // Orange
         glVertex3f(vertices[i + 0], vertices[i + 1], vertices[i + 2]);
         glVertex3f(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
         glVertex3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
         glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
    
         i+=12;
         // Front face  (z = 1.0f)
         glColor3f(1.0f, 0.0f, 0.0f);     // Red
         glVertex3f(vertices[i + 0], vertices[i + 1], vertices[i + 2]);
         glVertex3f(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
         glVertex3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
         glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
    
         i+=12;
         // Back face (z = -1.0f)
         glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
         glVertex3f(vertices[i + 0], vertices[i + 1], vertices[i + 2]);
         glVertex3f(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
         glVertex3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
         glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
    
         i+=12;
         // Left face (x = -1.0f)
         glColor3f(0.0f, 0.0f, 1.0f);     // Blue
         glVertex3f(vertices[i + 0], vertices[i + 1], vertices[i + 2]);
         glVertex3f(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
         glVertex3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
         glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
    
         i+=12;
         // Right face (x = 1.0f)
         glColor3f(1.0f, 1.0f, 1.0f);     // Magenta
         glVertex3f(vertices[i + 0], vertices[i + 1], vertices[i + 2]);
         glVertex3f(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
         glVertex3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
         glVertex3f(vertices[i + 9], vertices[i + 10], vertices[i + 11]);
      glEnd();  // End of drawing color-cube
}

void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods )
{
    // actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
    if ( action == GLFW_RELEASE || action == GLFW_PRESS )
    {
        const GLfloat scaleSpeed = 1.1;
        const GLfloat rotationSpeed = (action == GLFW_PRESS)?0.1:(-0.1);
        const GLfloat translationSpeed = (action == GLFW_PRESS)? 2: -2;
        switch ( key )
        {
            case GLFW_KEY_UP:
                rotationX -= rotationSpeed;
                break;
            case GLFW_KEY_DOWN:
                rotationX += rotationSpeed;
                break;
            case GLFW_KEY_RIGHT:
                rotationY += rotationSpeed;
                break;
            case GLFW_KEY_LEFT:
                rotationY -= rotationSpeed;
                break;
                
            case GLFW_KEY_A:
                traslationX -= translationSpeed;
                break;
            case GLFW_KEY_B:
                traslationX += translationSpeed;
                break;
            case GLFW_KEY_C:
                traslationY += translationSpeed;
                break;
            case GLFW_KEY_D:
                traslationY -= translationSpeed;
                break;
            case GLFW_KEY_E:
                traslationZ += translationSpeed;
                break;
            case GLFW_KEY_F:
                traslationZ -= translationSpeed;
                break;
                
            case GLFW_KEY_0:
                scaleX = 1/scaleSpeed;
                break;
            case GLFW_KEY_1:
                scaleX = scaleSpeed;
                break;
            case GLFW_KEY_2:
                scaleY = 1/scaleSpeed;
                break;
            case GLFW_KEY_3:
                scaleY = scaleSpeed;
                break;
            case GLFW_KEY_4:
                scaleZ = 1/scaleSpeed;
                break;
            case GLFW_KEY_5:
                scaleZ = scaleSpeed;
                break;
        }
        
        
    }
}

