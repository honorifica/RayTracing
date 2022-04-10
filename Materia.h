#ifndef MATERIAL_H
#define MATERIAL_H
#include<vec3.h>
class Materia{
public:
    //各个分量小于1。表示各个情况下RGB各可以反射多少分量
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    bool basedOnLightSource;
    //用于在BlingPhong的着色模型中使用
    float shiness;
    //用于基于颜色反射的使用
    vec3 color;
    //用于基于光线的粗糙程度（即反射扰动）和光强。用于结合颜色得到最后的效果。当intensity大于1即可当作光源使用
    float roughness;
    float intensity;

    Materia();
    Materia(vec3 diffuse, vec3 ambient , vec3 specular, float shiness);
    Materia(vec3 color);
    vec3 getColor();

    void operator = (Materia m);
};

#endif // MATERIAL_H
