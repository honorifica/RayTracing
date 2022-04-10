#ifndef BALL_H
#define BALL_H
#include<QApplication>
#include<point3.h>
#include<HitRecord.h>
#include<Ray.h>
#include<Materia.h>
class Ball{
public:
    point3 center;
    float radius;
    Materia materia;

    Ball(point3 center, float radius, Materia materia);
    Ball();
    HitRecord Hit(Ray ray);

    void operator = (Ball b);

    point3 samplingCenter = point3(0,0,0);
    float samplingRange = 0;
};

#endif // BALL_H
