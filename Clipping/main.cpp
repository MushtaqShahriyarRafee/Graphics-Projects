#include <iostream>
#include <GL/glut.h>

using namespace std;

struct edge {
    int x1, y1, x2, y2;
    string position = "";
};

int x1_point, x2_point, y1_point, y2_point, n;
int x1, x2, x3, x4, y1, y2, y3, y4;
edge edges[100];

void dda(double x1, double y1, double x2, double y2) {

    double dx, dy, _count, increment_x, increment_y, x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    if (abs(dy) > abs(dx))
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


    for (double i = 1; i <= _count; i++) {
        x += increment_x;
        y += increment_y;

        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
    }

    glFlush();
    glutSwapBuffers();
}

void draw_window() {

    x1 = min(x1_point, x2_point);
    x2 = max(x1_point, x2_point);
    x3 = x2;
    x4 = x1;

    y1 = min(y1_point, y2_point);
    y2 = y1;
    y3 = max(y1_point, y2_point);
    y4 = y3;

    dda(x1, y1, x2, y2);
    dda(x2, y2, x3, y3);
    dda(x3, y3, x4, y4);
    dda(x1, y1, x4, y4);
}

string points_clip(int x, int y) {

    string value = "9999";

    if (y > y3)
        value[0] = '1';
    else
        value[0] = '0';

    if (y < y1)
        value[1] = '1';
    else
        value[1] = '0';

    if (x > x2)
        value[2] = '1';
    else
        value[2] = '0';

    if (x < x1)
        value[3] = '1';
    else
        value[3] = '0';

    return value;
}

bool bitwise_and(string first_point, string second_point) {

    string result = "9999";
    for (int i = 0; i < 4; i++) {
        if (first_point[i] == '1' && second_point[i] == '1')
            result[i] = '1';
        else
            result[i] = '0';
    }

    cout << result << endl;

    if (result == "0000")
        return true;
    else
        return false;
}

void lines_clip(int i) {

    int x = 0, y = 0;
    string value = points_clip(edges[i].x1, edges[i].y1);
    cout << "initial first " << value << endl;
    if (value[0] == '1') {

        x = edges[i].x1 + ((y3 - edges[i].y1) * (edges[i].x2 - edges[i].x1) / (edges[i].y2 - edges[i].y1));

        glColor3f(0.0, 1.0, 0.0);
        dda(x, y3, edges[i].x1, edges[i].y1);

        edges[i].x1 = x;
        edges[i].y1 = y3;

        cout << edges[i].x1 << " " << edges[i].y1 << endl;
    }

    if (value[1] == '1') {

        x = edges[i].x1 +((y1 - edges[i].y1) * (edges[i].x2 - edges[i].x1) / (edges[i].y2 - edges[i].y1));

        glColor3f(0.0, 1.0, 0.0);
        dda(x, y1, edges[i].x1, edges[i].y1);

        edges[i].x1 = x;
        edges[i].y1 = y1;

        cout << edges[i].x1 << " " << edges[i].y1 << endl;
    }

    if (value[2] == '1') {

        y = edges[i].y1 +((x2 - edges[i].x1) * (edges[i].y2 - edges[i].y1) / (edges[i].x2 - edges[i].x1));

        glColor3f(0.0, 1.0, 0.0);
        dda(x2, y, edges[i].x1, edges[i].y1);

        edges[i].x1 = x2;
        edges[i].y1 = y;

        cout << edges[i].x1 << " " << edges[i].y1 << endl;
    }

    if (value[3] == '1') {

        y = edges[i].y1 +((x1 - edges[i].x1) * (edges[i].y2 - edges[i].y1) / (edges[i].x2 - edges[i].x1));

        glColor3f(0.0, 1.0, 0.0);
        dda(x1, y, edges[i].x1, edges[i].y1);

        edges[i].x1 = x1;
        edges[i].y1 = y;

        cout << edges[i].x1 << " " << edges[i].y1 << endl;
    }

    value = points_clip(edges[i].x1, edges[i].y1);
    cout << "final first: " << value << endl;

    x = 0; y = 0;
    value = points_clip(edges[i].x2, edges[i].y2);
    cout << "initial second " << value << endl;

    if (value[0] == '1') {

        x = edges[i].x2 + ((y3 - edges[i].y2) * (edges[i].x2 - edges[i].x1) / (edges[i].y2 - edges[i].y1));

        glColor3f(0.0, 1.0, 0.0);
        dda(x, y3, edges[i].x2, edges[i].y2);

        edges[i].x2 = x;
        edges[i].y2 = y3;

        cout << edges[i].x2 << " " << edges[i].y2 << endl;
    }
    value = points_clip(edges[i].x2, edges[i].y2);
    if (value[1] == '1') {

        x = edges[i].x2 +((y1 - edges[i].y2) * (edges[i].x2 - edges[i].x1) / (edges[i].y2 - edges[i].y1));

        glColor3f(0.0, 1.0, 0.0);
        dda(x, y1, edges[i].x2, edges[i].y2);

        edges[i].x2 = x;
        edges[i].y2 = y1;

        cout << edges[i].x2 << " " << edges[i].y2 << endl;
    }
    value = points_clip(edges[i].x2, edges[i].y2);
    if (value[2] == '1') {

        y = edges[i].y2 +((x2 - edges[i].x2) * (edges[i].y2 - edges[i].y1) / (edges[i].x2 - edges[i].x1));

        glColor3f(0.0, 1.0, 0.0);
        dda(x2, y, edges[i].x2, edges[i].y2);

        edges[i].x2 = x2;
        edges[i].y2 = y;

        cout << edges[i].x2 << " " << edges[i].y2 << endl;
    }
    value = points_clip(edges[i].x2, edges[i].y2);
    if (value[3] == '1') {

        y = edges[i].y2 +((x1 - edges[i].x2) * (edges[i].y2 - edges[i].y1) / (edges[i].x2 - edges[i].x1));

        glColor3f(0.0, 1.0, 0.0);
        dda(x1, y, edges[i].x2, edges[i].y2);

        edges[i].x2 = x1;
        edges[i].y2 = y;

        cout << edges[i].x2 << " " << edges[i].y2 << endl;
    }

    value = points_clip(edges[i].x2, edges[i].y2);
    cout << "final second " << value << endl;
}

