#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <GL/glut.h>

using namespace std;

int min_y_pol = 9999, max_y_pol = 0, n;
vector < pair<int,int> > vertices;
vector <double> intersect_x;

struct edge_list{
    int min_y, max_y;
    double present_x, inv_m;
};

edge_list main_edge[10];

void dda(double x1, double y1, double x2, double y2){

    double dx, dy, _count, increment_x, increment_y, x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    if(abs(dy) > abs(dx))
        _count = abs(dy) * 100;
    else
        _count = abs(dx) * 100;

    increment_x = dx / _count;
    increment_y = dy / _count;

    x = x1;
    y = y1;

    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();


    for(double i = 1; i <= _count; i++)
    {
        x += increment_x;
        y += increment_y;

        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();

    }
    glFlush();
    glutSwapBuffers();
}

void draw_polygon(){
    int x1, y1, x2, y2;

    for(int i = 0; i < n; i++){
        x1 = vertices[i].first;
        y1 = vertices[i].second;

        if(i == n-1){
            x2 = vertices[0].first;
            y2 = vertices[0].second;
        }
        else{
            x2 = vertices[i + 1].first;
            y2 = vertices[i + 1].second;
        }

        if(x1 > x2){
            swap(x1,x2);
            swap(y1,y2);
        }

        dda(x1, y1, x2, y2);
    }
}

void make_edge(){
    int x1, y1, x2, y2, x3, y3;

    for(int i = 0; i < n; i++) {
        x1 = vertices[i].first;
        y1 = vertices[i].second;

        if (i + 2 == n) {
            x2 = vertices[i + 1].first;
            y2 = vertices[i + 1].second;

            x3 = vertices[0].first;
            y3 = vertices[0].second;
        }
        else if(i + 1 == n){
            x2 = vertices[0].first;
            y2 = vertices[0].second;

            x3 = vertices[1].first;
            y3 = vertices[1].second;
        }
        else {
            x2 = vertices[i + 1].first;
            y2 = vertices[i + 1].second;

            x3 = vertices[i + 2].first;
            y3 = vertices[i + 2].second;
        }

        if(y1 == y2)
            continue;

        main_edge[i].present_x = x1;
        //cout << y1 << " " << y2 << " " << y3 << endl;

        if(y1 < y2 && y2 < y3){
            main_edge[i].max_y = y2 - 1;
            main_edge[i].min_y = y1;
            main_edge[i].present_x = x1;
            main_edge[i].inv_m = (double)(x1 - x2) / (double)(y1 - y2 + 1);
        }
        else if(y1 > y2 && y2 > y3){
            main_edge[i].max_y = y1;
            main_edge[i].min_y = y2 + 1;
            main_edge[i].present_x = x2;
            main_edge[i].inv_m = (double)(x1 - x2) / (double)(y1 - y2 - 1);
        }
        else{
            if(y1 >= y2){
                main_edge[i].max_y = y1;
                main_edge[i].min_y = y2;
                main_edge[i].present_x = x2;
            }
            else{
                main_edge[i].max_y = y2;
                main_edge[i].min_y = y1;
                main_edge[i].present_x = x1;
            }
            main_edge[i].inv_m = (double)(x1 - x2) / (double)(y1 - y2);
        }
    }

    /*for(int i = 0; i < n; i++){
        cout << main_edge[i].edge_no << " ";
        cout << main_edge[i].max_y << " ";
        cout << main_edge[i].min_y << " ";
        cout << main_edge[i].inv_m << endl;
        cout << endl;
    }*/

}

void color_polygon(){

    for(int i = min_y_pol; i <= max_y_pol; i++){
        intersect_x.clear();
        //cout << "i = " << i << endl;
        for(int j = 0; j < n; j++){
            if(i <= main_edge[j].max_y && i >= main_edge[j].min_y){
                //cout << "inv = " << main_edge[j].inv_m << endl;
                //cout << "x = " << main_edge[j].present_x << endl;

                intersect_x.push_back(main_edge[j].present_x);
                main_edge[j].present_x = main_edge[j].present_x + main_edge[j].inv_m;
            }
        }

        //cout << "size = " << v1.size() << endl;
        sort(intersect_x.begin(), intersect_x.end());
        for(int j = 0; j < intersect_x.size(); j += 2){
            //cout << "x points = " << v1[j] << " " << v1[j+1] << endl;
            dda(intersect_x[j], i, intersect_x[j + 1], i);
        }
    }
}

void display(){
    glPointSize(1.0);

    glColor3f(1.0,1.0,0.0);
    dda(-500, 0, 500, 0);
    dda(0, -500, 0, 500);

    glColor3f(1.0,1.0,1.0);
    draw_polygon();
    glEnd();
    glFlush();

    make_edge();

    glPointSize(2.0);
    glColor3f(1.0,0.0,0.0);
    color_polygon();
    glEnd();
    glFlush();

    glPointSize(1.0);
    glColor3f(1.0,1.0,1.0);
    draw_polygon();
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    cout << "Input number of edges: " << endl;
    cin >> n;

    int x, y;
    cout << "Input vertices clockwise: " << endl;
    for(int i = 0; i < n; i++){
        cin >> x >> y;

        min_y_pol = min(y, min_y_pol);
        max_y_pol = max(y, max_y_pol);

        vertices.push_back(make_pair(x, y));
    }

    //cout << min_y_pol << " " << max_y_pol;

    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(450,100);
    glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
    glutCreateWindow("Drawing a polygon and color it");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 500, -100, 500);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
