#include <GL/glut.h>
#include <stdlib.h>  // For rand()
#include <time.h>    // For seeding random numbers
#include <cmath>    // For sin() and cos()
#include <iostream>  // For input/output

//.......................................Global Variables & Function Declarations..........................................

#define NUM_SNOWFLAKES 1000  // Number of snowflakes

bool isDay = true;
bool isSnowFalling = false;
bool isEvening = false;
char key;
float sceenIntensity = 0.0f;
float bladeRotationAngle = 0.0f;

float cloud1PosX = 0.0f; // Initial position of the cloud
float cloudSpeed = 0.2f;     // Speed at which the cloud moves

float cloud2PosX = 280.0f; // Initial position of the cloud
float cloudSpeed2 = -0.2f;

float cloud3PosX = 180.0f; // Initial position of the cloud
float cloudSpeed3 = -0.2f;  // Speed at which the cloud moves (negative for moving left)


// Define initial position and movement speed
float boatPositionX = 0.0f;
float boatSpeed = 0.1f;  // Speed of movement, you can adjust this

// Define a flag for the direction
bool movingRight = true;

typedef struct {
    float x, y;    // Position of the snowflake
    float speed;   // Falling speed of the snowflake
    float size;    // Thickness of the snowflake
} Snowflake;

typedef struct {
    float x, y;
} Point;

//display & initializer
void initGL();
void display();

//keyboard-mouse
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);

//shapes
void drawLines(Point p1, Point p2);
void drawPolygon(Point* points, int numPoints);
void drawTriangle(Point p1, Point p2, Point p3);
void drawCircle(float x1, float y1, float radius);
void drawRectangle(Point p1, Point p2, Point p3, Point p4);

//scene elements
void drawSky();
void drawCloud1();
void drawCloud2();
void drawCloud3();
void drawSunMoon();
void drawStar();
void drawFireflies();
void drawField();
void drawCloudBackground();
void drawBackShadow();
void drawBackground();
void drawHut1();
void drawHut2();
void drawHut3();
void drawHut4();
void drawHut5();
void drawHut6();
void drawPond();
void drawWindMill();
void drawSnowflakes();
void drawMountain1();
void drawMountain2();
void drawMountain3();
void drawMountain4();
void drawMountain5();
void drawMountain6();
void drawTrees1();
void drawTrees2();
void drawTrees3();
void drawRoad();
void drawMovableCloud1();
void drawMovableCloud2();
void drawMovableCloud3();
void drawFence(int x, float y);
void drawBoat();
void drawFence2(int x, float y);

//updater
void updateSnowflakes(int value);

//....................................................Snowflakes part.....................................................

Snowflake snowflakes[NUM_SNOWFLAKES];
int snowEnabled = 0;  // Toggle for snowfall (1 = on, 0 = off)

// Initialize snowflakes with random positions, speeds, and sizes
void initSnowflakes() {
    srand(time(NULL));  // Seed random number generator
    for (int i = 0; i < NUM_SNOWFLAKES; i++) {
        snowflakes[i].x = (rand() % 400) - 200;  // Random x between -200 and 200
        snowflakes[i].y = (rand() % 400) + 200;  // Start above the visible area
        snowflakes[i].speed = (rand() % 5 + 1) / 10.0f;  // Random speed between 0.1 and 0.5
        snowflakes[i].size = (rand() % 3 + 1);  // Random size between 1 and 3
    }
}

// Function to calculate the binomial coefficient (n choose k)
int binomialCoeff(int n, int k) {
    int res = 1;
    if (k > n - k) k = n - k;  // Take advantage of symmetry
    for (int i = 0; i < k; i++) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

void updateSnowflakes(int value) {
    if (snowEnabled) {
        for (int i = 0; i < NUM_SNOWFLAKES; i++) {
            if (snowflakes[i].y > -200) {  // If the snowflake is still above the bottom
                snowflakes[i].y -= snowflakes[i].speed;  // Move snowflake down
            }
            else {  // Reset snowflake to top only if it's completely off-screen
                snowflakes[i].y = 200 + (rand() % 100);  // Reset slightly above the visible area
                snowflakes[i].x = (rand() % 400) - 200;  // Randomize x position
            }
        }
    }
    glutPostRedisplay();  // Request a redraw
    glutTimerFunc(16, updateSnowflakes, 0);  // Call this function again after 16ms (~60 FPS)
}

//....................................................Bezier curve part.....................................................

// Function to generate Bézier curve points for n control points
void bezierCurve(Point* controlPoints, int numPoints, int segments) {  // Draw the curve as a series of line segments
    for (int j = 0; j <= segments; j++) {
        float t = (float)j / segments;
        float x = 0.0f, y = 0.0f;
        for (int i = 0; i < numPoints; i++) {
            float coeff = binomialCoeff(numPoints - 1, i) * pow(1 - t, numPoints - 1 - i) * pow(t, i);
            x += coeff * controlPoints[i].x;
            y += coeff * controlPoints[i].y;
        }
        glVertex2f(x, y);  // Plot the calculated point on the Bézier curve
    }
}

void fadeToBlack(int value) {
    if (sceenIntensity < 1.0f) {
        sceenIntensity += 0.01f;  // Increment intensity (adjust the speed by changing this value)
        if (sceenIntensity > 1.0f) {
            sceenIntensity = 1.0f;  // Clamp to maximum
        }
        glutPostRedisplay();  // Request a redraw
        glutTimerFunc(16, fadeToBlack, 0);  // Call this function again after 16ms (~60 FPS)
    }
}

// Keyboard callback for toggling snowfall
void keyboard(unsigned char key, int x, int y) {
    if (key == 's' || key == 'S') {
        snowEnabled = !snowEnabled;  // Toggle snowfall on/off
    }
    if (key == 'd' || key == 'D') {
        isDay = !isDay;  // Toggle day/night
    }
    if (key == 'e' || key == 'E') {
        isDay = !isDay;  // Toggle day/night
        isEvening = !isEvening;  // Toggle evening
    }
    if (key == 'f' || key == 'F') {  // Press 'F' to start fade to black
        if (sceenIntensity < 1.0f) {
            glutTimerFunc(0, fadeToBlack, 0);  // Start the fade effect
        }
    }
}

// Special keys function for Shift or Arrow keys
void specialKeys(int key, int x, int y) {
    int modifiers = glutGetModifiers();
    if (modifiers & GLUT_ACTIVE_SHIFT) {  // Detect if Shift is pressed
        for (int i = 0; i < NUM_SNOWFLAKES; i++) {
            snowflakes[i].speed += 0.1;  // Increase snowflake speed
        }
    }
    if (modifiers & GLUT_ACTIVE_CTRL) {  // Detect if Shift is pressed
        for (int i = 0; i < NUM_SNOWFLAKES; i++) {
            snowflakes[i].speed -= 0.1;  // Increase snowflake speed
        }
    }
}

// Set up OpenGL
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);  // Set up a 2D orthographic viewing region

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void updateBoatPosition() {
    // Check if the boat exceeds the threshold
    if (movingRight) {
        boatPositionX += boatSpeed;
        if (boatPositionX >= 200.0f) {
            movingRight = false;  // Change direction to left
        }
    }
    else {
        boatPositionX -= boatSpeed;
        if (boatPositionX <= 0.0f) {
            movingRight = true;  // Change direction to right
        }
    }
}
// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    drawSunMoon();
    drawHut1();
    drawHut6();
    drawHut3();
    drawHut2();
    drawHut4();
    drawRoad();
    drawCloud1();
    drawCloud2();
    drawCloud3();
    drawMovableCloud1();
    drawMovableCloud2();
    drawMovableCloud3();
    drawTrees1();
    drawTrees2();
    drawMountain6();
    drawMountain5();
    drawMountain4();
    drawMountain3();
    drawMountain2();
    drawMountain1();
    drawPond();
    drawWindMill();
    drawHut5();
    drawTrees3();
    drawFence(10, 10.0);
    drawBoat();
    drawSnowflakes();
    updateBoatPosition();
    drawFence2(10, 5);

    glutSwapBuffers();
}

