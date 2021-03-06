#include<GL/glut.h>
#include<stdio.h>
#include <math.h>

GLint xc, yc, r, sizes=1000;
double theta = 0;

void myInit(void)
{
    glClearColor(0.0,1.0,1.0,0.0);
    glColor3f(1.0f,0.0f,0.0f);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(0.0,640.0,0.0,480.0);
    glOrtho(-sizes/2,sizes/2,-sizes/2,sizes/2,-1,1);
}

void readInput()
{
    printf("Enter X coordinate: ");
    scanf("%i",&xc);
    printf("Enter Y coordinate: ");
    scanf("%i",&yc);
    printf("Enter Radius: ");
    scanf("%i",&r);
}

void setPixel(GLint x_coordinate, GLint y_coordinate)
{
    glBegin(GL_POINTS);
    glVertex2i(x_coordinate,y_coordinate);
    glEnd();
    glFlush();
}

void draw_axis()
{
    GLint i=(-sizes)/2;
    for(; i<(sizes/2); i++)
    {
        setPixel(i,0);
        setPixel(0,i);
    }
}

void draw(GLint xk,GLint yk, GLint xc,GLint yc)
{
    setPixel(xc+xk,yc+yk);
    setPixel(xc+yk,yc+xk);
    setPixel(xc-yk,yc+xk);
    setPixel(xc-xk,yc+yk);
    setPixel(xc-xk,yc-yk);
    setPixel(xc-yk,yc-xk);
    setPixel(xc+yk,yc-xk);
    setPixel(xc+xk,yc-yk);
}

void polynomial(GLint xc,GLint yc,GLint r)
{
    GLint pk,xk,yk;
    pk=3-2*r;
    xk=0;
    yk=r;
    draw(xk,yk,xc,yc);
    while(theta<=45)
    {
        xk=r*cos(theta);
        yk=r*sin(theta);
        draw(xk,yk,xc,yc);
        theta=theta+.20;

    }
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //draw_axis();
    polynomial(xc,yc,r);
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Trigonometric Equation");
    readInput();
    glutDisplayFunc(Display);
    myInit();
    glutMainLoop();
    return 0;
}
