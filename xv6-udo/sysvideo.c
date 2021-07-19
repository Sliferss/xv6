#include "types.h"
#include "defs.h"
#include "graphicscall.h"

int sys_getch(void) {
    return consoleget();
}

int sys_drawPixel(void)
{
    int x;
    int y;
    int colour; //parameters passed onto variables in order set
    if (argint(0, &x) < 0 || argint(1, &y) < 0 || argint(2, &colour) < 0) //valid parameter check
    {
        return -1;
    }
    return conDrawPixel(x, y, colour); //draw pixel set in console.c at the bottom
}

int abs(int value) //absolute value needed for bresenham draw line algorithm
{
    if (value > 0)
    {
        return value;
    }
    else {
        return value * -1;
    }
}

int sys_drawLine(void)
{
    //bresenham draw line implemented
    int x0;
    int y0;
    int x1;
    int y1;
    int colour;
    //parameters passed onto variables in order set
    if (argint(0, &x0) < 0 || argint(1, &y0) < 0 || argint(2, &x1) < 0 || argint(3, &y1) < 0 || argint(4, &colour) < 0) //valid parameter check
    {
        return -1;
    }
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
    int err = (dx > dy ? dx : -dy) / 2, e2;
 
    for(;;){
        conDrawPixel(x0, y0, colour); //draw pixel
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
    return 0;
}

int sys_setvideomode(void)
{
    int videomode;
    if (argint(0, &videomode) < 0)  //check parameter is acceptable
    {
        return -1;
    }
    consolevgamode(videomode);
    return 0;
}

int sys_executeGraphicsCall(void)
{
    struct drawParam *call;
    int count; //parameters passed onto variables in order set
    if (argptr(0, (void*)&call, sizeof(*call)) < 0 || argint(1, &count) < 0) //valid parameter check
    {
        return -1;
    }

    for (int i = 0; i < count; i++) //loops through pointer to array using paramater count
    {
        //check enum value to determine what graphicscall is needed
        //graphics calls are called in the order they were put in this way
        //functions parameters assigned using struct
        if (call[i].type == PIXEL){
            conDrawPixel(call[i].param[0], call[i].param[1], call[i].colour);
        }
        else if (call[i].type == LINE)
        {
            conDrawLine(call[i].param[0], call[i].param[1], call[i].param[2], call[i].param[3], call[i].colour);
        }
        else if (call[i].type == FILL_RECT)
        {
            conFillRect(call[i].param[0], call[i].param[1], call[i].param[2], call[i].param[3], call[i].colour);
        }
        else if (call[i].type == CIRCLE)
        {
            conDrawCircle(call[i].param[0], call[i].param[1], call[i].param[2], call[i].colour);
        }
        else if (call[i].type == TRIANGLE)
        {
            conDrawTriangle(call[i].param[0], call[i].param[1], call[i].param[2], call[i].colour);
        }
        else if (call[i].type == PENTAGON)
        {
            conDrawPentagon(call[i].param[0], call[i].param[1], call[i].param[2], call[i].colour);
        }
        else if (call[i].type == FILL_CIRCLE)
        {
            conFillCircle(call[i].param[0], call[i].param[1], call[i].param[2], call[i].colour);
        }
        else if (call[i].type == FILL_PENTAGON)
        {
            conFillPentagon(call[i].param[0], call[i].param[1], call[i].param[2], call[i].colour);
        }
    }
    return 0;
}

void conDrawLine(int x0, int y0, int x1, int y1, int colour) //bresenham line draw algorithm
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
    int err = (dx > dy ? dx : -dy) / 2, e2;
 
    for(;;){
        conDrawPixel(x0, y0, colour);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

void plotCircle(int xc, int yc, int x, int y, int colour) //part of bresenham circle draw plots points in radius of circle
{ 
    conDrawPixel(xc+x, yc+y, colour); 
    conDrawPixel(xc-x, yc+y, colour); 
    conDrawPixel(xc+x, yc-y, colour); 
    conDrawPixel(xc-x, yc-y, colour); 
    conDrawPixel(xc+y, yc+x, colour); 
    conDrawPixel(xc-y, yc+x, colour); 
    conDrawPixel(xc+y, yc-x, colour); 
    conDrawPixel(xc-y, yc-x, colour); 
} 

void conDrawCircle(int xc, int yc, int r, int colour) {
    int x = 0;
    int y = r; 
    int d = 3 - 2 * r; 
    plotCircle(xc, yc, x, y, colour); //initial radius plots
    while (y >= x) 
    {       
        x++; 
  
        if (d > 0) 
        { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; //calculates rotation of next points and assigns x and y values for plot circle
        plotCircle(xc, yc, x, y, colour);
    }
}

void conFillRect(int x, int y, int width, int height, int colour) {
    for (int i = x; i < x + height; i++) {
        for (int j = y; j < y + width; j++) {
            conDrawPixel(j, i, colour); //simple loop through specific area and fills
        }
    }
}

void conDrawTriangle(int xc, int yc, int r, int colour) { //calculates the relative points from centre using radius as all triangle will have the same relative dimentions and angles
    //calcualted using triangles myself
    int d = r / 2;
    int h = d * 1.7;
    conDrawLine(xc, (yc - r), (xc + h), (yc + d), colour);
    conDrawLine(xc, (yc - r), (xc - h), (yc + d), colour);
    conDrawLine((xc - h), (yc + d), (xc + h), (yc + d), colour);
}

void conDrawPentagon(int xc, int yc, int r, int colour) { //same as triangle but relative radius points to pentagon instead
    //calcualted using pentagon myself
    int upperPointX = r * 0.95;
    int upperPointY = r * 0.31;
    int lowerPointX = r * 0.59;
    int lowerPointY = r * 0.81;
    conDrawLine(xc, yc - r, xc + upperPointX, yc - upperPointY, colour);
    conDrawLine(xc, yc - r, xc - upperPointX, yc - upperPointY, colour);
    conDrawLine(xc - upperPointX, yc - upperPointY, xc - lowerPointX, yc + lowerPointY, colour);
    conDrawLine(xc + upperPointX, yc - upperPointY, xc + lowerPointX, yc + lowerPointY, colour);
    conDrawLine(xc - lowerPointX, yc + lowerPointY, xc + lowerPointX, yc + lowerPointY, colour);
    //y coords are inversed as vga y increases while going down the screen instead of decreasing
}

/*void plotCircleFill(int xc, int yc, int x, int y, int colour) //  extremly slow and inefficeint
{
    //uses the same bresenham circle draw but coupled with line draw to draw a line from circle diameter
    //this method is not good as it does not fill circle completly
    conDrawLine(xc+x, yc+y, xc-x, yc-y, colour);
    conDrawLine(xc-x, yc+y, xc+x, yc-y, colour);
    conDrawLine(xc+y, yc+x, xc-y, yc-x, colour);
    conDrawLine(xc-y, yc+x, xc+y, yc-x, colour);
} */

void conFillCircle(int xc, int yc, int r, int colour) {
    //  extremly slow and inefficeint
    /*int x = 0;
    int y = r; 
    int d = 3 - 2 * r; 
    plotCircleFill(xc, yc, x, y, colour); 
    while (y >= x) 
    {       
        x++; 
  
        if (d > 0) 
        { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; 
        plotCircleFill(xc, yc, x, y, colour);
    }*/
    //new method much faster algorithm, removes nested loop
    int r2 = r * r;
    int area = r2 << 2;
    int rr = r << 1;

    for (int i = 0; i < area; i++)
    {
        int tx = (i % rr) - r;
        int ty = (i / rr) - r;

        if (tx * tx + ty * ty <= r2)
            conDrawPixel(xc + tx, yc + ty, colour);
    }
}

void conFillPentagon(int xc, int yc, int r, int colour) //algorithm is slow
{
    int upperPointX = r * 0.95;
    int upperPointY = r * 0.31;
    int lowerPointX = r * 0.59;
    int lowerPointY = r * 0.81;
    //draws line over y axis from mid points of each side symmetrically
    for (int i = 0; i < (r + lowerPointY); i++)
    {
        conDrawLine(xc - upperPointX, yc - upperPointY, xc, yc - r + i, colour);
        conDrawLine(xc + upperPointX, yc - upperPointY, xc, yc - r + i, colour);
    }
    //after reaching bottom of pentagon draws line from mid point to bottom corners along x axis symmetrically
    for (int j = 0; j < lowerPointX; j++)
    {
        conDrawLine(xc - upperPointX, yc - upperPointY, xc - j, yc + lowerPointY, colour);
        conDrawLine(xc + upperPointX, yc - upperPointY, xc + j, yc + lowerPointY, colour);
    }
}