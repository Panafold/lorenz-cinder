//
//  LorenzSolver.cpp
//
//  Created by Guillaume on 7/7/11. guillaume@panafold.com
//  Copyright 2011 Panafold. All rights reserved.
//

#include "LorenzSolver.h"

LorenzSolver::LorenzSolver(){
    this->delta=0.01f;
    this->sigma=10.f;
    this->beta=8.f/3.f;
    this->rho=28.0f;
}

Vec3f LorenzSolver::computePoint(Vec3f oldPoint){
    this->oldPoint= oldPoint;
    
    Vec3f newPoint;
    
    this->computeA();
    this->computeB();
    this->computeC();
    this->computeD();
    
    newPoint.x= oldPoint.x + (this->A.x+this->B.x*2+this->C.x*2+this->D.x) * this->delta/6.0f;
    newPoint.y= oldPoint.y + (this->A.y+this->B.y*2+this->C.y*2+this->D.y) * this->delta/6.0f;
    newPoint.z= oldPoint.z + (this->A.z+this->B.z*2+this->C.z*2+this->D.z) * this->delta/6.0f;
    
    std::cerr << newPoint.x << " " << newPoint.y << " " << newPoint.z << " " << std::endl;
    return newPoint;
}

void LorenzSolver::computeA(){
    this->A.x= f1(0.0f,0.0f,0.0f);
    this->A.y= f2(0.0f,0.0f,0.0f);
    this->A.z= f3(0.0f,0.0f,0.0f);
}

void LorenzSolver::computeB(){
    this->B.x= f1(this->A.x,this->A.y,this->A.z);
    this->B.y= f2(this->A.x,this->A.y,this->A.z);
    this->B.z= f3(this->A.x,this->A.y,this->A.z);
}

void LorenzSolver::computeC(){
    this->C.x= f1(this->B.x,this->B.y,this->B.z);
    this->C.y= f2(this->B.x,this->B.y,this->B.z);
    this->C.z= f3(this->B.x,this->B.y,this->B.z);
}

void LorenzSolver::computeD(){
    this->D.x= f1(this->C.x,this->C.y,this->C.z);
    this->D.y= f2(this->C.x,this->C.y,this->C.z);
    this->D.z= f3(this->C.x,this->C.y,this->C.z);
}

float LorenzSolver::f1(float p1, float p2, float p3){
    float r= this->sigma * (this->oldPoint.y + p2 * this->delta/2 - (this->oldPoint.x + p1 * this->delta/2));

    return r;
}

float LorenzSolver::f2(float p1, float p2, float p3){
    float r= -1*(this->oldPoint.x + p1 * this->delta/2) * (this->oldPoint.z + p3 * delta/2) + this->rho * (this->oldPoint.x+p1*this->delta/2)-(this->oldPoint.y+p2*this->delta/2);
    
    return r;
}

float LorenzSolver::f3(float p1, float p2, float p3){
    float r= (this->oldPoint.x + p1 * this->delta/2) * (this->oldPoint.y + p2 * delta/2) - this->beta * (this->oldPoint.z+p3*this->delta/2);
    
    return r;
}