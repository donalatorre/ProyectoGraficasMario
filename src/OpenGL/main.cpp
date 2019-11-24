/*
 * OGL01Shape3D.cpp: 3D Shapes
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <GLUT/glut.h>  // GLUT, include glu.h and gl.h
#define POINT_COUNT 24
#define MAX_PRISM 50

using namespace std;

/* Global variables */
char title[] = "3D Shapes";
GLfloat marioPoints[MAX_PRISM][POINT_COUNT * 3];
int prismCount = 0;

/*  Create checkerboard texture  */
#define checkImageWidth 65
#define checkImageHeight 65
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
int width,height,colours;

void makeCheckImage(void)
{
    int i, j, c;
    char keyword[2];
    string comment;
    //Generating Checker Pattern
    /*for (i = 0; i < checkImageHeight; i++) {
     for (j = 0; j < checkImageWidth; j++) {
     c = ((((i&0x8)==0)^((j&0x8))==0))*255;
     checkImage[i][j][0] = (GLubyte) c;
     checkImage[i][j][1] = (GLubyte) c;
     checkImage[i][j][2] = (GLubyte) c;
     checkImage[i][j][3] = (GLubyte) 255;
     }
     }*/
    
    //Reading texture file
    ifstream inFile;
    
    inFile.open("/Users/adanlopezalatorre/Desktop/Raul.ppm");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    inFile >> keyword;
    cout << keyword << " ";
    inFile >> comment;
    cout << comment << " ";
    inFile >> comment;
    cout << comment << " ";
    inFile >> comment;
    cout << comment << " ";
    inFile >> comment;
    cout << comment << " ";
    
    inFile >> width;
    cout << width;
    inFile >> height;
    cout << height << "\n";
    inFile >> colours;
    cout << colours;
    cout << endl;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            inFile >> c;
            checkImage[height-i][j][0] = (GLubyte) c;
            //cout << c << " ";
            inFile >> c;
            checkImage[height-i][j][1] = (GLubyte) c;
            //cout << c << " ";
            inFile >> c;
            checkImage[height-i][j][2] = (GLubyte) c;
            //cout << c << " ";
            checkImage[height-i][j][3] = (GLubyte) 255;
            //cout << "255n";
        }
        //cout << endl;
    }
    inFile.close();
}

/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
   makeCheckImage();
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    /*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
                 checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 checkImage);
    gluBuild2DMipmaps(GL_TEXTURE_2D,1,checkImageWidth,checkImageHeight,GL_RGBA,GL_UNSIGNED_BYTE,checkImage);*/
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix
   glTranslatef(1.5f, 0.0f, -8.0f);  // Move right and into the screen

glEnable(GL_TEXTURE_2D);
   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out

	for(int u = 0; u < prismCount; u++)
	for(int i = 0; i < POINT_COUNT; i += 4) {
      //glColor3f(0.0f, 1.0f, 0.0f);     // Green

	
	for(int j = i; j < i + 4; j++) {
		auto entr = 200.0f;
		glTexCoord2f(4.0, 0.0);
		glVertex3f( marioPoints[u][j * 3]/entr, marioPoints[u][j * 3 + 1]/entr, marioPoints[u][j * 3 + 2]/entr);
		//for(int r = 0; r < 3; r++) cout << marioPoints[u][j * 3 + r] << ' '; cout << '\n';
	}
	}

      /*glColor3f(0.0f, 1.0f, 0.0f);     // Green

      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);

      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);

      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);

      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);

      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);

      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);*/
   glEnd();  // End of drawing color-cube
glDisable(GL_TEXTURE_2D);

   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
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
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
