//
//  Image.h
//  LibGairP
//
//  Created by Silencer on 2/3/14.
//  Copyright (c) 2014 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_Image_h
#define LibGairP_Image_h

#include <iostream>
#include <fstream>
#include "Constants.h"

class Image {
public:
    GLfloat * pixelData;
    int width, height;
    Image() { pixelData = NULL; width = height = 0; }
    Image(int w, int h)  {
        width = w;
        height = h;
        pixelData = new GLfloat[width * height * 3];
    }
    ~Image() { if (pixelData) delete [] pixelData; }
    Image(const Image & image) {
        width = image.width;
        height = image.height;
        if (pixelData) delete [] pixelData;
        pixelData = new GLfloat[width * height * 3];
        forinc(i, 0,width * height-1)
        pixelData[i] = image.pixelData[i];
    }
    Image & operator = (const Image & image) {
        width = image.width;
        height = image.height;
        if (pixelData) delete [] pixelData;
        pixelData = new GLfloat[width * height * 3];
        forinc(i, 0,width * height-1)
            pixelData[i] = image.pixelData[i];
        return *this;
    }
    void setPixel(int i, int j, GLfloat r, GLfloat g, GLfloat b) {
        pixelData[(i * width + j) * 3 + 0] = r;
        pixelData[(i * width + j) * 3 + 1] = g;
        pixelData[(i * width + j) * 3 + 2] = b;
    }
    void setPixel(int i, int j, const GLfloat * c) {
        pixelData[(i * width + j) * 3 + 0] = c[0];
        pixelData[(i * width + j) * 3 + 1] = c[1];
        pixelData[(i * width + j) * 3 + 2] = c[2];
    }
    void saveToPpm(const char *filename)
    {
        float gamma = 1;
        std::ofstream ofs;
        ofs.open(filename);
        ofs << "P6\n" << width << " " << height << "\n255\n";
        float *pixel = pixelData;
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                unsigned char r = (unsigned char)(std::max(0.f, std::min(255.f, powf(pixel[0], 1 / gamma) * 255 + 0.5f)));
                unsigned char g = (unsigned char)(std::max(0.f, std::min(255.f, powf(pixel[1], 1 / gamma) * 255 + 0.5f)));
                unsigned char b = (unsigned char)(std::max(0.f, std::min(255.f, powf(pixel[2], 1 / gamma) * 255 + 0.5f)));
                ofs << r << g << b;
                pixel += 3;
            }
        }
        ofs.close();
    }
};

#endif
