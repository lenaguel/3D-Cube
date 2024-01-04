// ----------------------------------------------------------
// This is a simple representation of a 3D cube that can be played around with. 
// There are 3 different modes - R for Rotation, S for Scaling and L for Loop. Loop means that the cube rotates automatically.
// 
// Actions by pressing these keys in mode R:
//      Arrow up - Rotation on x-axis by 5 degree
//      Arrow down - Rotation on x-axis by -5 degree
//      Arrow right - Rotation on y-axis by 5 degree
//      Arrow left - Rotation on y-axis by -5 degree
//      z - Rotation on z-axis by 5 degree
//      u - Rotation on z-axis by -5 degree
//      
// Actions by pressing these keys in mode S:
//      Arrow up - Scaling on x-axis by 0.05
//      Arrow down - Scaling on x-axis by -0.05
//      Arrow right - Scaling on y-axis by 0.05
//      Arrow left - Scaling on y-axis by -0.05
//      z - Scaling on z-axis by 0.05
//      u - Scaling on z-axis by -0.05
// 
// General actions by pressing these keys (regardless of the mode):
//      ESC - Close the window
//      r - Activate mode R
//      s - Activate mode S
//      l - Activate mode L
//      k - Stop mode L
//      e - Enable depth test
//      d - Disable depth test
//      m - "Zoom in" (make cube on all axis bigger)
//      n - "Zoom out" (make cube on all axis smaller)
// ----------------------------------------------------------

#include <GL/freeglut.h>

float rotate_x = 0.0f;
float rotate_y = 0.0f;
float rotate_z = 0.0f;
float scale_x = 1.0f;
float scale_y = 1.0f;
float scale_z = 1.0f;
char mode = 'r';
bool isR = true;
bool isS = false;
bool isL = false;
const unsigned char* t = reinterpret_cast<const unsigned char*>("Mode: R");
float delta = 0.0f;

void display() {
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    //if l is pressed
    if (isL) {
        //automatically rotate the cube
        delta += 0.03f;
        glRotatef(delta, 1.0f, 0.0f, 0.0f);
        glRotatef(delta, 0.0f, 1.0f, 0.0f);
        glRotatef(delta, 0.0f, 0.0f, 1.0f);

        //Draw text on screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(-0.9f, -0.9f);
        t = reinterpret_cast<const unsigned char*>("Mode: L");
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, t);
        glutPostRedisplay();
    }
    else {
        // Rotate when user changes rotate_x, rotate_y and rotate_z
        glRotatef(rotate_x, 1.0f, 0.0f, 0.0f);
        glRotatef(rotate_y, 0.0f, 1.0f, 0.0f);
        glRotatef(rotate_z, 0.0f, 0.0f, 1.0f);

        // Scale when user changes scale_x, scale_y and scale_z
        glScalef(scale_x, scale_y, scale_z);

        // Draw text on screen
        glColor3f(1.0f, 1.0f, 1.0f);
        if (isR) {
            glRasterPos2f(-0.9f, -0.9f);
            t = reinterpret_cast<const unsigned char*>("Mode: R");
            glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, t);
        }
        else if (isS) {
            glRasterPos2f(-0.9f, -0.9f);
            t = reinterpret_cast<const unsigned char*>("Mode: S");
            glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, t);
        }
    }

    //Multi-colored side - FRONT
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);     glVertex3f(0.5, -0.5, -0.5);      // P1 is red
    glColor3f(0.0, 1.0, 0.0);     glVertex3f(0.5, 0.5, -0.5);      // P2 is green
    glColor3f(0.0, 0.0, 1.0);     glVertex3f(-0.5, 0.5, -0.5);      // P3 is blue
    glColor3f(1.0, 0.0, 1.0);     glVertex3f(-0.5, -0.5, -0.5);      // P4 is purple
    glEnd();

    // White side - BACK
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    // Purple side - RIGHT
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    // Green side - LEFT
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    // Blue side - TOP
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // Red side - BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {
    if (mode == 'r') {
        //  Right arrow - increase y-rotation by 5 degree
        if (key == GLUT_KEY_RIGHT)
            rotate_y += 5;
        //  Left arrow - decrease y-rotation by 5 degree
        else if (key == GLUT_KEY_LEFT)
            rotate_y -= 5;
        //  Up arrow - increase x-rotation by 5 degree
        else if (key == GLUT_KEY_UP)
            rotate_x += 5;
        //  down arrow - decrease x-rotation by 5 degree
        else if (key == GLUT_KEY_DOWN)
            rotate_x -= 5;
    }
    else if (mode == 's') {
        //  Right arrow - increase y-scaling by 0.05
        if (key == GLUT_KEY_RIGHT)
            scale_y += 0.05f;
        //  Left arrow - decrease y-scaling by 0.05
        else if (key == GLUT_KEY_LEFT)
            scale_y -= 0.05f;
        //  Up arrow - increase x-scaling by 0.05
        else if (key == GLUT_KEY_UP)
            scale_x += 0.05f;
        //  down arrow - decrease x-scaling by 0.05
        else if (key == GLUT_KEY_DOWN)
            scale_x -= 0.05f;
    }
    //  Request display update
    glutPostRedisplay();
}

void keyboard(unsigned char button, int x, int y) {
    //Exit if ESC is pressed
    if (button == 27)
        exit(0);
    //Activate mode r (Rotation) if r is pressed
    else if (button == 114) {
        mode = 'r';
        isR = true;
        isS = false;
    }
    //Activate mode s (Scaling) if s is pressed
    else if (button == 115) {
        mode = 's';
        isS = true;
        isR = false;
    }
    //  e is pressed - enable depth test
    else if (button == 101)
        glEnable(GL_DEPTH_TEST);
    //  d is pressed - disable depth test
    else if (button == 100)
        glDisable(GL_DEPTH_TEST);
    //  n is pressed - "zoom in" (increase x-, y- and z-scaling by 0.05)
    else if (button == 110) {
        scale_x += 0.05f;
        scale_y += 0.05f;
        scale_z += 0.05f;
    }
    //  m is pressed - "zoom out" (decrease x-, y- and z-scaling by 0.05)
    else if (button == 109) {
        scale_x -= 0.05f;
        scale_y -= 0.05f;
        scale_z -= 0.05f;
    }
    //Activate mode l (Loop) if l is pressed
    else if (button == 108)
        isL = true;
    //Stop mode l (Loop) if k is pressed
    else if (button == 107)
        isL = false;
    else {
        if (mode == 'r') {
            //  z is pressed - increase z-rotation by 5 degree
            if (button == 122)
                rotate_z += 5;
            //  u is pressed - decrease z-rotation by 5 degree
            else if (button == 117)
                rotate_z -= 5;
        }
        else if (mode == 's') {
            //  z is pressed - increase z-scaling by 0.05
            if (button == 122)
                scale_z += 0.05f;
            //  u is pressed - decrease z-scaling by 0.05
            else if (button == 117)
                scale_z -= 0.05f;
        }
    }
    //Request display update
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    //  Initialize GLUT and process user parameters
    glutInit(&argc, argv);

    //  Request double buffered true color window with Z-buffer and anti-aliasing
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);

    // Create window
    glutInitWindowSize(700, 700);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 800) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 800) / 2);
    glutCreateWindow("3D Cube");
   
    //  Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);

    // Callback functions
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);

    //  Pass control to GLUT for events
    glutMainLoop();

    return 0;
}