void updateBladeRotation(int value) {
    bladeRotationAngle -= 1.0f;  // Rotate anticlockwise (adjust this value for speed)
    if (bladeRotationAngle <= -360.0f) {
        bladeRotationAngle = 0.0f;  // Reset the angle to 0 when it completes a full rotation
    }
    glutPostRedisplay();  // Request a redraw to update the display
    glutTimerFunc(16, updateBladeRotation, 0);  // Call this function again every ~16 ms (60 FPS)
}
// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Snowfall Scene with Toggle");

    initGL();
    initSnowflakes();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);  // Register keyboard callback
    glutSpecialFunc(specialKeys);  // Register special keys callback
    glutTimerFunc(0, updateSnowflakes, 0);
    glutTimerFunc(0, updateBladeRotation, 0);  // Start the rotation

    glutMainLoop();
    return 0;
}

//....................................................Function Definitions.....................................................

// Function to draw a line between two points
void drawLines(Point p1, Point p2) {
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

// Function to draw a border around a polygon
void drawBorder(Point* pts, int count) {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < count; i++) {
        glVertex2f(pts[i].x, pts[i].y);
    }
    glEnd();
}

// Function to draw a rectangle using four points
void drawRectangle(Point p1, Point p2, Point p3, Point p4) {
    glBegin(GL_QUADS);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p3.x, p3.y);
    glVertex2f(p4.x, p4.y);
    glEnd();
}

// Function to draw a polygon
void drawPolygon(Point* points, int numPoints) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < numPoints; i++) {
        glVertex2f(points[i].x, points[i].y);  // Access each point from the array
    }
    glEnd();
}

// Function to draw a triangle using three points
void drawTriangle(Point p1, Point p2, Point p3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p3.x, p3.y);
    glEnd();
}

