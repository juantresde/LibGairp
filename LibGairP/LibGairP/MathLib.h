//
//  MathLib.h
//  LibGairP
//
//  Created by Silencer on 1/11/14.
//  Copyright (c) 2014 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_MathLib_h
#define LibGairP_MathLib_h

#include "Constants.h"
#include "Vector.h"
#include "Matrix.h"
#include "Light.h"
#include "Ray.h"


typedef enum {
    LightingModelPhong,
    LightingModelBlinPhong
} LightingModels;

GLfloat clamp(GLfloat value, GLfloat minVal = 0.0, GLfloat maxVal = 1.0) {
    return min(maxVal, max(minVal, value));
}

MatrixN matrixForVector(Vector3D & p) {
    MatrixN m = MatrixN(4,1);
    m[0] = p.x();
    m[1] = p.y();
    m[2] = p.z();
    m[3] = 1;
    return m;
}

Vector3D vectorFromMatrix(MatrixN & m) {
    return Vector3D(m[0], m[1], m[2]);
}

MatrixN translateToNormalTransformMatrix(MatrixN & matrix) {
    MatrixN m = MatrixN(matrix);
    forinc(i,0,matrix.M()-1) {
        double a = m.get(matrix.N()-1, i),
        b = m.get(i, matrix.M()-1);
        m.set(matrix.N() - 1, i, b);
        m.set(i,matrix.M() - 1, a);
    }
    return m;
}

Vector3D convertVectorToObjectSpace(Vector3D p, Matrix4 m) {
    Matrix4 transform = translateToNormalTransformMatrix(m);
    MatrixN matrixVector = matrixForVector(p);
    MatrixN mat = transform * matrixVector;
    return vectorFromMatrix(mat);
}

Vector3D reflect(Vector3D L, Vector3D N) {
    return L - N * 2 * L.dotProduct(N);
}

GLfloat mix(const GLfloat &a, const GLfloat &b, const GLfloat &mix)
{
	return b * mix + a * (GLfloat(1) - mix);
}

bool nearlyEqual(GLfloat a, GLfloat b) {
    GLfloat absA = fabs(a), absB = fabs(b), dif = fabs(a - b);
    if (a == 0 || b == 0 || dif < EPS) {
        return dif < EPS;
    }
    else
        return dif / (absA + absB) < EPS;
}

bool rayIntersectsPlane(const Ray & ray, const Vector3D & N, const Vector3D & P, Vector3D * V) {
    GLfloat NDotD = ray.dir.dotProduct(N);
    GLfloat numerator = P.dotProduct(N) - ray.dest.dotProduct(N);
    if (fabs(NDotD) < EPS) {
        if (fabs(numerator) < EPS) {
            if (V)
                *V = Vector3D(P);
            return true;
        }
        else {
            return false;
        }
    }
    GLfloat t = numerator / NDotD;
    
    if (t < EPS) {
        return false;
    }
    if (V)
        *V = ray.dest + ray.dir * t;
    
    return true;
}

GLfloat areaOfTriangle(Vector3D a, Vector3D b, Vector3D c) {
    Vector3D ab = b - a, ac = c-a;
    return ab.crossProduct(ac).length();
}

GLfloat areaOfRectangle(Vector3D a, Vector3D b, Vector3D c, Vector3D d) {
    return areaOfTriangle(a, b, c) + areaOfTriangle(b, c, d);
}


bool triangleContainsPoint(Vector3D & a, Vector3D & b, Vector3D & c, Vector3D & p) {
    GLfloat area = areaOfTriangle(a, b, c);
    GLfloat tempArea = areaOfTriangle(p, a, b) +
                       areaOfTriangle(p, b, c) +
                       areaOfTriangle(p, c, a);
    
    return nearlyEqual(area, tempArea);
}
        
bool rectangleContainsPoint(Vector3D & a, Vector3D & b, Vector3D & c, Vector3D & d, Vector3D & p) {
    GLfloat area = areaOfRectangle(a, b, c, d);
    GLfloat tempArea = areaOfTriangle(p, a, b) +
                       areaOfTriangle(p, b, c) +
                       areaOfTriangle(p, c, d) +
                       areaOfTriangle(p, d, a);
    
    return nearlyEqual(area, tempArea);
}


Vector4D colorToGreyScale(Vector4D color, double & greyscale) {
    double r = 0.2126 * color.x(), g = 0.7152 * color.y(), b = 0.0722 * color.z();
    greyscale = r + g + b;
    return Vector4D(r,g,b,1.0);
}

