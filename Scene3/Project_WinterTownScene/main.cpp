#include <GL/glut.h>
#include <cmath>

void init()
{
    glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200.0, 200.0, -200.0, 200.0);
}
void drawCircle(GLfloat centerX, GLfloat centerY, GLfloat radius, GLint segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // Center of the circle
    for (int i = 0; i <= segments; i++) {
        GLfloat angle = 2.0f * 3.14159f * i / segments; // Calculate the angle
        GLfloat x = centerX + cos(angle) * radius;      // X coordinate
        GLfloat y = centerY + sin(angle) * radius;      // Y coordinate
        glVertex2f(x, y);
    }
    glEnd();
}
void drawSun() {
    GLfloat centerX = 42.0f;
    GLfloat centerY = 160.0f;
    GLfloat radius = 20.0f;


    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 255, 0);
    glVertex2f(centerX, centerY);
    for (int angle = 0; angle <= 360; angle++) {
        GLfloat rad = angle * 3.14159f / 180.0f;
        GLfloat x = centerX + cos(rad) * radius;
        GLfloat y = centerY + sin(rad) * radius;
        glVertex2f(x, y);
    }
    glEnd();

    glColor3ub(255, 255, 0);
    for (int i = 0; i < 360; i += 30) {
        GLfloat rad = i * 3.14159f / 180.0f;
        GLfloat xStart = centerX + cos(rad) * radius;
        GLfloat yStart = centerY + sin(rad) * radius;
        GLfloat xEnd = centerX + cos(rad) * (radius + 15);
        GLfloat yEnd = centerY + sin(rad) * (radius + 15);

        glBegin(GL_LINES);
        glVertex2f(xStart, yStart);
        glVertex2f(xEnd, yEnd);
        glEnd();
    }
}
void Bigtree()
{
    glBegin(GL_TRIANGLES);

    // Top point of the tree
    GLfloat topX = 5.33397f;
    GLfloat topY = 92.24686f;

    glColor3ub(51, 102, 153); // Deepest icy blue
    glVertex2f(topX, topY - 75.0f);
    glVertex2f(-30.0f, -40.0f);
    glVertex2f(45.0f, -40.0f);

    glColor3ub(77, 128, 179); // Dark icy blue
    glVertex2f(topX, topY - 60.0f);
    glVertex2f(-30.0f, -15.0f);
    glVertex2f(41.0f, -15.0f);

    glColor3ub(102, 153, 204); // Deeper icy blue
    glVertex2f(topX, topY - 45.0f);
    glVertex2f(-23.0f, 11.0f);
    glVertex2f(35.0f, 11.0f);

    glColor3ub(128, 179, 230); // Moderate icy blue
    glVertex2f(topX, topY - 30.0f);
    glVertex2f(-17.0f, 35.0f);
    glVertex2f(30.0f, 35.0f);

    glColor3ub(153, 204, 255); // Slightly darker icy blue
    glVertex2f(topX, topY - 15.0f);
    glVertex2f(-10.0f, 50.0f);
    glVertex2f(22.0f, 50.0f);

    // Draw six overlapping triangles for a big tree
    glColor3ub(179, 229, 255); // Light icy blue
    glVertex2f(topX, topY);
    glVertex2f(-2.31f, 69.0f);
    glVertex2f(15.0f, 69.0f);

    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(-0.5f, -37.0f);
    glVertex2f(13.5f, -37.0f);
    glVertex2f(13.5f, -73.0f);
    glVertex2f(-0.5f, -73.0f);
    glEnd();

}

