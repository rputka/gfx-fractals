// fractals.c

//Ryan Putka
//Fundamentals of Computing
//December 8

// This program generates 8 different fractal shapes depending on which number key (1-8) is pressed.

#include <stdio.h>
#include <math.h>
#include "gfx.h"

// function prototypes
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3);
void shrinkingSquares(int x, int y, int size, int depth);
void spiralSquares(double length, double radius, double angle, int depth);
void circularLace(int x, int y, int radius, int depth);
void snowflake(int x, int y, int size, int depth);
void tree(int x, int y, int length, double angle, int depth);
void fern(double x, double y, double length, double angle, int depth);
void spiralOfSpirals(double x, double y, double radius, double angle, int depth);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void drawSquare(int x, int y, int widHei);

int main() {
    int width = 800, height = 600, margin = 20;
    gfx_open(width, height, "Fractals");
    
    char c;
    while (1) {
        c = gfx_wait();
        gfx_clear();

        if (c == '1') { // sierpinski Triangle
            sierpinski(margin, margin, width - margin, margin, width / 2, height - margin);
        } else if (c == '2') { // shrinking Squares
            shrinkingSquares(width / 2, height / 2, 200, 6);
        } else if (c == '3') { // spiral squares
            spiralSquares(70, 400, 0, 40);
        } else if (c == '4') { // circular Lace
            circularLace(width / 2, height / 2, 200, 6);
        } else if (c == '5') { // snowflake
            snowflake(width / 2, height / 2, 200, 6);
        } else if (c == '6') { // tree
            tree(width / 2, height - margin, 150, -M_PI / 2, 20);
        } else if (c == '7') { // fern
            fern(400, 680, 500, M_PI/2, 5);
        } else if (c == '8') { // spiral of spirals
            spiralOfSpirals(400, 400, 400, 0, 30);
        } else if (c == 'q') { // q to quit
            break;
        }
    }
    return 0;
}

// sierpinski triangle
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3) {
	// base case
    if (abs(x2 - x1) < 5) return;

	// draw triangle
    drawTriangle(x1, y1, x2, y2, x3, y3);

	// recursive calls
    sierpinski(x1, y1, (x1 + x2) / 2, (y1 + y2) / 2, (x1 + x3) / 2, (y1 + y3) / 2);
    sierpinski((x1 + x2) / 2, (y1 + y2) / 2, x2, y2, (x2 + x3) / 2, (y2 + y3) / 2);
    sierpinski((x1 + x3) / 2, (y1 + y3) / 2, (x2 + x3) / 2, (y2 + y3) / 2, x3, y3);
}

// shrinking Squares
void shrinkingSquares(int x, int y, int size, int depth) {
	// base case
    if (depth == 0) return;

	// draw square
    drawSquare(x - size / 2, y - size / 2, size);

	// recursive calls
    int newSize = size / 2;
    shrinkingSquares(x - newSize, y - newSize, newSize, depth - 1);
    shrinkingSquares(x + newSize, y - newSize, newSize, depth - 1);
    shrinkingSquares(x - newSize, y + newSize, newSize, depth - 1);
    shrinkingSquares(x + newSize, y + newSize, newSize, depth - 1);
}

// spiral of squares
void spiralSquares(double length, double radius, double angle, int depth) {
    // base case
    if (depth == 0) return;

    // draw squares
    int center = 300;
    double xcenter = radius * cos(angle) + center;
    double ycenter = radius * sin(angle) + center;

    gfx_line(xcenter - length, ycenter - length, xcenter + length, ycenter - length);
    gfx_line(xcenter + length, ycenter - length, xcenter + length, ycenter + length);
    gfx_line(xcenter + length, ycenter + length, xcenter - length, ycenter + length);
    gfx_line(xcenter - length, ycenter + length, xcenter - length, ycenter - length);

    // recursive calls
    angle = angle + M_PI / 5;
    length = length * 0.88;
    radius = radius * 0.90;
    spiralSquares(length, radius, angle, depth-1);
}

// circular Lace
void circularLace(int x, int y, int radius, int depth) {
	// base case
    if (depth == 0) return;

	// draw circle
    gfx_circle(x, y, radius);

	// recursive calls
    for (int i = 0; i < 6; i++) {
        double angle = i * M_PI / 3;
        int newX = x + cos(angle) * radius;
        int newY = y + sin(angle) * radius;
        circularLace(newX, newY, radius / 3, depth - 1);
    }
}

// snowflake
void snowflake(int x, int y, int size, int depth) {
	// base case
    if (depth == 0) return;

    // drawing triangles
    for (int i = 0; i < 6; i++) {
        double angle = i * M_PI / 3;
        int newX = x + cos(angle) * size;
        int newY = y + sin(angle) * size;
        gfx_line(x, y, newX, newY);
        
        // recursive calls
        snowflake(newX, newY, size / 3, depth - 1);
    }
}

// tree
void tree(int x, int y, int length, double angle, int depth) {
	// base case
    if (depth == 0) return;

	// drawing lines
    int newX = x + cos(angle) * length;
    int newY = y + sin(angle) * length;

    gfx_line(x, y, newX, newY);

	// recursive calls
    tree(newX, newY, length * 0.7, angle - M_PI / 6, depth - 1);
    tree(newX, newY, length * 0.7, angle + M_PI / 6, depth - 1);
}

// fern 
void fern(double x, double y, double length, double angle, int depth) {
    // base case
    if (depth == 0) return;

    // draw lines
    double y2 = y - length * sin(angle) / 4;
    double x2 = x + length * cos(angle) / 4;

    double y3 = y - length * sin(angle) / 2;
    double x3 = x + length * cos(angle) / 2;

    double y4 = y - length * sin(angle) * 3 / 4;
    double x4 = x + length * cos(angle) * 3 / 4;

    double y5 = y - length * sin(angle);
    double x5 = x + length * cos(angle);

    gfx_line(x, y, x5, y5);

    // recursive calls for left and right branches
    double leftAngle = angle - M_PI / 6;
    double rightAngle = angle + M_PI / 6;
    length = length * 0.3;

    fern(x2, y2, length, leftAngle, depth - 1);
    fern(x2, y2, length, rightAngle, depth - 1);

    fern(x3, y3, length, leftAngle, depth - 1);
    fern(x3, y3, length, rightAngle, depth - 1);

    fern(x4, y4, length, leftAngle, depth - 1);
    fern(x4, y4, length, rightAngle, depth - 1);

    fern(x5, y5, length, leftAngle, depth - 1);
    fern(x5, y5, length, rightAngle, depth - 1);
}


// spiral of spirals
void spiralOfSpirals(double x, double y, double radius, double angle, int depth) {
    // base case
    if (depth == 0) return;

    // draw points
    double newx = x + radius * cos(angle);
    double newy = y + radius * sin(angle);
    gfx_point(newx, newy);

    // recursive calls
    radius = radius * 0.9;
    angle = angle + M_PI / 6;
    spiralOfSpirals(x, y, radius, angle, depth-1);
	spiralOfSpirals(newx, newy, radius / 2.7, angle, depth-1);
}



// drawing triangle
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    gfx_line(x1, y1, x2, y2);
    gfx_line(x2, y2, x3, y3);
    gfx_line(x3, y3, x1, y1);
}

// drawing square
void drawSquare(int x, int y, int widHei) {
    gfx_line(x, y, x + widHei, y);
    gfx_line(x + widHei, y, x + widHei, y + widHei);
    gfx_line(x + widHei, y + widHei, x, y + widHei); 
    gfx_line(x, y + widHei, x, y);
}

