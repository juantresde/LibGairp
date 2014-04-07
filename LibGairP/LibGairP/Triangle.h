//
//  Triangle.h
//  LibGairP
//
//  Created by Giorgi Pataraia on 27/12/2013.
//  Copyright (c) 2013 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_Triangle_h
#define LibGairP_Triangle_h

#include "Vector.h"
#include "Polygon.h"
#include "MathLib.h"

class Triangle : public Polygon {
public:
    Triangle() : Polygon(3) { }
    Triangle(Vector3D a, Vector3D b, Vector3D c) : Polygon(3) {
        points[0] = a;
        points[1] = b;
        points[2] = c;
        center = (a + b + c) / 3;
    }
    Triangle(const Triangle & p) : Polygon(p) {}
    Triangle & operator = (const Triangle & p) {
        Polygon::operator=(p);
        return *this;
    }
    Vector3D & a() { return points[0]; }
    Vector3D & b() { return points[1]; }
    Vector3D & c() { return points[2]; }
    
    Vector3D surfaceNormal() {
        Vector3D ab = b() - a(),
                 ac = c() - a();
        Vector3D N = ab.crossProduct(ac);
        N.normalize();
        return N;
    }
    
    bool intersects(Ray & ray, Vector3D * p = NULL, Vector3D * normal = NULL) {
        Vector3D V;
        Vector3D N = normalForTriangle(a(), b(), c());
        
        if (triangleContainsPoint(a(), b(), c(), ray.dest))
            return false;
        
        if (rayIntersectsPlane(ray, N, center, &V)) {
            if (triangleContainsPoint(a(), b(), c(), V)) {
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