// Function to draw a circle using a center point and radius
void drawCircle(Point center, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(center.x, center.y);  // Center point
    for (int i = 0; i <= 1000; i++) {
        float angle = i * (M_PI / 180.0f);  // Convert degrees to radians
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawBackground() {
    drawField();
    drawCloudBackground();
    drawBackShadow();
}

void drawField() {
    // points
    Point p1 = { -200.0, 0.0 };
    Point p2 = { 200.0, 0.0 };
    Point p3 = { 200.0, -200.0 };
    Point p4 = { -200.0, -200.0 };

    if (isDay) {
        glColor3ub(38, 109, 5);
    }
    else if (isEvening) {
        glColor3ub(197, 152, 63);
    }
    else {
        glColor3ub(33, 63, 26);
    }
    drawRectangle(p1, p2, p3, p4);
}

void drawBackShadow() {
    Point p1 = { -200.0, 80.0 };
    Point p2 = { 200.0, 80.0 };
    Point p3 = { 200.0, 0.0 };
    Point p4 = { -200.0, 0.0 };

    glColor3ub(25, 79, 168);
    drawRectangle(p1, p2, p3, p4);
}

void drawCloudBackground() {
    Point p1 = { -200.0, 80.0 };
    Point p2 = { 200.0, 80.0 };
    Point p3 = { 200.0, 200.0 };
    Point p4 = { -200.0, 200.0 };

    glColor3ub(60, 192, 234);
    drawRectangle(p1, p2, p3, p4);
}

void drawSnowflakes() {
    glDisable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  // White color for snowflakes
    if (snowEnabled) {
        glEnable(GL_POINT_SMOOTH);    // Enable smooth points for circular snowflakes
        glBegin(GL_POINTS);  // Start drawing points
        for (int i = 0; i < NUM_SNOWFLAKES; i++) {
            glPointSize(snowflakes[i].size);  // Set point size for this snowflake
            glVertex2f(snowflakes[i].x, snowflakes[i].y);  // Draw snowflake at its position
        }
        glEnd();
    }
}

void drawHut1() {

    glPushMatrix();
    glTranslatef(0, 0, 0);

    glColor3ub(159, 96, 48);
    drawRectangle({ -170, -150 }, { -130, -150 }, { -130, -185 }, { -170, -180 });
    glColor3ub(220, 142, 32);
    drawRectangle({ -110, -120 }, { -90, -140 }, { -95, -145 }, { -115, -125 });
    glColor3ub(158, 96, 9);
    drawRectangle({ -150.0, -120.0 }, { -110.0, -120.0 }, { -130, -150 }, { -170, -150 });
    glColor3ub(191, 124, 28);
    drawRectangle({ -174, -154 }, { -134, -154 }, { -110.0, -120.0 }, { -150.0, -120.0 });
    glColor3ub(153, 100, 26);
    drawRectangle({ -130, -150 }, { -130, -185 }, { -95, -177 }, { -95, -145 });
    drawTriangle({ -130, -150 }, { -114, -126 }, { -95, -145 });
    glColor3ub(181, 117, 71);
    drawRectangle({ -125, -160 }, { -100, -155 }, { -100, -165 }, { -125, -170 });
    glColor3ub(181, 117, 71);
    drawRectangle({ -160, -160 }, { -140, -160 }, { -140.08, -183.74 }, { -160.15, -181.23 });

    glPopMatrix();
}

void drawHut2() {

    Point p1[] = { { -200, -70 }
                    , { -194.45, -69.56 }
                    , { -186.93864,-56.29343  }
                    , { -189.70233,-52.50157 }
                    , { -200, -66.17 } };

    Point p2[] = { { -189.70233,-52.50157 }
                    , { -166.86378,-55.78158 }
                    , { -155.3906,-70.76946  }
                    , { -177.49342,-70.66308 } };

    Point p3[] = { { -195.44525,-69.55954 }
                    , { -187.33344,-56.44972 }
                    , { -179.19417,-68.17271  }
                    , { -180.24478,-82.65024 }
                    , { -195.53828,-80.33058 } };

    Point p4[] = { { -180.24478,-82.65024 }
                , { -179.19417,-68.17271 }
                , { -177.49342,-70.66308 }
                , { -159.81952,-70.75396 }
                , { -160.24117,-81.58383 } };

    Point p5[] = { { -195.53828,-80.33058 }
                , { -180.24478,-82.65024 }
                , { -160.24117,-81.58383 }
                , { -160.03, -80.45 }
                , { -158.67085,-80.98693 }
                , { -158.56215,-83.64988}
                , { -180.7434,-85.8587 }
                , { -197.66785,-83.06704 } };

    Point p6[] = { { -173.25122,-72.44586 }
                , { -165.8141,-72.81313 }
                , { -166.15513,-81.44388 }
                , { -173.23842,-81.77181 } };

    glPushMatrix();
    glTranslatef(0, 30, 0);

    glColor3ub(190, 100, 23);
    drawPolygon(p1, 5);
    glColor3ub(207, 139, 4);
    drawPolygon(p2, 4);
    glColor3ub(117, 100, 92);
    drawPolygon(p3, 5);
    glColor3ub(117, 100, 92);
    drawPolygon(p4, 5);
    glColor3ub(177, 108, 32);
    drawPolygon(p5, 8);
    glColor3ub(195, 143, 64);
    drawPolygon(p6, 4);

    glPopMatrix();
}

void drawHut3() {

    Point p1[] = { { -164.44484,-58.9497 }
                    , { -160.12076,-55.23075 }
                    , { -157.40234,-58.63114  }
                    , { -161.55503,-62.73831 } };

    Point p2[] = { { -160.12076,-55.23075 }
                    , { -136.65869,-58.67551 }
                    , { -125.24499,-70.96804  }
                    , { -148.55596,-69.6874 } };

    Point p3[] = { { -161.55503,-62.73831 }
                    , { -157.40234,-58.63114 }
                    , { -150.57372,-67.29017  }
                    , { -150.40465,-79.95023 }
                    , { -160.05964,-77.52527 } };

    Point p4[] = { { -150.85003,-66.60195 }
                , { -148.55596,-69.6874 }
                , { -128.73075,-70.77559}
                , { -128.81368,-78.99759 }
                , { -150.40465,-79.95023 } };

    Point p5[] = { { -160.05964,-77.52527 }
                , { -160.02, -80.47 }
                , { -150.6555,-83.01752 }
                , { -128.21106,-81.49419 }
                , { -128.22182,-79.47109 }
                , { -128.81368,-78.99759 }
                , { -150.40465,-79.95023 } };

    Point p6[] = { { -141.85609,-71.43914 }
                , { -136.08297,-71.6274 }
                , { -135.58096,-78.7183 }
                , { -142.2326,-78.78105 } };

    glPushMatrix();
    glTranslatef(0, 30, 0);

    glColor3ub(190, 100, 23);
    drawPolygon(p1, 4);
    glColor3ub(207, 139, 4);
    drawPolygon(p2, 4);
    glColor3ub(117, 100, 92);
    drawPolygon(p3, 5);
    glColor3ub(117, 100, 92);
    drawPolygon(p4, 5);
    glColor3ub(177, 108, 32);
    drawPolygon(p5, 7);
    glColor3ub(195, 143, 64);
    drawPolygon(p6, 4);

    glPopMatrix();
}

void drawHut4() {

    Point p1[] = { { -58.97924,-48.44328 }
                    , { -51.61276,-42.05356 }
                    , { -49.57782,-44.2513  }
                    , { -55.84544,-48.60607 } };

    Point p2[] = { { -51.61276,-42.05356 }
                    , { -37.61237,-44.04781 }
                    , { -31.01916,-51.41429  }
                    , { -44.49047,-50.47822 } };

    Point p3[] = { { -45.97837,-55.68412 }
                    , { -46.01, -48.61 }
                    , { -49.57782,-44.2513 }
                    , { -55.84544,-48.60607 }
                    , { -55.82743,-55.29146 } };

    Point p4[] = { { -46.01, -48.61 }
                , { -44.49047,-50.47822 }
                , { -33.67, -51.90 }
                , { -34.00244,-55.45507 }
                , { -45.97837,-55.68412 } };

    Point p5[] = { { -55.82743,-55.29146 }
                , { -45.97837,-55.68412 }
                , { -34.00244,-55.45507 }
                , { -33.25533,-56.03043 }
                , { -33.13783,-56.9313 }
                , { -45.98504,-57.34257 }
                , { -56.53823,-56.73984 }
                , { -56.51182,-55.61739 } };

    Point p6[] = { { -52.6695,-49.56503 }
                , { -48.48705,-49.62478 }
                , { -48.4273,-54.22547 }
                , { -52.72924,-54.10597 } };

    glPushMatrix();
    glTranslatef(60, 80, 0);
    glScalef(2, 2, 1);

    glColor3ub(208, 152, 88);
    drawPolygon(p1, 4);
    glColor3ub(210, 119, 1);
    drawPolygon(p2, 4);
    glColor3ub(185, 168, 158);
    drawPolygon(p3, 5);
    glColor3ub(153, 100, 26);
    drawPolygon(p4, 5);
    glColor3ub(181, 117, 71);
    drawPolygon(p5, 8);
    glColor3ub(195, 143, 64);
    drawPolygon(p6, 4);

    glPopMatrix();
}

void drawHut6() {

    glPushMatrix();
    glTranslatef(30, 50, 0);
    glScalef(.8, .8, 1);

    glColor3ub(159, 96, 48);
    drawRectangle({ -170, -150 }, { -130, -150 }, { -130, -185 }, { -170, -180 });
    glColor3ub(220, 142, 32);
    drawRectangle({ -110, -120 }, { -90, -140 }, { -95, -145 }, { -115, -125 });
    glColor3ub(158, 96, 9);
    drawRectangle({ -150.0, -120.0 }, { -110.0, -120.0 }, { -130, -150 }, { -170, -150 });
    glColor3ub(191, 124, 28);
    drawRectangle({ -174, -154 }, { -134, -154 }, { -110.0, -120.0 }, { -150.0, -120.0 });
    glColor3ub(153, 100, 26);
    drawRectangle({ -130, -150 }, { -130, -185 }, { -95, -177 }, { -95, -145 });
    drawTriangle({ -130, -150 }, { -114, -126 }, { -95, -145 });
    glColor3ub(181, 117, 71);
    drawRectangle({ -125, -160 }, { -100, -155 }, { -100, -165 }, { -125, -170 });
    glColor3ub(181, 117, 71);
    drawRectangle({ -160, -160 }, { -140, -160 }, { -140.08, -183.74 }, { -160.15, -181.23 });

    glPopMatrix();
}

void drawRoad() {
    // Define control points for the Bézier curves
    Point c1[] = { { -60, -170 }, { -78.11437, -185.90823 }, { -110, -190 } };
    Point c2[] = { { -90, -200 }, { -59.53942, -196.21258 }, { -40, -180 } };
    int segments = 100;  // Number of segments for the Bézier curve

    glPushMatrix();
    glTranslated(0, 0, 0);
    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_POLYGON);
    bezierCurve(c2, 3, segments);
    bezierCurve(c1, 3, segments);// Second Bézier curve
    // glVertex2f(-200, -190);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-200, -190);
    glVertex2f(-200, -200);
    glVertex2f(-90, -200);
    glVertex2f(-110, -190);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-60, -170);
    glVertex2f(30, 0);
    glVertex2f(50, 0);
    glVertex2f(-40, -180);
    glEnd();

    glPopMatrix();
}

