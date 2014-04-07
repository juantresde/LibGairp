//
//  Rectangle.h
//  LibGairP
//
//  Created by Silencer on 1/1/14.
//  Copyright (c) 2014 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_Rectangle_h
#define LibGairP_Rectangle_h

#include "Constants.h"
#include "Vector.h"
#include "Polygon.h"
#include "MathLib.h"

class Rectangle : public Polygon {
public:
    Rectangle() : Polygon(4) { }
    Rectangle(Vector3D a, Vector3D b, Vector3D c, Vector3D d) : Polygon(4) {
        points[0] = a;
        points[1] = b;
        points[2] = c;
        points[3] = d;
        center = (a + b + c + d) / 4;
    }
    Rectangle(const Rectangle & r) : Polygon(r) {}
    Rectangle & operator = (const Rectangle & p) {
        Polygon::operator=(p);
        return *this;
    }
    Vector3D & a() { return points[0]; }
    Vector3D & b() { return points[1]; }
    Vector3D & c() { return points[2]; }
    Vector3D & d() { return points[3]; }
    
    bool intersects(Ray & ray, Vector3D * p = NULL, Vector3D * normal = NULL) {
        Vector3D V;
        Vector3D N = normalForTriangle(a(), b(), c());
        
        if (rectangleContainsPoint(a(), b(), c(), d(), ray.dest))
            return false;
        
        if (rayIntersectsPlane(ray, N, center, &V)) {
            if (rectangleContainsPoint(a(), b(), c(), d(), V)) {
                if (p)
                    *p = Vector3D(V);
                if (normal)
                    *normal = Vector3D(N);
                return true;
            }
            else {
                return false;
            }
        }
        return false;
    }
};

#endif