void smallTree1() {
    glBegin(GL_TRIANGLES);

    // Top point of the tree
    GLfloat topX = -77.0f;
    GLfloat topY = -48.0f;

      glColor3ub(179, 229, 255);
    glVertex2f(topX, topY - 20);
    glVertex2f(-85.0f, -68.0f);
    glVertex2f(-68.0f, -68.0f);

      glColor3ub(153, 204, 255);
    glVertex2f(topX, topY -25);
    glVertex2f(-88.0f, -80.0f);
    glVertex2f(-65.0f, -80.0f);

    glColor3ub(128, 179, 230);
    glVertex2f(topX, topY -30);
    glVertex2f(-93.0f, -90.0f);
    glVertex2f(-61.0f, -90.0f);


    glColor3ub(102, 153, 204);
    glVertex2f(topX, topY -35);
    glVertex2f(-93.0f, -98.0f);
    glVertex2f(-58.0f, -100.0f);



      glColor3ub(77, 128, 179);
    glVertex2f(topX, topY - 40);
    glVertex2f(-95.0f, -108.0f);
    glVertex2f(-57.0f, -108.0f);

    glEnd();

    // Draw the tree trunk
    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(-72.0f, -108.0f);
    glVertex2f(-82.0f, -108.0f);
    glVertex2f(-82.0f, -120.0f);
    glVertex2f(-72.0f, -120.0f);
    glEnd();
}
void smallTree2() {
    glBegin(GL_TRIANGLES);

    // Top point of the tree
    GLfloat topX = -77-70;
    GLfloat topY = -48+18;

      glColor3ub(179, 229, 255);
    glVertex2f(topX, topY - 20);
    glVertex2f(-85-70, -68+18);
    glVertex2f(-68-70, -68+18);

      glColor3ub(153, 204, 255);
    glVertex2f(topX, topY -25);
    glVertex2f(-88-70, -80+18);
    glVertex2f(-65-70, -80+18);

    glColor3ub(128, 179, 230);
    glVertex2f(topX, topY -30);
    glVertex2f(-93-70, -90+18);
    glVertex2f(-61-70, -90+18);


    glColor3ub(102, 153, 204);
    glVertex2f(topX, topY -35);
    glVertex2f(-93-70, -98+18);
    glVertex2f(-58-70, -100+18);



      glColor3ub(77, 128, 179);
    glVertex2f(topX, topY - 40);
    glVertex2f(-95-70, -108+18);
    glVertex2f(-57-70, -108+18);

    glEnd();

    // Draw the tree trunk
    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(-72-70, -108+18);
    glVertex2f(-82-70, -108+18);
    glVertex2f(-82-70, -120+18);
    glVertex2f(-72-70, -120+18);
    glEnd();
}
void smallTree3() {
    glBegin(GL_TRIANGLES);

    // Top point of the tree
    GLfloat topX = -77+235;
    GLfloat topY = -48-82;

      glColor3ub(179, 229, 255);
    glVertex2f(topX, topY - 20);
    glVertex2f(-85+235, -68-82);
    glVertex2f(-68+235, -68-82);

      glColor3ub(153, 204, 255);
    glVertex2f(topX, topY -25);
    glVertex2f(-88+235, -80-82);
    glVertex2f(-65+235, -80-82);

    glColor3ub(128, 179, 230);
    glVertex2f(topX, topY -30);
    glVertex2f(-93+235, -90-82);
    glVertex2f(-61+235, -90-82);


    glColor3ub(102, 153, 204);
    glVertex2f(topX, topY -35);
    glVertex2f(-93+235, -98-82);
    glVertex2f(-58+235, -100-82);



      glColor3ub(77, 128, 179);
    glVertex2f(topX, topY - 40);
    glVertex2f(-95+235, -108-82);
    glVertex2f(-57+235, -108-82);

    glEnd();

    // Draw the tree trunk
    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(-72+235, -108-82);
    glVertex2f(-82+235, -108-82);
    glVertex2f(-82+235, -120-82);
    glVertex2f(-72+235, -120-82);
    glEnd();
}
void drawTrainRoad()
{
    glColor3f(0.66f, 0.66f, 0.66f); // RGB equivalent of gray
    glBegin(GL_LINES);

    glVertex2f(-201, 110);
    glVertex2f(201, 110);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.66f, 0.66f, 0.66f);
    glVertex2f(-201, 80);
    glVertex2f(201, 80);
    glVertex2f(200, 90);
    glVertex2f(-201, 90);


    glEnd();
    glFlush();
}

