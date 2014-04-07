//
//  Vector.h
//  LibGairP
//
//  Created by Silencer on 12/26/13.
//  Copyright (c) 2013 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef __LibGairP__Vector__
#define __LibGairP__Vector__

#include "Constants.h"

const int MaxVectorLength = 4;

class VectorN {
protected:
    int n;
    GLfloat v[MaxVectorLength];
    void initialise() {
        forinc(i,0,n-1)
            v[i] = 0;
    }
public:
    VectorN(int size = 2) : n(size) { initialise(); }
    VectorN(const VectorN & p) {
		n = p.n;
        forinc(i,0,n-1)
            v[i] = p.v[i];
    }
    int size() { return n; }
    const GLfloat * V() const { return v; }
    bool isEqual(const VectorN & p) {
        if (p.n != n)
            return false;
        
        forinc(i ,0 , n-1)
        if (p.V()[i] != v[i])
            return false;
        
        return true;
    }
    GLfloat length() const {
        GLfloat squaredLength = 0;
        forinc(i,0,n-1)
            squaredLength += v[i] * v[i];
        return sqrt(squaredLength);
    }
    VectorN & normalize() {
        GLfloat len = length();
        (*this) /= len;
        return *this;
    }
    void clamp(GLfloat lower = 0.0, GLfloat higher = 1.0) {
        forinc(i, 0, n-1)
            v[i] = max(lower,min(higher, v[i]));
    }
    GLfloat dotProduct(const VectorN & p) const {
        GLfloat dotProduct = 0;
        for (int i = 0; i < min(n,p.n); i++)
            dotProduct += v[i] * p.v[i];
        return dotProduct;
    }
    GLfloat distanceBetweenVectors(const VectorN & p) const {
        VectorN C = *this - p;
        return C.length();
    }
    VectorN & operator = (const VectorN & p) {
        initialise();
        n = p.n;
        forinc(i,0,n-1)
            v[i] = p.v[i];
        return *this;
    }
    GLfloat & operator[](int index) {
        return v[index];
    }
    VectorN & operator - () {
        (*this) *= -1;
        return *this;
    }
    VectorN & operator *= (GLfloat k) {
        forinc(i,0,n-1)
            v[i] *= k;
        return *this;
    }
    VectorN & operator /= (GLfloat k) {
        forinc(i,0,n-1)
            v[i] /= k;
        return *this;
    }
    VectorN & operator += (const VectorN & p) {
        for (int i = 0; i < min(n,p.n); i++)
            v[i] += p.v[i];
        return *this;
    }
    VectorN & operator -= (const VectorN & p) {
        for (int i = 0; i < min(n,p.n); i++)
            v[i] -= p.v[i];
        return *this;
    }
    VectorN operator + (const VectorN & p) const {
        VectorN point = VectorN(*this);
        point += p;
        return point;
    }
    VectorN operator - (const VectorN & p) const {
        VectorN point = VectorN(*this);
        point -= p;
        return point;
    }
    VectorN operator * (GLfloat k) const {
        VectorN point = VectorN(*this);
        point *= k;
        return point;
    }
    VectorN operator / (GLfloat k) const {
        VectorN point = VectorN(*this);
        point /= k;
        return point;
    }
    void printDescription() const {
        printf("VectorN of size %d [",n);
        forinc(i,0,n-1) {
            if (i != 0)
                printf(", ");
            printf("%6.6lf",v[i]);
        }
        printf("]\n");
    }
};

