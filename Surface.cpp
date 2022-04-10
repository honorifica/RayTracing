#include "Surface.h"
#include "QtMath"

Surface::Surface(){
    A=point3(0,0,0);
    AC = vec3(0,0,0);
    AB = vec3(0,0,0);
    materia = Materia();
    normal = vec3(0,0,0);
}

Surface::Surface(point3 A, point3 B, point3 C, Materia materia){
    this->A = A;
    AC = C-A;
    AB = B-A;
    this->materia = materia;
    normal = AB.cross(AC).unit();
};

Surface::Surface(point3 A, vec3 AB, vec3 AC, Materia materia){
    this->A = A;
    this->AB= AB;
    this->AC = AC;
    this->materia = materia;
    normal = AB.cross(AC).unit();
};

void Surface::operator=(Surface s){
    A=s.A;
    AB=s.AB;
    AC=s.AC;
    materia = s.materia;
    normal = s.normal;
}

HitRecord Surface::Hit(Ray ray){
    if(ray.direction.dot(normal)>1e-3)
        return HitRecord();
    else{
        vec3 d = ray.direction;
        point3 R = ray.origin;
        point3 P;
        float A1 = AB.x*d.y-AB.y*d.x;
        float B1 = AC.x*d.y-AC.y*d.x;
        float C1 = d.y*(A.x-R.x)-(A.y-R.y)*d.x;
        float A2 = AB.y*d.z-AB.z*d.y;
        float B2 = AC.y*d.z - AC.z*d.y;
        float C2 = (A.y-R.y)*d.z-(A.z-R.z)*d.y;
        float a=(C2*B1-C1*B2)/(A1*B2-A2*B1);
        if(a<0.0 || a>1.0) return HitRecord();
        float b=(C2*A1-C1*A2)/(B1*A2-B2*A1);
        if(b<0.0 || b>1.0 || a+b>1.0) return HitRecord();
        else {
            P=A+AB*a+AC*b;
            float distance = (P-ray.origin).module();
            HitRecord hitRecord(P,normal,distance,materia,true);
            hitRecord.refDirection = ray.direction+normal*(abs(ray.direction.dot(normal)))*2;
            return hitRecord;
        }
    }
}
