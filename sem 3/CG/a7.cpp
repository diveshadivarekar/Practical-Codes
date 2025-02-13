#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <iostream.h>
using namespace std;

// Function to draw the Koch curve recursively
void kochCurve(int x1, int y1, int x2, int y2, int iterations) {
    // Base case: If the recursion depth reaches 0, draw a line
    if (iterations == 0) {
        line(x1, y1, x2, y2);
    } else {
        // Calculate the points required for dividing the line into segments
        int x3 = (2 * x1 + x2) / 3;
        int y3 = (2 * y1 + y2) / 3;
        int x4 = (x1 + 2 * x2) / 3;
        int y4 = (y1 + 2 * y2) / 3;

        // Calculate the peak of the equilateral triangle (rotated 60 degrees)
        int x = x3 + (x4 - x3) * cos(M_PI / 3) - (y4 - y3) * sin(M_PI / 3);
        int y = y3 + (x4 - x3) * sin(M_PI / 3) + (y4 - y3) * cos(M_PI / 3);

        // Recursively draw the four parts of the Koch curve
        kochCurve(x1, y1, x3, y3, iterations - 1);
        kochCurve(x3, y3, x, y, iterations - 1);
        kochCurve(x, y, x4, y4, iterations - 1);
        kochCurve(x4, y4, x2, y2, iterations - 1);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int x1 = 150, y1 = 300;
    int x2 = 450, y2 = 300;

    int iterations = 4; // Number of iterations (recursion depth)

    // Draw the Koch curve with the specified number of iterations
    kochCurve(x1, y1, x2, y2, iterations);

    getch();
    closegraph();
    return 0;
}
