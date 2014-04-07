//
//  Conus.h
//  LibGairP
//
//  Created by Silencer on 1/1/14.
//  Copyright (c) 2014 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_Conus_h
#define LibGairP_Conus_h

#include "Constants.h"
#include "Rectangle.h"
#include "Triangle.h"

class Conus : public DrawableObject {
private:
    vector<Polygon> polygons;
    
public:
    Conus() {};
    Conus(int numberOfEdges, int numberOfUnitsInBottom, double bottomUnitLength, int numberOfUnitsInHeight, double unitHeight, Vector4D cl, Material mt) {
        color = cl;
        material = mt;
        double bottomRadius = numberOfUnitsInBottom * bottomUnitLength;
        double height = numberOfUnitsInHeight * unitHeight;
        double angleStep = 360.0 / numberOfEdges;
        
        //bottom polygons
        forinc(i, 0, numberOfEdges-1) {
            double radAngle = AngleToRadian(angleStep * i);
            forinc(j,0,numberOfUnitsInBottom-1) {
                double curBottomRadius = bottomUnitLength * (j + 1);
                double nextRadAngle = radAngle + AngleToRadian(angleStep);
                if (j == 0) {
                    Vector3D a = Vector3D(curBottomRadius * cos(radAngle),
                                        0,curBottomRadius * sin(radAngle)),
                    b = Vector3D(curBottomRadius * cos(nextRadAngle),
                                0,curBottomRadius * sin(nextRadAngle));
                    Triangle tr = Triangle(Vector3D(), b, a);
                    tr.color = color;
                    tr.material = material;
                    polygons.push_back(tr);
                    center += a;
                }
                else {
                    double prevBottomRadius = bottomUnitLength * j;
                    Vector3D a = Vector3D(curBottomRadius * cos(radAngle),
                                        0,curBottomRadius * sin(radAngle)),
                    b = Vector3D(curBottomRadius * cos(nextRadAngle),
                                0,curBottomRadius * sin(nextRadAngle)),
                    c = Vector3D(prevBottomRadius * cos(radAngle),
                                0,prevBottomRadius * sin(radAngle)),
                    d = Vector3D(prevBottomRadius * cos(nextRadAngle),
                                0,prevBottomRadius * sin(nextRadAngle));
                    Rectangle rect = Rectangle(a, c , d, b);
                    rect.color = color;
                    rect.material = material;
                    polygons.push_back(rect);
                }
            }
        }
        
        //middle polygons
        forinc(i, 0, numberOfEdges-1) {
            double radAngle = AngleToRadian(angleStep * i);
            double nextRadAngle = radAngle + AngleToRadian(angleStep);
            forinc(j, 0, numberOfUnitsInHeight - 1) {
                double curHeight = unitHeight * j;
                double nextHeight = unitHeight * (j + 1);
                double curBottomRadius = bottomRadius * (height - curHeight) / height;
                double nextBottomRadius = bottomRadius * (height - nextHeight) / height;
                Vector3D a = Vector3D(curBottomRadius * cos(radAngle),
                                    curHeight, curBottomRadius * sin(radAngle)),
                        b = Vector3D(curBottomRadius * cos(nextRadAngle),
                                    curHeight, curBottomRadius * sin(nextRadAngle)),
                        c = Vector3D(nextBottomRadius * cos(radAngle),
                                    nextHeight, nextBottomRadius * sin(radAngle)),
                        d = Vector3D(nextBottomRadius * cos(nextRadAngle),
                                    nextHeight, nextBottomRadius * sin(nextRadAngle));
                Rectangle rect = Rectangle(a,c,d,b);
                rect.color = color;
                rect.material = material;
                polygons.push_back(rect);
            }
        }
        
        center /= numberOfEdges;
    }
    Conus(const Conus & f) : DrawableObject(f) {
        polygons = f.polygons;
    }
    Conus & operator = (const Conus & f) {
        DrawableObject::operator=(f);

        polygons = f.polygons;

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
