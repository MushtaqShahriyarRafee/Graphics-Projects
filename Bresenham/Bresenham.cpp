#include <gl/glut.h>
#include <stdio.h>

float x1, y1, x2, y2;

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void draw_pixel(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_line(float x1, float x2, float y1, float y2)
{
    float dx, dy, i, e, incx, incy, inc1, inc2, x,y;

    dx = x2-x1;
    dy = y2-y1;

    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    incx = 1;
    if (x2 < x1)
        incx = -1;
    incy = 1;
    if (y2 < y1)
        incy = -1;
    x = x1;
    y = y1;
    if (dx > dy)
    {
        draw_pixel(x, y);
        e = 2 * dy-dx;
        inc1 = 2*(dy-dx);
        inc2 = 2*dy;
        for (i=0; i<dx; i++)
        {
            if (e >= 0)
            {
                y += incy;
                e += inc1;
            }
            else
                e += inc2;
            x += incx;
            draw_pixel(x, y);
        }
    }
    else
    {
        draw_pixel(x, y);
        e = 2*dx-dy;
        inc1 = 2*(dx-dy);
        inc2 = 2*dx;
        for (i=0; i<dy; i++)
        {
            if (e >= 0)
            {
                x += incx;
                e += inc1;
            }
            else
                e += inc2;
            y += incy;
            draw_pixel(x, y);
        }
    }
}

void myDisplay()
{
    draw_line(x1, x2, y1, y2);
    glFlush();
}

int main(int argc, char **argv)
{
    printf("Enter the value of x1 : ");
    scanf("%f",&x1);
    printf("Enter the value of y1 : ");
    scanf("%f",&y1);
    printf("Enter the value of x2 : ");
    scanf("%f",&x2);
    printf("Enter the value of y2 : ");
    scanf("%f",&y2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Algorithm");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
}