void Building1()
{
    //body1
    glBegin(GL_QUADS);
    glColor3ub(220.0f, 220.0f, 220.0f);
    glVertex2f(80, 140+15);
    glVertex2f(134, 143+15);
    glVertex2f(134, 93+15);
    glVertex2f(81, 95+15);
    glEnd();
    //windowforbody1
    //window1
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(86, 133+15);
    glVertex2f(92, 133+15);
    glVertex2f(92, 118+15);
    glVertex2f(86, 118+15);
    glEnd();
    //window2
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(86+10, 133+15);
    glVertex2f(92+10, 133+15);
    glVertex2f(92+10, 118+15);
    glVertex2f(86+10, 118+15);
    glEnd();
    //window3
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(86+20, 133+15);
    glVertex2f(92+20, 133+15);
    glVertex2f(92+20, 118+15);
    glVertex2f(86+20, 118+15);
    glEnd();
    //window4
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(86+30, 133+15);
    glVertex2f(92+30, 133+15);
    glVertex2f(92+30, 118+15);
    glVertex2f(86+30, 118+15);
    glEnd();
    //window5
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(86, 133-8);
    glVertex2f(92, 133-8);
    glVertex2f(92, 118-8);
    glVertex2f(86, 118-8);
    glEnd();
    //window6
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(86+10, 133-8);
    glVertex2f(92+10, 133-8);
    glVertex2f(92+10, 118-8);
    glVertex2f(86+10, 118-8);
    glEnd();
    //window7
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(86+20, 133-8);
    glVertex2f(92+20, 133-8);
    glVertex2f(92+20, 118-8);
    glVertex2f(86+20, 118-8);
    glEnd();
    //window8
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(86+30, 133-8);
    glVertex2f(92+30, 133-8);
    glVertex2f(92+30, 118-8);
    glVertex2f(86+30, 118-8);
    glEnd();

    //body2
    glBegin(GL_QUADS);
    glColor3ub(240.0f, 240.0f, 240.0f);
    glVertex2f(134, 143+15);
    glVertex2f(172, 142+15);
    glVertex2f(171, 95+15);
    glVertex2f(134, 93+15);
    glEnd();

    //windowforbody2
    //window1
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(140, 133-8);
    glVertex2f(144, 133-8);
    glVertex2f(144, 118-8);
    glVertex2f(140, 118-8);
    glEnd();
    //window2
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(140+10, 133-8);
    glVertex2f(144+10, 133-8);
    glVertex2f(144+10, 118-8);
    glVertex2f(140+10, 118-8);
    glEnd();
    //window3
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(140+20, 133-8);
    glVertex2f(144+20, 133-8);
    glVertex2f(144+20, 118-8);
    glVertex2f(140+20, 118-8);
    glEnd();
    //window4
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(140, 133+15);
    glVertex2f(144, 133+15);
    glVertex2f(144, 118+15);
    glVertex2f(140, 118+15);
    glEnd();
    //window2
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(140+10, 133+15);
    glVertex2f(144+10, 133+15);
    glVertex2f(144+10, 118+15);
    glVertex2f(140+10, 118+15);
    glEnd();
    //window3
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(140+20, 133+15);
    glVertex2f(144+20, 133+15);
    glVertex2f(144+20, 118+15);
    glVertex2f(140+20, 118+15);
    glEnd();
    glFlush();
}

