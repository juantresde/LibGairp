//
//  NGone.h
//  LibGairP
//
//  Created by Silencer on 1/1/14.
//  Copyright (c) 2014 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_NGone_h
#define LibGairP_NGone_h

#include "Constants.h"
#include "Rectangle.h"
#include "Triangle.h"

class NGone : public DrawableObject {
private:
    vector<Polygon> polygons;
    
public:
    NGone() {};
    NGone(int numberOfEdges, int numberOfUnitsInBottom, double bottomUnitLength, int numberOfUnitsInHeight, double unitHeight, Vector4D cl, Material mt) {
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
            forinc(j,0,numberOfUnitsInHeight-1) {
                double curHeight = unitHeight * j;
                double nextRadAngle = radAngle + AngleToRadian(angleStep);
                Vector3D a = Vector3D(bottomRadius * cos(radAngle),
                                    curHeight,bottomRadius * sin(radAngle)),
                b = Vector3D(bottomRadius * cos(nextRadAngle),
                            curHeight,bottomRadius * sin(nextRadAngle)),
                c = a + Vector3D(0,unitHeight,0),
                d = b + Vector3D(0,unitHeight,0);
                
                Rectangle rect = Rectangle(a, c , d, b);
                rect.color = color;
                rect.material = material;
                polygons.push_back(rect);
            }
        }
        
        //top bolygons
        forinc(i, 0, numberOfEdges-1) {
            double radAngle = AngleToRadian(angleStep * i);
            forinc(j,0,numberOfUnitsInBottom-1) {
                double curBottomRadius = bottomUnitLength * (j + 1);
                double nextRadAngle = radAngle + AngleToRadian(angleStep);
                if (j == 0) {
                    Vector3D a = Vector3D(curBottomRadius * cos(radAngle),
                                        height,curBottomRadius * sin(radAngle)),
                    b = Vector3D(curBottomRadius * cos(nextRadAngle),
                                height,curBottomRadius * sin(nextRadAngle));
                    Triangle tr = Triangle(Vector3D(0,height,0), b, a);
                    tr.color = color;
                    tr.material = material;
                    polygons.push_back(tr);
                    center += a;
                }
                else {
                    double prevBottomRadius = bottomUnitLength * j;
                    Vector3D a = Vector3D(curBottomRadius * cos(radAngle),
                                        height,curBottomRadius * sin(radAngle)),
                    b = Vector3D(curBottomRadius * cos(nextRadAngle),
                                height,curBottomRadius * sin(nextRadAngle)),
                    c = Vector3D(prevBottomRadius * cos(radAngle),
                                height,prevBottomRadius * sin(radAngle)),
                    d = Vector3D(prevBottomRadius * cos(nextRadAngle),
                                height,prevBottomRadius * sin(nextRadAngle));
                    Rectangle rect = Rectangle(a, c , d, b);
                    rect.color = color;
                    rect.material = material;
                    polygons.push_back(rect);
                }
            }
        }
        center /= 2.0 * numberOfEdges;
    }
    NGone(const NGone & f) : DrawableObject(f) {
        polygons = f.polygons;
    }
    NGone & operator = (const NGone & f) {
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