Vector4D phongLighingModelForColor(Vector3D V, Vector3D N, Vector4D color, vector<Light> & lightSources, Vector3D eyeCoordinate) {
    Vector4D finalColor = Vector4D();

    GLfloat shiness = 1.0;
    
    for (int i = 0; i < lightSources.size(); i++) {
		Light light = lightSources[i];
        Vector3D L = (light.position - V);
        Vector3D E = (V - eyeCoordinate).normalize();
        double attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * L.length() + light.quadraticAttenuation * L.length() * L.length());
        L.normalize();
        Vector4D diffuse = light.material.diffuse * max((GLfloat)0.0,L.dotProduct(N));
        Vector4D specular = light.material.specular * pow(max((reflect(L, N)).dotProduct(E), (GLfloat)0.0), shiness);
        finalColor += (light.material.ambient+ diffuse + specular) * attenuation;
    }
    
    finalColor.clamp();
    
    return finalColor;
}

Vector4D phongLighingModelForMaterial(Vector3D V, Vector3D N, Material material, vector<Light> & lightSources, Vector3D eyeCoordinate) {
    Vector4D finalColor = Vector4D(0,0,0,1);
    
    for (int i = 0; i < lightSources.size(); i++) {
		Light light = lightSources[i];
        Vector3D L = (light.position - V);
        Vector3D E = (V - eyeCoordinate).normalize();
        double attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * L.length() + light.quadraticAttenuation * L.length() * L.length());
        L.normalize();
        Vector4D diffuse = light.material.diffuse.scalarCombination(material.diffuse) * max((GLfloat)0.0,L.dotProduct(N));
        Vector4D specular = light.material.specular.scalarCombination(material.specular) * pow(max((reflect(L, N)).dotProduct(E), (GLfloat)0.0), material.shiness);
        finalColor += (light.material.ambient.scalarCombination(material.ambient) + diffuse + specular) * attenuation;
    }
    
    finalColor.clamp();
    
    return finalColor;
}

Vector4D blinPhongLightingModelForMaterial(Vector3D V, Vector3D N, Material material, vector<Light> & lightSources, Vector3D eyeCoordinate) {
    Vector4D finalColor = Vector4D();
    
    for (int i = 0; i < lightSources.size(); i++) {
        Light light = lightSources[i];
        Vector3D L = (light.position - V);
        Vector3D E = (V - eyeCoordinate);
        GLfloat distance = L.length() * L.length();
        L.normalize();
        
        GLfloat diffuseK = clamp(N.dotProduct(L));
        
        Vector3D H = (L + E).normalize();
        GLfloat specularK = pow(clamp(N.dotProduct(H)), material.shiness);
        
        Vector4D diffuse = light.material.diffuse.scalarCombination(material.diffuse) * diffuseK;
        Vector4D specular = light.material.specular.scalarCombination(material.specular) * specularK * material.shiness / distance;
        
        finalColor += (light.material.ambient.scalarCombination(material.ambient) + diffuse + specular);

    }
    
    return finalColor;
}

Vector4D blinPhongLightingModelForColor(Vector3D V, Vector3D N, Vector4D color, vector<Light> & lightSources, Vector3D eyeCoordinate) {
    Vector4D finalColor = Vector4D();
    GLfloat specularHardness = 2.0;
    
    for (int i = 0; i < lightSources.size(); i++) {
        Light light = lightSources[i];
        Vector3D L = (light.position - V);
        Vector3D E = (V - eyeCoordinate);
        GLfloat distance = L.length() * L.length();
        L.normalize();
        
        GLfloat diffuseK = clamp(N.dotProduct(L));
        
        Vector3D H = (L + E).normalize();
        GLfloat specularK = pow(clamp(N.dotProduct(H)), specularHardness);
        
        Vector4D diffuse = light.material.diffuse * diffuseK;
        Vector4D specular = light.material.specular * specularK * specularHardness / distance;
        
        finalColor += (light.material.ambient + diffuse + specular);
        
    }
    
    return finalColor;
}

Vector4D colorWithLightingModelForMaterial(LightingModels lightingModel, Vector3D V, Vector3D N, Material material, vector<Light> & lightSources, Vector3D eyeCoordinate) {
    switch (lightingModel) {
        case LightingModelPhong:
            return phongLighingModelForMaterial(V, N, material, lightSources, eyeCoordinate);
            break;
        case LightingModelBlinPhong:
            return blinPhongLightingModelForMaterial(V, N, material, lightSources, eyeCoordinate);
            break;
    }
}

Vector4D colorWithLightingModelForColor(LightingModels lightingModel, Vector3D V, Vector3D N, Vector4D color, vector<Light> & lightSources, Vector3D eyeCoordinate) {
    switch (lightingModel) {
        case LightingModelPhong:
            return phongLighingModelForColor(V, N, color, lightSources, eyeCoordinate);
            break;
        case LightingModelBlinPhong:
            return blinPhongLightingModelForColor(V, N, color, lightSources, eyeCoordinate);
            break;
    }
}

Vector3D normalForTriangle(Vector3D a, Vector3D b, Vector3D c) {
    Vector3D ab = b - a, ac = c - a;
    Vector3D crossProduct = ab.crossProduct(ac);
    Vector3D normal = crossProduct.normalize();
    return normal;
}

#endif
