//
//  Constants.h
//  LibGairP
//
//  Created by Silencer on 12/26/13.
//  Copyright (c) 2013 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_Constants_h
#define LibGairP_Constants_h

#ifdef MacOSX
    #import <GLUT/GLUT.h>
    #import <OpenGL/OpenGL.h>
#else
	#include <glut.h>
#endif

#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

const double PI = 3.14159265359;

int dx[8] = {-1,0,1,1,1,0,-1,-1};
int dy[8] = {-1,-1,-1,0,1,1,1,0};

#define Angle2PI 360.0
#define AnglePI 180.0
#define INF 1e8
#define EPS 1e-5
#define MaxDepth 3
#define NotFound -1
#define AngleToRadian(_angle_) _angle_ / 180.0 * PI
#define RadianToAngle(_radian_) _radian_ / PI * 180
#define forinc(_i_,_from_,_to_) for (int _i_ = _from_; _i_ <= _to_; _i_++)
#define fordec(_i_,_from_,_to_) for (int _i_ = _from_; _i_ >= _to_; _i_--)

#define indexForPair(_i_,_j_,_n_,_m_) _i_ * _m_ + _j_

// Copper
const GLfloat copperAmbient[4] = {0.19125, 0.0735, 0.0225, 1.0};
const GLfloat copperDiffuse[4] = {0.7038, 0.27048, 0.0828, 1.0};
const GLfloat copperSpecular[4] = {0.256777, 0.137622, 0.086014, 1.0};
const GLfloat copperShiness[1] = {2.8};

//
// Polished Copper
const GLfloat polishedCopperAmbient[] = {0.2295, 0.08825, 0.0275, 1.0};
const GLfloat polishedCopperDiffuse[] = {0.5508, 0.2118, 0.066, 1.0};
const GLfloat polishedCopperSpecular[] = {0.580594, 0.223257, 0.0695701, 1.0};
const GLfloat polishedCopperShiness[] = {51.2};

// Gold
const GLfloat goldAmbient[4] = {0.24725, 0.1995, 0.0745, 1.0};
const GLfloat goldDiffuse[4] = {0.75164, 0.60648, 0.22648, 1.0};
const GLfloat goldSpecular[4] = {0.628281, 0.555802, 0.366065, 1.0};
const GLfloat goldShiness[1] = {51.2};

//const GLfloat Ambient[4] = {};
//const GLfloat Diffuse[4] = {};
//const GLfloat Specular[4] = {};
//const GLfloat Shiness[1] = {};

// Polished Gold
const GLfloat PolishedGoldAmbient[4] = {0.24725, 0.2245, 0.0645, 1.0};
const GLfloat PolishedGoldDiffuse[4] = {0.34615, 0.3143, 0.0903, 1.0};
const GLfloat PolishedGoldSpecular[4] = {0.797357, 0.723991, 0.208006, 1.0};
const GLfloat PolishedGoldShiness[1] = {83.2};

//Silver
const GLfloat SilverAmbient[4] = {0.19225, 0.19225, 0.19225, 1.0};
const GLfloat SilverDiffuse[4] = {0.50754, 0.50754, 0.50754, 1.0};
const GLfloat SilverSpecular[4] = {0.508273, 0.508273, 0.508273, 1.0};
const GLfloat SilverShiness[1] = {51.2};

//Petwer
const GLfloat PewterAmbient[4] = {0.105882, 0.058824, 0.113725, 1.0};
const GLfloat PewterDiffuse[4] = {0.427451, 0.470588, 0.541176, 1.0};
const GLfloat PewterSpecular[4] = {0.333333, 0.333333, 0.521569, 1.0};
const GLfloat PewterShiness[1] = {9.84615};
#endif
