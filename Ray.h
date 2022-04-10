#ifndef RAY_H
#define RAY_H
#include<point3.h>
#include<vec3.h>

class Ray{
public:
    point3 origin;
    vec3 direction;

    Ray();
    Ray(point3 ori,vec3 dir);
    point3 pointAt(float depth);

    void operator = (Ray r);
};

#endif // RAY_H
