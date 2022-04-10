#include<HitRecord.h>
#include<vec3.h>
#include<point3.h>
#include<QApplication>
HitRecord::HitRecord(point3 hitPoint,vec3 normal,float depth, Materia materia, bool usable){
    this->hitPoint =hitPoint;
    this->normal = normal;
    this->depth = depth;
    this->materia = materia;
    this->usable = usable;
    refDirection = vec3();
};

HitRecord::HitRecord(){
    hitPoint = point3(0,0,0);
    normal = vec3(0,0,0);
    depth = (float)INT32_MAX;
    materia = Materia();
    usable=false;
    refDirection = vec3();
}
bool HitRecord::isUsable(){
    return usable;
}

void HitRecord::operator = (HitRecord hr){
    hitPoint = hr.hitPoint;
    normal = hr.normal;
    depth = hr.depth;
    materia = hr.materia;
    usable = hr.usable;
    refDirection = hr.refDirection;
}
