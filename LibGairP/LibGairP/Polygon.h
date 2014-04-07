//
//  Polygon.h
//  LibGairP
//
//  Created by Giorgi Pataraia on 27/12/2013.
//  Copyright (c) 2013 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_Polygon_h
#define LibGairP_Polygon_h

#include "DrawableObject.h"

const int MaxPointCount = 4;

class Polygon : public DrawableObject {
protected:
    int n; // number of points
    Vector3D points[MaxPointCount];
    void initialise() {
        transform = Matrix4().identity();
    }
public:
    Polygon(int nVectors = 2) : n(nVectors) { initialise(); }
    Polygon(const Polygon & p) : DrawableObject(p) {
        n = p.n;
        forinc(i, 0, n-1)
            points[i] = Vector3D(p.points[i]);
    }
    Polygon & operator = (const Polygon & p) {
        DrawableObject::operator=(p);
        
        n = p.n;
        forinc(i, 0, n-1)
            points[i] = Vector3D(p.points[i]);
        
        return *this;
    }
    int size() const { return n; }
    void draw() {
        glPushMatrix();
        
        glMultMatrixf(transform.A());
        
        glLineWidth(2);
        if (material.materialType == MaterialTypeNone) {
            glEnable(GL_COLOR_MATERIAL);
            glColor3fv(color.V());
            glDisable(GL_COLOR_MATERIAL);
        }
        else
            setMaterial();
        
        glBegin(GL_POLYGON);
        forinc(i,0,n-1) {
            glNormal3fv(points[i].V());
            glVertex3fv(points[i].V());
        }
        glEnd();
//        
//        glColor3d(0, 0, 0);
//        glBegin(GL_LINE_LOOP);
//        forinc(i,0,n-1) {
//            glVertex3dv(points[i].V());
//        }
//        glEnd();
        
        glPopMatrix();
    }
};

#endif
