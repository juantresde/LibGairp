//
//  Ray.h
//  LibGairP
//
//  Created by Silencer on 1/22/14.
//  Copyright (c) 2014 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_Ray_h
#define LibGairP_Ray_h

#include "constants.h"
#include "Vector.h"

class Ray {
public:
    Vector3D dest, dir;// destination, dirrection
    Ray() { dest = Vector3D(), dir = Vector3D(); }
    Ray(Vector3D de, Vector3D di) { dest = de, dir = di; }
    
    Ray(const Ray & r) {
        dest = r.dest;
        dir = r.dir;
    }
    
    Ray & operator = (const Ray & r) {
        dest = r.dest;
        dir = r.dir;
        return *this;
    }
    void printDescription() const {
        dest.printDescription();
        dir.printDescription();
    }
};

#endif
