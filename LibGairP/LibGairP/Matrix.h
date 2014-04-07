//
//  Matrix.h
//  LibGairP
//
//  Created by Silencer on 12/27/13.
//  Copyright (c) 2013 Giorgi Pataraia LLC. A_ll rights reserved.
//

#ifndef LibGairP_Matrix_h
#define LibGairP_Matrix_h

#include "Constants.h"

const int maxN = 5;

class MatrixN {
protected:
    int n,m;
    GLfloat A_[maxN * maxN], inv[maxN * maxN];
    bool isDetCalculated, isCalculatedInv;
    GLfloat calculatedDet;
    void initialise() {
		isDetCalculated = false;
		isCalculatedInv = false;
        forinc(i,0,n * m -1)
                A_[i] = 0;
    }
    int indForPair(int i, int j) {
        return indexForPair(i, j, n, m);
    }
public:
	MatrixN() { }
    MatrixN(int rows, int columns) : n(rows), m(columns) { initialise(); }
    MatrixN(const MatrixN & mx) : n(mx.n),m(mx.m) {
        initialise();
        forinc(i,0,n * m - 1)
           A_[i] = mx.A_[i];
    }
    MatrixN(int rows,int columns, const GLfloat * p) : n(rows),m(columns) {
		initialise();
        forinc(i,0,n * m - 1)
            A_[i] = p[i];
    }
    ~MatrixN() {
        
    }
    int N() { return n; }
    int M() { return m; }
    const GLfloat* A() const { return A_; }
    GLfloat get(int i, int j) const {
        return A_[i * m + j];
    }
    void set(int i, int j, GLfloat v) {
        A_[indForPair(i, j)] = v;
        isDetCalculated = false;
        isCalculatedInv = false;
    }
    MatrixN identity() {
        MatrixN mx = MatrixN(n,m);
        forinc(i, 0, n-1)
            forinc(j, 0, m-1)
                mx.set(i, j ,i == j ? 1 : 0);
        return mx;
    }
    MatrixN cofactor(int i, int j) {
        MatrixN C = MatrixN(n-1,m-1);
        forinc(ii,0,n-1)
        forinc(jj,0,m-1) {
            int curi = ii < i ? ii : ii + 1;
            int curj = jj < j ? jj : jj + 1;
            C.set(ii, jj, get(curi,curj));
        }
        return C;
    }
    GLfloat determinant() {
        if (isDetCalculated)
            return calculatedDet;
        isDetCalculated = true;
        calculatedDet = 0;
        
        if (n == m && n == 1) {
            calculatedDet = get(0,0);
        }
        else {
            forinc(i, 0, m-1) {
                if (get(0,i) != 0) {
                    MatrixN cof = cofactor(0, i);
                    calculatedDet += cof.determinant() * get(0,i) * ((0 + i) % 2 == 0 ? 1 : -1);
                }
            }
        }
        return calculatedDet;
    }
    MatrixN inverse() {
        if (isCalculatedInv) {
            return MatrixN(n,m,inv);
        }
        
        isCalculatedInv = true;
        MatrixN cofs = MatrixN(n,m);
        
        if (determinant() == 0) {
            cofs = cofs.identity();
        }
        else {
            forinc(i,0,n-1)
            forinc(j,0,m-1) {
                cofs.set(i, j, cofactor(i, j).determinant() * ((i + j) % 2 == 0 ? 1 : -1));
            }
        }
        
        cofs = cofs.transpose() / determinant();
        forinc(i,0,n * m - 1)
            inv[i] = cofs.A_[i];
        
        return cofs;
    }
    MatrixN transpose() {
        MatrixN C = MatrixN(m,n);
        forinc(i,0,n-1)
        forinc(j,0,m-1) {
            C.set(i, j, get(j,i));
        }
        return C;
    }
    GLfloat & operator [] (int index) {
        return A_[index];
    }
    MatrixN & operator = (const MatrixN & mx) {
        n = mx.n;
        m = mx.m;
		initialise();
        forinc(i,0,n-1)
            forinc(j,0,m-1)
                set(i, j, mx.get(i,j));
        return *this;
    }
    MatrixN & operator *= (GLfloat k) {
        forinc(i, 0, n-1)
            forinc(j, 0, m-1)
                set(i, j, get(i, j) * k);
        return *this;
    }
    MatrixN & operator /= (GLfloat k) {
        forinc(i, 0, n-1)
            forinc(j, 0, m-1)
                set(i, j, get(i, j) / k);
        return *this;
    }
    MatrixN & operator -= (const MatrixN & B) {
        forinc(i, 0, min(n-1,B.n-1))
            forinc(j, 0, min(m-1,B.m-1))
                set(i, j, get(i,j) - B.get(i, j));
        return *this;
    }
    MatrixN & operator += (const MatrixN & B) {
        forinc(i, 0, min(n-1,B.n-1))
            forinc(j, 0, min(m-1,B.m-1))
                set(i, j, get(i,j) + B.get(i, j));
        return *this;
    }
    MatrixN operator * (GLfloat k) {
        MatrixN C = MatrixN(*this);
        C *= k;
        return C;
    }
    MatrixN operator / (GLfloat k) {
        MatrixN C = MatrixN(*this);
        C /= k;
        return C;
    }
    MatrixN operator - (const MatrixN & B) {
        MatrixN C = MatrixN(*this);
        C -= B;
        return C;
    }
    MatrixN operator + (const MatrixN & B) {
        MatrixN C = MatrixN(*this);
        C += B;
        return C;
    }
    MatrixN operator * (const MatrixN & B) {
        MatrixN C = MatrixN(n,B.m);
        forinc(i, 0, n-1)
            forinc(j, 0, B.m-1) {
                GLfloat value = 0;
                forinc(k, 0, m-1)
                value += get(i,k) * B.get(k, j);
                C.set(i, j, value);
            }
        return C;
    }
    void printDescription() const {
        printf("Matrix %dx%d : \n",n,m);
        forinc(i, 0, n-1)
        forinc(j, 0, m-1) {
            if (j == 0)
                printf("|");
            else
                printf(", ");
            printf("%6.6f",get(i, j));
            if (j == m-1)
                printf("|\n");
        }
    }
};

