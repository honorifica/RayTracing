#include<Scene.h>
#include<qmath.h>
Scene::Scene(){
    balls = QVector<Ball>();
    globalAmbient = vec3(0.7, 0.7, 0.7);
    dotLightSources = LightSource();
}

HitRecord Scene::BlingPhongHit(Ray ray, float maxDistance){
    if(maxDistance>0){
        float currentDistance=0;
        HitRecord hitRecord;
        HitRecord currentRecord;
        int ballAmount = balls.size();
        Ball currentBall;
        for(int i=0;i<ballAmount;i++){
            currentBall = balls.at(i);
            hitRecord = currentBall.Hit(ray);
            if(hitRecord.isUsable() && hitRecord.depth>0){
                if(hitRecord.depth<currentRecord.depth && hitRecord.depth<=maxDistance)
                    currentRecord = hitRecord;
            }
        }
        HitRecord nextReflectHit;
        currentDistance=currentRecord.depth;

        if(currentRecord.isUsable() && currentDistance>=0.001)
            nextReflectHit =  BlingPhongHit(
                        Ray(currentRecord.hitPoint,currentRecord.refDirection),
                        maxDistance-currentDistance
                        );
        if(!currentRecord.isUsable()){
            return currentRecord;
        }

        if(nextReflectHit.isUsable()){
            //下次反射能打到物体上
            //算靠光源产生的颜色
            Materia hitPointMateria;
            hitPointMateria = BlingPhongColor(
                        currentRecord.hitPoint,currentRecord.normal, ray.direction*-1, currentRecord.materia
                        );
            if(!dotLightSourceReachable(currentRecord.hitPoint)){
                //若到不了光源则根据环境光进行缩减
                hitPointMateria.ambient = hitPointMateria.ambient*globalAmbient.x;
                hitPointMateria.specular = hitPointMateria.specular*globalAmbient.y;
                hitPointMateria.diffuse = hitPointMateria.diffuse*globalAmbient.z;
            }
            nextReflectHit.materia.diffuse = hitPointMateria.diffuse*0.5+nextReflectHit.materia.diffuse*0.5;
            nextReflectHit.materia.specular = hitPointMateria.specular*0.5+nextReflectHit.materia.specular*0.5;
            nextReflectHit.materia.ambient = hitPointMateria.ambient*0.5+nextReflectHit.materia.ambient*0.5;
            nextReflectHit.materia.shiness = hitPointMateria.shiness*0.5+nextReflectHit.materia.shiness*0.5;
            //算自己直接靠颜色反射的值
            nextReflectHit.materia.color = hitPointMateria.color*0.5+nextReflectHit.materia.color*0.5;
            return nextReflectHit;
        } else{
            //下次反射没物体了
            //算靠光源产生的颜色
            Materia hitPointMateria;
            hitPointMateria = BlingPhongColor(
                        currentRecord.hitPoint,currentRecord.normal, ray.direction*-1, currentRecord.materia
                        );
            if(!dotLightSourceReachable(currentRecord.hitPoint)){
                //若到不了光源则根据环境光进行缩减
                hitPointMateria.ambient = hitPointMateria.ambient*globalAmbient.x;
                hitPointMateria.specular = hitPointMateria.specular*globalAmbient.y;
                hitPointMateria.diffuse = hitPointMateria.diffuse*globalAmbient.z;
            }
            currentRecord.materia.diffuse = hitPointMateria.diffuse;
            currentRecord.materia.specular = hitPointMateria.specular;
            currentRecord.materia.ambient = hitPointMateria.ambient;
            currentRecord.materia.shiness = hitPointMateria.shiness;
            //算自己直接靠颜色反射的值
            float t = abs(currentRecord.normal.z);
            currentRecord.materia.color = vec3((1-t)*255+t*128,(1-t)*255+t*179,(1-t)*255+t*255)*0.2+currentRecord.materia.color*0.8;
            return currentRecord;
        }
    } else
        return HitRecord();
}

bool Scene::dotLightSourceReachable(point3 currentPoint){
    vec3 direction = dotLightSources.place - currentPoint;
    float distance = direction.module();
    Ray ray(currentPoint,direction);
    bool clear = true;
    for(int i=0;i<balls.size();i++){
        Ball ball = balls.at(i);
        HitRecord tryHitBall = ball.Hit(ray);
        if(tryHitBall.isUsable()&&tryHitBall.depth<distance) {
            clear=false;
            break;
        }
    }
    return clear;
}

