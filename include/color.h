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

    RGB(double R, double G , double B) :  R{R}, G{G}, B{B} {}

    
    static RGB from_HSV(double hue, double saturation, double value){
        double normalizedHue = std::fmod(hue, 1);
        double chroma = value*saturation;
        double X = chroma * (1.0 - std::abs(std::fmod(hue/(1.0/6.0), 2.0) - 1.0));
        
        if (normalizedHue < 1.0/6.0){
            return RGB{chroma, X, 0.0};
        
        }else if (normalizedHue < 2.0/6.0){
            return RGB{X, chroma, 0.0};
        }else if (normalizedHue < 3.0/6.0){
            return RGB{0.0, chroma, X};
        }else if (normalizedHue < 4.0/6.0){
            return RGB{0.0, X, chroma};
        }else if (normalizedHue < 5.0/6.0){
            return RGB{X, 0.0, chroma};
        }else{
            return RGB{chroma, 0.0, X};
        }        
    }

    
    RGB operator+(const RGB other) const { return RGB(R+other.R, G+other.G, B+other.B); }
    RGB operator-(const RGB other) const { return RGB(R-other.R, G-other.G, B-other.B); }
    RGB operator*(const RGB other) const { return RGB(R*other.R, G*other.G, B*other.B); }
    RGB operator/(const RGB other) const { return RGB(R/other.R, G/other.G, B/other.B); }

    template <typename T>
    RGB operator+(T val) const { return RGB(R+val, G+val, B+val); }
    template <typename T>
    RGB operator-(T val) const { return RGB(R-val, G-val, B-val); }
    template <typename T>
    RGB operator*(T val) const { return RGB(R*val, G*val, B*val); }
    template <typename T>
    RGB operator/(T val) const { return RGB(R/val, G/val, B/val); }

};

#endif