class Matrix4 : public MatrixN {
public:
    Matrix4() : MatrixN(4,4) { }
    Matrix4(const MatrixN & mx) : MatrixN(mx) { }
    Matrix4 inverse() {
        MatrixN invrs = MatrixN::inverse();
        Matrix4 invrs4 = Matrix4(invrs);
        return invrs4;
    }
    MatrixN transpose() {
        MatrixN trans = MatrixN::transpose();
        Matrix4 trans4 = Matrix4(trans);
        return trans4;
    }
    Matrix4 identity() {
        MatrixN iden = MatrixN::identity();
        Matrix4 iden4 = Matrix4(iden);
        return iden4;
    }
    Matrix4 & operator = (const Matrix4 mx) {
        forinc(i,0,n-1)
            forinc(j,0,m-1)
                set(i, j,  mx.get(i, j));
        return *this;
    }
    Matrix4 & operator *= (GLfloat k) {
        forinc(i, 0, n-1)
            forinc(j, 0, m-1)
                set(i, j, get(i, j) * k);
        return *this;
    }
    Matrix4 & operator /= (GLfloat k) {
        forinc(i, 0, n-1)
            forinc(j, 0, m-1)
                set(i, j, get(i, j) / k);
        return *this;
    }
    Matrix4 & operator -= (const Matrix4 & B) {
        forinc(i, 0, n-1)
            forinc(j, 0, m-1)
                set(i, j, get(i, j) - B.get(i, j));
        return *this;
    }
    Matrix4 & operator += (const Matrix4 & B) {
        forinc(i, 0, n-1)
            forinc(j, 0, m-1)
                set(i, j, get(i, j) + B.get(i, j));
        return *this;
    }
    Matrix4 operator * (GLfloat k) {
        Matrix4 C = Matrix4(*this);
        C *= k;
        return C;
    }
    Matrix4 operator / (GLfloat k) {
        Matrix4 C = Matrix4(*this);
        C /= k;
        return C;
    }
    Matrix4 operator - (const Matrix4 & B) {
        Matrix4 C = Matrix4(*this);
        C -= B;
        return C;
    }
    Matrix4 operator + (const Matrix4 & B) {
        Matrix4 C = Matrix4(*this);
        C += B;
        return C;
    }
    Matrix4 operator * (const Matrix4 & B) {
        MatrixN mult = MatrixN::operator*(B);
        Matrix4 m = Matrix4(mult);
        return m;
    }
    Matrix4 scaleMatrix(GLfloat x, GLfloat y, GLfloat z) {
        Matrix4 C = identity();
        C.set(0, 0, x);
        C.set(1, 1, y);
        C.set(2, 2, z);
        return C;
    }
    Matrix4 translationMatrix(GLfloat x, GLfloat y, GLfloat z) {
        Matrix4 C = identity();
        C.set(3, 0, x);
        C.set(3, 1, y);
        C.set(3, 2, z);
        return C;
    }
    Matrix4 rotationMatrix(GLfloat x, GLfloat y, GLfloat z) {
        Matrix4 C = identity();
        C = rotationZ(z) * rotationY(y) * rotationX(x) * C;
        return C;
    }
    Matrix4 & translate(GLfloat x, GLfloat y, GLfloat z) {
        Matrix4 C = Matrix4(*this);
        Matrix4 tm = translationMatrix(x, y, z);
        C = tm * C;
        (*this) = C;
        return *this;
    }
    Matrix4 rotationX(GLfloat radian) {
        Matrix4 C = identity();
        C.set(1, 1, cos(radian));
        C.set(1, 2, -sin(radian));
        C.set(2, 1, sin(radian));
        C.set(2, 2, cos(radian));
        return C;
    }
    Matrix4 rotationY(GLfloat radian) {
        Matrix4 C = identity();
        C.set(0, 0, cos(radian));
        C.set(0, 1, -sin(radian));
        C.set(1, 0, sin(radian));
        C.set(1, 1, cos(radian));
        return C;
    }
    Matrix4 rotationZ(GLfloat radian) {
        Matrix4 C = identity();
        C.set(0, 0, cos(radian));
        C.set(0, 2, sin(radian));
        C.set(2, 0, -sin(radian));
        C.set(2, 2, cos(radian));
        return C;
    }
    Matrix4 & rotate(GLfloat x, GLfloat y, GLfloat z) {
        Matrix4 C = Matrix4(*this);
        C =  rotationMatrix(x, y, z) * C;
        (*this) = C;
        return *this;
    }
    Matrix4 & rotateX(GLfloat x) {
        Matrix4 C = Matrix4(*this);
        C = rotationX(x) * C;
        (*this) = C;
        return *this;
    }
    Matrix4 & rotateY(GLfloat y) {
        Matrix4 C = Matrix4(*this);
        C = rotationY(y) * C;
        (*this) = C;
        return *this;
    }
    Matrix4 & rotateZ(GLfloat z) {
        Matrix4 C = Matrix4(*this);
        C = rotationZ(z) * C;
        (*this) = C;
        return *this;
    }
    Matrix4 & scale(GLfloat x, GLfloat y, GLfloat z) {
        Matrix4 C = Matrix4(*this);
        C = scaleMatrix(x, y, z) * C;
        (*this) = C;
        return *this;
    }
    void printDescription() const {
        printf("Matrix 4 : \n");
        forinc(i, 0, n-1)
            forinc(j, 0, m-1) {
                if (j == 0)
                    printf("|");
                else
                    printf(", ");
                printf("%6.6f",get(i, j));
                if (j == m-1)
                    printf("|\n");
            }
    }
};

#endif