void Building2(){

  //Top1
   glBegin(GL_QUADS);
    glColor3ub(255.0f, 255.0f, 255.0f);
    glVertex2f(68, 53);
    glVertex2f(154, 53);
    glVertex2f(154, 47);
    glVertex2f(68, 47);
    glEnd();
      //Top2
   glBegin(GL_QUADS);
    glColor3ub(255.0f, 255.0f, 255.0f);
    glVertex2f(154, 53);
    glVertex2f(154, 47);
    glVertex2f(199, 45);
    glVertex2f(199, 52);
    glEnd();

     //body1
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 22.0f, 22.0f);
   glVertex2f(68, 47);
    glVertex2f(154, 47);
    glVertex2f(154, -30);
    glVertex2f(67, -30);
    glEnd();
    //windowforbody1
    //window1
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76, 38);
    glVertex2f(85, 38);
    glVertex2f(85, 24);
    glVertex2f(76, 24);
    glEnd();
    //window2
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76+15, 38);
    glVertex2f(85+15, 38);
    glVertex2f(85+15, 24);
    glVertex2f(76+15, 24);
    glEnd();
    //window3
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76+30, 38);
    glVertex2f(85+30, 38);
    glVertex2f(85+30, 24);
    glVertex2f(76+30, 24);
    glEnd();
     //window4
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76+45, 38);
    glVertex2f(85+45, 38);
    glVertex2f(85+45, 24);
    glVertex2f(76+45, 24);
    glEnd();
        //window4=5
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76+60, 38);
    glVertex2f(85+60, 38);
    glVertex2f(85+60, 24);
    glVertex2f(76+60, 24);
    glEnd();
      //window6
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76, 38-20);
    glVertex2f(85, 38-20);
    glVertex2f(85, 24-20);
    glVertex2f(76, 24-20);
    glEnd();
    //window7
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76+15, 38-20);
    glVertex2f(85+15, 38-20);
    glVertex2f(85+15, 24-20);
    glVertex2f(76+15, 24-20);
    glEnd();
    //window8
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76+30, 38-20);
    glVertex2f(85+30, 38-20);
    glVertex2f(85+30, 24-20);
    glVertex2f(76+30, 24-20);
    glEnd();
     //window9
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76+45, 38-20);
    glVertex2f(85+45, 38-20);
    glVertex2f(85+45, 24-20);
    glVertex2f(76+45, 24-20);
    glEnd();
        //window10
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76+60, 38-20);
    glVertex2f(85+60, 38-20);
    glVertex2f(85+60, 24-20);
    glVertex2f(76+60, 24-20);
    glEnd();
        //window11
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76+60, 38-40);
    glVertex2f(85+60, 38-40);
    glVertex2f(85+60, 24-40);
    glVertex2f(76+60, 24-40);
    glEnd();
      //window6
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76, 38-40);
    glVertex2f(85, 38-40);
    glVertex2f(85, 24-40);
    glVertex2f(76, 24-40);
    glEnd();
    //window7
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76+15, 38-40);
    glVertex2f(85+15, 38-40);
    glVertex2f(85+15, 24-40);
    glVertex2f(76+15, 24-40);
    glEnd();
    //window8
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76+30, 38-40);
    glVertex2f(85+30, 38-40);
    glVertex2f(85+30, 24-40);
    glVertex2f(76+30, 24-40);
    glEnd();
     //window9
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76+45, 38-40);
    glVertex2f(85+45, 38-40);
    glVertex2f(85+45, 24-40);
    glVertex2f(76+45, 24-40);
    glEnd();
        //window10
    glBegin(GL_QUADS);
    glColor3ub(40.0f, 40.0f, 40.0f);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(76+60, 38-40);
    glVertex2f(85+60, 38-40);
    glVertex2f(85+60, 24-40);
    glVertex2f(76+60, 24-40);
    glEnd();

    //body2
    glBegin(GL_QUADS);
   glColor3ub(150.0f, 150.0f, 150.0f);
      glVertex2f(154, 47);
    glVertex2f(199, 45);
    glVertex2f(202, -26);
    glVertex2f(154, -30);
    glEnd();

    //windowforbody2
    //window1
    glBegin(GL_QUADS);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(140, 133-8);
    glVertex2f(144, 133-8);
    glVertex2f(144, 118-8);
    glVertex2f(140, 118-8);
    glEnd();

    glFlush();

    //down1
     glBegin(GL_QUADS);
   glColor3ub(0.0f, 0.0f, 0.0f);
    glVertex2f(67, -30);
    glVertex2f(68, -24);
    glVertex2f(154, -30);
    glVertex2f(155, -38);
    glEnd();
     //down2
     glBegin(GL_QUADS);
   glColor3ub(0.0f, 0.0f, 0.0f);
    glVertex2f(154, -30);
    glVertex2f(154, -38);
    glVertex2f(201, -33);
    glVertex2f(201, -26);
    glEnd();
}