string check_points() {

    for (int i = 0; i < n; i++) {

        string first_point = points_clip(edges[i].x1, edges[i].y1);
        string second_point = points_clip(edges[i].x2, edges[i].y2);


        if (first_point == "0000" && second_point == "0000")
            edges[i].position = "inside";
        else if (!bitwise_and(first_point, second_point)) {
            edges[i].position = "outside";
            cout << "outside" << endl;
        }
        else {
            lines_clip(i);

            first_point = points_clip(edges[i].x1, edges[i].y1);
            second_point = points_clip(edges[i].x2, edges[i].y2);

            if (first_point == "0000" && second_point == "0000")
                edges[i].position = "inside";
            else
                edges[i].position = "outside";
        }
    }
}

void draw_lines() {
    for (int i = 0; i < n; i++) {
        if (edges[i].position == "inside") {
            glColor3f(1.0, 0.0, 0.0);
            dda(edges[i].x1, edges[i].y1, edges[i].x2, edges[i].y2);
        }
        else {
            glColor3f(0.0, 1.0, 0.0);
            dda(edges[i].x1, edges[i].y1, edges[i].x2, edges[i].y2);
        }
    }
}

void display() {

    glPointSize(1.0);
    glColor3f(1.0, 1.0, 1.0);
    dda(-500, 0, 500, 0);
    dda(0, -500, 0, 500);

    glPointSize(1.0);
    glColor3f(1.0, 1.0, 1.0);
    draw_window();

    glPointSize(1.0);
    check_points();
    draw_lines();
}

int main(int argc, char *argv[]) {

    cout << "The two corner points of the window: " << endl;
    cin >> x1_point >> y1_point >> x2_point >> y2_point;

    cout << "The number of edges: ";
    cin >> n;
    cout << "Input vertices: " << endl;

    for (int i = 0; i < n; i++) {
        cin >> edges[i].x1;
        cin >> edges[i].y1;
        cin >> edges[i].x2;
        cin >> edges[i].y2;
    }

    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(150, 150);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutCreateWindow("Line Clipping");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
