#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vec3.h"
#include "Camera.h"
#include "point3.h"
#include "Ray.h"
#include "QtMath"
#include "Ball.h"
#include "Scene.h"
#include "ctime"
#include "Materia.h"
#include "LightSource.h"
#include "omp.h"

float Pi = acosf(-1);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


vec3 vec3ColorVerify(vec3 color){
    if(color.x>255) color.x=255;
    if(color.x<0)color.x = 0;
    if(color.y>255) color.y=255;
    if(color.y<0) color.y=0;
    if(color.z>255) color.z=255;
    if(color.z<0)color.z=0;
    return color;
};

void MainWindow::on_BlingPhongTracing_clicked()
{
    int rayPerPixel=1;
    int width = 400;
    int height = 300;
    float fov = 0.42*Pi;
    QImage traceImage(width,height,QImage::Format_RGB888);
    Scene scene;
    Materia materia(vec3(255,255,0));
    materia.shiness = 5;
    scene.balls.append(Ball(point3(1.125,1.125,1),1,materia));

    materia = Materia(vec3(255,0,255));
    materia.shiness = 25;
    scene.balls.append(Ball(point3(1.125,-1.125,1),1,materia));

    materia = Materia(vec3(255,128,64));
    materia.shiness = 200;
    scene.balls.append(Ball(point3(-1.125,-1.125,1),1,materia));

    materia=Materia(vec3(64,255,128));
    materia.shiness = 500;
    scene.balls.append(Ball(point3(-1.125,1.125,1),1,materia));

    materia = Materia(vec3(255,255,255));
    materia.shiness = 300;
    scene.balls.append(Ball(point3(0,0,-100),100,materia));

    scene.globalAmbient = vec3(0.4,0.4,0.4);
    scene.dotLightSources.place = point3(1.5,4,3.5);
    Camera camera(point3(0.7,1,3),point3(0,0,1),vec3(0,0,1),fov,(float)width/(float)height);
    Ray ray;
    HitRecord hitRecord;
    for(int x=0;x<width;x++){
        printf("%f%\n",(float)x*100.0/(float)width),fflush(stdout);
        for(int y=0;y<height;y++){
            vec3 intensityPerRay(0,0,0);
            vec3 colorPerRay(0,0,0);
            for(int i=0;i<rayPerPixel;i++){
                float move = (float)(rand()%1000)/1000.0;
                ray = camera.getRay(((float)x+move)/(float)width,((float)y+move)/(float)height);
                hitRecord=scene.BlingPhongHit(ray, INT8_MAX);
                if(hitRecord.isUsable()){
                    Materia materia = hitRecord.materia;
                    materia.basedOnLightSource = false;
                    colorPerRay = colorPerRay+materia.getColor();
                    materia.basedOnLightSource = true;
                    intensityPerRay=intensityPerRay+materia.getColor();
                }
            }
            vec3 color(
                colorPerRay.x/rayPerPixel,
                colorPerRay.y/rayPerPixel,
                colorPerRay.z/rayPerPixel
                );
            vec3 intensity(
                intensityPerRay.x/rayPerPixel/255,
                intensityPerRay.y/rayPerPixel/255,
                intensityPerRay.z/rayPerPixel/255
                );
            color = vec3ColorVerify(vec3(
                color.x*intensity.x,
                color.y*intensity.y,
                color.z*intensity.z
                ));
            traceImage.setPixelColor(x,y,QColor(color.x,color.y,color.z));
        }
    }
//    traceImage.save("C:\\Users\\MSI-PC\\Desktop\\RayTracing.bmp","bmp",100);
    ui->displayArea->setPixmap(QPixmap::fromImage(traceImage));
    ui->displayArea->setGeometry((1600-width)/2,(900-height)/2,width,height);
}

