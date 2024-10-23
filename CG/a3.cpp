#include <graphics.h>
#include <conio.h>
#include <iostream.h>
using namespace std;

struct Edge {
    int ymin, ymax, x, dx, dy, sign;
    float slope;
};

void scanFill(int x[], int y[], int n) {
    int i, j, k;
    int ymin = y[0], ymax = y[0];

    // Finding minimum and maximum y-values (scan line range)
    for (i = 1; i < n; i++) {
        if (y[i] < ymin)
            ymin = y[i];
        if (y[i] > ymax)
            ymax = y[i];
    }

    // Scan through each line between ymin and ymax
    for (int yi = ymin; yi <= ymax; yi++) {
        int x_intersections[10], xi = 0;

        // Find intersections with scan line
        for (i = 0; i < n; i++) {
            int x1 = x[i], y1 = y[i];
            int x2 = x[(i + 1) % n], y2 = y[(i + 1) % n];

            if ((y1 <= yi && y2 > yi) || (y2 <= yi && y1 > yi)) {
                float x_inter = x1 + (yi - y1) * (float)(x2 - x1) / (y2 - y1);
                x_intersections[xi++] = x_inter;
            }
        }

        // Sorting intersections
        for (i = 0; i < xi - 1; i++) {
            for (j = i + 1; j < xi; j++) {
                if (x_intersections[i] > x_intersections[j]) {
                    int temp = x_intersections[i];
                    x_intersections[i] = x_intersections[j];
                    x_intersections[j] = temp;
                }
            }
        }

        // Filling between pairs of intersections
        for (i = 0; i < xi; i += 2) {
            line(x_intersections[i], yi, x_intersections[i + 1], yi);
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int x[] = {150, 250, 300, 200, 100};
    int y[] = {150, 100, 200, 250, 200};
    int n = sizeof(x) / sizeof(x[0]);

    // Draw the polygon
    for (int i = 0; i < n; i++) {
        line(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n]);
    }

    // Fill the polygon using scanline fill algorithm
    setcolor(RED);
    scanFill(x, y, n);

    getch();
    closegraph();
    return 0;
}
