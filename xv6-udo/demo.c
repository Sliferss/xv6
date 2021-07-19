#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    printf(1, "Hello, world!\n");
    setvideomode(0x13);
    drawPixel(10, 10, 4);
    drawLine(20, 20, 35, 35, 8);
    printf(1, "Hello, world!\n");
    getch();
    setvideomode(0x12);
    printf(1, "Hello, world in 12h!\n");
    drawLine(20, 2, 70, 90, 8);
    getch();
    setvideomode(0x03);
    exit();
}