//
//  Floor.h
//  LibGairP
//
//  Created by Silencer on 1/1/14.
//  Copyright (c) 2014 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_Floor_h
#define LibGairP_Floor_h

#include "Rectangle.h"

class Floor : public DrawableObject {
private:
    vector<Rectangle> rects;
    
public:
    Floor() {};
    Floor(int numberOfUnitsInWidth, int numberOfUnitsInHeight, double unitHeight, Vector4D cl, Material mt) {
        color = cl;
        material = mt;
        forinc(i,0,numberOfUnitsInWidth - 1)
        forinc(j,0,numberOfUnitsInHeight - 1) {
            Vector3D a = Vector3D(j * unitHeight - numberOfUnitsInHeight * unitHeight / 2,
                                0,i * unitHeight - numberOfUnitsInWidth * unitHeight / 2),
                    b = a + Vector3D(0, 0, unitHeight),
                    c = b + Vector3D(unitHeight,0,0),
                    d = c - Vector3D(0, 0, unitHeight);
            Rectangle rect = Rectangle(a, b, c, d);
            rect.color = color;
            rect.material = material;
            rects.push_back(rect);
        }
    }
    Floor(const Floor & f) : DrawableObject(f) {
        rects = f.rects;
    }
    Floor & operator = (const Floor & f) {
        DrawableObject::operator=(f);
        
        rects = f.rects;
        
        return *this;
    }
    void draw() {
        glPushMatrix();
        
        glMultMatrixf(transform.A());

        forinc(i, 0, rects.size()-1)
            rects[i].draw();
        
        glPopMatrix();
    }
};


#endif
