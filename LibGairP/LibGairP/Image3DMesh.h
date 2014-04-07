//
//  Image3DMesh.h
//  LibGairP
//
//  Created by Silencer on 1/6/14.
//  Copyright (c) 2014 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_Image3DMesh_h
#define LibGairP_Image3DMesh_h

#include "Constants.h"
#include "DrawableObject.h"
#include "Triangle.h"
#include "stb_image.c"
#include "Light.h"
#include "MathLib.h"

class Image3DMesh : public DrawableObject {
private:
    unsigned char * imageData;
    int width, height;
    double pointSize;
    vector<Vector3D> points, normals;
    vector<Vector4D> colors;
public:
    Image3DMesh() {}
    Image3DMesh(const char * filename) {
        imageData = stbi_load(filename, &width, &height, NULL, 0);
		if (imageData == NULL)
			width = 0, height = 0;
        pointSize = 0.02;
        
        double x = -width / 2 * pointSize, y = -height/2 * pointSize, z = 0;

        forinc(i, 0, height-1)
            forinc(j, 0, width-1) {
                int index = 3 * ((height - i - 1) * width + j);
                Vector4D color = Vector4D(imageData[index] / 255.0,imageData[index+1] / 255.0,imageData[index+2] / 255.0, 1.0);
                double greyScale;
                Vector4D greyScaleColor = colorToGreyScale(color, greyScale);
                Vector3D point = Vector3D(x + j * pointSize, y + i * pointSize, z + greyScale * pointSize * 10.0);
                colors.push_back(greyScaleColor);
                points.push_back(point);
            }
        
        Vector3D a,b,c,d;
        vector< vector<Vector3D> > norms(width * height);
        
        for (int i = 0 ; i < height - 1; i++) {
            for (int j = 0; j < width ; j++) {
                int ai = i * width + j,
                    bi = i * width + j + 1,
                    ci = (i + 1) * width + j + 1,
                    di = (i + 1) * width + j;
                Vector3D a = points[ai],
                         b = points[bi],
                         c = points[ci],
                         d = points[di];
                Triangle abd = Triangle(a,b,d),
                         bcd = Triangle(b,c,d);
                Vector3D abdn = abd.surfaceNormal(),
                         bcdn = bcd.surfaceNormal();
                
                norms[ai].push_back(abdn);
                norms[bi].push_back(abdn);
                norms[di].push_back(abdn);
                norms[bi].push_back(bcdn);
                norms[ci].push_back(bcdn);
                norms[di].push_back(bcdn);
            }
        }
        
        forinc(i, 0, height-1)
        forinc(j, 0, width-1) {
            Vector3D normal = Vector3D();
            forinc(t, 0, norms[i * width + j].size()-1)
                normal += norms[i * width + j][t];
            
            //normal /= (double)norms[i * width + j].size();
            normal.normalize();
            normals.push_back(normal);
        }
    }
    int getWidth() { return width * pointSize; }
    int getHeight() { return height * pointSize; }

    void draw() {
        glPushMatrix();
        glMultMatrixf(transform.A());
        
        glPointSize(pointSize);
        
        if (material.materialType == MaterialTypeNone) {
            glEnable(GL_COLOR_MATERIAL);
        }
        else {
            setMaterial();
        }
        
        for (int i = 0 ; i < height - 1; i++) {
            glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j < width ; j++) {
                int index = i * width + j;
                glNormal3fv(normals[index].V());
                glColor3fv(colors[index].V());
                glVertex3fv(points[index].V());
                index = (i + 1) * width + j;
                glNormal3fv(normals[index].V());
                glColor3fv(colors[index].V());
                glVertex3fv(points[index].V());
            }
            glEnd();
        }
        
        glDisable(GL_COLOR_MATERIAL);
        
        glPopMatrix();
    }
    
    void drawWithLightSources(LightingModels lightingModel, vector<Light> & lightSources, Vector3D eyeCoordinate) {
        glPushMatrix();
        
        glPointSize(pointSize);
        
        for (int i = 0 ; i < height - 1; i++) {
            glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j < width ; j++) {
                int index = i * width + j;
                Vector3D curVertex = points[index];
                Vector3D normal = normals[index];
                Vector4D color;
                if (material.materialType == MaterialTypeNone)
                    color = colorWithLightingModelForColor(lightingModel, curVertex, normal, colors[index], lightSources, eyeCoordinate);
                else
                    color = colorWithLightingModelForMaterial(lightingModel, curVertex, normal, material, lightSources, eyeCoordinate);
                glColor3fv(color.V());
                glVertex3fv(points[index].V());
                index = (i + 1) * width + j;
                curVertex = points[index];
                normal = normals[index];
                if (material.materialType == MaterialTypeNone)
                    color = colorWithLightingModelForColor(lightingModel, curVertex, normal, colors[index], lightSources, eyeCoordinate);
                else
                    color = colorWithLightingModelForMaterial(lightingModel, curVertex, normal, material, lightSources, eyeCoordinate);
                glColor3fv(color.V());
                glVertex3fv(points[index].V());
            }
            glEnd();
        }
        
        glPopMatrix();
    }
};

#endif