void Building3(){

    //bodyone
  glBegin(GL_POLYGON);
    glColor3ub(150, 16, 16 );
    glVertex2f(-157.47993,-1.84999);
    glVertex2f(-123.88842,32.27472);
    glVertex2f(-92.42971,1.3492);
    glVertex2f(-72.16816,2.9488);
      glVertex2f(-68.97595,-40.06488);
      glVertex2f(-157.32255,-54.80844);
    glEnd();

    //body2
    glBegin(GL_POLYGON);
    glColor3ub(150, 16, 16 );
    glVertex2f(-157.32255,-54.80844);
    glVertex2f(-157.47993,-1.84999);
    glVertex2f(-185.36237,33.11448);
    glVertex2f(-205.59467,8.54668);
      glVertex2f(-202.70435,-50.22336);
    glEnd();

      //body1line
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(-157.47993,-1.84999);
    glVertex2f(-123.88842,32.27472);
    glVertex2f(-92.42971,1.3492);
    glVertex2f(-72.16816,2.9488);
      glVertex2f(-68.97595,-40.06488);
      glVertex2f(-157.32255,-54.80844);
    glEnd();

    //body2line
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 );
    glVertex2f(-157.32255,-54.80844);
    glVertex2f(-157.47993,-1.84999);
    glVertex2f(-185.36237,33.11448);
    glVertex2f(-205.59467,8.54668);
    glVertex2f(-202.70435,-50.22336);
    glEnd();

    //top
     glBegin(GL_POLYGON);
    glColor3ub(245, 250, 255 );
    glVertex2f(-184.88065,35.85858);
    glVertex2f(-93.35354,40.3403);
    glVertex2f(-70.2309,4.6929);
    glVertex2f(-92.42971,1.3492);
      glVertex2f(-123.88842,32.27472);
       glVertex2f(-157.47993,-1.84999);
    glEnd();
    //topline
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0, 0 );
    glVertex2f(-184.88065,35.85858);
    glVertex2f(-93.35354,40.3403);
    glVertex2f(-70.2309,4.6929);
    glVertex2f(-92.42971,1.3492);
      glVertex2f(-123.88842,32.27472);
       glVertex2f(-157.47993,-1.84999);
    glEnd();

    glColor3ub(0,0, 0 );
    drawCircle(-125.62889,11.91873,5,200);

   //DOORLine

    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0, 0 );
    glVertex2f(-128.0375,-7.35014);
    glVertex2f(-108.76863,-7.35014);
    glVertex2f(-108.76863,-41.55237);
    glVertex2f(-128.06438,-46.36959);

    glEnd();
    //Door
     glBegin(GL_POLYGON);
    glColor3ub(235,235, 235 );
    glVertex2f(-128.0375,-7.35014);
    glVertex2f(-108.76863,-7.35014);
    glVertex2f(-108.76863,-41.55237);
    glVertex2f(-128.06438,-46.36959);

    glEnd();

    //Window1
     glBegin(GL_POLYGON);
    glColor3ub(200,200, 200);
    glVertex2f(-149,-20);
    glVertex2f(-140,-20);
    glVertex2f(-140,-34);
    glVertex2f(-149,-34);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0, 0);
    glVertex2f(-149,-20);
    glVertex2f(-140,-20);
    glVertex2f(-140,-34);
    glVertex2f(-149,-34);
    glEnd();
    //window2
    glBegin(GL_POLYGON);
    glColor3ub(200,200, 200);
    glVertex2f(-149+55,-20+5);
    glVertex2f(-140+55,-20+5);
    glVertex2f(-140+55,-34+5);
    glVertex2f(-149+55,-34+5);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0, 0);
    glVertex2f(-149+55,-20+5);
    glVertex2f(-140+55,-20+5);
    glVertex2f(-140+55,-34+5);
    glVertex2f(-149+55,-34+5);
    glEnd();
    //window3
    glBegin(GL_POLYGON);
    glColor3ub(200,200, 200);
    glVertex2f(-192.70752,-8.6697);
    glVertex2f(-174.56096,-8.6697);
    glVertex2f(-174.56096,-25.74881);
    glVertex2f(-193.06333,-25.92672);
    glEnd();
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0, 0);
  glVertex2f(-192.70752,-8.6697);
    glVertex2f(-174.56096,-8.6697);
    glVertex2f(-174.56096,-25.74881);
    glVertex2f(-193.06333,-25.92672);
    glEnd();
   //topPipe
    glBegin(GL_POLYGON);
   glColor3ub(150, 16, 16 );
  glVertex2f(-155.42449,52.27393);
    glVertex2f(-142.18791,52.56168);
    glVertex2f(-141.61241,38.35363);
    glVertex2f(-156.57549,38.35363);
    glEnd();

        glBegin(GL_LINE_LOOP);
    glColor3ub(0,0, 0);
  glVertex2f(-155.42449,52.27393);
    glVertex2f(-142.18791,52.56168);
    glVertex2f(-141.61241,38.35363);
    glVertex2f(-156.57549,38.35363);
    glEnd();



  glColor3ub(0,0, 0 );
