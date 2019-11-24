//
//  main.cpp
//  OpenGL
//
//  Free software
//  Copyright © 2019 Daniel Tijerina. All rights reserved.
//
/*
 Model for mario, allows the following operations
 
 -Rotate left: LEFT_KEY
 -Rotate right: RIGHT_KEY
 -Rotate up: UP_KEY
 -Rotate down: DOWN_KEY
 -Scale bigger x-axis: 0
 -Scale smaller x-axis: 1
 -Scale bigger y-axis: 2
 -Scale smaller y-axis 3
 -Scale bigger z-axis: 4
 -Scale smaller z-axis 5
 -Translate left x-axis: a
 -Translate right x-axis: b
 -Translate forth y-axis: c
 -Translate back y-axis: d
 -Translate up z-axis: e
 -Translate down z-axis: f
 */

using namespace std;
namespace raul {
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
}

/*
 Colors used for the model.
 */
GLubyte red[] = {
    255, 0, 0,255,
    255, 0, 0,255,
    255, 0, 0,255,
    255, 0, 0,255,
    255, 0, 0,255,
    255, 0, 0,255,
    255, 0, 0,255,
    255, 0, 0,255,
    255, 0, 0,255,
    255, 0, 0,255,
    255, 0, 0,255,
    255, 0, 0,255,
    255, 0, 0,255,
    255, 0, 0,255,
    255, 0, 0,255,
    255, 0, 0,255,
};

GLubyte green[] = {
    0, 255, 0,255,
    0, 255, 0,255,
    0, 255, 0,255,
    0, 255, 0,255,
    0, 255, 0,255,
    0, 255, 0,255,
    0, 255, 0,255,
    0, 255, 0,255,
    0, 255, 0,255,
    0, 255, 0,255,
    0, 255, 0,255,
    0, 255, 0,255,
    0, 255, 0,255,
    0, 255, 0,255,
    0, 255, 0,255,
    0, 255, 0,255,
};

GLubyte blue[] = {
    0, 0, 255,255,
    0, 0, 255,255,
    0, 0, 255,255,
    0, 0, 255,255,
    0, 0, 255,255,
    0, 0, 255,255,
    0, 0, 255,255,
    0, 0, 255,255,
    0, 0, 255,255,
    0, 0, 255,255,
    0, 0, 255,255,
    0, 0, 255,255,
    0, 0, 255,255,
    0, 0, 255,255,
    0, 0, 255,255,
    0, 0, 255,255,
};

GLubyte white[] = {
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
};

GLubyte yellow[] = {
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
};

GLubyte skin[] = {
    255, 220, 117,255,
    255, 220, 117,255,
    255, 220, 117,255,
    255, 220, 117,255,
    255, 220, 117,255,
    255, 220, 117,255,
    255, 220, 117,255,
    255, 220, 117,255,
    255, 220, 117,255,
    255, 220, 117,255,
    255, 220, 117,255,
    255, 220, 117,255,
    255, 220, 117,255,
    255, 220, 117,255,
    255, 220, 117,255,
    255, 220, 117,255,
};

GLubyte brown[] = {
    145, 86, 61,255,
    145, 86, 61,255,
    145, 86, 61,255,
    145, 86, 61,255,
    145, 86, 61,255,
    145, 86, 61,255,
    145, 86, 61,255,
    145, 86, 61,255,
    145, 86, 61,255,
    145, 86, 61,255,
    145, 86, 61,255,
    145, 86, 61,255,
    145, 86, 61,255,
    145, 86, 61,255,
    145, 86, 61,255,
    145, 86, 61,255,
};

GLubyte black[] = {
    0, 0, 0, 255,
    0, 0, 0, 255,
    0, 0, 0, 255,
    0, 0, 0, 255,
    0, 0, 0, 255,
    0, 0, 0, 255,
    0, 0, 0, 255,
    0, 0, 0, 255,
    0, 0, 0, 255,
    0, 0, 0, 255,
    0, 0, 0, 255,
    0, 0, 0, 255,
    0, 0, 0, 255,
    0, 0, 0, 255,
    0, 0, 0, 255,
    0, 0, 0, 255,
};

GLubyte *colors[] = {
    black, black, blue, blue, blue, red, skin, yellow, yellow, blue, blue, skin, skin, brown, skin, skin, skin, black, black, red, red, red, white
};

/*
 NOTE: all three operations will be performed. In order to apply only one, leave the default values in all the rest.
 */
GLfloat scaleMatrix[4][4] =
{
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1},
};

GLfloat translateMatrix[4][4] =
{
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1},
};

double thetha = 0.0;// To rotate (values over 0.7 are not recommended, since they might not be displayed entirely.
GLfloat rotateMatrix[4][4] =
{
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1},
};


