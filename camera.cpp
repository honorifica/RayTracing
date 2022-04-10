#include<Camera.h>
#include<qmath.h>
#include<QApplication>
Camera::Camera(
        point3 lookFrom,
        point3 lookAt,
        vec3 up,
        float fov,
        float vpRatio
        ){
    vec3 w = (lookFrom-lookAt).unit();
    vec3 u = (w.cross(up)).unit();
    vec3 v = w.cross(u);
    float vpHeight = tanf(fov/2)*2;
    float vpWidth = vpHeight*vpRatio;

    cameraPlace=lookFrom;
    cameraX = u*vpWidth;
    cameraY = v*vpHeight;
    this->fov = fov;
    leftUpPoint = (cameraPlace - cameraX/2 - cameraY/2) - w;
    target = lookAt;
};

Ray Camera::getRay(float cX, float cY){
    return Ray(cameraPlace,(leftUpPoint+cameraX*cX + cameraY*cY - cameraPlace));
}
