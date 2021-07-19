#include "graphicscall.h"
#include "types.h"
#include "user.h"

int main()
{
    printf(1, "before batch process\n");
    beginBatch(); //initiate batch process
    drawPixelBatched(100, 100, 5);
    for (int i = 0; i < 16; i++)
    {
    drawLineBatched(0, i * 10, 639, 479 - (i * 10), i);
    drawLineBatched(639, i * 10, 0, 479 - (i * 10), i);
    }
    drawCircleBatched(50, 50, 10, 4);
    drawCircleBatched(100, 150, 100, 9);
    drawCircleBatched(100, 150, 80, 8);
    drawCircleBatched(100, 150, 70, 7);
    drawCircleBatched(100, 150, 60, 6);
    fillRectBatched(10, 90, 25, 25, 5);
    drawTriangleBatched(100, 150, 100, 9);
    drawTriangleBatched(100, 150, 80, 8);
    drawTriangleBatched(100, 150, 70, 7);
    drawTriangleBatched(100, 150, 60, 6);
    drawPentagonBatched(300, 150, 100, 9);
    drawPentagonBatched(300, 150, 80, 8);
    drawPentagonBatched(300, 150, 70, 7);
    drawPentagonBatched(300, 150, 60, 6);
    drawCircleBatched(300, 150, 100, 9);
    drawCircleBatched(300, 150, 80, 8);
    drawCircleBatched(300, 150, 70, 7);
    drawCircleBatched(300, 150, 60, 6);
    fillCircleBatched(100, 350, 30, 4);
    fillPentagonBatched(300, 350, 30, 4);
    executeBatch(); //execute batch process, does printf to test snapshot updating and switch back to text mode after with getch pause
    printf(1, "after batch process\n");
    exit();
}