Materia Scene::BlingPhongColor(point3 currentPoint, vec3 normal, vec3 viewDirection, Materia currentMateria){
    if(normal.dot(viewDirection)>=0){
        point3 lightSourcePlace = dotLightSources.place;
        vec3 lightSourceDirection = (lightSourcePlace - currentPoint).unit();
        vec3 halfDirection  = (lightSourceDirection+viewDirection).unit();

        float lDotN = lightSourceDirection.dot(normal);
        float nDotH = normal.dot(halfDirection);
        float nDotHPower = qPow(nDotH,currentMateria.shiness);
        if(nDotHPower!=nDotHPower)nDotHPower=0;
        float rAmbient = (currentMateria.ambient.x*dotLightSources.ambient.x+currentMateria.ambient.x*globalAmbient.x)/2;
        float gAmbient = (currentMateria.ambient.y*dotLightSources.ambient.y+currentMateria.ambient.y*globalAmbient.y)/2;
        float bAmbient = (currentMateria.ambient.z*dotLightSources.ambient.z+currentMateria.ambient.z*globalAmbient.z)/2;
        float rDiffuse = dotLightSources.diffuse.x*currentMateria.diffuse.x*lDotN;
        float gDiffuse = dotLightSources.diffuse.y*currentMateria.diffuse.y*lDotN;
        float bDiffuse = dotLightSources.diffuse.z*currentMateria.diffuse.z*lDotN;
        float rSpecular = dotLightSources.specular.x*currentMateria.specular.x*nDotHPower;
        float gSpecular = dotLightSources.specular.y*currentMateria.specular.y*nDotHPower;
        float bSpecular = dotLightSources.specular.z*currentMateria.specular.z*nDotHPower;
        Materia materia(
                    vec3(rDiffuse,gDiffuse,bDiffuse),
                    vec3(rAmbient, gAmbient,bAmbient),
                    vec3(rSpecular,gSpecular,bSpecular),
                    currentMateria.shiness
                    );
        return materia;
    } else return Materia();
}

HitRecord Scene::RayTraceHit(Ray ray, float maxBumpTime){
    if(maxBumpTime<0){
        vec3 color(0,0,0);
        HitRecord runOut;
        runOut.materia.color=color;
        return runOut;
    }
    else{
        HitRecord hitRecord,currentRecord;
        int ballAmount = balls.size();
        Ball currentBall;
        for(int i=0;i<ballAmount;i++){
            currentBall = balls.at(i);
            hitRecord = currentBall.Hit(ray);
            if(hitRecord.isUsable() && hitRecord.depth>1e-4){
                if(hitRecord.depth<currentRecord.depth)
                    currentRecord = hitRecord;
            }
        }
        Surface currentSurface;
        for(int i=0;i<surfaces.size();i++){
            currentSurface=surfaces.at(i);
            hitRecord = currentSurface.Hit(ray);
            if(hitRecord.isUsable() && hitRecord.depth>1e-4){
                if(hitRecord.depth<currentRecord.depth)
                    currentRecord = hitRecord;
            }
        }

        HitRecord nextReflex;
        if(currentRecord.isUsable() && maxBumpTime - 1 >= 0){
            vec3 disturbedDirection = rayDirectionDisturb(
                currentRecord.refDirection,
                currentRecord.materia.roughness
                );
            nextReflex = RayTraceHit(
                Ray(currentRecord.hitPoint,disturbedDirection),
                maxBumpTime - 1
                );
        } else{
            nextReflex=currentRecord;
        }

        float sampleRatio = (float)(rand()%1000)/1000.0;
        if(ballLightSources.size()==0){
            if(maxBumpTime==0) currentRecord.materia.intensity=1.0;
            else currentRecord.materia.intensity = nextReflex.materia.intensity*0.5+0.5;
            currentRecord.materia.color = nextReflex.materia.color*(currentRecord.materia.color/255.0);
        } else{
            if(sampleRatio<currentRecord.materia.roughness){
                int lsMark = onLightSource(currentRecord.hitPoint);
                //看当前点是不是直接在光源上。没有则进行采样
                if(lsMark==-1){
                    HitRecord lsSamplingRec = lightSourceSampling(currentRecord.normal,currentRecord.hitPoint);
                    currentRecord.materia.intensity = nextReflex.materia.intensity*0.5+
                                                      lsSamplingRec.materia.intensity;
                    currentRecord.materia.color = (nextReflex.materia.color*0.5+
                                                   lsSamplingRec.materia.color*0.5)*
                                                  (currentRecord.materia.color/255.0);
                }
                else {
                    Ball lightSrc = ballLightSources.at(lsMark);
                    currentRecord.materia.intensity=lightSrc.materia.intensity;
                    currentRecord.materia.color = lightSrc.materia.color*0.5
                                                  +currentRecord.materia.color*0.5;
                }
            } else {
                currentRecord.materia.intensity = nextReflex.materia.intensity;
                currentRecord.materia.color = nextReflex.materia.color*(currentRecord.materia.color/255.0);
            }
        }
        return currentRecord;
    }
}

