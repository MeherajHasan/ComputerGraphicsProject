#include <GL/glut.h>
#include <iostream>
using namespace std;

// Declaration Part

// Step 1: Declare all variables with initial values first (if applicable)
float boat_move = 0.6f;
float boat_speed = 0.1f;
bool boat_direction = true; 

// Step 2: Declare the mouse and keyboard functions
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);

// Step 3: Declare the draw functions (functions responsible for drawing different objects)
void drawBoat(float x, float y);

// Step 4: Declare the transition functions (e.g., car/boat moving)
void moveBoat();

// Implementation Part

// Step 5: Implement the mouse and keyboard functions
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        boat_move = -100;  
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'q') {
        exit(0); 
    }
}

// Step 6: Implement the logic for the object-drawing functions
void drawBoat(float x, float y) {
    glColor3f(1.0f, 0.0f, 0.0f);  
    glBegin(GL_POLYGON);
    glVertex2f(x, y);           
    glVertex2f(x + 20, y);     
    glVertex2f(x + 20, y + 10); 
    glVertex2f(x, y + 10);     
    glEnd();
}

// Step 7: Implement the logic for the transition functions
void moveBoat() {
    if (boat_direction) {
        boat_move += boat_speed;  
    } else {
        boat_move -= boat_speed; 
    }

    if (boat_move > 100) boat_direction = false;  
    if (boat_move < -100) boat_direction = true;  
    
    glutPostRedisplay();
}

// Step 8: Define the display() function to handle rendering
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBoat(boat_move, -20); 
    glFlush();
}

// Step 9: Define the init() function to initialize OpenGL settings
void init() {
    gluOrtho2D(-200, 200, -200, 200); 
    glutMouseFunc(mouse);            
    glutKeyboardFunc(keyboard);       
}

// Step 10: Define the main() function to set up the GLUT window and start the main loop
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Boat Animation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(16, moveBoat, 0); 
    glutMainLoop();
    return 0;
}
