#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>
#include <math.h>
#include <cmath>

struct RGB {
    double R;
    double G;
    double B;

    RGB(int R, int G , int B) : 
        R{static_cast<double>(R)/255},
        G{static_cast<double>(G)/255},
        B{static_cast<double>(B)/255} {}
    
    RGB operator+(RGB other) { return RGB(R+other.R, G+other.G, B+other.B); }
    RGB operator-(RGB other) { return RGB(R-other.R, G-other.G, B-other.B); }
    RGB operator*(RGB other) { return RGB(R*other.R, G*other.G, B*other.B); }
    RGB operator/(RGB other) { return RGB(R/other.R, G/other.G, B/other.B); }

};

#endif