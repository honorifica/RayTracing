#ifndef SCENE_H
#define SCENE_H
#include<QVector>
#include<Ball.h>
#include<Ray.h>
#include<LightSource.h>
#include"Surface.h"

class Scene{
public:
    QVector<Ball> balls;
    QVector<Surface> surfaces;

    vec3 globalAmbient;
    LightSource dotLightSources;

    float digradationFactor=100;

    Scene();

    HitRecord BlingPhongHit(Ray ray, float maxDistance);
    HitRecord RayTraceHit(Ray ray, float maxBumpTime);
    void setBallLightSrc(QVector<Ball>lightSrcs);

private:
    QVector<Ball> ballLightSources;
    bool dotLightSourceReachable(point3 currentPoint);
    Materia BlingPhongColor(point3 currentPoint, vec3 normal, vec3 viewDirection, Materia currentMateria);
    vec3 rayDirectionDisturb(vec3 direction,float roughness);
    HitRecord lightSourceSampling(vec3 normal,point3 standPoint);
    int onLightSource(point3 point);
};

#endif // SCENE_H