class Vector3D : public VectorN {
public:
    Vector3D() : VectorN(3) {}
    Vector3D(GLfloat x, GLfloat y, GLfloat z) : VectorN(3) { v[0] = x; v[1] = y; v[2] = z; }
    Vector3D(const GLfloat p[3]) {
        n = 3;
        initialise();
        forinc(i, 0, n-1)
            v[i] = p[i];
    }
    GLfloat & x() { return v[0]; }
    GLfloat & y() { return v[1]; }
    GLfloat & z() { return v[2]; }
    Vector3D crossProduct(Vector3D & p) const {
        Vector3D point = Vector3D();
        
        point.x() = v[1] * p.z() - v[2] * p.y();
        point.y() = v[2] * p.x() - v[0] * p.z();
        point.z() = v[0] * p.y() - v[1] * p.x();

        return point;
    }
    Vector3D scalarCombination(Vector3D & p) const {
        Vector3D sc = Vector3D();
        
        forinc(i, 0, n-1)
            sc[i] = v[i] * p[i];
        
        return sc;
    }
    Vector3D & normalize() {
        GLfloat len = length();
        (*this) /= len;
        return *this;
    }
    Vector3D & operator = (const Vector3D & p) {
        initialise();
        n = p.n;
        forinc(i,0,n-1)
            v[i] = p.v[i];
        return *this;
    }
    Vector3D & operator - () {
        (*this) *= -1;
        return *this;
    }
    Vector3D & operator *= (GLfloat k) {
        forinc(i,0,n-1)
            v[i] *= k;
        return *this;
    }
    Vector3D & operator /= (GLfloat k) {
        forinc(i,0,n-1)
            v[i] /= k;
        return *this;
    }
    Vector3D & operator += (const Vector3D & p) {
        for (int i = 0; i < min(n,p.n); i++)
            v[i] += p.v[i];
        return *this;
    }
    Vector3D & operator -= (const Vector3D & p) {
        for (int i = 0; i < min(n,p.n); i++)
            v[i] -= p.v[i];
        return *this;
    }
    Vector3D operator + (const Vector3D & p) const {
        Vector3D point = Vector3D(*this);
        point += p;
        return point;
    }
    Vector3D operator - (const Vector3D & p) const {
        Vector3D point = Vector3D(*this);
        point -= p;
        return point;
    }
    Vector3D operator * (GLfloat k) const {
        Vector3D point = Vector3D(*this);
        point *= k;
        return point;
    }
    Vector3D operator / (GLfloat k) const {
        Vector3D point = Vector3D(*this);
        point /= k;
        return point;
    }
    void printDescription() const {
        printf("Vector3D [");
        forinc(i,0,n-1) {
            if (i != 0)
                printf(", ");
            printf("%6.6lf",v[i]);
        }
        printf("]\n");
    }
};

class Vector4D : public VectorN {
public:
    Vector4D() : VectorN(4) {}
    Vector4D(GLfloat x, GLfloat y, GLfloat z,GLfloat d) : VectorN(4) { v[0] = x; v[1] = y; v[2] = z; v[3] = d; }
    Vector4D(const GLfloat p[4]) {
        n = 4;
        initialise();
        forinc(i, 0, n-1)
            v[i] = p[i];
    }
    
    GLfloat & x() { return v[0]; }
    GLfloat & y() { return v[1]; }
    GLfloat & z() { return v[2]; }
    GLfloat & d() { return v[3]; }
    
    Vector4D & normalize() {
        GLfloat len = length();
        (*this) /= len;
        return *this;
    }
    Vector4D scalarCombination(Vector4D & p) const {
        Vector4D sc = Vector4D();
        
        forinc(i, 0, n-1)
            sc[i] = v[i] * p[i];
        
        return sc;
    }
    Vector4D & operator = (const Vector4D & p) {
        initialise();
        n = p.n;
        forinc(i,0,n-1)
        v[i] = p.v[i];
        return *this;
    }
    Vector4D & operator - () {
        (*this) *= -1;
        return *this;
    }
    Vector4D & operator *= (GLfloat k) {
        forinc(i,0,n-1)
        v[i] *= k;
        return *this;
    }
    Vector4D & operator /= (GLfloat k) {
        forinc(i,0,n-1)
        v[i] /= k;
        return *this;
    }
    Vector4D & operator += (const Vector4D & p) {
        for (int i = 0; i < min(n,p.n); i++)
            v[i] += p.v[i];
        return *this;
    }
    Vector4D & operator -= (const Vector4D & p) {
        for (int i = 0; i < min(n,p.n); i++)
            v[i] -= p.v[i];
        return *this;
    }
    Vector4D operator + (const Vector4D & p) const {
        Vector4D point = Vector4D(*this);
        point += p;
        return point;
    }
    Vector4D operator - (const Vector4D & p) const {
        Vector4D point = Vector4D(*this);
        point -= p;
        return point;
    }
    Vector4D operator * (GLfloat k) const {
        Vector4D point = Vector4D(*this);
        point *= k;
        return point;
    }
    Vector4D operator / (GLfloat k) const {
        Vector4D point = Vector4D(*this);
        point /= k;
        return point;
    }
    void printDescription() const {
        printf("Vector4D [");
        forinc(i,0,n-1) {
            if (i != 0)
                printf(", ");
            printf("%6.6lf",v[i]);
        }
        printf("]\n");
    }
};

#endif /* defined(__LibGairP__Vector__) */
