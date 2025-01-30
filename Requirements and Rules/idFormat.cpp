#include <GL/glut.h>
#include <iostream>
using namespace std;

float tree1_position = -30.0f;
float tree2_position = 20.0f;
float boat_position = 0.0f;
float boat_speed = 0.1f;

void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);

void drawTree1(float x, float y);   //  O201
void drawTree2(float x, float y);   //  O202
void drawBoat(float x, float y);    //  O203
void moveBoat();                    //  A201

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        boat_position = -100;  
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'q') {
        exit(0);  
    }
}

void drawTree1(float x, float y) {      // O201
    glColor3f(0.0f, 1.0f, 0.0f);  
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);            
    glVertex2f(x + 10, y + 20);  
    glVertex2f(x + 20, y);       
    glEnd();
}

void drawTree2(float x, float y) {      // O202
    glColor3f(0.0f, 0.8f, 0.0f); 
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);           
    glVertex2f(x + 10, y + 30);  
    glVertex2f(x + 20, y);      
    glEnd();
}

void drawBoat(float x, float y) {       // O203
    glColor3f(0.8f, 0.2f, 0.2f); 
    glBegin(GL_POLYGON);
    glVertex2f(x, y);          
    glVertex2f(x + 20, y);       
    glVertex2f(x + 20, y + 10);  
    glVertex2f(x, y + 10);      
    glEnd();
}

void moveBoat() {                       // A201
    boat_position += boat_speed;  
    if (boat_position > 100) boat_position = -100;  
    glutPostRedisplay();  
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawTree1(tree1_position, -20);  // O201
    drawTree2(tree2_position, -20);  // O202
    drawBoat(boat_position, -30);    // O203
    glFlush();
}

void init() {
    gluOrtho2D(-200, 200, -200, 200); 
    glutMouseFunc(mouse);           
    glutKeyboardFunc(keyboard);      
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Scene with Objects and Animations");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(16, moveBoat, 0);  // A201
    glutMainLoop();
    return 0;
}
