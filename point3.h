#ifndef POINT3_H
#define POINT3_H

#include"vec3.h"
class point3{
public:
    float x;
    float y;
    float z;
    float module;

    point3();
    point3(float x,float y, float z);
    void show();

    void operator = (point3 p);
    point3 operator + (vec3 v);
    point3 operator - (vec3 v);
    vec3 operator - (point3 p);
};
#endif // POINT3_H
