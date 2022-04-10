#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include<vec3.h>
#include<point3.h>

class LightSource{
public:
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    point3 place;
    LightSource();
    LightSource(vec3 d, vec3 a , vec3 s, point3 p);
};

#endif // LIGHTSOURCE_H
