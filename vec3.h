#ifndef VEC3_H
#define VEC3_H
class vec3{
public:
    float x;
    float y;
    float z;

    float module();
    vec3();
    vec3(float x,float y, float z);
    vec3 cross(vec3 v1,vec3 v2);
    vec3 cross(vec3 v);
    float dot(vec3 v1,vec3 v2);
    float dot(vec3 v);
    vec3 unit();
    void show();
    vec3 getPolarCor();
    void setByPolarCor(vec3 polarCor);

    vec3 operator * (float f);
    vec3 operator * (vec3 v);
    vec3 operator = (vec3 v);
    vec3 operator + (vec3 v);
    vec3 operator - (vec3 v);
    vec3 operator / (float f);
    bool operator != (vec3 v);
    bool operator == (vec3 v);
    void operator *= (float f);
    void operator += (vec3 v);
};

#endif // VEC3_H
