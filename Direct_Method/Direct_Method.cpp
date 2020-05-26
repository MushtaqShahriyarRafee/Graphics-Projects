#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

float x1,y1,x2,y2;

void display();

void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}
void drawPoint(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawLine(float x1,float y1,float x2,float y2)
{
    float i,b,m, dx, dy,x,y;

    dx = x2-x1;
    dy = y2-y1;
    x=x1;
    y=y1;
    m = dy/dx;
    b=y1-(m*x1);

    if (dx > dy)
    {
        for (y=y1; y<=y2; y++)
        {
            drawPoint(x, y);
            x=(y-b)/m;
        }
    }
    else
    {
        for (x=x1; x<=x2; x++)
        {
            drawPoint(x, y);
            y=(m*x)+b;
        }
    }
}

int main(int argc,char **argv)
{
    printf("Enter the value of x1 : ");
    scanf("%f",&x1);
    printf("Enter the value of y1 : ");
    scanf("%f",&y1);
    printf("Enter the value of x2 : ");
    scanf("%f",&x2);
    printf("Enter the value of y2 : ");
    scanf("%f",&y2);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Direct Method");
    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

void display()
{
    drawLine(x1,y1,x2,y2);
    glFlush();
}

