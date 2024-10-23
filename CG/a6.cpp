#include <iostream.h>
#include <graphics.h>
#include <cmath>
using namespace std;

class Point {
public:
    float x, y;

    // Constructor to initialize the point
    Point() {
        x = 0;
        y = 0;
    }

    Point(float x, float y) {
        this->x = x;
        this->y = y;
    }

    // Operator overloading for translation
    Point operator+(const Point& p) {
        Point temp;
        temp.x = this->x + p.x;
        temp.y = this->y + p.y;
        return temp;
    }

    // Operator overloading for scaling
    Point operator*(const Point& scale) {
        Point temp;
        temp.x = this->x * scale.x;
        temp.y = this->y * scale.y;
        return temp;
    }

    // Operator overloading for rotation (angle in degrees)
    Point operator^(float angle) {
        Point temp;
        float radian = angle * M_PI / 180;  // Convert degree to radian
        temp.x = x * cos(radian) - y * sin(radian);
        temp.y = x * sin(radian) + y * cos(radian);
        return temp;
    }
};

// Function to draw a 2D object (Triangle)
void drawObject(Point p1, Point p2, Point p3) {
    line(p1.x, p1.y, p2.x, p2.y);
    line(p2.x, p2.y, p3.x, p3.y);
    line(p3.x, p3.y, p1.x, p1.y);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Initial object points (Triangle)
    Point p1(100, 100), p2(200, 100), p3(150, 50);

    // Draw the original object
    setcolor(WHITE);
    drawObject(p1, p2, p3);
    outtextxy(50, 200, "Original Object");

    // Translation vector
    Point translation(100, 50);

    // Scaling factors
    Point scale(1.5, 1.5);

    // Rotation angle
    float angle = 45;

    // Performing translation
    Point t1 = p1 + translation;
    Point t2 = p2 + translation;
    Point t3 = p3 + translation;
    setcolor(GREEN);
    drawObject(t1, t2, t3);
    outtextxy(50, 220, "Translated Object");

    // Performing scaling
    Point s1 = p1 * scale;
    Point s2 = p2 * scale;
    Point s3 = p3 * scale;
    setcolor(YELLOW);
    drawObject(s1, s2, s3);
    outtextxy(50, 240, "Scaled Object");

    // Performing rotation
    Point r1 = p1 ^ angle;
    Point r2 = p2 ^ angle;
    Point r3 = p3 ^ angle;
    setcolor(RED);
    drawObject(r1, r2, r3);
    outtextxy(50, 260, "Rotated Object");

    getch();
    closegraph();
    return 0;
}
