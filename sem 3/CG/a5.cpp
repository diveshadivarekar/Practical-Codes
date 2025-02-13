#include <graphics.h>
#include <conio.h>
#include <iostream.h>
using namespace std;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Define the clipping window
int x_min, y_min, x_max, y_max;

// Function to compute the region code of a point
int computeCode(int x, int y) {
    int code = INSIDE;

    if (x < x_min)       // to the left of rectangle
        code |= LEFT;
    else if (x > x_max)  // to the right of rectangle
        code |= RIGHT;
    if (y < y_min)       // below the rectangle
        code |= BOTTOM;
    else if (y > y_max)  // above the rectangle
        code |= TOP;

    return code;
}

// Function to implement Cohen-Sutherland line clipping algorithm
void cohenSutherlandClip(int x1, int y1, int x2, int y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // Both points are inside the rectangle
            accept = true;
            break;
        } else if (code1 & code2) {
            // Both points share an outside region, trivially reject
            break;
        } else {
            int code_out;
            int x, y;

            // At least one endpoint is outside the rectangle, pick it
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            // Find intersection point
            if (code_out & TOP) {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            } else if (code_out & BOTTOM) {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            } else if (code_out & RIGHT) {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            } else if (code_out & LEFT) {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            // Replace the point outside the rectangle with intersection point
            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        setcolor(WHITE);
        rectangle(x_min, y_min, x_max, y_max);  // Draw clipping window
        setcolor(GREEN);
        line(x1, y1, x2, y2);                   // Draw the clipped line
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Define the clipping window (rectangle)
    x_min = 100, y_min = 100, x_max = 300, y_max = 300;

    // Original line coordinates
    int x1 = 50, y1 = 50, x2 = 350, y2 = 350;

    // Draw the original line in RED
    setcolor(RED);
    line(x1, y1, x2, y2);

    // Perform Cohen-Sutherland line clipping
    cohenSutherlandClip(x1, y1, x2, y2);

    getch();
    closegraph();
    return 0;
}