vec3 Scene::rayDirectionDisturb(vec3 direction,float roughness){
    if(roughness < 0) roughness = 0;
    float xDisturb = float(rand()%1000-500);
    float yDisturb = float(rand()%1000-500);
    float zDisturb = float(rand()%1000-500);
    direction = direction+vec3(xDisturb,yDisturb,zDisturb).unit()*roughness;
    return direction;
};

int Scene::onLightSource(point3 point){
    for(int i=0;i<ballLightSources.size();i++){
        Ball lightSrc = ballLightSources.at(i);
        vec3 lsVector = point-lightSrc.center;
        if(sqrtf(lsVector.dot(lsVector))-lightSrc.radius<1e-4) return i;
    }
    return -1;
}

HitRecord Scene::lightSourceSampling(vec3 normal,point3 standPoint){
    float totalIntensity=0;
    vec3 totalColor;
    vec3 lightSrcDirection;
    HitRecord lsSamplingRec;
    bool sampledLightSrc[ballLightSources.size()];
    for(int i=0;i<ballLightSources.size();i++){
        sampledLightSrc[i]=false;
    }
    for(int i=0;i<ballLightSources.size();i++){
        Ball ballLightSrc = ballLightSources.at(i);
        point3 samplingCenter=ballLightSrc.samplingCenter;
        lightSrcDirection = samplingCenter-standPoint;
        vec3 direction = rayDirectionDisturb(lightSrcDirection,ballLightSrc.samplingRange);
        if(normal.dot(direction)>=1e-4) {
            Ray ray(standPoint,direction);
            HitRecord currentRecord;
            HitRecord finalRecord;
            for(int i=0;i<balls.size();i++){
                Ball ball = balls.at(i);
                currentRecord=ball.Hit(ray);
                if(currentRecord.isUsable() &&
                    currentRecord.depth>1e-4 &&
                    currentRecord.depth<finalRecord.depth){
                    finalRecord=currentRecord;
                }
            }
            for(int i=0;i<surfaces.size();i++){
                Surface surface = surfaces.at(i);
                currentRecord=surface.Hit(ray);
                if(currentRecord.isUsable() &&
                    currentRecord.depth>1e-3 &&
                    currentRecord.depth<finalRecord.depth){
                    finalRecord=currentRecord;
                }
            }
            int lsMark = onLightSource(finalRecord.hitPoint);
            if(lsMark!=-1 && !sampledLightSrc[lsMark]){
                Ball hittedLightSrc = ballLightSources.at(lsMark);
                float distance = (standPoint-hittedLightSrc.samplingCenter).module();
                float baseDistance = (finalRecord.hitPoint-hittedLightSrc.samplingCenter).module();
                float digradationRatio = digradationFactor/(digradationFactor+distance-baseDistance);
                totalIntensity+=hittedLightSrc.materia.intensity*digradationRatio;
                totalColor+=hittedLightSrc.materia.color*digradationRatio;
                sampledLightSrc[lsMark]=true;
            }
        }
    }
    lsSamplingRec.materia.intensity=totalIntensity;
    lsSamplingRec.materia.color=totalColor;
    return lsSamplingRec;
}

void Scene::setBallLightSrc(QVector<Ball> lightSrcVec){
    for(int i=0;i<lightSrcVec.size();i++){
        float samplingRange=0;
        QVector<point3> samplingCenterVec;
        Ball lightSrc = lightSrcVec.at(i);
        point3 samplingCenter;
        vec3 c1c2;
        bool decieded = false;
        for(int i=0;i<balls.size();i++){
            Ball currentBall = balls.at(i);
            c1c2 = currentBall.center - lightSrc.center;
            float r1 = lightSrc.radius;
            float r2 = currentBall.radius;
            float d = c1c2.module();
            if(r1+r2>=d && d>r2-r1){
                float cosTheta = (r1*r1+d*d-r2*r2)/(2*r1*d);
                vec3 c1o = c1c2.unit()*(r1*cosTheta);
                point3 o = lightSrc.center+c1o;
                samplingCenterVec.append(o);
                decieded=true;
            }
        }
        if(!decieded){
            samplingCenter=lightSrc.center;
            samplingRange=lightSrc.radius;
        } else {
            samplingCenterVec.append(lightSrc.center);
            vec3 total(0,0,0);
            for(int i=0;i<samplingCenterVec.size();i++){
                point3 center = samplingCenterVec.at(i);
                total+=center-point3(0,0,0);
            }
            samplingCenter=point3(0,0,0)+total/samplingCenterVec.size();
            float rsDistance = (lightSrc.center-samplingCenter).module();
            samplingRange=sqrtf(lightSrc.radius*lightSrc.radius-rsDistance*rsDistance);
        }
        lightSrc.samplingCenter = samplingCenter;
        lightSrc.samplingRange = samplingRange;
        ballLightSources.append(lightSrc);
        balls.append(lightSrc);
    }
}
