#include <graphics.h>
#include <conio.h>
#include <iostream.h>
using namespace std;

void DDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;
    for (int i = 0; i <= steps; i++) {
        putpixel(x, y, WHITE);
        x += xInc;
        y += yInc;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int x1 = 100, y1 = 100, x2 = 300, y2 = 300;
    DDA(x1, y1, x2, y2);

    getch();
    closegraph();
    return 0;
}
