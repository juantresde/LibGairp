//
//  RayTracer.h
//  LibGairP
//
//  Created by Silencer on 1/22/14.
//  Copyright (c) 2014 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_RayTracer_h
#define LibGairP_RayTracer_h

#include "Constants.h"
#include "Camera.h"
#include "Ray.h"
#include "Image.h"

#include "MathLib.h"

const float offsetX [] = {0,0,0.5,0.5};
const float offsetY [] = {0,0.5,0,0.5};

class RayTracer {
public:
    int screenWidth, screenHeight;
    Image image;

    RayTracer() { }
    RayTracer(int sw, int sh) {
        screenWidth = sw;
        screenHeight = sh;
        image = Image(screenWidth, screenHeight);
    }
    
    RayTracer(const RayTracer & r) {
        screenWidth = r.screenWidth;
        screenHeight = r.screenHeight;
        image = r.image;
    }
    
    RayTracer & operator = (const RayTracer & r) {
        screenWidth = r.screenWidth;
        screenHeight = r.screenHeight;
        image = r.image;
        
        return *this;
    }
    
    ~RayTracer() { }
    
    Vector4D trace(Ray & ray,vector<DrawableObject*> & objects, Camera & camera, vector<Light> & lightSources, int depth) {
        GLfloat minDist = INF;
        int inObjectIndex = NotFound;
        Vector3D inP, inNormal;
        
        forinc(k, 0, objects.size()-1) {
            Vector3D p1, p2, normal;
            if (objects[k]->intersects(ray,&p1,&normal)) {
                GLfloat curDist = (ray.dest - p1).length();
                if (minDist > curDist && !nearlyEqual(minDist, curDist)) {
                    minDist = curDist;
                    inObjectIndex = k;
                    inP = p1;
                    inNormal = normal;
                }
            }
        }
        
        if (inObjectIndex == NotFound)
            return lightSources[0].material.ambient;
        
        bool inside = false;
        if (ray.dir.dotProduct(inNormal) > 0) inNormal = -inNormal, inside = true;
        
        if ((objects[inObjectIndex]->reflection > 0) && depth < MaxDepth) {
            GLfloat facingratio = -ray.dir.dotProduct(inNormal);
            // change the mix value to tweak the effect
            GLfloat fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
            // compute reflection direction (not need to normalize because all vectors
            // are already normalized)
            Vector3D refldir = ray.dir - inNormal * 2 * ray.dir.dotProduct(inNormal);

            Ray reflectionRay = Ray(inP + inNormal, refldir.normalize());
            
            Vector4D reflection = trace(reflectionRay, objects, camera, lightSources, depth + 1);
            Vector4D refraction = Vector4D();
            
            if (objects[inObjectIndex]->transparency > 0) {
                GLfloat ior = 1.1, eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
                GLfloat cosi = -inNormal.dotProduct(ray.dir);
                GLfloat k = 1 - eta * eta * (1 - cosi * cosi);
                Vector3D refrdir = ray.dir * eta + inNormal * (eta *  cosi - sqrt(k));
                refrdir.normalize();
                
                Ray refractionRay = Ray(inP - inNormal, refrdir);
                
                refraction = trace(refractionRay, objects, camera, lightSources, depth + 1);
            }
            
            Vector4D surfaceColor;
            
            if (objects[inObjectIndex]->material.materialType == MaterialTypeNone) {
                surfaceColor = phongLighingModelForColor(inP, inNormal, objects[inObjectIndex]->color, lightSources, camera.eyePos);
            }
            else {
                surfaceColor = phongLighingModelForMaterial(inP, inNormal, objects[inObjectIndex]->material, lightSources, camera.eyePos);
            }
            
            return (reflection * fresneleffect +
                    surfaceColor * (1 - fresneleffect));
        }
        else { // it's a diffuse object
            bool isShadowed = false;
            
            forinc(i, 0, objects.size()-1) {
                if (i != inObjectIndex) {
                    Ray shadowRay = Ray(inP,(lightSources[0].position - inP).normalize());
                    Vector3D cP, cN;
                    if (objects[i]->intersects(shadowRay, &cP, &cN)) {
                        isShadowed = true;
                        break;
                    }
                }
            }
            if (!isShadowed) {
                if (objects[inObjectIndex]->material.materialType == MaterialTypeNone) {
                    return phongLighingModelForColor(inP, inNormal, objects[inObjectIndex]->color, lightSources, camera.eyePos);
                }
                else {
                    return phongLighingModelForMaterial(inP, inNormal, objects[inObjectIndex]->material, lightSources, camera.eyePos);
                }
            }
                else {
                    return lightSources[0].material.ambient;
            }
        }
        
        return Vector4D(0,0,0,1);
    }

    void render(vector<DrawableObject*> & objects, Camera & camera, vector<Light> & lightSources) {
        double pointSize = 0.2;
        glPointSize(pointSize);

        forinc(i, 1, camera.height) {
            forinc(j, 1, camera.width) {
                //int index = ((camera.height - i) * screenWidth + j - 1) * 3;
                Vector4D color = Vector4D();
                
                forinc(t, 0, 3) {
                    Ray ray = camera.getRay(i + offsetX[t], j + offsetY[t]);
                    color += trace(ray, objects, camera, lightSources, 1);
                }
                
                color /= 4.0;
                
                image.setPixel(i, j, color.V());
            }
        }
        
        glDrawPixels(screenWidth,screenHeight,GL_RGB,GL_FLOAT,image.pixelData);

    }
};

#endif
