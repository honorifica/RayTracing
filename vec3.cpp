#include"vec3.h"
#include<QtMath>
#include<QApplication>
vec3::vec3(){
    x=0;
    y=0;
    z=0;
}

vec3::vec3(float x,float y, float z){
    this->x=x;
    this->y=y;
    this->z=z;
};

float vec3::module(){
    return sqrtf(x*x+y*y+z*z);
};

vec3 vec3::cross(vec3 v1,vec3 v2){
    return vec3(
                v1.y*v2.z-v1.z*v2.y,
                v1.z*v2.x-v1.x*v2.z,
                v1.x*v2.y-v1.y*v2.x
                );
};

vec3 vec3::cross(vec3 v){
    return vec3(
                y*v.z-z*v.y,
                z*v.x-x*v.z,
                x*v.y-y*v.x
                );
};

float vec3::dot(vec3 v1,vec3 v2){
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
};

float vec3::dot(vec3 v){
    return x*v.x+y*v.y+z*v.z;
};

vec3 vec3::unit(){
    float module = sqrtf(x*x+y*y+z*z);
    x=x/module;
    y=y/module;
    z=z/module;
    return vec3(x,y,z);
};

vec3 vec3::getPolarCor(){
    float fi = atan2f(x,y);//平面角度
    float module = sqrtf(x*x+y*y+z*z);
    float theta = asinf(z/module);//立体角度
    return vec3(fi,theta,module);
}

void vec3::setByPolarCor(vec3 polarCor){
    float fi = polarCor.x;
    float theta = polarCor.y;
    float module = polarCor.z;
    float xyModule = module*cosf(theta);
    x=xyModule*cosf(fi);
    y=xyModule*sinf(fi);
    z=module*sinf(theta);
}
vec3 vec3::operator * (float f){
    return vec3(x*f, y*f, z*f);
};

vec3 vec3::operator * (vec3 v){
    return vec3(x*v.x,y*v.y,z*v.z);
}


vec3 vec3::operator = (vec3 v){
    x=v.x;
    y=v.y;
    z=v.z;
    return vec3(x,y,z);
};

vec3 vec3::operator + (vec3 v){
    return vec3(
                x+v.x,
                y+v.y,
                z+v.z
                );
};
vec3 vec3::operator - (vec3 v){
    return vec3(
                x-v.x,
                y-v.y,
                z-v.z
                );
};

vec3 vec3::operator / (float f){
    return vec3(x/f,y/f,z/f);
}

bool vec3::operator != (vec3 v){
    if(x==v.x && y==v.y && z==v.z) return false;
    else return true;
}

bool vec3::operator == (vec3 v){
    if(x==v.x && y==v.y && z==v.z) return true;
    else return false;
}

void vec3::show(){
    printf("vec3 x: %f , y: %f , z: %f\n",x,y,z);
}

void vec3::operator *= (float f){
    x*=f;
    y*=f;
    z*=f;
}

void vec3::operator += (vec3 v){
    x+=v.x;
    y+=v.y;
    z+=v.z;
}
