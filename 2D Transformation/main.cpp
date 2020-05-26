#include <iostream>
#include <cmath>
#include <GL/glut.h>

#define PI 3.14159265

using namespace std;

struct pointset {

    double x, y, z = 1;

};

pointset points[4], translated_points[4], rotated_points[4], scaled_points[4], mirrored_x_points[4], mirrored_y_points[4];
double n, tx, ty, theta, sx, sy;

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

void draw_polygon() {

    for (int i = 0; i < 4; i++) {
        if (i + 1 == 4)
            dda(points[i].x, points[i].y, points[0].x, points[0].y);
        else
            dda(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
    }
}

void translate() {

    double translated_matrix[3][1];

    double translation_matrix[3][3] = {
            {1, 0, tx},
            {0, 1, ty},
            {0, 0, 1}
    };

    for (int p = 0; p < 4; p++) {

        memset(translated_matrix, 0, sizeof(translated_matrix));

        double point_matrix[3][1] = {
                {points[p].x},
                {points[p].y},
                {points[p].z}
        };

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 1; j++)
                for (int k = 0; k < 3; k++)
                    translated_matrix[i][j] += translation_matrix[i][k] * point_matrix[k][j];

        translated_points[p].x = translated_matrix[0][0];
        translated_points[p].y = translated_matrix[1][0];
        translated_points[p].z = translated_matrix[2][0];
    }

    for (int i = 0; i < 4; i++) {
        if (i + 1 == 4)
            dda(translated_points[i].x, translated_points[i].y, translated_points[0].x, translated_points[0].y);
        else
            dda(translated_points[i].x, translated_points[i].y, translated_points[i + 1].x, translated_points[i + 1].y);
    }
}

void rotate() {

    double rotated_matrix[3][1];

    double rotation_matrix[3][3] = {
            {cos(theta), -sin(theta), 0},
            {sin(theta), cos(theta),  0},
            {0,          0,           1}
    };

    for (int p = 0; p < 4; p++) {

        memset(rotated_matrix, 0, sizeof(rotated_matrix));

        double point_matrix[3][1] = {
                {points[p].x},
                {points[p].y},
                {points[p].z}
        };

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 1; j++)
                for (int k = 0; k < 3; k++)
                    rotated_matrix[i][j] += rotation_matrix[i][k] * point_matrix[k][j];

        rotated_points[p].x = rotated_matrix[0][0];
        rotated_points[p].y = rotated_matrix[1][0];
        rotated_points[p].z = rotated_matrix[2][0];
    }

    for (int i = 0; i < 4; i++) {
        if (i + 1 == 4)
            dda(rotated_points[i].x, rotated_points[i].y, rotated_points[0].x, rotated_points[0].y);
        else
            dda(rotated_points[i].x, rotated_points[i].y, rotated_points[i + 1].x, rotated_points[i + 1].y);
    }
}

void scale() {

    double scaled_matrix[3][1];

    double scaling_matrix[3][3] = {
            {sx, 0,  0},
            {0,  sy, 0},
            {0,  0,  1}
    };

    for (int p = 0; p < 4; p++) {

        memset(scaled_matrix, 0, sizeof(scaled_matrix));

        double point_matrix[3][1] = {
                {points[p].x},
                {points[p].y},
                {points[p].z}
        };

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 1; j++)
                for (int k = 0; k < 3; k++)
                    scaled_matrix[i][j] += scaling_matrix[i][k] * point_matrix[k][j];

        scaled_points[p].x = scaled_matrix[0][0];
        scaled_points[p].y = scaled_matrix[1][0];
        scaled_points[p].z = scaled_matrix[2][0];
    }

    for (int i = 0; i < 4; i++) {
        if (i + 1 == 4)
            dda(scaled_points[i].x, scaled_points[i].y, scaled_points[0].x, scaled_points[0].y);
        else
            dda(scaled_points[i].x, scaled_points[i].y, scaled_points[i + 1].x, scaled_points[i + 1].y);
    }
}

