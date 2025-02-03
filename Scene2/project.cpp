#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <vector>
using namespace std;
# define pi 3.1416

/*-------------------------------- Initial variables and values --------------------------------------------*/
bool day = true;
bool rain = false;
bool lantern = false;
bool flood = false;
bool hasRained = false;
char key;

/*------------------------------------- Function Declarations -------------------------------------------------*/

//keyboard-mouse
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);

//shapes
void drawLines(float x1, float y1, float x2, float y2);
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
void drawRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void drawPentagon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5);
void drawHexagon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5, float x6, float y6);
void drawOctagon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5, float x6, float y6, float x7, float y7, float x8, float y8);
void drawCircle(float x1, float y1, float radius);
void drawCircleWM(double radius);

//sky elements
void drawSky(); // O201
void drawCloud1(); // O224
void drawCloud2(); // O225
void drawCloud3(); // O226
void drawCloud4(); // O227
void drawCloud5(); // O228
void drawSun(); // O203
void drawMoon(); // O204
void drawStars(); // O229
void drawFireflies(); // O238

//field elements
void drawField(); // O202
void drawHut1(); // O206
void drawHut2(); // O207
void drawHut3(); // O208
void drawHut4(); // O209
void drawHut5(); // O210
void drawHut6(); // O211
void drawRiver(); // O214
void drawBoat1(); // O220
void drawBoat2(); // O221
void drawBoat3(); // O222
void drawBoat4(); // O223
void drawMountain1(); // O215
void drawMountain2(); // O216
void drawMountain3(); // O217
void drawMountain4(); // O218
void drawMountain5(); // O219
void drawTree1(); // O230
void drawTree2();  // O231
void drawTree3();  // O232
void drawTree4();  // O233
void drawCoconutTree1(); // O234
void drawCoconutTree2(); // O235
void drawCoconutTree3(); // O236
void drawCoconutTree4(); // O237
void drawWindMill(); // O212
void drawBridge(); // O240
void drawStones(); // O241
void drawRoads(); // O242

//weather elements
void drawRain(); //O205
void drawFlood(); //O243
void drawRipple(float x, float y, float radius, float alpha); // O213
void drawLightningFlash(); // O239

/*------------------------------------------- Initialize Functions ----------------------------------------------------*/
void initializeRain();
void initializeRipple();
void initializeStars();
void initializeFireflies();

/*------------------------------------- Animation Function Declarations -------------------------------------------------*/
void updateSunMoon(int value); // A201
void updateRain(int value); // A202
void updateWindMill(int value); // A203
void updateRipples(int value); // A204
void updateBoatType1(int value); // A205
void updateBoatType2(int value); // A206
void updateClouds(int value); // A207
void updateFireflies(int value); // A208
void updateLightningFlash(int value); // A209
void updateFlood(int value); // A210

/*------------------------------------- Predefined Shapes -------------------------------------------------*/
void drawLines(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
}

void drawPentagon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5)
{
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glVertex2f(x5, y5);
    glEnd();
}

void drawHexagon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5, float x6, float y6)
{
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glVertex2f(x5, y5);
    glVertex2f(x6, y6);
    glEnd();
}

void drawOctagon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5, float x6, float y6, float x7, float y7, float x8, float y8)
{
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glVertex2f(x5, y5);
    glVertex2f(x6, y6);
    glVertex2f(x7, y7);
    glVertex2f(x8, y8);
    glEnd();
}

void drawCircle(float cx, float cy, float r)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        float theta = 2.0f * pi * float(i) / float(100);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawCircleWM(double radius)
{
    int d;
    glBegin(GL_POLYGON);
    for (d = 0; d < 32; d++)
    {
        double angle = 2 * pi / 32 * d;
        glVertex2d(radius * cos(angle), radius * sin(angle));
    }
    glEnd();
}

/*------------------------------------- Sky -------------------------------------------------*/
void drawSky() // O201
{
    glBegin(GL_QUADS);

    if (day && !rain)
    {
        glColor3f(0.0, 0.4, 0.8);
        glVertex2f(-200.0, 200.0);
        glVertex2f(200.0, 200.0);

        glColor3f(0.6, 0.9, 1.0);
        glVertex2f(200.0, 28.75);
        glVertex2f(-200.0, 28.75);
    }
    else if (!day && !rain)
    {
        glColor3f(0.0, 0.0, 0.2);
        glVertex2f(-200.0, 200.0);
        glVertex2f(200.0, 200.0);

        glColor3f(0.0, 0.0, 0.0);
        glVertex2f(200.0, 28.75);
        glVertex2f(-200.0, 28.75);
    }

    else if (day && rain)
    {
        glColor3ub(150, 150, 160);  
        glVertex2f(-200.0, 200.0);
        glVertex2f(200.0, 200.0);

        glColor3ub(50, 50, 60); 
        glVertex2f(200.0, 28.75);
        glVertex2f(-200.0, 28.75);
    }

    else if (!day && rain)
    {
        glColor3ub(20, 20, 30); 
        glVertex2f(-200.0, 200.0);
        glVertex2f(200.0, 200.0);

        glColor3ub(10, 10, 20);
        glVertex2f(200.0, 28.75);
        glVertex2f(-200.0, 28.75);
    }
    
    glEnd();
}

/*------------------------------------- Field -------------------------------------------------*/
void drawField() // O202
{
    glBegin(GL_TRIANGLE_STRIP);

    if (day)
    {
        glColor3ub(10, 60, 10);
        glVertex2f(-200.0, 28.75);
        glVertex2f(200.0, 28.75);

        glColor3ub(50, 130, 30);
        glVertex2f(-200.0, -50);
        glVertex2f(200.0, -50);

        glColor3ub(120, 200, 50);
        glVertex2f(-200.0, -200.0);
        glVertex2f(200.0, -200.0);
    }
    else
    {
        glColor3ub(30, 50, 30);
        glVertex2f(-200.0, 28.75);
        glVertex2f(200.0, 28.75);

        glColor3ub(40, 70, 40);
        glVertex2f(-200.0, -50);
        glVertex2f(200.0, -50);

        glColor3ub(20, 35, 20);
        glVertex2f(-200.0, -200.0);
        glVertex2f(200.0, -200.0);
    }

    glEnd();
}

/*------------------------------------- Sun and Moon -------------------------------------------------*/
float sunX = -11.25, moonX = 400.0;
bool sunMoonMoving = false; // Track transition status
void drawSun() // O203
{
    if (day || sunMoonMoving) // if it's day or transitioning
    {
        glColor3f(0.97, 0.91, 0.39);
        drawCircle(sunX, 144.58, 18.0);
    }
}

void drawMoon() // O204
{
    if (!day || sunMoonMoving) // if it's night or transitioning
    {
        glColor3f(1.0, 1.0, 1.0);
        drawCircle(moonX, 144.58, 18.0);
    }
}

void updateSunMoon(int value) //A201
{
    if (sunMoonMoving)  
    {
        if (!day) 
        {
            if (sunX > -250.0) sunX -= 1.0; 
            if (moonX > -11.25) moonX -= 1.0; 
        }
        else 
        {
            if (moonX > -250.0) moonX -= 1.0; 
            if (sunX > -11.25) sunX -= 1.0; 
        }

        glutPostRedisplay();

        // Continue animation only if either object is still moving
        if ((day && sunX > -250.0) || (!day && moonX > -250.0))  
            glutTimerFunc(16, updateSunMoon, 0); // A201
        else
            sunMoonMoving = false; // Stop movement when transition is done
    }
}

/*------------------------------------- Rain -------------------------------------------------*/
struct Raindrop
{
    float x, y;
    float size; 
    float speed;
};
vector<Raindrop> raindrops;
int maxRaindrops = 3000; 
void initializeRain() 
{
    raindrops.clear();
    for (int i = 0; i < maxRaindrops; i++)
    {
        Raindrop raindrop;
        raindrop.x = rand() % 400 - 200;     
        raindrop.y = rand() % 401 - 200;     
        raindrop.size = (rand() % 3 + 1) / 4.0; 
        raindrop.speed = raindrop.size * 10.0;
        raindrops.push_back(raindrop);
    }
}

void drawRain() // O205
{
    if (rain)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        if (day) glColor4f(151.0f / 255.0f, 229.0f / 255.0f, 253.0f / 255.0f, 0.5f); 
        else glColor4f(27.0/255.0, 184.0/255.0, 238.0/255.0, 0.5f); 

        for (int i = 0; i < raindrops.size(); i++)
            drawLines(raindrops[i].x, raindrops[i].y, raindrops[i].x, raindrops[i].y - 6.0);
        
        glDisable(GL_BLEND);
    }
}