void MainWindow::on_RayTrace_clicked()
{
    int thread_count = omp_get_num_procs();
    int rayPerPixel=1000;
    int width = 1600;
    int height = 900;
    float processed = 0;
    float fov = 0.35*Pi;
    int maxBumpTime = 32;
    QImage traceImage(width,height,QImage::Format_RGB888);
    Scene scene;
    Camera camera(point3(-75,-40,50),point3(25,50,20),vec3(0,0,1),fov,(float)width/(float)height);
    Materia materia;
//墙
    materia.color = vec3(240,240,240);
    materia.roughness=1;
    scene.surfaces.append(Surface(point3(-100,-100,0),point3(100,-100,0),point3(-100,100,0),materia));
    scene.surfaces.append(Surface(point3(100,-100,0),point3(100,100,0),point3(-100,100,0),materia));
    scene.surfaces.append(Surface(point3(-100,-100,100),point3(-100,100,100),point3(100,-100,100),materia));
    scene.surfaces.append(Surface(point3(100,-100,100),point3(-100,100,100),point3(100,100,100),materia));
    materia.roughness=0.001;
    scene.surfaces.append(Surface(point3(100,100,0),point3(100,100,100),point3(-100,100,0),materia));
    scene.surfaces.append(Surface(point3(-100,100,100),point3(-100,100,0),point3(100,100,100),materia));
    scene.surfaces.append(Surface(point3(100,-100,0),point3(-100,-100,0),point3(100,-100,100),materia));
    scene.surfaces.append(Surface(point3(-100,-100,100),point3(100,-100,100),point3(-100,-100,0),materia));
    scene.surfaces.append(Surface(point3(100,100,0),point3(100,-100,100),point3(100,100,100),materia));
    scene.surfaces.append(Surface(point3(100,100,0),point3(100,-100,0),point3(100,-100,100),materia));
    scene.surfaces.append(Surface(point3(-100,100,0),point3(-100,100,100),point3(-100,-100,100),materia));
    scene.surfaces.append(Surface(point3(-100,100,0),point3(-100,-100,100),point3(-100,-100,0),materia));
//球
    materia.roughness=0.0;
    materia.color = vec3(255,0,0);
    scene.balls.append(Ball(point3(-50,40,30),30,materia));
//光源
    QVector<Ball> lightSrcVec;

    materia.intensity=0.8;
    materia.roughness=1.0;
    materia.color = vec3(255,255,255);
    lightSrcVec.append(Ball(point3(0,0,15),15,materia));

    scene.setBallLightSrc(lightSrcVec);

    if(ui->wholeViewOnly->isChecked()){
        QImage wholeViewImage(360,180,QImage::Format_RGB888);
#pragma omp parallel num_threads(thread_count)
        {
#pragma omp for
            for(int fi=-180;fi<180;fi++){
                for(int theta=-90;theta<90;theta++){
                    vec3 colorPerRay(0,0,0);
                    float intensityPerRay=0;
                    int x=fi+180;
                    int y=89-theta;
                    vec3 rayDirection;
                    for(int i=0;i<rayPerPixel;i++){
                        float move = (float)(rand()%100)/100.0;
                        rayDirection.setByPolarCor(vec3(((float)fi+move)/360.0*2*Pi,((float)theta+move)/360.0*2*Pi,1.0));
                        Ray ray(camera.cameraPlace,rayDirection);
                        HitRecord rayHit = scene.RayTraceHit(ray,maxBumpTime);
                        if(rayHit.isUsable()){
                            colorPerRay += rayHit.materia.color;
                            intensityPerRay+=rayHit.materia.intensity;
                        } else {
                            float t = abs(ray.direction.z);
                            colorPerRay += vec3((1-t)*255+t*128,(1-t)*255+t*179,(1-t)*255+t*255);
                            intensityPerRay+=1.0;
                        }
                    }
                    vec3 color = vec3ColorVerify(colorPerRay/(float)rayPerPixel*(float)intensityPerRay/(float)rayPerPixel);
                    wholeViewImage.setPixelColor(x,y,QColor(color.x,color.y,color.z));
                }
                processed++;
                printf("%f%\n",(float)processed*100.0/360.0),fflush(stdout);
            }
        }
        wholeViewImage.save("C:\\Users\\MSI-PC\\Desktop\\WholeView.bmp","bmp",100);
        ui->wholeView->setPixmap(QPixmap::fromImage(wholeViewImage));
    } else{
# pragma omp parallel num_threads(thread_count)
    {
    Ray ray;
    HitRecord hitRecord;
#pragma omp for
        for(int x=0;x<width;x++){
            for(int y=0;y<height;y++){
                vec3 colorPerRay(0,0,0);
                float intensityPerRay=0;
                for(int i=0;i<rayPerPixel;i++){
                    float move = (float)(rand()%100)/100.0;
                    ray = camera.getRay(((float)x+move)/(float)width,((float)y+move)/(float)height);
                    HitRecord rayHit = scene.RayTraceHit(ray,maxBumpTime);
                    if(rayHit.isUsable()){
                        colorPerRay += rayHit.materia.color;
                        intensityPerRay+=rayHit.materia.intensity;
                    } else {
                        float t = abs(ray.direction.z);
                        colorPerRay += vec3((1-t)*255+t*128,(1-t)*255+t*179,(1-t)*255+t*255);
                        intensityPerRay+=1.0;
                    }
                }
                vec3 color = vec3ColorVerify(colorPerRay/(float)rayPerPixel*(float)intensityPerRay/(float)rayPerPixel);
                traceImage.setPixelColor(x,y,QColor(color.x,color.y,color.z));
            }
            processed++;
            printf("%f%\n",(float)processed*100.0/(float)width),fflush(stdout);
        }
    }
    traceImage.save("C:\\Users\\MSI-PC\\Desktop\\RayTracing.bmp","bmp",100);
    ui->displayArea->setPixmap(QPixmap::fromImage(traceImage));
    ui->displayArea->setGeometry((1600-width)/2,(900-height)/2,width,height);
    }
}

