//
//  DrawableObject.h
//  LibGairP
//
//  Created by Silencer on 1/1/14.
//  Copyright (c) 2014 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_DrawableObject_h
#define LibGairP_DrawableObject_h

#include "Constants.h"
#include "Vector.h"
#include "Matrix.h"
#include "Ray.h"

typedef enum {
    MaterialTypeNone,
    MaterialTypeGold,
    MaterialTypeCopper,
    MaterialTypePolishedCopper,
    MaterialTypePolishedGold,
    MaterialTypeSilver,
    MaterialTypePewter
} MaterialTypes;

class Material;

class Material {
public:
    Vector4D ambient, diffuse, specular;
    GLfloat shiness;
    MaterialTypes materialType;
    Material(MaterialTypes type = MaterialTypeNone) {
        materialType = type;
        switch(materialType) {
            case MaterialTypeGold: {
                ambient = Vector4D(goldAmbient);
                diffuse = Vector4D(goldDiffuse);
                specular = Vector4D(goldSpecular);
                shiness = goldShiness[0];
                break;
            }
            case MaterialTypeCopper: {
                ambient = Vector4D(copperAmbient);
                diffuse = Vector4D(copperDiffuse);
                specular = Vector4D(copperSpecular);
                shiness = copperShiness[0];
                break;
            }
            case MaterialTypePewter: {
                ambient = Vector4D(PewterAmbient);
                diffuse = Vector4D(PewterDiffuse);
                specular = Vector4D(PewterSpecular);
                shiness = PewterShiness[0];
                break;
            }
            case MaterialTypePolishedCopper: {
                ambient = Vector4D(polishedCopperAmbient);
                diffuse = Vector4D(polishedCopperDiffuse);
                specular = Vector4D(polishedCopperSpecular);
                shiness = polishedCopperShiness[0];
                break;
            }
            case MaterialTypePolishedGold: {
                ambient = Vector4D(PolishedGoldAmbient);
                diffuse = Vector4D(PolishedGoldDiffuse);
                specular = Vector4D(PolishedGoldSpecular);
                shiness = PolishedGoldShiness[0];
                break;
            }
            case MaterialTypeSilver: {
                ambient = Vector4D(SilverAmbient);
                diffuse = Vector4D(SilverDiffuse);
                specular = Vector4D(SilverSpecular);
                shiness = SilverShiness[0];
                break;
            }
            case MaterialTypeNone: {
                ambient = Vector4D();
                diffuse = Vector4D();
                specular = Vector4D();
                shiness = 0.0;
            }
        }
    }
    Material(Vector4D ambient, Vector4D diffuse, Vector4D specular, GLfloat shiness) {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->shiness = shiness;
    }
    Material(const Material & p) {
        ambient = Vector4D(p.ambient.V());
        diffuse = Vector4D(p.diffuse.V());
        specular = Vector4D(p.specular.V());
        shiness = p.shiness;
        materialType = p.materialType;
    }
    
    Material & operator = (const Material & p) {
        ambient = Vector4D(p.ambient.V());
        diffuse = Vector4D(p.diffuse.V());
        specular = Vector4D(p.specular.V());
        shiness = p.shiness;
        materialType = p.materialType;
        return *this;
    }
};

class DrawableObject {
public:
    DrawableObject() { transform = Matrix4().identity(); center = Vector3D(); color = Vector4D(); material = Material(); reflection = 0; transparency = 0; }
    Matrix4 transform;
    Material material;
    Vector3D center;
    Vector4D color;
    GLfloat transparency, reflection;
    DrawableObject(const DrawableObject & t) {
        transform = t.transform;
        color = t.color;
        material = t.material;
        center = t.center;
        transparency = t.transparency;
        reflection = t.reflection;
    }
    DrawableObject & operator = (const DrawableObject & t) {
        
        transform = t.transform;
        color = t.color;
        material = t.material;
        center = t.center;
        transparency = t.transparency;
        reflection = t.reflection;
        
        return *this;
    }
    void rotate(double x, double y, double z) {
        Matrix4 mov = Matrix4().translationMatrix(center.x(), center.y(), center.z()),
        rot = Matrix4().identity().rotationMatrix(x, y, z),
        tra = mov.inverse() * rot * mov;
        transform = tra * transform;
    }
    void scale(double x, double y, double z) {
        Matrix4 mov = Matrix4().translationMatrix(center.x(), center.y(), center.z()),
        scl = Matrix4().identity().scaleMatrix(x, y, z),
        tra = mov.inverse() * scl * mov;
        transform = tra * transform;
    }
    void translate(double x, double y, double z) {
        Matrix4 mov = Matrix4().translationMatrix(x,y,z);
        transform = mov * transform;
    }
    void setMaterial() {
        glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient.V());
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse.V());
        glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular.V());
        glMaterialf(GL_FRONT, GL_SHININESS, material.shiness);
    }
    virtual void draw() {
        
    }
    virtual bool intersects(Ray & ray, Vector3D * p = NULL, Vector3D * normal = NULL) {
        return false;
    }
};

#endif
