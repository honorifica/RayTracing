#include<point3.h>
#include<QApplication>

point3::point3(){
    x=0,y=0,z=0;
};
point3::point3(float x,float y, float z){
    this->x=x;
    this->y=y;
    this->z=z;
};

void point3::operator = (point3 p){
    x=p.x;
    y=p.y;
    z=p.z;
};

point3 point3::operator + (vec3 v){
    return point3(x+v.x,y+v.y,z+v.z);
};

point3 point3::operator - (vec3 v){
    return point3(x-v.x,y-v.y,z-v.z);
};

vec3 point3::operator - (point3 p){
    return vec3(x-p.x,y-p.y,z-p.z);
};

void point3::show(){
    printf("point3 x: %f , y: %f , z: %f\n",x,y,z);
}
