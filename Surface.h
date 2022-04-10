#ifndef SURFACE_H
#define SURFACE_H
#include "point3.h"
#include "vec3.h"
#include "HitRecord.h"

class Surface{
public:
    point3 A;
    vec3 AB;
    vec3 AC;
    Materia materia;
    vec3 normal;
    Surface();
    Surface(point3 A, point3 B, point3 C, Materia materia);
    Surface(point3 A, vec3 AB, vec3 AC, Materia materia);

    void operator = (Surface s);

    HitRecord Hit(Ray ray);
};

#endif // SURFACE_H
