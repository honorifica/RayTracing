#include<Ray.h>
#include<QApplication>
Ray::Ray(){
    origin = point3(0,0,0);
    direction = vec3(0,0,0);
};
Ray::Ray(point3 ori,vec3 dir){
    origin = ori;
    direction = dir.unit();
};
point3 Ray::pointAt(float depth){
    return(origin+direction.unit()*depth);
};

void Ray::operator = (Ray r){
    origin = r.origin;
    direction = r.direction;
}