void drawCloud1() {
    glEnable(GL_BLEND);
    // cloud1
    Point p1[] = { { -200.0, 162.85 },
                    { -139.98288,151.64423 },
                    { -120, 80 } };

    // cloud2
    Point p2[] = { { -140, 80 },
                    {-88.58408,137.74365},
                    { -30.2847,119.87084} };

    // cloud3
    Point p3[] = { { -60, 100 },
                    {-20, 160},
                    { 46.73857,105.82793} };

    // cloud4
    Point p4[] = { { 46.73857,105.8279 },
                    {60, 160},
                    {107.59122,134.76485} };

    // cloud5
    Point p5[] = { {100, 140},
                    {160, 175},
                    {183.33786,105.82793} };

    // cloud6
    Point p6[] = { {160, 110},
                    {150, 160},
                    {200, 150} };

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0, 0, 0);

    glBegin(GL_POLYGON);
    glVertex2f(-200, 80);
    bezierCurve(p1, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-40, 80);
    bezierCurve(p2, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(45, 80);
    glVertex2f(-40, 80);
    bezierCurve(p3, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(110, 80);
    glVertex2f(30, 80);
    bezierCurve(p4, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(90, 80);
    glVertex2f(200, 80);
    bezierCurve(p5, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(160, 85);
    bezierCurve(p6, 3, 100);
    glVertex2f(200, 80);
    glEnd();

    glPopMatrix();

}

void drawCloud2() {
    glEnable(GL_BLEND);
    // cloud1
    Point p1[] = { { -200.0, 162.85 },
                    { -139.98288,151.64423 },
                    { -120, 80 } };

    // cloud2
    Point p2[] = { { -140, 80 },
                    {-88.58408,137.74365},
                    { -30.2847,119.87084} };

    // cloud3
    Point p3[] = { { -60, 100 },
                    {-20, 160},
                    { 46.73857,105.82793} };

    // cloud4
    Point p4[] = { { 46.73857,105.8279 },
                    {60, 160},
                    {107.59122,134.76485} };

    // cloud5
    Point p5[] = { {100, 140},
                    {160, 175},
                    {183.33786,105.82793} };

    // cloud6
    Point p6[] = { {160, 110},
                    {150, 160},
                    {200, 150} };


    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

    glPushMatrix();
    glTranslatef(0, 5, 0);

    glBegin(GL_POLYGON);
    glVertex2f(-200, 80);
    bezierCurve(p1, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-40, 80);
    bezierCurve(p2, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(45, 80);
    glVertex2f(-40, 80);
    bezierCurve(p3, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(110, 80);
    glVertex2f(30, 80);
    bezierCurve(p4, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(90, 80);
    glVertex2f(200, 80);
    bezierCurve(p5, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(160, 85);
    bezierCurve(p6, 3, 100);
    glVertex2f(200, 80);
    glEnd();

    glPopMatrix();

}

void drawCloud3() {
    glEnable(GL_BLEND);
    // cloud1
    Point p1[] = { { -200.0, 162.85 },
                    { -139.98288,151.64423 },
                    { -120, 80 } };

    // cloud2
    Point p2[] = { { -140, 80 },
                    {-88.58408,137.74365},
                    { -30.2847,119.87084} };

    // cloud3
    Point p3[] = { { -60, 100 },
                    {-20, 160},
                    { 46.73857,105.82793} };

    // cloud4
    Point p4[] = { { 46.73857,105.8279 },
                    {60, 160},
                    {107.59122,134.76485} };

    // cloud5
    Point p5[] = { {100, 140},
                    {160, 175},
                    {183.33786,105.82793} };

    // cloud6
    Point p6[] = { {160, 110},
                    {150, 160},
                    {200, 150} };


    glColor4f(1.0f, 1.0f, 1.0f, 0.25f);

    glPushMatrix();
    glTranslatef(0, 10, 0);

    glBegin(GL_POLYGON);
    glVertex2f(-200, 80);
    bezierCurve(p1, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-40, 80);
    bezierCurve(p2, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(45, 80);
    glVertex2f(-40, 80);
    bezierCurve(p3, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(110, 80);
    glVertex2f(30, 80);
    bezierCurve(p4, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(90, 80);
    glVertex2f(200, 80);
    bezierCurve(p5, 3, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(160, 85);
    bezierCurve(p6, 3, 100);
    glVertex2f(200, 80);
    glEnd();

    glPopMatrix();

}

void drawMovableCloud1() {
    // Move the cloud horizontally based on the current position
    cloud1PosX += cloudSpeed;

    // If the cloud moves past the right edge, reset it to the left
    if (cloud1PosX > 350.0f) {
        cloud1PosX = -200.0f; // Reset cloud position to the left side
    }

    //circles
    glPushMatrix();
    glTranslatef(cloud1PosX, 0, 0);  // Translate the cloud to its current position

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    drawCircle({ -121.78197,167.93386 }, sqrt(148.77));
    drawCircle({ -117.19636,163.07851 }, sqrt(137.54));
    drawCircle({ -127.24, 157.03 }, sqrt(79.52));
    drawCircle({ -137.29213,157.95341 }, sqrt(61.59));
    drawCircle({ -138.23623,166.31541 }, sqrt(53.88));
    drawCircle({ -145.789,161.7298 }, sqrt(65.94));

    glPopMatrix();
}

void drawMovableCloud2() {
    cloud2PosX += cloudSpeed2;

    // If the cloud moves past the left edge, wrap it around to the right side
    if (cloud2PosX < -300.0f) {
        cloud2PosX = 300.0f;  // Wrap the cloud back to the right side (off-screen)
    }

    //circles
    glPushMatrix();
    glTranslatef(cloud2PosX, 0, 0);  // Translate the cloud to its current position

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    drawCircle({ -121.78197,167.93386 }, sqrt(148.77));
    drawCircle({ -117.19636,163.07851 }, sqrt(137.54));
    drawCircle({ -127.24, 157.03 }, sqrt(79.52));
    drawCircle({ -137.29213,157.95341 }, sqrt(61.59));
    drawCircle({ -138.23623,166.31541 }, sqrt(53.88));
    drawCircle({ -145.789,161.7298 }, sqrt(65.94));

    glPopMatrix();

}

void drawMovableCloud3() {
    // Move the cloud horizontally based on the current position
    cloud3PosX += cloudSpeed3;

    // If the cloud moves past the left edge, reset it to the right
    if (cloud3PosX < -200.0f) {
        cloud3PosX = 300.0f; // Reset cloud position to the right side
    }

    //circles
    glPushMatrix();
    glTranslatef(cloud3PosX, 0, 0);  // Translate the cloud to its current position

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    drawCircle({ -121.78197,167.93386 }, sqrt(148.77));
    drawCircle({ -117.19636,163.07851 }, sqrt(137.54));
    drawCircle({ -127.24, 157.03 }, sqrt(79.52));
    drawCircle({ -137.29213,157.95341 }, sqrt(61.59));
    drawCircle({ -138.23623,166.31541 }, sqrt(53.88));
    drawCircle({ -145.789,161.7298 }, sqrt(65.94));

    glPopMatrix();
}

void drawTrees1() {
    //Trees
    glColor3ub(23, 116, 78);

    glPushMatrix();
    glTranslatef(0, 0, 0);

    drawCircle({ -63.45423,-146.51753 }, sqrt(103.5));
    drawCircle({ -63.45423,-139.35682 }, sqrt(51.28));
    drawCircle({ -63.78472,-130.76397 }, sqrt(34.15));
    glColor4f(0.5f, 0.5f, 1.0f, 1.0f);
    drawRectangle({ -65,-155 }, { -63.15012,-155.13121 }, { -62.80601,-166.08535 }, { -65.32948,-166.1427 });

    glPopMatrix();
}

void drawTrees2() {
    //Trees
    glColor3ub(23, 116, 78);

    glPushMatrix();
    glTranslatef(0, 0, 0);

    drawCircle({ -40.76029,-111.81563 }, sqrt(81.5));
    drawCircle({ -40.20947,-104.21426 }, sqrt(58.28));
    drawCircle({ -39.98914,-95.73157 }, sqrt(28.15));
    glColor4f(0.5f, 0.5f, 1.0f, 1.0f);
    drawRectangle({ -40.91954,-120.26526 }, { -39.54483,-120.26526 }, { -39.40611,-128.11332 }, { -41.67672,-128.78609 });

    glPopMatrix();
}

void drawMountain1() {
    //Mountain
    Point p1[] = { { -120, 120 }
                    , { -90, 170 }
                    , { -60, 120 } };

    glPushMatrix();
    glTranslatef(0, 0, 0);
    // glColor4f(0.0f, 0.5f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(21, 99, 75); // Red
    glVertex2f(-92.52137, 66.94745);  // Center point

    glColor3ub(54, 176, 30); // Blue
    glVertex2f(-120, 120); // Bottom-left
    glVertex2f(-60, 120);  // Bottom-right
    glColor3ub(21, 99, 75); // Blue
    glVertex2f(-40, 0);   // Top-right
    glVertex2f(-140, 0);  // Top-left
    glVertex2f(-120, 120); // Repeat first corner to close shape
    glEnd();

    glColor3ub(54, 176, 30);
    glBegin(GL_POLYGON);
    glVertex2f(-120, 120);
    bezierCurve(p1, 3, 100);
    glVertex2f(-60, 120);
    glEnd();

    glPopMatrix();
}

void drawMountain2() {
    //Mountain
    Point p1[] = { { -80, 160 }
                    , { -60, 180 }
                    , { -40, 160 } };

    glPushMatrix();
    glTranslatef(10, -30, 0);
    // glColor4f(0.0f, 0.5f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(21, 99, 75); // Red
    glVertex2f(-60, 120);  // Center point

    glColor3ub(54, 176, 30); // Blue
    glVertex2f(-80, 160); // Bottom-left
    glVertex2f(-40, 160);  // Bottom-right
    glColor3ub(21, 99, 75); // Blue
    glVertex2f(-20, 30);   // Top-right
    glVertex2f(-100, 30);  // Top-left
    glVertex2f(-80, 160); // Repeat first corner to close shape
    glEnd();

    glColor3ub(54, 176, 30);
    glBegin(GL_POLYGON);
    glVertex2f(-80, 160);
    bezierCurve(p1, 3, 100);
    glVertex2f(-40, 160);
    glEnd();

    glPopMatrix();
}

void drawMountain3() {
    //Mountain
    Point p1[] = { { -20,160 }
                    , { 10, 185 }
                    , { 40,160 } };

    glPushMatrix();
    glTranslatef(170, 0, 0);
    // glColor4f(0.0f, 0.5f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(21, 99, 75); // Red
    glVertex2f(0, 80);  // Center point

    glColor3ub(54, 176, 30); // Blue
    glVertex2f(-20, 160); // Bottom-left
    glVertex2f(40, 160);  // Bottom-right
    glColor3ub(21, 99, 75); // Blue
    glVertex2f(50, 0);  // Top-left
    glVertex2f(-60, 0);   // Top-right
    glVertex2f(-20, 160); // Repeat first corner to close shape
    glEnd();

    glColor3ub(54, 176, 30);
    glBegin(GL_POLYGON);
    glVertex2f(-20, 160);
    bezierCurve(p1, 3, 100);
    glVertex2f(40, 160);
    glEnd();

    glPopMatrix();
}

void drawMountain4() {
    //Mountain
    Point p1[] = { { -80, 160 }
                    , { -60, 180 }
                    , { -40, 160 } };

    glPushMatrix();
    glTranslatef(140, -23, 0);
    glScalef(2, .7, 1);
    // glColor4f(0.0f, 0.5f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(21, 99, 75); // Red
    glVertex2f(-60, 120);  // Center point

    glColor3ub(54, 176, 30); // Blue
    glVertex2f(-80, 160); // Bottom-left
    glVertex2f(-40, 160);  // Bottom-right
    glColor3ub(21, 99, 75); // Blue
    glVertex2f(-20, 30);   // Top-right
    glVertex2f(-100, 30);  // Top-left
    glVertex2f(-80, 160); // Repeat first corner to close shape
    glEnd();

    glColor3ub(54, 176, 30);
    glBegin(GL_POLYGON);
    glVertex2f(-80, 160);
    bezierCurve(p1, 3, 100);
    glVertex2f(-40, 160);
    glEnd();

    glPopMatrix();
}

void drawMountain5() {
    //Mountain
    Point p1[] = { { -120, 120 }
                    , { -90, 170 }
                    , { -60, 120 } };

    glPushMatrix();
    glTranslatef(180, 0, 0);
    // glColor4f(0.0f, 0.5f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(21, 99, 75); // Red
    glVertex2f(-92.52137, 66.94745);  // Center point

    glColor3ub(54, 176, 30); // Blue
    glVertex2f(-120, 120); // Bottom-left
    glVertex2f(-60, 120);  // Bottom-right
    glColor3ub(21, 99, 75); // Blue
    glVertex2f(-40, 0);   // Top-right
    glVertex2f(-140, 0);  // Top-left
    glVertex2f(-120, 120); // Repeat first corner to close shape
    glEnd();

    glColor3ub(54, 176, 30);
    glBegin(GL_POLYGON);
    glVertex2f(-120, 120);
    bezierCurve(p1, 3, 100);
    glVertex2f(-60, 120);
    glEnd();

    glPopMatrix();
}

void drawMountain6() {
    //Mountain
    Point p1[] = { { -80, 160 }
                    , { -60, 180 }
                    , { -40, 160 } };

    glPushMatrix();
    glTranslatef(-50, -23, 0);
    glScalef(2, .7, 1);
    // glColor4f(0.0f, 0.5f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(21, 99, 75); // Red
    glVertex2f(-60, 120);  // Center point

    glColor3ub(54, 176, 30); // Blue
    glVertex2f(-80, 160); // Bottom-left
    glVertex2f(-40, 160);  // Bottom-right
    glColor3ub(21, 99, 75); // Blue
    glVertex2f(-20, 30);   // Top-right
    glVertex2f(-100, 30);  // Top-left
    glVertex2f(-80, 160); // Repeat first corner to close shape
    glEnd();

    glColor3ub(54, 176, 30);
    glBegin(GL_POLYGON);
    glVertex2f(-80, 160);
    bezierCurve(p1, 3, 100);
    glVertex2f(-40, 160);
    glEnd();

    glPopMatrix();
}

void drawPond() {
    //Pond
    glPushMatrix();
    glTranslatef(0, 0, 0);

    glBegin(GL_POLYGON);
    glColor4f(0.1, 0.5, 0.7, 1.0f);
    glVertex2f(-40, -200);
    glVertex2f(-20, -180);
    glVertex2f(0, -140);
    glVertex2f(40, -120);
    glVertex2f(60, -100);
    glVertex2f(100, -80);
    glVertex2f(140, -80);
    glVertex2f(180, -80);
    glVertex2f(200, -80);
    glColor4f(0.05, 0.3, 0.6, 1.0f);
    glVertex2f(200, -200);

    glEnd();
}

void drawWindMill() {
    Point p1[] = { { 145.58926,-44.13562 }
                    , { 151.30299,11.70645 }
                    , { 179.72283,11.75327 }
                    , {185.19305,-44.2032 } };

    Point p2[] = { { 151.06889,14.6093 }
                , { 151.30299,11.70645 }
                , { 179.72283,11.75327 }
                , {180.05057,14.8434} };

    Point p3[] = { { 152.85, 14.62 }
                , { 178.21, 14.62 }
                , { 165.32021,26.99323 } };

    Point p4[] = {
        { 170, 14.76 }
        , { 165.88905,10.0263 }
        , { 190.83192,-15.80163 }
        , { 197.16928, -9.30075 }
    };

    Point p5[] = {
            { 160.02, 14.14 }
            , { 155.80025,18.33329 }
            , { 130.10708,-6.76923 }
            , { 136.53098,-13.08281 }
    };

    Point p6[] = {
        { 170, 24.22 }
        , { 174.00286,20.1341 }
        , { 199.53054,44.97117 }
        , { 193.48915,51.101 }
    };

    Point p7[] = {
        { 160.89, 23.34 }
        , { 164.0015,27.97425 }
        , { 138.94507,53.61518 }
        , { 132.93579,47.45037 }
    };

    //windows

    Point p8[] = {
        { 160.77735,-30.01885 }
        , { 170,-30 }
        , { 170.2384,-42.80758 }
        , { 160.84183,-42.68756 }
    };

    Point p9[] = {
        { 151.03776,-19.33832 }
        , { 154.50488,-19.15192 }
        , { 154.61672,-25.86247 }
        , { 151.22416,-25.82519 }
    };

    Point p10[] = {
        { 175.41945,-19.33832 }
        , { 178.84929,-19.45016 }
        , { 178.73745,-26.16072 }
        , { 175.49401,-26.04888 }
    };

    Point p11[] = {
        { 163.31755,4.57291 }
        , { 166.65718,4.57291 }
        , { 166.79077,-1.12673 }
        , { 163.18396,-0.99315 }
    };

    glPushMatrix();
    glTranslatef(0, 0, 0);  // Move to the center of the windmill (if needed)

    // Windmill base (fixed, no rotation)
    glColor3f(0.5f, 0.5f, 0.5f);
    drawPolygon(p1, 4);

    glColor3f(0.5f, 0.5f, 0.5f);
    drawPolygon(p2, 4);

    glColor3f(0.5f, 0.5f, 0.5f);
    drawPolygon(p3, 3);

    // // Draw fixed elements (not rotating)
    // drawPolygon(p4, 4);
    // drawPolygon(p5, 4);
    // drawPolygon(p6, 4);
    // drawPolygon(p7, 4);

    // Windows
    glColor3f(0.5f, 0.0f, 0.5f);
    drawPolygon(p8, 4);
    drawPolygon(p9, 4);
    drawPolygon(p10, 4);
    drawPolygon(p11, 4);

    // Rotate and draw the blades
    glPushMatrix();
    glTranslatef(164.9647f, 19.2735f, 0.0f);  // Move to the center of the circle for rotation
    glRotatef(bladeRotationAngle, 0.0f, 0.0f, 1.0f);  // Rotate anticlockwise around the Z-axis

    // Windmill blades (rotate only these)
    glColor3f(1.0f, 0.5f, 0.5f);
    drawCircle({ 0.0f, 0.0f }, sqrt(6));  // Blades at the center

    // Blade lines (rotate along with blades)
    glLineWidth(2);

    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(28.52445f, 31.8275f);  // Adjusted for center
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(32.3149f, -28.8496f);  // Adjusted for center
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-32.3149f, 28.8496f);  // Adjusted for center
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-28.52445f, -31.8275f);  // Adjusted for center
    glEnd();

    glPopMatrix();  // Pop the blade rotation matrix

    glPopMatrix();  // Pop the base and windows matrix

    glPushMatrix();  // Save current transformation

    // Center of rotation for polygons
    float cx = 164.9647f;
    float cy = 19.2735f;

    // Rotate the polygons (p4, p5, p6, p7)
    glTranslatef(cx, cy, 0.0f);  // Translate to center
    glRotatef(bladeRotationAngle, 0.0f, 0.0f, 1.0f);  // Rotate anticlockwise around Z-axis
    glTranslatef(-cx, -cy, 0.0f);  // Translate back to the original position

    // Draw the rotated polygons
    glColor3f(0.5f, 0.5f, 0.5f); // Set color for the polygons
    drawPolygon(p4, 4);
    drawPolygon(p5, 4);
    drawPolygon(p6, 4);
    drawPolygon(p7, 4);

    glPopMatrix();  // Restore transformation
}

void drawFence(int numPosts, float gap) {
    glColor3f(0.5, 0.3, 0.1); // Brown color

    Point p1 = { 103.00156,-46.81078 };
    Point p2 = { 107.57544,-46.81078 };
    Point p3 = { 107.46763,-72.25566 };
    Point p4 = { 102.94777,-72.41354 };

    glPushMatrix();
    glTranslatef(0, 0, 0);

    glBegin(GL_QUADS);
    for (int i = 0; i < numPosts; i++) {
        float shiftX = i * gap; // Shift by 'gap' each iteration
        glVertex2f(p1.x + shiftX, p1.y);
        glVertex2f(p2.x + shiftX, p2.y);
        glVertex2f(p3.x + shiftX, p3.y);
        glVertex2f(p4.x + shiftX, p4.y);
    }
    glEnd();

    // Draw a THIN HORIZONTAL PLANK (instead of just a line)
    glColor3f(0.3, 0.2, 0.1); // Darker brown for contrast
    float plankThickness = 5; // Control thickness of the horizontal plank
    float leftX = p4.x;
    float rightX = p3.x + (numPosts - 1) * gap;
    float plankYTop = p4.y + 10; // Adjust to place the plank slightly below the top
    float plankYBottom = plankYTop - plankThickness; // Make it thin

    glBegin(GL_QUADS);
    glVertex2f(leftX, plankYBottom);
    glVertex2f(rightX, plankYBottom);
    glVertex2f(rightX, plankYTop);
    glVertex2f(leftX, plankYTop);
    glEnd();
}

void drawHut5() {
    Point p1[] = {
        { 51.85474,-40.00719 }
        , { 112.1837,-39.65541 }
        , { 111.83193,-10.45831 }
        , { 51.85474,-10.98597 }
    };

    Point p2[] = {
        { 111.83193,-10.45831 }
        , { 51.85474,-10.98597 }
        , { 60,10 }
        , { 80,20 }
        , { 101.45465,10.82392 }
    };

    Point p3[] = {
        { 45,-15 }
        , { 57.56161,14.62338 }
        , { 81.35235,24.09457 }
        , { 105.25584,14.39788 }
        , { 118.38115,-15.43237 }
    };

    Point p4[] = {
        { 76.33129,15.62434 }
        , { 86.32994,15.81123 }
        , { 86.61027,6.74704 }
        , { 76.33129,6.65359 }
    };

    Point p5[] = {
        { 61.94071,-16.80119 }
        , { 81.47078,-16.61429 }
        , { 81.94, -39.83 }
        , { 62.03,-39.83 }
    };

    Point p6[] = {
        { 81.47078,-16.61429 }
        , { 101.65497,-16.4274 }
        , { 102.22, -39.83 }
        , { 81.94, -39.83 }
    };

    glPushMatrix();
    glTranslatef(0, 0, 0);

    glColor3ub(186, 37, 29);
    drawPolygon(p1, 4);

    glColor3ub(186, 37, 29);
    drawPolygon(p2, 5);

    glColor3ub(206, 192, 184);
    glLineWidth(20);
    drawBorder(p3, 5);

    glColor3ub(164, 180, 184);
    drawPolygon(p4, 4);

    glColor3ub(255, 100, 26);
    drawPolygon(p5, 4);

    glColor3ub(255, 100, 26);
    drawPolygon(p6, 4);

    glPopMatrix();
}

void drawTrees3() {
    //Trees
    glColor3ub(23, 116, 78);

    glPushMatrix();
    glTranslatef(250, 270, 0);
    glScalef(2, 2, 1);

    drawCircle({ -63.45423,-146.51753 }, sqrt(103.5));
    drawCircle({ -63.45423,-139.35682 }, sqrt(51.28));
    drawCircle({ -63.78472,-130.76397 }, sqrt(34.15));
    glColor4f(0.5f, 0.5f, 1.0f, 1.0f);
    drawRectangle({ -65,-155 }, { -63.15012,-155.13121 }, { -62.80601,-166.08535 }, { -65.32948,-166.1427 });

    glPopMatrix();
}

void drawBoat() {
    Point p1[] = {
        { 47.70587,-179.48803 }
        , { 95.32071,-179.94272 }
        , { 98.80177,-174.89518 }
        , { 101.50581,-170.61099 }
        , { 104.76185,-164.09891 }
        , { 99.09393,-167.11376 }
        , { 94.87313,-168.4403 }
        , { 90,-170 }
        , { 73.64366,-172.06558 }
        , { 68.09721,-172.31028 }
        , { 63.04016,-172.06558 }
        , { 56.92276,-171.41306 }
        , { 38.91741,-166.87257 }
        , { 40,-170 }
        , { 44.36169,-175.40976 }
    };

    Point p2[] = {
        { 56.64726,-166.27593 }
        , { 61.13096,-166.50785 }
        , { 65.46004,-166.43054 }
        , { 71.02601,-165.96671 }
        , { 89.88299,-164.81631 }
        , { 104.76185,-164.09891 }
        , { 99.09393,-167.11376 }
        , { 94.87313,-168.4403 }
        , { 90,-170 }
        , { 73.64366,-172.06558 }
        , { 68.09721,-172.31028 }
        , { 63.04016,-172.06558 }
        , { 56.92276,-171.41306 }
        , { 38.91741,-166.87257 }
        , { 40,-170 }
        , { 44.36169,-175.40976 }
    };

    Point p3[] = {
        { 69.27755,-155.42063 }
        , { 87.18047,-155.02455 }
        , { 89.08167,-159.85675 }
        , { 89.88299,-164.81631 }
        , { 90,-170 }
        , { 73.64366,-172.06558 }
        , { 73.09, -165.08 }
        , { 73.55524,-161.83717 }
        , { 72.52542,-158.51007 }
    };

    Point p4[] = {
        { 61.13096,-166.50785 }
        , { 72.68385,-142.74599 }
        , { 73.64366,-172.06558 }
    };

    glPushMatrix();

    // Translate the boat horizontally based on boatPositionX
    glTranslatef(boatPositionX, 0.0f, 0.0f);

    // Boat drawing code
    glColor3ub(158, 96, 9);
    drawPolygon(p1, 14);

    glColor3ub(191, 124, 28);
    drawPolygon(p2, 15);

    glColor3ub(220, 142, 32);
    drawPolygon(p3, 9);

    glBegin(GL_POLYGON);
    glVertex2f(61.13096, -166.50785);
    bezierCurve(p4, 3, 100);
    glVertex2f(73.64366, -172.06558);
    glEnd();

    glPopMatrix();

}

void drawSunMoon() {

    if (isDay) {
        // Sun
        glPushMatrix();
        glTranslatef(0, 0, 0);
        glColor3ub(255, 255, 0); // Yellow
        drawCircle({ -200, 200 }, 30);  // Sun at the left-right corner
        glPopMatrix();
    }
    else {
        // Moon
        glPushMatrix();
        glTranslatef(0, 0, 0);
        glColor3ub(255, 255, 255); // White
        drawCircle({ -200, 200 }, 30);  // Moon at the left-right corner
        glPopMatrix();
    }
}

void drawFence2(int numPosts, float gap) {
    glColor3f(0.5, 0.3, 0.1); // Brown color

    Point p1 = { -151.69726,-89.57737 };
    Point p2 = { -148.48735,-89.45391 };
    Point p3 = { -148.61081,-104.14542 };
    Point p4 = { -151.82072,-104.63925 };

    glPushMatrix();
    glTranslatef(-20, 30, 0);

    glBegin(GL_QUADS);
    for (int i = 0; i < numPosts; i++) {
        float shiftX = i * gap; // Shift by 'gap' each iteration
        glVertex2f(p1.x + shiftX, p1.y);
        glVertex2f(p2.x + shiftX, p2.y);
        glVertex2f(p3.x + shiftX, p3.y);
        glVertex2f(p4.x + shiftX, p4.y);
    }
    glEnd();

    // Draw a THIN HORIZONTAL PLANK (instead of just a line)
    glColor3f(0.3, 0.2, 0.1); // Darker brown for contrast
    float plankThickness = 5; // Control thickness of the horizontal plank
    float leftX = p4.x;
    float rightX = p3.x + (numPosts - 1) * gap;
    float plankYTop = p4.y + 10; // Adjust to place the plank slightly below the top
    float plankYBottom = plankYTop - plankThickness; // Make it thin

    glBegin(GL_QUADS);
    glVertex2f(leftX, plankYBottom);
    glVertex2f(rightX, plankYBottom);
    glVertex2f(rightX, plankYTop);
    glVertex2f(leftX, plankYTop);
    glEnd();

    glPopMatrix();
}
