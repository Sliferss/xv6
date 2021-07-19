#include "graphicscall.h"
#include "types.h"
#include "user.h"

struct drawParam drawArray[128];
int count;

void beginBatch() //starts batching process by initialising count to 0 so only new graphics calls are executed
{
    setvideomode(0x12); //added setvideomode to save having to manually add it in application, also makes sure that console is in vgamode if forgotton
    count = 0;
}

void executeBatch()
{
    executeGraphicsCall(drawArray, count); //syscall for batched graphicall, uses array as pointer and count to only draw graphics call done in application
    printf(1, "during batch process\n");   //tests snapshot updating during mode 12h
    getch();                               //stops instantly switching graphics mode
    setvideomode(0x03); 
}

//all functions save coords and radius to param array and colour as int and draw type to enum in struct

void drawPixelBatched(int x, int y, int colour)
{
    drawArray[count] = (struct drawParam){.param = {x, y,}, .colour = colour, .type = PIXEL};
    count++;
}

void drawLineBatched(int x0, int y0, int x1, int y1, int colour)
{
    drawArray[count] = (struct drawParam){.param = {x0, y0, x1, y1}, .colour = colour, .type = LINE};
    count++;
}

void drawCircleBatched(int xc, int yc, int r, int colour)
{
    drawArray[count] = (struct drawParam){.param = {xc, yc, r}, .colour = colour, .type = CIRCLE};
    count++;
}

void fillRectBatched(int x, int y, int width, int height, int colour)
{
    drawArray[count] = (struct drawParam){.param = {x, y, width, height}, .colour = colour, .type = FILL_RECT};
    count++;
}

void drawTriangleBatched(int xc, int yc, int r, int colour)
{
drawArray[count] = (struct drawParam){.param = {xc, yc, r}, .colour = colour, .type = TRIANGLE};
count++;
}

void drawPentagonBatched(int xc, int yc, int r, int colour)
{
drawArray[count] = (struct drawParam){.param = {xc, yc, r}, .colour = colour, .type = PENTAGON};
count++;
}

void fillCircleBatched(int xc, int yc, int r, int colour)
{
    drawArray[count] = (struct drawParam){.param = {xc, yc, r}, .colour = colour, .type = FILL_CIRCLE};
    count++;
}

void fillPentagonBatched(int xc, int yc, int r, int colour)
{
    drawArray[count] = (struct drawParam){.param = {xc, yc, r}, .colour = colour, .type = FILL_PENTAGON};
    count++;
}