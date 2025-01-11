#include <GL/glut.h>
#include <iostream>
using namespace std;

float tree1_position = -30.0f;
float tree2_position = 20.0f;
float boat_position = 0.0f;
float boat_speed = 0.1f;

void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);

void drawTree1(float x, float y);   //  O21
void drawTree2(float x, float y);   //  O22
void drawBoat(float x, float y);    //  O23
void moveBoat();                    //  A21

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

void drawTree1(float x, float y) {      // O21
    glColor3f(0.0f, 1.0f, 0.0f);  
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);            
    glVertex2f(x + 10, y + 20);  
    glVertex2f(x + 20, y);       
    glEnd();
}

void drawTree2(float x, float y) {      // O22
    glColor3f(0.0f, 0.8f, 0.0f); 
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);           
    glVertex2f(x + 10, y + 30);  
    glVertex2f(x + 20, y);      
    glEnd();
}

void drawBoat(float x, float y) {       // O23
    glColor3f(0.8f, 0.2f, 0.2f); 
    glBegin(GL_POLYGON);
    glVertex2f(x, y);          
    glVertex2f(x + 20, y);       
    glVertex2f(x + 20, y + 10);  
    glVertex2f(x, y + 10);      
    glEnd();
}

void moveBoat() {                       // A21
    boat_position += boat_speed;  
    if (boat_position > 100) boat_position = -100;  
    glutPostRedisplay();  
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawTree1(tree1_position, -20);  // O21
    drawTree2(tree2_position, -20);  // O22
    drawBoat(boat_position, -30);    // O23
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
    glutTimerFunc(16, moveBoat, 0);  // A21
    glutMainLoop();
    return 0;
}