drawCircle(-181.99032,11.91873,5,200);



}



float xOffset = 0.0f;


void drawMovingTrain(){

    glPushMatrix();
    glTranslatef(xOffset, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(150.0f, 150.0f, 150.0f);
    glVertex2f(-106 + xOffset, 123);
    glVertex2f(-1.8 + xOffset, 123);
    glVertex2f(4 + xOffset, 97);
    glVertex2f(-109 + xOffset, 97);
    glEnd();
    glPopMatrix();


    xOffset += 1.0f;


    if (xOffset > 200)
    {
        xOffset = -200.0f; // Reset to left side
    }
}

void timerforTrain(int value) {
    glutPostRedisplay();  // Trigger a redraw of the screen
    glutTimerFunc(10, timerforTrain, 0);  // Call the timer function again after 10ms
}

void road1(){

    glBegin(GL_QUADS);
    glColor3ub(0.0f, 0.0f, 0.0f);
    glVertex2f(-201, -109);
    glVertex2f(-78, -152);
    glVertex2f(-142, -174);
    glVertex2f(-201, -150);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255.0f, 255.0f, 255.0f);
    glVertex2f(-201, -132);
    glVertex2f(-111, -168);
    glEnd();
}
void road2(){

    glBegin(GL_QUADS);
    glColor3ub(0.0f, 0.0f, 0.0f);
    glVertex2f(-178, -186);
    glVertex2f(-6, -185);
    glVertex2f(200, -118);
    glVertex2f(201, -60);
    glEnd();
     glBegin(GL_LINES);
    glColor3ub(255.0f, 255.0f, 255.0f);
    glVertex2f(-87, -188);
    glVertex2f(200, -90);
    glEnd();
}

void road3(){

    glBegin(GL_QUADS);
    glColor3ub(0.0f, 0.0f, 0.0f);
    glVertex2f(148, -86);
    glVertex2f(185, -69);
    glVertex2f(-201, 15);
    glVertex2f(-200, 0);
    glEnd();
     glBegin(GL_LINES);
    glColor3ub(255.0f, 255.0f, 255.0f);
    glVertex2f(165, -78);
    glVertex2f(-200, 6);
    glEnd();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawSun();
    road1();
    road2();
    road3();
    Building3();
    Building1();
    Building2();
    drawTrainRoad();
    Bigtree();
    smallTree1();
    smallTree2();
    smallTree3();
    drawMovingTrain();  // Draw the moving rectangle

    glutSwapBuffers();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Winter Tree Scene");
    init();
    glutDisplayFunc(display);
     glutTimerFunc(10, timerforTrain, 0);
    glutMainLoop();
    return 0;
}

