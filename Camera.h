#ifndef CAMERA_H
#define CAMERA_H
#include<point3.h>
#include<vec3.h>
#include <Ray.h>
class Camera{
public:
    point3 cameraPlace;
    vec3 cameraX;
    vec3 cameraY;
    point3 target;
    float fov;
    point3 leftUpPoint;

    Camera(
            point3 lookFrom,
            point3 lookAt,
            vec3 up,
            float fov,
            float vpRatio
            );
    Ray getRay(float cX, float cY);
};
#endif // CAMERA_H