void updateRain(int value) // A202
{
    if (rain)
    {
        // Update position of each raindrop
        for (int i = 0; i < raindrops.size(); i++)
        {
            raindrops[i].y -= raindrops[i].speed; // Use initialized speed
            if (raindrops[i].y < -200) // Reset if below screen
            {
                raindrops[i].x = rand() % 400 - 200; // Random x position
                raindrops[i].y = 200; // Reset to top
            }
        }

        while (raindrops.size() < maxRaindrops)
        {
            Raindrop raindrop;
            raindrop.x = rand() % 400 - 200;
            raindrop.y = rand() % 400 - 200;
            raindrops.push_back(raindrop);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(50, updateRain, 0); // A202
}

/*------------------------------------- Huts -------------------------------------------------*/
void drawHut1() // O206
{
    if (day) glColor3ub(255, 197, 62);
    else glColor3ub(204, 157, 49);
    drawRectangle(-183.89, 30.84, -144.28, 29.72, -116.35, 3.58, -157.64, 2.78);
    drawRectangle(-183.89, 30.84, -200.0, 16.26, -200.0, 12.18, -179.22, 26.95);

    glColor3ub(247, 141, 67);
    drawRectangle(-159.26, 4.51, -159.93, -15.72, -123.37, -12.16, -124.24, 3.42);
    drawTriangle(-179.22, 26.95, -200.0, 12.18, -159.26, 4.51);
    drawRectangle(-200.0, 12.18, -200.0, -10.0, -158.93, -15.72, -159.26, 4.51);

    //window
    if (!lantern)
        glColor3ub(76, 5, 61);
    else
        glColor3f(0.97, 0.91, 0.39);

    drawRectangle(-186.89, 8.39, -186.83, -0.56, -175.92, -1.47, -175.64, 7.49);

    //door
    drawRectangle(-147.43, 0.79, -147.01, -14.53, -137.39, -13.57, -138.33, 0.61);

    glColor3ub(175, 65, 56);
    drawRectangle(-200.0, -10.0, -200.0, -15.0, -159.12, -20.5, -158.93, -15.72);
    drawRectangle(-159.27, -17.55, -159.12, -20.5, -118.92, -16.6, -119.21, -13.74);
    glColor3ub(251, 165, 62);
    drawPentagon(-158.93, -15.72, -159.27, -17.55, -119.21, -13.74, -119.3, -12.92, -123.37, -12.16);
}

void drawHut2() // 0207
{
    if (day) glColor3ub(255, 197, 62);
    else glColor3ub(204, 157, 49);
    drawRectangle(-69.72, 29.65, -93.58, 6.17, -59.01, 5.31, -36.81, 30.16);
    drawRectangle(-36.81, 30.16, -39.34, 27.0, -20.98, 6.66, -15.62, 7.12);

    glColor3ub(247, 141, 67);
    drawRectangle(-86.0, 5.98, -85.65, -7.75, -59.46, -12.7, -59.29, 5.37);
    drawRectangle(-59.29, 5.37, -59.46, -12.7, -20.92, -7.47, -21.71, 7.47);
    drawTriangle(-59.29, 5.37, -21.71, 7.47, -39.56, 27.36);

    //window
    if (!lantern)
        glColor3ub(76, 5, 61);
    else
        glColor3f(0.97, 0.91, 0.39);
    drawRectangle(-45.73, 7.37, -45.57, 0.34, -35.93, 0.72, -36.01, 7.58);

    //door
    drawRectangle(-76.71, 2.8, -77.08, -9.47, -69.41, -10.7, -69.29, 2.59);

    glColor3ub(175, 65, 56);
    drawRectangle(-88.77, -7.18, -88.96, -10.82, -58.95, -16.83, -59.46, -12.7);
    drawRectangle(-59.46, -12.7, -58.95, -16.83, -19.68, -10.85, -20.21, -7.48);
}

void drawHut3() // O208
{
    if (day) glColor3ub(255, 197, 62);
    else glColor3ub(204, 157, 49);
    drawRectangle(-2.02, 34.97, -11.22, 27.15, 3.66, 26.88, 12.98, 35.52);
    drawRectangle(12.98, 35.52, 10.77, 33.47, 18.15, 26.92, 21.98, 27.15);

    glColor3ub(247, 141, 67);
    drawRectangle(-6.69, 27.12, -6.72, 21.67, 3.88, 21.14, 3.66, 26.88);
    drawRectangle(3.66, 26.88, 3.88, 21.14, 17.48, 22.26, 17.17, 27.79);
    drawTriangle(3.66, 26.88, 17.17, 27.79, 10.77, 33.47);

    if (!lantern)
        glColor3ub(76, 5, 61);
    else
        glColor3f(0.97, 0.91, 0.39);
    drawRectangle(8.8, 27.05, 9.02, 21.53, 12.69, 21.97, 12.43, 27.14);
}

void drawHut4() // 0209
{
    if (day) glColor3ub(255, 197, 62);
    else glColor3ub(204, 157, 49);
    drawRectangle(55.26, 39.82, 46.65, 32.74, 73.32, 32.01, 65.99, 39.5);

    glColor3ub(247, 141, 67);
    drawRectangle(51.57, 32.6, 51.5, 28.09, 67.49, 28.09, 67.45, 32.17);

    //door
    if (!lantern)
        glColor3ub(76, 5, 61);
    else
        glColor3f(0.97, 0.91, 0.39);
    drawRectangle(58.05, 32.42, 58.05, 28.09, 60.76, 28.09, 60.66, 32.35);
}

void drawHut5() // 0210
{
    glColor3ub(247, 141, 67);
    drawRectangle(95.43, 8.77, 95.0, -5.68, 127.94, -7.6, 127.68, 10.42);
    drawTriangle(127.68, 10.42, 160.04, 12.05, 143.82, 24.68);
    drawRectangle(127.68, 10.42, 127.94, -7.6, 159.52, -2.83, 160.04, 12.05);

    if (day) glColor3ub(255, 197, 62);
    else glColor3ub(204, 157, 49);
    drawRectangle(111.45, 28.1, 90.47, 8.81, 125.51, 8.49, 147.68, 28.1);
    drawRectangle(143.82, 24.68, 160.04, 12.05, 167.8, 11.78, 147.68, 28.1);

    //door
    if (!lantern)
        glColor3ub(76, 5, 61);
    else
        glColor3f(0.97, 0.91, 0.39);
    drawRectangle(107.05, 4.73, 106.4, -6.35, 115.19, -6.86, 115.12, 4.23);
    //window
    drawRectangle(137.61, 10.13, 137.73, 3.54, 142.63, 3.63, 142.52, 10.11);
    drawRectangle(148.09, 10.68, 148.26, 4.11, 153.24, 4.1, 153.04, 10.67);
}

void drawHut6() // O211
{
    glColor3ub(247, 141, 67);
    drawRectangle(176.57, 24.16, 176.54, 19.61, 190.61, 19.65, 190.81, 24.25);
    drawTriangle(172.1, 30.52, 165.59, 25.89, 176.57, 24.16);
    drawRectangle(165.59, 25.89, 165.55, 20.24, 176.54, 19.61, 176.57, 24.16);

    if (day) glColor3ub(255, 197, 62);
    else glColor3ub(204, 157, 49);
    drawRectangle(170.58, 32.66, 176.57, 24.16, 192.02, 24.26, 184.0, 32.0);
    drawRectangle(170.58, 32.66, 172.1, 30.52, 164.93, 25.42, 162.86, 25.61);

    //door
    if (!lantern)
        glColor3ub(76, 5, 61);
    else
        glColor3f(0.97, 0.91, 0.39);
    drawRectangle(180.53, 23.84, 180.53, 19.62, 183.16, 19.63, 183.01, 23.82);
}

/*------------------------------------- Windmill -------------------------------------------------*/
int frameNumber = 0;
void drawWindMill() // O212
{
    // Draw the pole
    glColor3f(0.8f, 0.8f, 0.9f);
    drawRectangle(-153.04, 28.62, -149.81, 28.62, -149.81, 100.62, -153.04, 100.62);

    // Draw the circle at the top of the pole
    glPushMatrix();
    glTranslatef(-151.425, 100.62, 0.0);
    glColor3f(0.8f, 0.8f, 0.9f);
    drawCircleWM(5.0);
    glPopMatrix();

    // Draw the windmill blades (rotating around the top-center of the pole)
    glPushMatrix();
    glTranslatef(-151.425, 100.62, 0.0); // Top-center of the pole
    glRotatef(frameNumber * 10, 0.0, 0.0, 1.0); // Rotate blades based on animation frame
    glColor3f(0.4f, 0.4f, 0.8f);
    for (int i = 0; i < 4; i++) // Fixed loop condition to iterate exactly 4 times
    {
        drawRectangle(-2.25, 4.76, -7.52, 24.04, -2.65, 40.23, 1.56, 24.45); // Adjusted blade coordinates relative to the rotation center
        glRotatef(90, 0.0, 0.0, 1.0); // Rotate each blade by 90 degrees
    }
    glPopMatrix();
}

void updateWindMill(int value) //A203
{
    frameNumber++;
    glutPostRedisplay(); 
    glutTimerFunc(40, updateWindMill, 0); // A203
}

/*------------------------------------- Ripple Effect in River While Raining -------------------------------------------------*/
struct Ripple
{
    float x, y;       
    float radius;    
    float alpha;       // Ripple transparency
};

vector<Ripple> ripples;
void initializeRipple()
{
    // ripple generation within river bounds
    float xMin = -200.0f, xMax = 200.0f; 
    float yMin = -200.0f, yMax = -80.0f;  

    if (rand() % 10 == 0) 
    {
        float x = xMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (xMax - xMin)));
        float y = yMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (yMax - yMin)));

        ripples.push_back({ x, y, 0.3f, 1.0f}); 
    }
}

