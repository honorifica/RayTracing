#ifndef HITRECORD_H
#define HITRECORD_H
#include<point3.h>
#include<vec3.h>
#include <Ray.h>
#include <Materia.h>

class HitRecord{
public:
    /**
     * @brief hitPoint
     * hitPoint 可以击中的点
     * normal 击中点的法向量
     * depth 击中地方的深度
     * materia 集中处的材质
     * refDirection 击中后光的反射方向
     */
    point3 hitPoint;
    vec3 normal;
    float depth;
    Materia materia;
    bool usable;
    vec3 refDirection;

    HitRecord(point3 hitPoint,vec3 normal,float depth, Materia materia, bool usable);
    HitRecord();
    bool isUsable();

    void operator = (HitRecord hr);
};

#endif // HITRECORD_H
