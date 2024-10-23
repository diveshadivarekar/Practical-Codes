#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

// Base class Shape to demonstrate polymorphism
class Shape {
public:
    // Virtual function to be overridden
    virtual void draw() {
        cout << "Drawing Shape" << endl;
    }
};

// Derived class to draw the head of the man
class Head : public Shape {
public:
    void draw() override {
        // Draw the head (a circle)
        glColor3f(1.0, 0.8, 0.6);  // Skin color
        glBegin(GL_POLYGON);
        for (float angle = 0; angle < 2 * M_PI; angle += 0.1) {
            glVertex2f(0.1 * cos(angle), 0.2 + 0.1 * sin(angle));  // Head at (0, 0.2)
        }
        glEnd();
    }
};

// Derived class to draw the body of the man
class Body : public Shape {
public:
    void draw() override {
        // Draw the body
        glColor3f(0.0, 0.0, 1.0);  // Blue color for body
        glBegin(GL_LINES);
        glVertex2f(0, 0.1);    // Neck
        glVertex2f(0, -0.3);   // Body
        glVertex2f(0, 0);      // Arms
        glVertex2f(-0.2, -0.1);
        glVertex2f(0, 0);      // Arms
        glVertex2f(0.2, -0.1);
        glVertex2f(0, -0.3);   // Legs
        glVertex2f(-0.1, -0.5);
        glVertex2f(0, -0.3);   // Legs
        glVertex2f(0.1, -0.5);
        glEnd();
    }
};

// Derived class to draw the umbrella
class Umbrella : public Shape {
public:
    void draw() override {
        // Draw the umbrella
        glColor3f(1.0, 0.0, 0.0);  // Red color for umbrella
        glBegin(GL_TRIANGLES);
        glVertex2f(0, 0.3);   // Peak of the umbrella
        glVertex2f(-0.4, 0.1);
        glVertex2f(0.4, 0.1);
        glEnd();

        // Umbrella handle
        glColor3f(0.0, 0.0, 0.0);  // Black color for handle
        glBegin(GL_LINES);
        glVertex2f(0, 0.1);
        glVertex2f(0, -0.1);
        glEnd();
    }
};

// Derived class to draw the rain
class Rain : public Shape {
public:
    void draw() override {
        glColor3f(0.0, 0.0, 1.0);  // Blue color for rain drops
        glBegin(GL_LINES);
        for (float x = -1.0; x <= 1.0; x += 0.1) {
            glVertex2f(x, 0.9);  // Starting point of rain drop
            glVertex2f(x + 0.05, 0.8);  // End point of rain drop
        }
        glEnd();
    }
};

// Global objects for each component
Head head;
Body body;
Umbrella umbrella;
Rain rain;

float manPosition = -0.9;  // Starting position of the man
bool movingRight = true;   // Direction flag

// Function to draw the entire scene
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw the rain
    rain.draw();

    // Move and draw the man (head, body, and umbrella)
    glPushMatrix();
    glTranslatef(manPosition, -0.5, 0);
    head.draw();
    body.draw();
    umbrella.draw();
    glPopMatrix();

    // Update man position to create walking effect
    if (movingRight) {
        manPosition += 0.01;
        if (manPosition >= 0.9) movingRight = false;  // Switch direction
    } else {
        manPosition -= 0.01;
        if (manPosition <= -0.9) movingRight = true;  // Switch direction
    }

    glutSwapBuffers();
}

// Timer function for animation
void timer(int value) {
    glutPostRedisplay();  // Redraw the scene
    glutTimerFunc(16, timer, 0);  // Roughly 60 FPS
}

// Initialization function
void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Black background
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Set coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Man Walking in Rain with Umbrella - Polymorphism");

    initOpenGL();
    glutDisplayFunc(drawScene);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
