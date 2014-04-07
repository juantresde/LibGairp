//
//  LibGairP.h
//  LibGairP
//
//  Created by Silencer on 12/26/13.
//  Copyright (c) 2013 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_LibGairP_h
#define LibGairP_LibGairP_h

#include "Constants.h"
#include "Matrix.h"
#include "Vector.h"
#include "Ray.h"
#include "DrawableObject.h"
#include "Polygon.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Floor.h"
#include "Cube.h"
#include "NGone.h"
#include "Conus.h"
#include "Sphere.h"
#include "Image3DMesh.h"
#include "Light.h"
#include "MathLib.h"
#include "Camera.h"
#include "RayTracer.h"

#define BlackColor Vector4D(0,0,0,1.0)
#define WhiteColor Vector4D(1.0,1.0,1.0,1.0)
#define RedColor Vector4D(1.0,0,0,1.0)
#define GreenColor Vector4D(0,1.0,0,1.0)
#define BlueColor Vector4D(0,0,1.0,1.0)
#define YellowColor Vector4D(1.0,1.0,0,1.0)

#define NoneMaterial Material()
#define SilverMaterial Material(MaterialTypeSilver)
#define GoldMaterial Material(MaterialTypeGold)
#define PewterMaterial Material(MaterialTypePewter)
#define CopperMaterial Material(MaterialTypeCopper)

#endif