void drawRipple(float x, float y, float radius, float alpha) // O213
{
    glColor4f(1.0f, 1.0f, 1.0f, alpha); // White color with transparency
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 50; ++i)
    {
        float angle = 2.0f * M_PI * i / 50;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

void updateRipples(int value) // A204
{
    if (rain)
    {
        // Add new ripples periodically
        initializeRipple();

        // Expand and fade ripples
        for (auto& ripple : ripples)
        {
            ripple.radius += 0.2f;   
            ripple.alpha -= 0.01f;  
        }

        // Remove ripples that are fully faded
        ripples.erase(remove_if(ripples.begin(), ripples.end(),
            [](const Ripple& r) { return r.alpha <= 0.0f; }),
            ripples.end());
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateRipples, 0); // A204
}

/*------------------------------------- River -------------------------------------------------*/
void drawRiver() // O214
{
    if (day)
        glColor3ub(30, 90, 180); 
    else
        glColor3ub(5, 78, 156); 

    drawRectangle(-129.63, 13.2, -128.86, 7.1, -78.56, 7.1, -86.61, 13.03);
    drawRectangle(-21.46, 2.59, -21.05, -5.12, -5.96, -8.26, 2.2, 0.7);
    drawRectangle(-5.96, -8.26, 2.2, 0.7, 26.08, -1.68, 1.58, -11.52);
    drawRectangle(1.58, -11.52, 26.08, -1.68, 42.21, -5.17, 6.37, -15.22);
    drawTriangle(42.21, -5.17, 6.37, -15.22, 52.16, -6.53);
    drawRectangle(52.16, -6.53, 6.37, -15.22, -4.45, -24.43, 65.77, -11.36);
    drawTriangle(-4.45, -24.43, 65.77, -11.36, 78.35, -17.62);
    drawTriangle(-4.45, -24.43, 78.35, -17.62, 63.67, -29.9);
    drawRectangle(-4.45, -24.43, 63.67, -29.9, 62.82, -37.84, -51.07, -36.06);
    drawRectangle(-51.07, -36.06, 62.82, -37.84, 80.0, -60.0, -35.19, -41.57);
    drawTriangle(-35.19, -41.57, 80.0, -60.0, -18.49, -54.44);
    drawRectangle(-20.95, -47.56, -18.49, -54.44, 83.05, -65.36, 80.0, -60.0);
    drawTriangle(-18.49, -54.44, -36.17, -61.28, 83.05, -65.36);

    glBegin(GL_QUADS);

    if (day)
    {
        glColor3ub(30, 90, 180); 
        glVertex2f(200.0, -60.0);
        glVertex2f(-200.0, -60.0);

        glColor3ub(10, 40, 94); 
        glVertex2f(-200.0, -200.0);
        glVertex2f(200.0, -200.0);
    }
    else
    {
        glColor3ub(5, 78, 156); 
        glVertex2f(200.0, -60.0);
        glVertex2f(-200.0, -60.0);

        glColor3ub(2, 25, 50); 
        glVertex2f(-200.0, -200.0);
        glVertex2f(200.0, -200.0);
    }

    glEnd();
    
    // Draw ripples if it's raining
    if (rain) 
        for (const auto& ripple : ripples) 
            drawRipple(ripple.x, ripple.y, ripple.radius, ripple.alpha); // O213

    //river banks
    glColor3ub(46, 25, 21);
    drawTriangle(-36.17, -59.93, -18.49, -54.44, -37.36, -65.99);
    drawTriangle(-18.49, -54.44, -37.36, -70, -36.17, -59.93);
    drawRectangle(-36.17, -59.93, -37.36, -70, -200, -70, -200, -59.93);

    drawRectangle(79.16, -56.89, 90.97, -67, 200, -66.68, 200, -56);
}

/*------------------------------------- Mountains -------------------------------------------------*/
void drawMountain1() // O215
{
    if (day) glColor3ub(114, 7, 91);
    else glColor3ub(76, 5, 61);
    drawRectangle(-200.0, 54.27, -200.0, 28.75, -124.39, 28.55, -167.4, 56.12);
    drawTriangle(-124.39, 28.55, -167.4, 56.12, -145.63, 60.22);
    drawRectangle(-145.63, 60.22, -124.39, 28.55, -109.22, 28.51, -130.96, 62.66);
    drawTriangle(-130.96, 62.66, -109.22, 28.51, -122.6, 66.84);
    drawTriangle(-122.6, 66.84, -106.35, 70.39, -109.22, 28.51);
    drawTriangle(-106.35, 70.39, -109.22, 28.51, -92.57, 74.73);
    drawTriangle(-106.35, 70.39, -86.99, 73.53, -92.57, 74.73);
    drawTriangle(-92.57, 74.73, -86.99, 73.53, -109.22, 28.51);
    drawTriangle(-86.99, 73.53, -109.22, 28.51, -59.84, 60.32);
    drawRectangle(-37.52, 49.46, -59.84, 60.32, -109.22, 28.51, -32.92, 28.3);
    drawRectangle(-16.11, 45.21, -37.52, 49.46, -32.92, 28.3, -13.29, 28.25);
    drawRectangle(-2.02, 34.97, -16.11, 45.21, -13.29, 28.25, 0.49, 28.21);
}

void drawMountain2() // O216
{
    if (day) glColor3ub(246, 176, 113);
    else glColor3ub(195, 139, 89);
    drawRectangle(-40.56, 50.9, -15.81, 55.31, 0.49, 28.21, -32.92, 28.3);
    drawTriangle(0.49, 28.21, -15.81, 55.31, -6.74, 60.28);
    drawTriangle(-6.74, 60.28, -1.35, 61.14, 0.49, 28.21);
    drawRectangle(0.49, 28.21, -1.35, 61.14, 3.3, 63.08, 32.33, 28.12);
    drawRectangle(32.33, 28.12, 3.3, 63.08, 35.24, 48.78, 40.63, 28.14);
    drawRectangle(40.63, 28.14, 35.24, 48.78, 55.26, 39.82, 58.05, 28.09);
}

void drawMountain3() // O217
{
    if (day) glColor3ub(104, 185, 176);
    else glColor3ub(75, 133, 127);
    drawRectangle(40.63, 28.14, 35.24, 48.78, 48.98, 51.2, 48.28, 28.12);
    drawRectangle(48.28, 28.12, 48.98, 51.2, 59.71, 55.71, 74.64, 28.01);
    drawTriangle(74.64, 28.01, 59.71, 55.71, 72.93, 50.97);
    drawTriangle(72.93, 50.97, 74.64, 28.01, 78.95, 49.87);
    drawRectangle(78.95, 49.87, 74.64, 28.01, 86.07, 28.04, 85.29, 48.71);
    drawRectangle(85.29, 48.71, 86.07, 28.04, 111.45, 28.1, 99.52, 43.5);
}

void drawMountain4() // O218
{
    if (day) glColor3ub(114, 7, 91);
    else glColor3ub(76, 5, 61);
    drawTriangle(99.52, 43.5, 78.95, 49.87, 92.12, 52.68);
    drawTriangle(92.12, 52.68, 99.52, 43.5, 102.86, 53.22);
    drawRectangle(102.86, 53.22, 99.52, 43.5, 111.45, 28.1, 135.19, 58.54);
    drawRectangle(111.45, 28.1, 152.76, 27.79, 152.62, 51.73, 135.19, 58.54);
    drawTriangle(152.62, 51.73, 138.31, 27.79, 180.79, 27.79);
}

void drawMountain5() // O219
{
    if (day) glColor3ub(246, 176, 113);
    else glColor3ub(195, 139, 89);
    drawRectangle(138.31, 27.77, 152.62, 51.73, 159.58, 55.1, 161.4, 27.77);
    drawRectangle(161.4, 27.77, 159.58, 55.1, 169.07, 48.46, 180.79, 27.77);
    drawRectangle(180.79, 27.77, 169.07, 48.46, 200.0, 38.34, 200.0, 27.67);
}

/*------------------------------------- Boats -------------------------------------------------*/
void drawBoatType1()
{
    //inner shell
    glColor3ub(95, 41, 19);
    drawRectangle(-31.35, -165.01, -32.21, -159.36, -34.97, -154.14, -39.75, -166.32);
    drawTriangle(-39.75, -166.32, -34.97, -154.14, -38.74, -149.8);
    drawTriangle(-39.75, -166.32, -38.74, -149.8, -41.78, -148.93);
    drawTriangle(-39.75, -166.32, -41.78, -148.93, -45.26, -150.09);
    drawTriangle(-39.75, -166.32, -45.26, -150.09, -48.15, -155.59);
    drawRectangle(-48.15, -155.59, -39.75, -166.32, -49.89, -167.19, -50.04, -164.14);

    //outer shell
    glColor3ub(255, 242, 74);
    drawRectangle(-66.88, -150.59, -41.78, -148.93, -45.26, -150.09, -69.6, -152.61);
    glColor3ub(213, 131, 65);
    drawRectangle(-69.6, -152.61, -45.26, -150.09, -48.15, -155.59, -72.54, -155.87);
    drawRectangle(-72.54, -155.87, -48.15, -155.59, -50.04, -164.14, -75.0, -160.0);
    drawRectangle(-75.0, -160.0, -50.04, -164.14, -49.89, -167.19, -76.29, -164.41);
    drawTriangle(-76.29, -164.41, -76.93, -170.57, -70.79, -171.18);
    drawTriangle(-76.29, -164.41, -70.79, -171.18, -62.27, -171.59);
    drawTriangle(-76.29, -164.41, -62.27, -171.59, -55.12, -171.69);
    drawTriangle(-76.29, -164.41, -55.12, -171.69, -49.67, -171.66);
    drawTriangle(-76.29, -164.41, -49.67, -171.66, -49.89, -167.19);

    //base
    glColor3ub(0, 0, 0);
    drawTriangle(-98.91, -162.08, -95.5, -165.22, -93.87, -164.97);
    drawRectangle(-95.5, -165.22, -93.87, -164.97, -88.98, -167.42, -91.5, -168.39);
    drawRectangle(-91.5, -168.39, -88.98, -167.42, -82.51, -169.43, -85.33, -172.29);
    drawRectangle(-85.33, -172.29, -82.51, -169.43, -76.93, -170.57, -80.0, -175.0);
    drawTriangle(-80.0, -175.0, -76.93, -170.57, -74.68, -176.07);
    drawRectangle(-74.68, -176.07, -76.93, -170.57, -70.79, -171.18, -70.09, -176.49);
    drawRectangle(-70.09, -176.49, -70.79, -171.18, -42.06, -170.89, -37.65, -175.94);
    drawRectangle(-42.06, -170.89, -37.65, -175.94, -32.39, -173.58, -36.88, -169.81);
    drawTriangle(-36.88, -169.81, -32.39, -173.58, -32.67, -168.73);
    drawRectangle(-32.39, -173.58, -32.67, -168.73, -28.24, -167.44, -25.08, -168.59);
    drawRectangle(-25.08, -168.59, -28.24, -167.44, -24.36, -165.6, -19.5, -163.97);
    drawTriangle(-19.5, -163.97, -24.36, -165.6, -19.07, -162.55);
    drawTriangle(-19.5, -163.97, -19.07, -162.55, -16.75, -161.26);
    drawRectangle(-16.75, -161.26, -19.07, -162.55, -15.6, -159.5, -14.51, -159.03);
    drawTriangle(-14.51, -159.03, -15.6, -159.5, -13.72, -158.14);

    //macha
    glColor3ub(153, 83, 22);
    drawRectangle(-49.89, -167.19, -39.75, -166.32, -42.06, -170.89, -49.67, -171.66);
    drawRectangle(-42.06, -170.89, -39.75, -166.32, -31.35, -165.01, -36.88, -169.81);
    drawTriangle(-36.88, -169.81, -31.35, -165.01, -28.24, -167.44);
    drawRectangle(-28.24, -167.44, -31.35, -165.01, -26.48, -163.7, -24.36, -165.6);
    drawRectangle(-24.36, -165.6, -26.48, -163.7, -21.73, -162.1, -19.07, -162.55);
    drawTriangle(-21.73, -162.1, -19.07, -162.55, -15.6, -159.5);

    drawRectangle(-76.61, -167.52, -76.93, -170.57, -82.51, -169.43, -83.05, -167.11);
    drawRectangle(-83.05, -167.11, -82.51, -169.43, -88.98, -167.42, -87.73, -166.45);
    drawTriangle(-87.73, -166.45, -88.98, -167.42, -93.87, -164.97);
}

float boat1X = -100.0f; // Initial x position of boat
void drawBoat1() // O220
{
    glPushMatrix();
    glTranslatef(boat1X, 0.0f, 0.0f);
    drawBoatType1();
    //paal
    glColor3ub(178, 100, 51);
    drawRectangle(-56.85, -146.4, -56.85, -149.86, -53.95, -149.74, -54.09, -146.31);

    glColor3ub(255, 0, 0);
    drawTriangle(-67.73, -147.64, -56.85, -146.4, -71.21, -132.52);
    drawTriangle(-56.85, -146.4, -54.09, -146.31, -71.21, -132.52);
    drawRectangle(-54.09, -146.31, -71.21, -132.52, -38.15, -131.88, -46.5, -145.7);
    drawRectangle(-46.5, -145.7, -38.43, -144.86, -37.5, -140.14, -38.15, -131.88);
    drawRectangle(-38.15, -131.88, -40.93, -115.1, -76.58, -124.36, -71.21, -132.52);
    drawRectangle(-76.58, -124.36, -40.93, -115.1, -49.32, -95.11, -87.32, -112.62);
    drawRectangle(-87.32, -112.62, -49.32, -95.11, -54.09, -88.35, -101.05, -103.07);
    glPopMatrix();
}

float Boat2X = 170.0f;
float Boat2Y = 55.0f;
void drawBoat2() // O221
{
    glPushMatrix();
    glPushMatrix();
    glTranslatef(Boat2X, Boat2Y, 0.0f);
    glScalef(0.75, 0.75, 0.0);
    glColor3ub(95, 41, 19);
    drawRectangle(-83.42, -122.17, -81.5, -122.26, -89.45, -180.0, -91.0, -180.0);
    drawBoatType1();
    glPopMatrix();
    glPopMatrix();
}

void drawBoatType2()
{
    glColor3ub(208, 198, 198); 
    drawTriangle(8.34, -110.88, 16.02, -114.6, 32.53, -114.11);
    drawTriangle(32.53, -114.11, 16.02, -114.6, 31.65, -114.77);
    drawTriangle(16.02, -114.6, 31.65, -114.77, 31.31, -115.03);
    drawTriangle(16.02, -114.6, 31.31, -115.03, 30.33, -117.34);
    drawTriangle(16.02, -114.6, 30.33, -117.34, 30.55, -118.36);

    glColor3ub(255, 255, 255);
    drawTriangle(8.34, -110.88, 16.02, -114.6, 14.4, -119.18);
    drawRectangle(16.02, -114.6, 14.4, -119.18, 18.77, -120.92, 30.55, -118.36);
    drawRectangle(30.55, -118.36, 18.77, -120.92, 33.12, -123.47, 41.27, -119.78);
    drawRectangle(41.27, -119.78, 33.12, -123.47, 50.79, -123.95, 54.97, -120.36);
    drawRectangle(54.97, -120.36, 50.79, -123.95, 67.07, -122.34, 56.67, -120.43);
    drawTriangle(67.07, -122.34, 56.67, -120.43, 70.85, -119.98);
    drawRectangle(70.85, -119.98, 69.59, -117.14, 57.66, -117.57, 54.97, -120.36);

    drawTriangle(30.33, -117.34, 31.31, -115.03, 31.65, -114.77);
    drawRectangle(30.33, -117.34, 31.31, -115.03, 44.47, -115.03, 54.97, -120.36);
    drawRectangle(54.97, -120.36, 57.66, -117.57, 57.52, -114.92, 44.47, -115.03);
    drawRectangle(57.66, -117.57, 57.52, -114.92, 63.73, -114.92, 64.16, -117.33);
    drawRectangle(57.52, -114.92, 57.09, -111.26, 45.24, -113.28, 44.47, -115.03);
    drawTriangle(57.09, -111.26, 45.24, -113.28, 45.67, -112.31);
    drawTriangle(57.09, -111.26, 45.67, -112.31, 45.92, -111.59);
    drawTriangle(57.09, -111.26, 45.92, -111.59, 45.52, -111.01);
    drawTriangle(57.09, -111.26, 45.52, -111.01, 45.67, -110.41);
    drawRectangle(45.67, -110.41, 46.62, -110.08, 55.68, -109.76, 57.09, -111.26);
    drawTriangle(57.09, -111.26, 55.68, -109.76, 57.76, -110.94);
    drawRectangle(55.68, -109.76, 57.76, -110.94, 65.72, -109.61, 64.02, -109.53);
    drawRectangle(57.76, -110.94, 65.72, -109.61, 66.22, -110.05, 66.24, -110.53);
    drawTriangle(57.76, -110.94, 66.24, -110.53, 65.84, -110.68);
    drawTriangle(8.34, -110.88, 16.02, -114.6, 14.4, -119.18);
    drawRectangle(16.02, -114.6, 14.4, -119.18, 15.0, -120.0, 30.38, -118.41);
    drawRectangle(30.38, -118.41, 15.0, -120.0, 18.94, -124.07, 24.62, -128.76);
    drawTriangle(24.62, -128.76, 30.38, -118.41, 41.27, -119.78);
    drawTriangle(24.62, -128.76, 41.27, -119.78, 54.97, -120.36);
    drawTriangle(24.62, -128.76, 54.97, -120.36, 56.67, -120.43);
    drawTriangle(24.62, -128.76, 56.67, -120.43, 70.85, -119.98);
    drawTriangle(24.62, -128.76, 70.85, -119.98, 68.52, -122.32);
    drawTriangle(24.62, -128.76, 68.52, -122.32, 67.07, -125.78);
    drawTriangle(24.62, -128.76, 67.07, -125.78, 67.49, -127.59);
    drawTriangle(24.62, -128.76, 67.49, -127.59, 69.52, -128.78);
    drawTriangle(16.02, -114.6, 30.38, -118.41, 30.33, -117.34);
    drawRectangle(54.97, -120.36, 56.67, -120.43, 64.16, -117.33, 57.66, -117.57);
    drawRectangle(64.16, -117.33, 56.67, -120.43, 70.85, -119.98, 69.59, -117.14);

    glColor3ub(0, 0, 0);
    drawRectangle(31.65, -114.77, 31.31, -115.03, 44.47, -115.03, 45.24, -113.28);
    drawTriangle(57.76, -110.94, 65.84, -110.68, 65.85, -110.99);
    drawRectangle(57.76, -110.94, 65.85, -110.99, 66.9, -114.18, 63.73, -114.92);
    drawRectangle(57.76, -110.94, 63.73, -114.92, 57.52, -114.92, 57.09, -111.26);
    drawRectangle(63.73, -114.92, 64.16, -117.33, 69.59, -117.14, 66.9, -114.18);
    drawRectangle(69.59, -117.14, 66.9, -114.18, 74.74, -114.75, 75.5, -116.74);
    drawRectangle(30.33, -117.34, 30.38, -118.41, 41.27, -119.78, 52.0, -120.0);
    drawTriangle(52.0, -120.0, 41.27, -119.78, 54.97, -120.36);

    if (day)
        glColor3ub(0, 115, 230);
    else
        glColor3ub(0, 31, 62); 
    drawRectangle(47.02, -111.49, 45.51, -114.87, 50.19, -114.85, 50.23, -111.49);
    drawRectangle(51.33, -111.31, 54.69, -111.17, 55.38, -114.72, 51.27, -114.75);
    drawRectangle(32.63, -115.74, 32.58, -116.96, 36.92, -117.68, 36.82, -116.24);
    drawRectangle(38.26, -116.36, 38.33, -117.68, 42.82, -118.16, 42.82, -116.79);
    drawRectangle(44.61, -116.79, 44.53, -118.25, 49.2, -118.58, 49.19, -117.02);

    glColor3ub(192, 192, 192);
    drawRectangle(69.59, -117.14, 83.36, -116.21, 84.71, -118.34, 70.85, -119.98);
    glColor3ub(169, 169, 169);
    drawRectangle(68.52, -122.32, 70.85, -119.98, 84.71, -118.34, 82.56, -121.13);
    drawRectangle(68.52, -122.32, 82.56, -121.13, 80.77, -123.46, 67.07, -125.78);
    drawRectangle(67.07, -125.78, 69.47, -124.14, 80.77, -123.46, 78.76, -126.08);
    drawRectangle(67.07, -125.78, 78.76, -126.08, 75.62, -128.15, 67.49, -127.59);
    drawRectangle(75.62, -128.15, 67.49, -127.59, 69.52, -128.78, 70.43, -128.8);
    glColor3ub(169, 169, 169);
    drawRectangle(70.55, -122.24, 82.56, -121.13, 80.77, -123.46, 69.47, -124.14);
}

float boat3X = 0.0f;
void drawBoat3() // O222
{
    glPushMatrix();
    glPushMatrix();
    glPushMatrix();
    glScalef(1.5, 1.5, 0.0);
    glTranslatef(0.0f, 50.0f, 0.0f);
    glTranslatef(boat3X, 0.0f, 0.0f);

    drawBoatType2();
    glColor3ub(0, 0, 0);
    glLineWidth(2.0);
    drawLines(71.32, -114.63, 40.67, -47.8);
    drawLines(40.24, -35.99, 81.08, -116.36);
    glColor3ub(255, 255, 255);
    // paal
    drawRectangle(41.53, -115.06, 43.95, -115.06, 43.26, -102.24, 41.1, -101.76);
    drawRectangle(43.46, -106.02, 82.89, -101.06, 82.16, -99.86, 43.29, -103.76);
    drawRectangle(39.75, -76.56, 41.76, -78.33, 40.14, -33.15, 38.78, -33.2);
    drawRectangle(38.07, -33.22, 41.01, -33.14, 41, -32, 38, -32);

    glColor3ub(255, 0, 0);
    drawRectangle(19.58, -57.74, 16.53, -60.41, 11.23, -67.6, 15.05, -65.48);
    drawRectangle(15.05, -65.48, 11.23, -67.6, 7.03, -78.86, 14.25, -70.45);
    drawRectangle(14.25, -70.45, 7.03, -78.86, 5.84, -88.85, 13.84, -74.57);
    drawRectangle(13.84, -74.57, 5.84, -88.85, 6.71, -94.56, 14.52, -79.25);
    drawRectangle(14.52, -79.25, 6.71, -94.56, 7.98, -102.57, 16.96, -86.53);
    drawRectangle(16.96, -86.53, 7.98, -102.57, 11.23, -108.28, 18.29, -90.04);
    drawRectangle(18.29, -90.04, 11.23, -108.28, 14.4, -108.28, 26.69, -103.14);
    glColor3ub(169, 169, 169);
    drawTriangle(32.45, -47.22, 19.58, -57.74, 16.96, -86.53);
    drawTriangle(16.96, -86.53, 19.58, -57.74, 16.53, -60.41);
    drawTriangle(16.96, -86.53, 16.53, -60.41, 15.05, -65.48);
    drawTriangle(16.96, -86.53, 15.05, -65.48, 14.25, -70.45);
    drawTriangle(16.96, -86.53, 14.25, -70.45, 13.84, -74.57);
    drawTriangle(16.96, -86.53, 13.84, -74.57, 14.52, -79.25);

    glColor3ub(255, 0, 0);
    drawRectangle(32.3, -59.9, 31.29, -63.01, 30.45, -67.73, 32.89, -64.9);
    drawRectangle(32.89, -64.9, 30.45, -67.73, 30.25, -69.26, 34.75, -69.58);
    drawRectangle(34.75, -69.58, 30.25, -69.26, 30.06, -77.67, 37.48, -73.75);
    drawRectangle(37.48, -73.75, 30.06, -77.67, 30.9, -83.89, 39.75, -76.56);
    drawRectangle(39.75, -76.56, 30.9, -83.89, 33.51, -90.52, 41.76, -78.33);
    drawRectangle(41.76, -78.33, 33.51, -90.52, 37.74, -97.58, 53.48, -87.73);
    drawRectangle(53.48, -87.73, 37.74, -97.58, 41.1, -101.76, 59.86, -91.32);
    drawRectangle(59.86, -91.32, 41.1, -101.76, 43.26, -102.24, 76.62, -98.66);
    glColor3ub(169, 169, 169);
    drawTriangle(38.98, -41.92, 32.3, -59.9, 39.75, -76.56);
    drawTriangle(39.75, -76.56, 32.3, -59.9, 32.89, -64.9);
    drawTriangle(39.75, -76.56, 32.89, -64.9, 34.75, -69.58);
    drawTriangle(39.75, -76.56, 34.75, -69.58, 37.48, -73.75);

    glColor3ub(255, 255, 0);
    drawRectangle(25.72, -75.87, 23.18, -81.14, 21.24, -86.53, 24.51, -80.64);
    drawRectangle(24.51, -80.64, 21.24, -86.53, 19.86, -92.49, 24.85, -85.83);
    drawRectangle(24.85, -85.83, 19.86, -92.49, 26.69, -103.14, 26.23, -90.3);
    drawRectangle(26.23, -90.3, 26.69, -103.14, 32.7, -101.15, 27.05, -91.99);
    drawRectangle(26.69, -103.14, 20.52, -105.72, 21.8, -110.69, 25.95, -110.17);
    drawRectangle(26.69, -103.14, 25.95, -110.17, 37.18, -105.76, 32.7, -101.15);
    glColor3ub(169, 169, 169);
    drawRectangle(30.25, -69.26, 29.25, -70.09, 25.72, -75.87, 30.06, -77.67);
    drawRectangle(30.06, -77.67, 25.72, -75.87, 24.51, -80.64, 29.12, -79.94);
    drawRectangle(29.12, -79.94, 24.51, -80.64, 24.85, -85.83, 26.23, -90.3);

    glColor3ub(0, 0, 0);
    glLineWidth(2.0);
    drawLines(38.8, -34.17, 32.45, -47.22);
    drawLines(30.45, -108.4, 38.3, -119.41);
    drawLines(37.18, -105.76, 41.23, -110.14);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

float boat4X = -180.0f;
float boat4Y = 80.0f;
void drawBoat4() // O223
{
    glPushMatrix();
    glPushMatrix();
    glPushMatrix();
    glTranslatef(boat4X, boat4Y, 0.0f);
    glScalef(1.2, 1.2, 1.0);
    drawBoatType2();
    glPopMatrix();
    glPopMatrix();
}

void updateBoatType1(int value) // A205
{
    boat1X += 1.0f; 
    if (boat1X > 300.0f) 
        boat1X = -200.0f;

    glutPostRedisplay();
    glutTimerFunc(70, updateBoatType1, 0); // A205
}

void updateBoatType2(int value) // A206
{
    boat3X -= 1.0f; 
    if (boat3X < -600.0f) 
        boat3X = 200.0f;

    glutPostRedisplay();
    glutTimerFunc(30, updateBoatType2, 0); // A206
}

/*------------------------------------- Clouds -------------------------------------------------*/
float cloudOffsets[5] = { 0.0f, 100.0f, 200.0f, 350.0f, 400.0f}; 
float cloudSpeed = 5.0; 
void drawCloud1() // O224
{
    glPushMatrix();
    glTranslatef(cloudOffsets[0], 0.0f, 0.0f);
    if (day && !rain) glColor3ub(255, 255, 255);
    else if (day && rain) glColor3ub(78, 110, 125);
    else glColor3ub(52, 57, 64);

    drawCircle(69.07, 158.74, sqrt(217.73));
    drawCircle(85.15, 147.05, sqrt(205.51));
    drawCircle(106.49, 150.56, sqrt(289.94));
    drawCircle(89.83, 169.27, sqrt(286.18));
    drawCircle(114.38, 174.53, sqrt(121.43));
    drawCircle(133.09, 156.4, sqrt(322.15));
    glPopMatrix();
}

void drawCloud2() // O225
{
    glPushMatrix();
    glTranslatef(cloudOffsets[1], 0.0f, 0.0f);
    if (day && !rain) glColor3ub(255, 255, 255);
    else if (day && rain) glColor3ub(78, 110, 125);
    else glColor3ub(52, 57, 64);

    drawCircle(-161.97, 186.03, sqrt(308.15));
    drawCircle(-182.36, 172.98, sqrt(230.86));
    drawCircle(-164.21, 161.36, sqrt(166.87));
    drawCircle(-142.81, 160.75, sqrt(227.66));
    drawCircle(-117.52, 171.76, sqrt(250.48));
    drawCircle(-136.89, 185.21, sqrt(216.73));

    glPopMatrix();
}

void drawCloud3() // O226
{
    glPushMatrix();
    glTranslatef(cloudOffsets[2], 0.0f, 0.0f);
    if (day && !rain) glColor3ub(255, 255, 255);
    else if (day && rain) glColor3ub(78, 110, 125);
    else glColor3ub(52, 57, 64);

    drawCircle(-29.73, 194.0, sqrt(293.66));
    drawCircle(-50.0, 180.0, sqrt(239.48));
    drawCircle(-32.92, 169.29, sqrt(169.04));
    drawCircle(-12.2, 172.48, sqrt(232.68));
    drawCircle(-7.41, 195.0, sqrt(153.44));
    drawCircle(12.91, 180.45, sqrt(231.73));

    glPopMatrix();
}

void drawCloud4() // O227
{
    glPushMatrix();
    glTranslatef(cloudOffsets[3], 0.0f, 0.0f);
    if (day && !rain) glColor3ub(255, 255, 255);
    else if (day && rain) glColor3ub(78, 110, 125);
    else glColor3ub(52, 57, 64);

    drawCircle(143.67, 98.0, sqrt(223.81));
    drawCircle(161.77, 112.23, sqrt(282.38));
    drawCircle(160.8, 86.17, sqrt(276.91));
    drawCircle(187.33, 112.05, sqrt(191.14));
    drawCircle(183.76, 87.37, sqrt(308.6));
    drawCircle(205.2, 96.79, sqrt(206.79));
    glPopMatrix();
}

void drawCloud5() // O228
{
    glPushMatrix();
    glTranslatef(cloudOffsets[4], 0.0f, 0.0f);
    if (day && !rain) glColor3ub(255, 255, 255);
    else if (day && rain) glColor3ub(78, 110, 125);
    else glColor3ub(52, 57, 64);

    drawCircle(-81.57, 107.08, sqrt(220.92));
    drawCircle(-65.3, 94.63, sqrt(242.02));
    drawCircle(-57.34, 118.85, sqrt(212.3));
    drawCircle(-40.0, 100.0, sqrt(317.84));
    drawCircle(-33.12, 115.04, sqrt(137.94));
    drawCircle(-22.05, 102.58, sqrt(188.95));

    glPopMatrix();
}

void updateClouds(int value) // A207
{
    for (int i = 0; i < 5; ++i)
    {
        cloudOffsets[i] -= cloudSpeed; 

        if (cloudOffsets[i] < -400.0f)
        {
            cloudOffsets[i] = 400.0f;
            cloudOffsets[i] += static_cast<float>(rand() % 50);
        }
    }

    glutPostRedisplay(); 
    glutTimerFunc(100, updateClouds, 0); // A207
}

/*------------------------------------- Stars -------------------------------------------------*/
vector<pair<float, float>> starPositions;
// initialize star positions
void initializeStars()
{
    float xMin = -200.0f;
    float xMax = 200.0f;
    float yMin = 28.75f;
    float yMax = 200.0f;

    starPositions.resize(100); 
    for (int i = 0; i < 100; ++i)
    {
        starPositions[i].first = xMin + static_cast<float>(rand()) / RAND_MAX * (xMax - xMin);  // x coordinate
        starPositions[i].second = yMin + static_cast<float>(rand()) / RAND_MAX * (yMax - yMin); // y coordinate
    }
}

// draw a single star
void drawStar(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

// draw stars using pre-generated positions
void drawStars() // O229
{
    glColor3f(1.0f, 1.0f, 1.0f); 
    for (const auto& star : starPositions)
        drawStar(star.first, star.second); // Access x and y from the pair
}

/*------------------------------------- Trees -------------------------------------------------*/
void drawTree1() // O230
{
    glColor3ub(46, 138, 87);
    drawCircle(-83.04, 35.14, sqrt(207.32));
    drawCircle(-63.16, 38.17, sqrt(272.1));
    drawCircle(-38.45, 36.38, sqrt(207.32));

    glColor3ub(60, 179, 113);
    drawCircle(-78, 60, sqrt(419.42));
    drawCircle(-45.29, 59.19, sqrt(375.6));

    glColor3ub(101, 205, 170);
    drawCircle(-61.41, 87.05, sqrt(407.17));
}

void drawTree2()  // O231
{
    glColor3ub(46, 138, 87);
    drawCircle(110.28, 33.51, sqrt(105.12));
    drawCircle(123.6, 36.07, sqrt(131.72));
    drawCircle(139.47, 34.2, sqrt(104.58));

    glColor3ub(60, 179, 113);
    drawCircle(118.02, 51.53, sqrt(133.38));
    drawCircle(135.43, 51.91, sqrt(140.6));

    glColor3ub(101, 205, 170);
    drawCircle(125.45, 68.82, sqrt(137.94));
}

void drawTree3() // O232
{
    glColor3ub(97, 32, 29);
    drawRectangle(181.71, 39.36, 183.49, 36.57, 182.05, 36.38, 181.05, 37.9);
    drawRectangle(183.34, 39.26, 184.43, 38.2, 183.49, 36.57, 182.05, 36.38);
    drawRectangle(182.05, 36.38, 183.49, 36.57, 183.33, 32.04, 181.88, 32.1);

    glColor3ub(60, 179, 113);
    drawCircle(176.97, 40.82, sqrt(30.73));
    drawCircle(187.27, 42.26, sqrt(33.52));

    glColor3ub(101, 205, 170);
    drawCircle(181.5, 48.97, sqrt(38.39));
}

void drawTree4() // O233
{
    glColor3ub(97, 32, 29);
    drawRectangle(30.59, 25.15, 32.33, 25.18, 32.25, 27.56, 30.53, 28.14);
    drawRectangle(30.53, 28.14, 32.25, 27.56, 32.22, 30.72, 31.15, 29.92);
    drawRectangle(31.15, 29.92, 32.22, 30.72, 32.62, 33.83, 31.79, 34.29);
    drawRectangle(30.53, 28.14, 31.15, 29.92, 30.29, 33.99, 28.95, 33.79);

    glColor3ub(60, 179, 113);
    drawCircle(25.5, 38.82, sqrt(46.29));
    drawCircle(36.37, 39.6, sqrt(51.56));

    glColor3ub(101, 205, 170);
    drawCircle(30, 50, sqrt(47.48));
}

/*------------------------------------- Coconut Trees -------------------------------------------------*/
void drawCoconutTree1() // O234
{
    glColor3ub(97, 32, 29);
    drawRectangle(72.36, -3.23, 82.79, -1.69, 82.28, 4.33, 79.34, 2.64);
    drawRectangle(79.34, 2.64, 82.28, 4.33, 94.58, 38.22, 89.61, 31.09);
    drawTriangle(94.58, 38.22, 89.61, 31.09, 91.19, 35.4);
    drawRectangle(91.19, 35.4, 94.58, 38.22, 105.99, 83.27, 103.96, 83.04);
    drawRectangle(103.96, 83.04, 105.99, 83.27, 106.63, 88.02, 105.22, 88.44);

    glColor3ub(8, 144, 0);
    drawRectangle(84.22, 68.22, 87.06, 71.62, 89.14, 74.78, 88.61, 76.51);
    drawTriangle(85.55, 67.27, 87.06, 71.62, 89.14, 74.78);
    drawRectangle(88, 70, 89.14, 74.78, 88.61, 76.51, 91.84, 77.3);
    drawRectangle(89.48, 67.7, 89.84, 71.51, 91.84, 77.3, 90.81, 73.14);
    drawRectangle(91.03, 69.53, 90.81, 73.14, 91.84, 77.3, 91.67, 73.92);
    drawRectangle(91.84, 77.3, 91.67, 73.92, 92.47, 73.47, 93.49, 75.93);
    drawTriangle(93.49, 75.93, 92.47, 73.47, 92.42, 70.68); //ok.....
    drawRectangle(88.61, 76.51, 91.84, 77.3, 93.49, 75.93, 92.63, 80.1);
    drawRectangle(92.63, 80.1, 93.49, 75.93, 94.4, 71.86, 95.21, 76.28);
    drawTriangle(95.21, 76.28, 96.33, 77.4, 92.63, 80.1);
    drawTriangle(96.33, 77.4, 95.56, 72.39, 97.72, 79.49);
    drawRectangle(92.63, 80.1, 96.33, 77.4, 97.72, 79.49, 98.43, 83.5); //ok....
    drawRectangle(98.43, 83.5, 97.72, 79.49, 97.39, 72.62, 98.06, 79.31);
    drawRectangle(98.43, 83.5, 98.06, 79.31, 98.3, 73.48, 98.97, 80.33);
    drawRectangle(98.43, 83.5, 98.97, 80.33, 99.46, 74.64, 100, 82);
    drawRectangle(100, 82, 98.43, 83.5, 104.3, 84.52, 103.96, 83.04);

    drawTriangle(103.96, 83.04, 104.3, 84.52, 103.23, 84.89);
    drawTriangle(103.23, 84.89, 101.48, 86.22, 100, 86);
    drawRectangle(100, 86, 101.48, 86.22, 94.76, 84.13, 96.75, 87.21);
    drawPentagon(96.75, 87.21, 94.76, 84.13, 92.03, 81.61, 91.15, 84.42, 90, 86);
    drawRectangle(91.15, 84.42, 92.03, 81.61, 90.09, 79.35, 88.78, 80.92);
    drawTriangle(90, 86, 87.73, 83.28, 89.03, 83.25);
    drawRectangle(90, 86, 89.03, 83.25, 87.43, 80.34, 91.15, 84.42); //ok....
    drawTriangle(87.73, 83.28, 87.43, 80.34, 86, 82);
    drawRectangle(86, 82, 87.73, 83.28, 86.53, 81.28, 86.65, 80.54);

    //glColor3ub(14, 255, 0);
    drawTriangle(103.23, 84.89, 101.48, 86.22, 102.1, 86.92);
    drawRectangle(101.48, 86.22, 102.1, 86.92, 98.45, 88.76, 97.08, 88.45);
    drawRectangle(97.08, 88.45, 98.45, 88.76, 92.35, 89.62, 92.43, 88.54);
    drawRectangle(92.43, 88.54, 92.35, 89.62, 88, 88, 88.94, 86.66);
    drawPentagon(88.94, 86.66, 88, 88, 84.4, 84.1, 82.47, 79.18, 84.45, 82.13);

    drawRectangle(102.1, 86.92, 100.35, 88.72, 97.65, 91.29, 99.49, 91);
    drawTriangle(97.65, 91.29, 93.69, 93.01, 94.32, 93.4);
    drawPentagon(97.65, 91.29, 94.32, 93.4, 92.44, 94.23, 94.71, 93.97, 99.49, 91);

    drawTriangle(102.1, 86.92, 99.31, 92.57, 100.49, 93.08);
    drawPentagon(100.49, 93.08, 99.31, 92.57, 93.15, 96.66, 90.28, 98.54, 95.27, 97.08);

    drawRectangle(102.1, 86.92, 103.23, 84.89, 103.03, 91.69, 101.57, 92.19);
    drawRectangle(101.57, 92.19, 103.03, 91.69, 101.01, 96.81, 99.55, 96.66);
    drawRectangle(99.55, 96.66, 101.01, 96.81, 97.38, 100.85, 93.1, 99.9);
    drawRectangle(93.1, 99.9, 97.38, 100.85, 91.79, 101.69, 87.13, 100.85);

    drawRectangle(105.99, 83.27, 106.39, 80.3, 107.59, 79.43, 107.98, 83.32);
    drawRectangle(106.39, 80.3, 107.59, 79.43, 107.29, 76.38, 105.59, 71.76);
    drawRectangle(107.98, 83.32, 107.59, 79.43, 108.35, 76.24, 111.5, 79.32);
    drawRectangle(108.35, 76.24, 107.46, 70.7, 108.52, 72.46, 108.98, 74.52);
    drawRectangle(108.98, 74.52, 108.35, 76.24, 111.5, 79.32, 110.38, 75.58);
    drawRectangle(111.5, 79.32, 110.38, 75.58, 111.8, 74.48, 112.88, 74.85); //ok....
    drawPentagon(108.98, 74.52, 109.58, 71.99, 109.48, 69.47, 110, 72, 110.38, 75.58);
    drawRectangle(110.38, 75.58, 111.11, 73.12, 111.29, 67.69, 111.8, 74.48);
    drawPentagon(111.8, 74.48, 112.51, 69.87, 112.6, 67.67, 113.13, 71.11, 112.88, 74.85);

    drawRectangle(106.02, 84.54, 106.74, 85.56, 109.62, 87.19, 109.36, 85.65);
    drawPentagon(109.36, 85.65, 109.62, 87.19, 111.59, 86.43, 111.14, 85.8, 111.04, 84.84);
    drawPentagon(111.04, 84.84, 111.14, 85.8, 115.93, 81.28, 116.06, 79.72, 113.35, 82.88);
    drawRectangle(116.06, 79.72, 115.93, 81.28, 117.11, 79.09, 117.01, 77.81);
    drawPentagon(111.14, 85.8, 113.7, 83.91, 116.51, 81.8, 115.22, 83.93, 111.59, 86.43);
    drawRectangle(116.51, 81.8, 115.22, 83.93, 118.07, 80.83, 118.51, 78.54);
    drawRectangle(109.62, 87.19, 111.59, 86.43, 114.76, 85.93, 114.63, 87.44);
    drawRectangle(114.76, 85.93, 114.63, 87.44, 118.51, 85.68, 118, 84);
    drawRectangle(118, 84, 118.51, 85.68, 120.89, 81.99, 121.08, 79.23);

    drawRectangle(105.22, 88.44, 106.63, 88.02, 109.34, 89.69, 106.83, 90.18);
    drawPentagon(106.83, 90.18, 109.34, 89.69, 112, 92.48, 115.68, 93.74, 113.43, 93.96);
    drawTriangle(109.34, 89.69, 112, 92.48, 114.1, 89.35);
    drawRectangle(114.1, 89.35, 114.93, 90.03, 113.99, 91.08, 112, 92.48);
    drawRectangle(109.34, 89.69, 113.02, 89.05, 116.95, 87.18, 114.1, 89.35);
    drawPentagon(114.1, 89.35, 115.38, 89.05, 118.08, 87.51, 117.14, 88.86, 114.93, 90.03);
    drawHexagon(114.93, 90.03, 117.33, 89.95, 120.4, 89.16, 118.19, 90.55, 116.1, 90.81, 113.99, 91.08);
    drawHexagon(113.99, 91.08, 117.33, 91.79, 121.6, 90.93, 122, 92, 117.93, 93.03, 112, 92.48);
    drawPentagon(122, 92, 121.6, 90.93, 125.76, 88.86, 129.63, 85.83, 126.74, 88.98);
    drawPentagon(115.68, 93.74, 120, 94, 124.6, 92.13, 119.28, 95.01, 113.43, 93.96);

    drawHexagon(105.22, 88.44, 106.83, 90.18, 108.55, 91.86, 108.25, 93.93, 107.28, 95.01, 106.54, 92.65);
    drawTriangle(108.55, 91.86, 114, 96, 108.25, 93.93);
    drawRectangle(108.25, 93.93, 114.33, 97.45, 110.8, 97, 107.28, 95.01);
    drawPentagon(107.28, 95.01, 110.8, 97, 117.18, 99.59, 111.78, 98.69, 110.69, 99.74);
    drawTriangle(111.78, 98.69, 118.23, 101.42, 112.53, 99.62);
    drawOctagon(110.69, 99.74, 115.8, 102.72, 118, 104, 123.03, 104.95, 124.38, 105.02, 120.21, 103.19, 112.53, 99.62, 111.78, 98.69);
    drawRectangle(110.69, 99.74, 115.8, 102.72, 119.72, 106.53, 113.3, 104.32);
    drawHexagon(113.3, 104.32, 114, 106, 109.41, 102.62, 107.62, 98.28, 107.28, 95.01, 110.69, 99.74);

    drawPentagon(105.22, 88.44, 106.54, 92.65, 106.83, 98.31, 105.67, 98.06, 105.07, 95.73);
    drawRectangle(105.67, 98.06, 106.83, 98.31, 109.23, 104.87, 106.49, 101.24);
    drawPentagon(105.67, 98.06, 103.64, 102.17, 101.54, 101.65, 104.17, 96.96, 105.07, 95.73);
    drawRectangle(101.54, 101.65, 103.64, 102.17, 100.6, 103.34, 98.99, 102.62);

    glColor3ub(6, 59, 0);
    drawCircle(101.58, 82.03, sqrt(2.85));
    drawCircle(103.27, 82.31, sqrt(2.18));
    drawCircle(102.92, 80.54, sqrt(2.85));
    drawCircle(105.82, 82.04, sqrt(2.18));
    drawCircle(106.52, 80.8, sqrt(2.85));
}

void drawCoconutTree2() // O235
{
    glColor3ub(97, 32, 29);
    drawHexagon(70, 25, 79.34, 2.64, 82.79, -1.69, 86.16, -0.62, 77.06, 18.62, 67.67, 45);
    drawOctagon(70, 25, 67.67, 45, 64.62, 63.58, 63.81, 84.76, 61.17, 86.22, 61.44, 71.85, 63.44, 51.3, 70, 25);
    drawPentagon(61.17, 86.22, 61.8, 92.29, 62.06, 94.86, 63.26, 93.67, 63.81, 84.76);

    glColor3ub(8, 144, 0);
    drawOctagon(62.06, 94.86, 61.8, 92.29, 59.47, 84.89, 57.75, 88.68, 57.35, 82.85, 56.31, 87.01, 56, 82, 56.17, 92.03);
    drawOctagon(56.17, 92.03, 56, 82, 55.51, 87.47, 55.23, 80.74, 54, 86, 53.91, 78.6, 52.9, 85.78, 50.06, 87.55);
    drawOctagon(50.06, 87.55, 52.9, 85.78, 52.38, 78.83, 51.21, 86.06, 50.43, 78.9, 49.91, 83.97, 48.86, 80.24, 47.52, 81.88);
    drawTriangle(47.52, 81.88, 48.86, 80.24, 50.13, 73.83);

    drawOctagon(62.06, 94.86, 63.26, 93.67, 63.93, 91.6, 64.22, 81.48, 65.22, 85.79, 64.72, 90.32, 66.38, 88.62, 65.71, 93.59);
    drawHexagon(65.71, 93.59, 66.38, 88.62, 66.46, 81.31, 67.33, 82.97, 67.54, 87.74, 68.95, 89.65);
    drawRectangle(68.95, 89.65, 67.54, 87.74, 68.49, 80.98, 69.12, 87.66);
    drawOctagon(69.12, 87.66, 69.78, 85.13, 70.36, 78.12, 71.07, 82.31, 72.93, 77.16, 72.14, 80.69, 68.95, 89.65, 67.54, 87.74);

    drawOctagon(62.06, 94.86, 65.71, 93.59, 66.34, 93.47, 71.31, 88.99, 74, 82, 72.81, 88.33, 69.86, 92.64, 66.58, 95.59);
    drawTriangle(66.58, 95.59, 62.44, 96.42, 62.06, 94.86);

    drawRectangle(62.44, 96.42, 68, 96, 68, 100, 63.89, 98.46);
    drawOctagon(68, 100, 68, 96, 69.95, 97.43, 71, 97.95, 71.81, 98.4, 71.73, 99.54, 73.09, 100.29, 68, 100);
    drawPentagon(68, 96, 70.92, 94.91, 73.11, 91.63, 72.26, 94.26, 69.95, 97.43);
    drawTriangle(69.95, 97.43, 72.87, 94.71, 71, 97.95);
    drawRectangle(71, 97.95, 74.33, 93.74, 74.04, 95.08, 71.81, 98.4);
    drawHexagon(71.81, 98.4, 74.85, 95.68, 76.35, 91.51, 76.64, 93.78, 75.26, 96.29, 71.73, 99.54);
    drawOctagon(71.73, 99.54, 75.1, 97.51, 77.61, 94.47, 80.21, 90.86, 78.26, 95.24, 75.02, 98.81, 73.09, 100.29, 71.73, 99.54);
    drawHexagon(73.09, 100.29, 75.02, 98.81, 75.95, 98.6, 78.35, 96.67, 76.71, 99.36, 75.03, 99.79);

    drawHexagon(62.44, 96.42, 63.77, 100.27, 68.48, 106.17, 68.68, 103.38, 67.44, 101.46, 63.89, 98.46);
    drawPentagon(68.68, 103.38, 68.48, 106.17, 74.32, 109.2, 76.92, 109.07, 70.34, 106.04);
    drawPentagon(68.68, 103.38, 67.44, 101.46, 72.69, 104.55, 77.2, 106.59, 73.13, 105.38);

    drawPentagon(62.06, 94.86, 62.44, 96.42, 57.57, 98.39, 57.07, 96.78, 58, 96);
    drawOctagon(57.07, 96.78, 56.02, 96.51, 55.37, 96.6, 54.14, 96.48, 52.96, 95.43, 51.35, 95.31, 51.86, 99.1, 57.57, 98.39);
    drawOctagon(51.86, 99.1, 51.35, 95.31, 49.53, 95.22, 47.54, 95.39, 44.96, 95.06, 43.49, 93.89, 42.34, 94.99, 46.3, 98.64);
    drawHexagon(42.34, 94.99, 40, 90, 39.53, 86.77, 40.89, 89.48, 41.34, 86.17, 43.49, 93.89);
    drawPentagon(44.96, 95.06, 43.69, 91.33, 44.12, 90.61, 45.68, 93.32, 47.54, 95.39);
    drawHexagon(49.53, 95.22, 49.45, 93.95, 48, 90, 48.43, 89.17, 50.46, 93.57, 51.35, 95.31);
    drawTriangle(52.96, 95.43, 51.9, 90.86, 54.14, 96.48);
    drawTriangle(55.37, 96.6, 53.52, 91.84, 56.02, 96.51);
    drawTriangle(57.07, 96.78, 55.34, 92.33, 58, 96);

    drawOctagon(62.44, 96.42, 57.67, 101.06, 53.76, 101.6, 52.05, 102.46, 50.83, 104.12, 48.54, 104.8, 55.92, 106.6, 58.89, 103.09);
    drawHexagon(55.92, 106.6, 48.54, 104.8, 48, 106, 46.1, 106.37, 46, 108, 51.73, 108.49);
    drawTriangle(46, 108, 41.69, 105.16, 46.1, 106.37);
    drawTriangle(46.1, 106.37, 44, 104, 48, 106);
    drawTriangle(48, 106, 44.62, 102.86, 48.54, 104.8);
    drawTriangle(48.54, 104.8, 45.47, 101.15, 50.83, 104.12);
    drawTriangle(50.83, 104.12, 47.64, 100.88, 52.05, 102.46);
    drawTriangle(52.05, 102.46, 48.36, 100.16, 53.76, 101.6);

    drawOctagon(62.44, 96.42, 59.88, 102.91, 59.79, 103.58, 61.27, 105.41, 62, 106, 63.15, 106, 64, 104, 63.77, 100.27);
    drawOctagon(62.44, 96.42, 58.89, 103.09, 57.72, 106.64, 57.18, 107.86, 54.48, 109.93, 56.62, 110.19, 59.79, 103.58, 59.88, 102.91);
    drawHexagon(59.79, 103.58, 60, 106, 58.48, 109.42, 57.33, 112.49, 59.24, 109.24, 61.27, 105.41);
    drawPentagon(61.27, 105.41, 60.41, 110.46, 58.41, 114.76, 61.31, 110.52, 62, 106);
    drawTriangle(62, 106, 63.12, 108.62, 63.15, 106);
    drawTriangle(63.15, 106, 64.96, 109.96, 64, 104);

    glColor3ub(6, 59, 0);
    drawCircle(61.29, 90.67, sqrt(3.03));
    drawCircle(63.47, 92.22, sqrt(1.78));
    drawCircle(63.87, 90.97, sqrt(2.48));
}

float coconutTree3X = -170.0f; 
float coconutTree3Y = 0.0f; 
void drawCoconutTree3() // O236
{
    glPushMatrix();
    glTranslatef(coconutTree3X, coconutTree3Y, 0);
    drawCoconutTree2();
    glPopMatrix();
}

float coconutTree4X = 120.0f;
float coconutTree4Y = 28.0f; 
void drawCoconutTree4() // O237
{
    glPushMatrix();
    glPushMatrix();
    glTranslatef(coconutTree4X, coconutTree4Y, 0);
    glScalef(0.5, 0.5, 1.0);
    drawCoconutTree1();
    glPopMatrix();
    glPopMatrix();
}

/*------------------------------------- Fireflies -------------------------------------------------*/
const int numFireflies = 50;
float fireflyPositions[numFireflies][2]; 
void initializeFireflies()
{
    srand(static_cast<unsigned>(time(0))); 
    for (int i = 0; i < numFireflies; i++)
    {
        fireflyPositions[i][0] = rand() % 401 - 200; // (-200 to 200)
        fireflyPositions[i][1] = rand() % 401 - 200; // (-200 to 200)
    }
}

// Draw fireflies
void drawFireflies() // O238
{
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (int i = 0; i < numFireflies; i++)
    {
        float x = fireflyPositions[i][0];
        float y = fireflyPositions[i][1];
        float radius = 2.0f; 

        // Inner core (Bright Yellow)
        glColor4f(1.0f, 1.0f, 0.0f, 1.0f); 
        drawCircle(x, y, radius * 0.5f);

        // Outer glow (Faint Yellow)
        glColor4f(1.0f, 1.0f, 0.2f, 0.3f); 
        drawCircle(x, y, radius);
    }

    glDisable(GL_BLEND); 
}

void updateFireflies(int value) // A208
{
    for (int i = 0; i < numFireflies; i++)
    {
        // Randomly move each firefly in X and Y directions
        fireflyPositions[i][0] += (rand() % 5 - 2) * 1.0f; //  -2 to +2  in X
        fireflyPositions[i][1] += (rand() % 5 - 2) * 1.0f; //  -2 to +2  in Y

        // Ensure the fireflies stay within the bounds (-200 to 200)
        if (fireflyPositions[i][0] < -200.0f) fireflyPositions[i][0] = -200.0f;
        if (fireflyPositions[i][0] > 200.0f) fireflyPositions[i][0] = 200.0f;
        if (fireflyPositions[i][1] < -200.0f) fireflyPositions[i][1] = -200.0f;
        if (fireflyPositions[i][1] > 200.0f) fireflyPositions[i][1] = 200.0f;
    }

    glutPostRedisplay(); 
    glutTimerFunc(50, updateFireflies, 0); // A208
}

/*------------------------------------- Lightning Flash -------------------------------------------------*/
struct lightningBranch
{
    float x1, y1; // Start point
    float x2, y2; // End point
};

vector<lightningBranch> lightningBranches;
void generateLightning(float startX, float startY)
{
    lightningBranches.clear();

    float x = startX;  
    float y = startY;  

    while (y > 28.75)
    {
        // Stop when reaching the bottom of the sky
        float nextX = x + (rand() % 30 - 15); // Random zigzag movement (-15 to 15 units)
        if (nextX < -200.0f) nextX = -200.0f; // Keep within left boundary
        if (nextX > 200.0f) nextX = 200.0f;   // Keep within right boundary

        float nextY = y - (rand() % 20 + 10); // Move downward randomly (10 to 30 units)
        if (nextY < 28.75) nextY = 28.75;    // Stop at the bottom of the sky

        // Add the main bolt segment
        lightningBranches.push_back({ x, y, nextX, nextY });
        x = nextX;
        y = nextY;

        // Add random branches
        if (rand() % 100 < 30)
        {
            // 30% chance for a branch
            float branchX = x + (rand() % 20 - 10); // Branch x offset
            if (branchX < -200.0f) branchX = -200.0f; // Keep within left boundary
            if (branchX > 200.0f) branchX = 200.0f;   // Keep within right boundary

            float branchY = y - (rand() % 10 + 5);  // Branch y offset
            if (branchY < 28.75) branchY = 28.75;  // Stop at the bottom of the sky
            lightningBranches.push_back({ x, y, branchX, branchY });
        }
    }
}

void drawLightningFlash() // O239
{
    glColor3f(1.0f, 1.0f, 0.8f); 
    glBegin(GL_LINES);
    for (const lightningBranch& branch : lightningBranches)
    {
        glVertex2f(branch.x1, branch.y1);
        glVertex2f(branch.x2, branch.y2);
    }
    glEnd();
}

void updateLightningFlash(int value) // A209
{
    static int lightningDuration = 0; // Counter to track how long the lightning stays visible

    if (lightningDuration > 0)
        lightningDuration--; // Decrease the counter to maintain the lightning on screen
    else
    {
        // Generate a new lightning bolt
        float startX = static_cast<float>(rand() % 400 - 200); // Random start position (-200 to 200)
        float startY = 200.0f; // Start at the top of the sky
        generateLightning(startX, startY);

        lightningDuration = 5; // Set duration (e.g., 20 × 100ms = 2 seconds)
    }

    glutPostRedisplay();
    glutTimerFunc(100, updateLightningFlash, 0); // A209
}

/*------------------------------------- Bridge -------------------------------------------------*/
void drawBridge() // O240
{
    // dhore hatar jinish
    glColor3ub(61, 23, 3);
    glLineWidth(3.0);
    drawLines(82.7, -15.61, -16.99, -14.99);
    glLineWidth(2.0);
    drawLines(-1.02, -13, 79.14, -13.39);

    // pa deyar jayga
    glColor3ub(208, 169, 110);
    drawRectangle(-24.37, -24.06, -13.28, -19.01, 84.63, -19.7, 75.77, -26.59);

    // lifelines
    glColor3ub(61, 23, 3);
    glLineWidth(1.0);
    drawLines(1.08, -12.9, 1.08, -15.74);
    drawLines(8.88, -12.94, 8.88, -19.13);
    drawLines(17.08, -13.01, 17.08, -19.19);
    drawLines(24.25, -13.05, 24.25, -19.34);
    drawLines(32.25, -13.1, 32.25, -19.66);
    drawLines(39.55, -13.14, 39.55, -20.27);
    drawLines(47.44, -13.19, 47.44, -20.51);
    drawLines(55, -13.24, 55, -20);
    drawLines(63.22, -13.47, 63.22, -20.44);
    drawLines(75.29, -13.37, 75.29, -19.84);

    glLineWidth(2.0);
    drawLines(-14.05, -15.18, -14.05, -24.5);
    drawLines(-3.05, -15.11, -3.05, -24.75);
    drawLines(4.19, -15.34, 4.19, -24.62);
    drawLines(11.41, -15.49, 11.41, -24.95);
    drawLines(20, -15.32, 20, -25);
    drawLines(27.8, -15.46, 27.8, -26.37);
    drawLines(34.88, -15.38, 34.88, -26.22);
    drawLines(43.09, -15.94, 43.09, -26.5);
    drawLines(49.88, -16.05, 49.88, -26.05);
    drawLines(58.42, -15.71, 58.42, -26.69);
    drawLines(66.95, -15.83, 66.95, -27.16);
    drawLines(75.77, -15.89, 75.77, -26.59);

    //bridge er base
    glColor3ub(61, 23, 3);
    drawRectangle(-37.74, -23.73, -37.84, -26.84, 90.68, -29.78, 90.52, -26.97);

    glColor3ub(122, 122, 122);
    drawRectangle(62.82, -28.96, 62.82, -37.84, 73.62, -38.51, 85.01, -29.65);
    drawRectangle(-45.91, -26.24, -45.96, -34.08, -26.85, -38.56, -26.95, -27.09);
    glColor3ub(65, 61, 62);
    drawRectangle(-26.95, -27.09, -26.85, -38.56, -8.79, -34.5, -8.95, -27.5);
}

/*------------------------------------- Stones -------------------------------------------------*/
void drawStones() // O241
{
    glColor3ub(70, 58, 63);
    drawOctagon(69.57, -37.97, 71.98, -39.02, 72.97, -41.36, 72.93, -43, 71.97, -43.33, 71.21, -43.83, 68.32, -43.67, 65.97, -43.12);
    drawOctagon(65.97, -43.12, 62.91, -42.83, 59.17, -42.55, 58.95, -41.16, 60.19, -39.14, 62.82, -37.84, 67.16, -37.8, 65.97, -43.12);
    drawTriangle(67.16, -37.8, 65.97, -43.12, 69.57, -37.97);

    glColor3ub(179, 174, 173);
    drawOctagon(65.97, -43.12, 68.32, -43.67, 71.21, -43.83, 72.55, -45.47, 72.68, -47.44, 71.13, -50, 70.05, -50.22, 66.06, -51.04);
    drawRectangle(66.06, -51.04, 59.35, -44.3, 62.91, -42.83, 65.97, -43.12);
    drawOctagon(59.35, -44.3, 66.06, -51.04, 63.42, -50.86, 60.1, -50.62, 58, -50, 56.96, -48.18, 57.7, -46.51, 59.35, -44.3);

    glColor3ub(122, 122, 122);
    drawOctagon(66.06, -51.04, 70.05, -50.22, 72.93, -50.46, 75.03, -53.41, 72.26, -58.11, 67.53, -58.83, 64, -58, 62.85, -57.26);
    drawPentagon(62.85, -57.26, 61.73, -54.73, 61.88, -52.82, 63.42, -50.86, 66.06, -51.04);

    glColor3ub(179, 174, 173);
    drawOctagon(72.26, -58.11, 75.26, -53, 76.98, -51.75, 78.67, -52.15, 80.52, -53, 81.92, -55.4, 82.17, -57.76, 80, -60);
    drawPentagon(72.26, -58.11, 80, -60, 78.17, -60.46, 75.31, -60.76, 72.51, -60.56);

    glColor3ub(122, 122, 122);
    drawOctagon(82.17, -57.76, 85.21, -56.82, 90, -58, 92.53, -59.52, 90.23, -65.87, 88.46, -66.01, 84.35, -66.14, 80.84, -66.04);
    drawPentagon(80.84, -66.04, 77.77, -65.42, 76.84, -63.15, 80, -60, 82.17, -57.76);
}

/*------------------------------------- Roads -------------------------------------------------*/
void drawRoads() // O242
{
    glColor3ub(231, 188, 102);
    drawOctagon(106.4, -6.35, 115.33, -6.86, 113.54, -9.68, 111.25, -13.07, 113.54, -16.33, 96.53, -15.27, 98.01, -11.08, 102.61, -8.45);
    drawHexagon(96.53, -15.27, 95.63, -19.78, 97.59, -23.76, 105.09, -30.68, 112.42, -34.44, 113.54, -16.33);
    drawTriangle(113.54, -16.33, 174.25, -18.34, 112.42, -34.44);
    drawOctagon(174.25, -18.34, 181.91, -17.39, 193.39, -11.26, 200, -32.02, 195.02, -34.68, 176.39, -37.05, 146.78, -36.91, 112.42, -34.44);
    drawRectangle(200, -32.02, 193.39, -11.26, 192.82, -8.2, 200, -1.12);
    drawRectangle(95.63, -19.78, 102.05, -27.34, 75.77, -26.59, 84.63, -19.7);
    drawPentagon(95.63, -19.78, 96.53, -15.27, 95.43, -18.01, 94.04, -19.09, 84.63, -19.7);

    glColor3ub(243, 222, 170);
    drawOctagon(159.83, 6.21, 178.46, 4.43, 187.84, 2.51, 200, -1.12, 192.82, -8.2, 181.72, -3.7, 159.7, 2.23, 159.83, 6.21);

    drawRectangle(-20.84, 12.8, -16.82, 8.43, 99.81, 5.72, 98.61, 11.76);

    drawOctagon(-2.53, 21.33, -4.26, 20.26, -6.82, 18, -7.77, 16.81, -6.58, 15.02, -1.7, 16.93, -1.46, 19.19, 0.92, 21.04);
    drawHexagon(-6.58, 15.02, 0.21, 12.83, 18.6, 12.85, 12.41, 13.83, 3.54, 15.02, -1.7, 16.93);

    drawOctagon(58.05, 28.09, 60.43, 25.86, 61.59, 24.21, 61.41, 22.23, 64.78, 21.04, 64.78, 24.21, 63.6, 26, 60.82, 28.04);
    drawOctagon(61.41, 22.23, 64.78, 21.04, 60.27, 18.35, 51.61, 15.19, 44.74, 11.3, 32.05, 12.73, 55, 20, 61.41, 22.23);
}

/*------------------------------------- Flood -------------------------------------------------*/
float waterLevel = -220.0f;
float waveOffset = 0.0f;
void drawFlood() // O243
{
    glBegin(GL_QUAD_STRIP);
    for (float x = -200.0f; x <= 200.0f; x += 5.0f)
    {
        float waveHeight = 2.0f * sin(0.1 * x + waveOffset); 

        if (day) glColor3ub(30, 144, 255); 
        else glColor3ub(0, 0, 139); 
        glVertex2f(x, waterLevel + waveHeight);

        if (day) glColor3ub(0, 0, 139); 
        else glColor3ub(0, 0, 4);
        glVertex2f(x, -200.0f); 
    }
    glEnd();
}

void updateFlood(int value) // A210
{
    if (flood && rain && waterLevel < 44.14f)
        waterLevel += 0.5f;
    else if (!flood && waterLevel > -220.0f)
        waterLevel -= 0.5f;

    if (waterLevel <= -220.0f)
        waterLevel = -220.0f;
    if (waterLevel >= 44.14f)
        waterLevel = 44.14f; 

    waveOffset += 0.4f; // Keeps waves moving
    glutPostRedisplay();
    glutTimerFunc(25, updateFlood, 0); // A210
}

/*------------------------------------- Keyboard and Mouse Functions -------------------------------------------------*/
void keyboard(unsigned char key, int x, int y)
{
    if (key == 'n' || key == 'N') 
    {
        if (day) 
        {
            day = false;
            sunMoonMoving = true;
            moonX = 400.0; 
            glutTimerFunc(16, updateSunMoon, 0); // A201
        }
    }

    else if (key == 'd' || key == 'D') 
    {
        if (!day) 
        {
            day = true;
            sunMoonMoving = true;
            sunX = 400.0; 
            glutTimerFunc(16, updateSunMoon, 0); // A201
        }
    }

    else if (key == 'r' || key == 'R')
    {
        rain = !rain;
        hasRained = !hasRained;
    }
    
    else if ((key == 'f' || key == 'F') )
    {
        if (hasRained) flood = true;
        else flood = false;
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        lantern = !lantern;
    glutPostRedisplay();
}

void scenery()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawSky(); //O201
    if (!day) drawStars(); // O229
    drawSun(); //O203
    drawMoon(); //O204
    drawCloud1(); // O224
    drawCloud2(); // O225
    drawCloud3(); // O226
    drawCloud4(); // O227
    drawCloud5(); // O228
    drawField(); //O202

    if (rain)
        if (!lightningBranches.empty())
            drawLightningFlash(); // O239

    drawMountain5(); // O219
    drawMountain4(); // O218
    drawMountain3(); // O217
    drawMountain2(); // O216
    drawMountain1(); // O215

    drawWindMill(); // O212
    drawRiver(); // O214
    drawStones(); // O241
    drawBridge(); // O240

    drawRoads(); // O242

    drawCoconutTree1(); // O234
    drawCoconutTree3(); // O236
    drawCoconutTree4(); // O237

    drawHut1(); // O206
    drawHut2(); // O207
    drawHut3(); // O208
    drawHut4(); // O209
    drawHut5(); // O210
    drawHut6(); // O211

    drawCoconutTree2(); // O235

    drawTree1(); // O230
    drawTree2(); // O231
    drawTree3(); // O232
    drawTree4(); // O233

    drawBoat4(); // O223
    drawBoat2(); // O221
    drawBoat3(); // O222
    drawBoat1(); // O220
    
    if (!day && !rain) drawFireflies(); // O238

    if (rain) drawRain(); // O205
    drawFlood(); // O243

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rainy Season in Rural Area");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200.0, 200.0, -200.0, 200.0);

    initializeRain();
    initializeStars(); 
    initializeFireflies(); 

    glutDisplayFunc(scenery);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(50, updateFireflies, 0); // A208
    glutTimerFunc(50, updateRain, 0); // A202
    glutTimerFunc(70, updateBoatType1, 0); // A205
    glutTimerFunc(30, updateBoatType2, 0); // A206
    glutTimerFunc(40, updateWindMill, 0); //A203
    glutTimerFunc(100, updateClouds, 0); // A207
    glutTimerFunc(100, updateLightningFlash, 0); // A209
    glutTimerFunc(16, updateRipples, 0); // A204
    glutTimerFunc(25, updateFlood, 0); // A210

    glutMainLoop();
    return 0;
}