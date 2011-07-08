//
//  LorenzSolver.h
//
//  Created by Guillaume on 7/7/11. guillaume@panafold.com
//  Copyright 2011 Panafold. All rights reserved.
//

#ifndef _LORENZSOLVER_H_
#define _LORENZSOLVER_H_

#include "cinder/app/AppBasic.h"
using namespace ci;

// Computes numerical solutions to the Lorenz diff eq. using the Runge-Kutta method.
class LorenzSolver{
public:
    LorenzSolver();
        
    Vec3f computePoint(Vec3f);
    
    void setDelta(float newDelta){this->delta+= newDelta;};
    void setSigma(float newSigma){this->sigma+= newSigma;};
    void setBeta(float newBeta){this->beta+= newBeta;};
    void setRho(float newRho){this->rho+= newRho;};

    float getDelta(){return this->delta;};
    float getSigma(){return this->sigma;};
    float getBeta(){return this->beta;};
    float getRho(){return this->rho;};

private:

    void computeA();
    void computeB();
    void computeC();
    void computeD();
    
    float f1(float, float, float);
    float f2(float, float, float);
    float f3(float, float, float);
    
    float delta;
    float sigma;
    float beta;
    float rho;
    
    Vec3f oldPoint;
    
    Vec3f A;
    Vec3f B;
    Vec3f C;
    Vec3f D;
};

#endif
