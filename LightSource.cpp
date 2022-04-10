#include<LightSource.h>
LightSource::LightSource(){
    ambient = vec3(0.0f, 0.0f, 0.0f);
    diffuse = vec3(1.0f, 1.0f, 1.0f);
    specular = vec3(1.0f, 1.0f, 1.0f);
    place = point3(0,0,0);
}

LightSource::LightSource(vec3 d, vec3 a , vec3 s, point3 p){
    diffuse = d;
    ambient = a;
    specular = s;
    place = p;
}