void mirror() {

    double mirrored_matrix_x[3][1], mirrored_matrix_y[3][1];

    double mirroring_matrix_x[3][3] = {
            {1, 0,  0},
            {0, -1, 0},
            {0, 0,  1}
    };

    double mirroring_matrix_y[3][3] = {
            {-1, 0, 0},
            {0,  1, 0},
            {0,  0, 1}
    };

    for (int p = 0; p < 4; p++) {

        memset(mirrored_matrix_x, 0, sizeof(mirrored_matrix_x));
        memset(mirrored_matrix_y, 0, sizeof(mirrored_matrix_y));

        double point_matrix[3][1] = {
                {points[p].x},
                {points[p].y},
                {points[p].z}
        };

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 1; j++)
                for (int k = 0; k < 3; k++) {
                    mirrored_matrix_x[i][j] += mirroring_matrix_x[i][k] * point_matrix[k][j];
                    mirrored_matrix_y[i][j] += mirroring_matrix_y[i][k] * point_matrix[k][j];
                }

        mirrored_x_points[p].x = mirrored_matrix_x[0][0];
        mirrored_x_points[p].y = mirrored_matrix_x[1][0];
        mirrored_x_points[p].z = mirrored_matrix_x[2][0];

        mirrored_y_points[p].x = mirrored_matrix_y[0][0];
        mirrored_y_points[p].y = mirrored_matrix_y[1][0];
        mirrored_y_points[p].z = mirrored_matrix_y[2][0];
    }

    for (int i = 0; i < 4; i++) {
        if (i + 1 == 4) {
            dda(mirrored_x_points[i].x, mirrored_x_points[i].y, mirrored_x_points[0].x, mirrored_x_points[0].y);
            dda(mirrored_y_points[i].x, mirrored_y_points[i].y, mirrored_y_points[0].x, mirrored_y_points[0].y);
        } else {
            dda(mirrored_x_points[i].x, mirrored_x_points[i].y, mirrored_x_points[i + 1].x, mirrored_x_points[i + 1].y);
            dda(mirrored_y_points[i].x, mirrored_y_points[i].y, mirrored_y_points[i + 1].x, mirrored_y_points[i + 1].y);
        }
    }
}

void display() {

    glColor3f(1.0, 1.0, 0.0);
    dda(-500, 0, 500, 0);
    dda(0, -500, 0, 500);

    glPointSize(1.5);
    glColor3f(1.0, 1.0, 1.0);
    draw_polygon();
    glEnd();
    glFlush();

    glPointSize(2.0);
    glColor3f(1.0, 0.0, 0.0);

    if (n == 1)
        translate();
    else if (n == 2)
        rotate();
    else if (n == 3)
        scale();
    else
        mirror();

    glEnd();
    glFlush();
}

int main(int argc, char **argv) {

    cout << "Enter the coordinates: " << endl;
    int x, y;

    for (int i = 0; i < 4; i++) {
        cin >> x >> y;
        points[i].x = x;
        points[i].y = y;
    }

    cout << "What do you want to do?" << endl;
    cout << "*) To Translate, Enter 1" << endl;
    cout << "*) To Rotate, Enter 2" << endl;
    cout << "*) To Scale, Enter 3" << endl;
    cout << "*) To Mirror, Enter 4" << endl;

    cout << "Enter your choice: " << endl;
    cin >> n;

    if (n == 1) {
        cout << "Enter value of TX and TY: " << endl;
        cin >> tx >> ty;
    } else if (n == 2) {
        cout << "Enter value of Theta: " << endl;
        cin >> theta;
        theta = (theta * PI) / 180;
    } else if (n == 3) {
        cout << "Enter value of SX and SY: " << endl;
        cin >> sx >> sy;
    }

    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(450, 100);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutCreateWindow("Drawing a polygon and color it");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
