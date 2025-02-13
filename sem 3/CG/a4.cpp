#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <iostream.h>
using namespace std;

// Function to draw a triangle
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

// Function to draw the incircle of the triangle
void drawIncircle(int x1, int y1, int x2, int y2, int x3, int y3) {
    float a = sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2));
    float b = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
    float c = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

    float p = a + b + c;  // Perimeter
    float s = p / 2;      // Semi-perimeter

    int ix = (a * x1 + b * x2 + c * x3) / p;
    int iy = (a * y1 + b * y2 + c * y3) / p;

    float radius = sqrt((s - a) * (s - b) * (s - c) / s);
    circle(ix, iy, radius);
}

// Function to draw the circumcircle of the triangle
void drawCircumcircle(int x1, int y1, int x2, int y2, int x3, int y3) {
    float d = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));

    int ux = ((pow(x1, 2) + pow(y1, 2)) * (y2 - y3) +
              (pow(x2, 2) + pow(y2, 2)) * (y3 - y1) +
              (pow(x3, 2) + pow(y3, 2)) * (y1 - y2)) /
             d;

    int uy = ((pow(x1, 2) + pow(y1, 2)) * (x3 - x2) +
              (pow(x2, 2) + pow(y2, 2)) * (x1 - x3) +
              (pow(x3, 2) + pow(y3, 2)) * (x2 - x1)) /
             d;

    float r = sqrt(pow(x1 - ux, 2) + pow(y1 - uy, 2));
    circle(ux, uy, r);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Coordinates of the triangle
    int x1 = 150, y1 = 200;
    int x2 = 250, y2 = 100;
    int x3 = 350, y3 = 200;

    // Draw triangle
    drawTriangle(x1, y1, x2, y2, x3, y3);

    // Draw incircle
    drawIncircle(x1, y1, x2, y2, x3, y3);

    // Draw circumcircle
    drawCircumcircle(x1, y1, x2, y2, x3, y3);

    getch();
    closegraph();
    return 0;
}
