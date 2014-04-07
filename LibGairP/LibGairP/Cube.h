//
//  Cube.h
//  LibGairP
//
//  Created by Silencer on 1/2/14.
//  Copyright (c) 2014 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_Cube_h
#define LibGairP_Cube_h

#include "Constants.h"
#include "Vector.h"
#include "Rectangle.h"

class Cube : public DrawableObject {
public:
    vector<Polygon> polygons;
    Cube() {}
    Cube(double bottomWidth, double bottomHeight, double height, Vector4D cl, Material mt) {
        color = cl;
        material = mt;
        Vector3D a = Vector3D(-bottomWidth / 2, -height / 2, -bottomHeight / 2),
                b = a + Vector3D(0,0,bottomHeight),
                c = b + Vector3D(bottomWidth,0,0),
                d = c - Vector3D(0, 0, bottomHeight),
                e = d + Vector3D(0,height,0),
                f = e - Vector3D(bottomWidth, 0, 0),
                g = f + Vector3D(0,0,bottomHeight),
                h = g + Vector3D(bottomWidth, 0, 0);
        Rectangle rect = Rectangle(a,b,c,d);
        rect.color = color;
        rect.material = material;
        polygons.push_back(rect);
        
        rect = Rectangle(e,f,g,h);
        rect.color = color;
        rect.material = material;
        polygons.push_back(rect);
        
        rect = Rectangle(a,f,g,b);
        rect.color = color;
        rect.material = material;
        polygons.push_back(rect);
        
        rect = Rectangle(d,e,h,c);
        rect.color = color;
        rect.material = material;
        polygons.push_back(rect);
        
        rect = Rectangle(b,c,h,g);
        rect.color = color;
        rect.material = material;
        polygons.push_back(rect);
        
        rect = Rectangle(f,a,d,e);
        rect.color = color;
        rect.material = material;
        polygons.push_back(rect);
    }
    Cube(const Cube & c) : DrawableObject(c) {
        polygons = c.polygons;
    }
    Cube & operator = (const Cube & c) {
        DrawableObject::operator=(c);
        
        polygons = c.polygons;

        return *this;
    }
    void draw() {
        glPushMatrix();
        
        glMultMatrixf(transform.A());

        forinc(i, 0, polygons.size()-1)
        polygons[i].draw();
        
        glPopMatrix();
    }
};

#endif
