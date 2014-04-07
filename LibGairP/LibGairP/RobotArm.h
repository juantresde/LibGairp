//
//  RobotArm.h
//  LibGairP
//
//  Created by Silencer on 1/1/14.
//  Copyright (c) 2014 Giorgi Pataraia LLC. All rights reserved.
//

#ifndef LibGairP_RobotArm_h
#define LibGairP_RobotArm_h

#include "NGone.h"
#include "Sphere.h"
#include "Conus.h"

class RobotFinger : public DrawableObject {
public:
    NGone fingerStep;
    Sphere fingerRotationSphere;
    Conus fingerTop;
    RobotFinger() {
        fingerStep = NGone(12, 2, 0.01, 3, 0.1, YellowColor, NoneMaterial);
        fingerRotationSphere = Sphere(0.04, 10, 10, RedColor, NoneMaterial);
        fingerRotationSphere.translate(0, 0.3, 0);
        fingerTop = Conus(12, 2, 0.01, 4, 0.1, YellowColor, NoneMaterial);
        fingerTop.translate(0, 0.3, 0);
        fingerTop.rotate(0, AngleToRadian(-30), 0);
    }
    void draw() {
        glPushMatrix();
        
        glMultMatrixf(transform.A());
        
        fingerStep.draw();
        fingerTop.draw();
        fingerRotationSphere.draw();
        
        glPopMatrix();
    }
};

class RobotArmPart2 : public DrawableObject {
public:
    NGone   firstRotationStick;
    Sphere   stickHead;
    RobotFinger finger1,finger2;
    RobotArmPart2 () {
        firstRotationStick = NGone(32, 2, 0.1, 12, 0.1, YellowColor, NoneMaterial);
        stickHead = Sphere(0.25, 10, 10, WhiteColor, NoneMaterial);
        stickHead.translate(0, 1.2, 0);
        finger1 = RobotFinger();
        finger1.translate(0.2, 1.3, 0);
        finger1.rotate(0, AngleToRadian(45), 0);
        
        finger2 = RobotFinger();
        finger2.translate(-0.2, 1.3, 0);
        finger2.rotate(0, AngleToRadian(-45), AngleToRadian(180));
    }
    Matrix4 getObjectSpace() {
        return stickHead.transform * transform;
    }
    void draw() {
        glPushMatrix();
        
        glMultMatrixf(transform.A());
        
        firstRotationStick.draw();
        stickHead.draw();
        finger1.draw();
        finger2.draw();
        
        glPopMatrix();
    }
};

class RobotArmPart1 : public DrawableObject {
public:
    NGone   firstRotationStick,
            rotationCone1,
            rotationCone2;
    RobotArmPart2 part2;
    
    RobotArmPart1() {
        firstRotationStick = NGone(32, 2, 0.1, 12, 0.1, YellowColor, NoneMaterial);
        rotationCone1 = NGone(32, 2, 0.1, 8, 0.1, YellowColor, NoneMaterial);
        rotationCone1.translate(0,1.2,0.6);
        rotationCone1.rotate(AngleToRadian(90), 0, 0);
        rotationCone2 = NGone(32, 3, 0.1, 4, 0.1, BlueColor, NoneMaterial);
        rotationCone2.translate(0, 1.2, 0.8);
        rotationCone2.rotate(AngleToRadian(90), 0, 0);
        part2 = RobotArmPart2();
        part2.translate(0, 1.2, 0.6);
        part2.rotate(0,  AngleToRadian(-90), 0);
    }
    Matrix4 getObjectSpace() {
        return part2.getObjectSpace() * transform;
    }
    void draw() {
        glPushMatrix();
        
        glMultMatrixf(transform.A());
        
        firstRotationStick.draw();
        rotationCone1.draw();
        rotationCone2.draw();
        part2.draw();
        
        glPopMatrix();
    }
};


class RobotArm : public DrawableObject {
public:
    NGone   bottomRotationCone1,
            bottomRotationCone2,
            bottomStickCone,
            firstRotationCone1,
            firstRotationCone2;
    RobotArmPart1 part1;
    
    RobotArm() {
        bottomRotationCone1 = NGone(16, 5, 0.1, 1, 0.25, YellowColor, NoneMaterial);
        bottomRotationCone2 = NGone(16, 4, 0.1, 1, 0.18, RedColor, NoneMaterial);
        bottomRotationCone2.translate(0, 0.25, 0);
        bottomStickCone = NGone(16, 2, 0.1, 5, 0.2, YellowColor, NoneMaterial);
        firstRotationCone1 = NGone(32, 2, 0.1, 12, 0.1, YellowColor, NoneMaterial);
        firstRotationCone1.translate(0,1,0.4);
        firstRotationCone1.rotate(AngleToRadian(90), 0, 0);
        firstRotationCone2 = NGone(32, 3, 0.1, 4, 0.1, BlueColor, NoneMaterial);
        firstRotationCone2.translate(0, 1, -0.4);
        firstRotationCone2.rotate(AngleToRadian(90), 0, 0);
        part1 = RobotArmPart1();
        part1.translate(0, 1, -0.6);
        part1.rotate(0,  AngleToRadian(-30), 0);
    }
    Matrix4 getObjectSpace() {
        return part1.getObjectSpace() * transform;
    }
    void draw() {
        glPushMatrix();
        
        glMultMatrixf(transform.A());
        
        bottomRotationCone1.draw();
        bottomRotationCone2.draw();
        bottomStickCone.draw();
        firstRotationCone1.draw();
        firstRotationCone2.draw();
        part1.draw();
        
        glPopMatrix();
    }
};

#endif
