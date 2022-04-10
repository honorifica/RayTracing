
#include<Materia.h>
#include<vec3.h>
Materia::Materia(){
    ambient = vec3(0.5f, 0.5f, 0.5f);
    diffuse = vec3(0.3f, 0.3f, 0.3f);
    specular = vec3(0.2f, 0.2f, 0.2f);
    basedOnLightSource = false;
    shiness=1.0;
    color = vec3(255,255,255);
    roughness = 1.0f;
    intensity=0.0f;
}

Materia::Materia(vec3 diffuse, vec3 ambient , vec3 specular, float shiness){
    this->diffuse = diffuse;
    this->ambient = ambient;
    this->specular = specular;
    this->shiness = 1/shiness;
    basedOnLightSource=true;
    color = vec3(255,255,255);
    roughness = 1.0f;
    intensity=0.0;
}

Materia::Materia(vec3 color){
    this->color = color;
    ambient = vec3(0.5f, 0.5f, 0.5f);
    diffuse = vec3(0.3f, 0.3f, 0.3f);
    specular = vec3(0.2f, 0.2f, 0.2f);
    basedOnLightSource = false;
    shiness=1.0;
    roughness = 1.0;
    intensity=0.0;
}

void Materia::operator = (Materia m){
    ambient = m.ambient;
    diffuse = m.diffuse;
    specular = m.specular;
    basedOnLightSource = m.basedOnLightSource;
    shiness=m.shiness;
    color = m.color;
    roughness = m.roughness;
    intensity = m.intensity;
}

vec3 Materia::getColor(){
    if(basedOnLightSource)
        return (ambient+diffuse+specular)*255;
    else return color;
}
