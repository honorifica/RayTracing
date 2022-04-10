#include"Ball.h"
#include"QtMath"
#include"point3.h"
Ball::Ball(point3 center, float radius, Materia materia){
    this->center = center;
    this->radius = radius;
    this->materia = materia;
}
Ball::Ball(){
    center=point3(0,0,0);
    radius = 0;
    materia=Materia();
}

void Ball::operator=(Ball b){
    center = b.center;
    radius = b.radius;
    materia = b.materia;
    samplingCenter = b.samplingCenter;
    samplingRange = b.samplingRange;
}

HitRecord Ball::Hit(Ray ray){
    if((ray.direction.cross(center - ray.origin)).module()/ray.direction.module()<=radius){
        vec3 calculator;
        float a = calculator.dot(ray.direction,ray.direction);
        float b = 2*calculator.dot(ray.direction,ray.origin-center);
        float c = calculator.dot(ray.origin-center,ray.origin-center)-radius*radius;
        float delta = b*b-4*a*c;
        float depth1 = (-b-sqrtf(delta))/(2*a);
        float depth2 = (-b+sqrtf(delta))/(2*a);
        float depth;
        if(depth1>=1e-4){
            if(depth2>=1e-4 && depth2<depth1) depth = depth2;
            else depth = depth1;
            point3 hitPoint = ray.pointAt(depth);
            vec3 normal = hitPoint - center;
            vec3 normal_unit = normal.unit();
            HitRecord hirRecod(hitPoint,normal_unit,depth,materia, true);
            hirRecod.refDirection = ray.direction-normal_unit*(ray.direction.dot(normal_unit))*2;
            return hirRecod;
        } else{
            depth=depth2;
            if(depth>=1e-4){
                point3 hitPoint = ray.pointAt(depth);
                vec3 normal = hitPoint - center;
                vec3 normal_unit = normal.unit();
                HitRecord hitRecod(hitPoint,normal_unit,depth,materia, true);
                hitRecod.refDirection = ray.direction-normal_unit*(abs(ray.direction.dot(normal_unit)))*2;
                return hitRecod;
            }
        }
    }
    return HitRecord(point3(0,0,0),vec3(0,0,0),0,materia, false);
}
