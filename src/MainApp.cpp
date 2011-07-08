//
//  MainApp.cpp
//
//  Created by Guillaume Ardaud on 7/7/11. guillaume@panafold.com
//  Copyright 2011 Panafold. All rights reserved.
//

#define NUM_POINTS 1000

#include <iostream>
#include "MainApp.h"

#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/Rand.h"
using namespace ci;

MainApp::MainApp(){
    this->dx=this->dy=0;
    this->xFrustrumOffset=this->yFrustrumOffset=0;
    this->lineWidth=1.f;
    this->zoomFactor=10.f;
    
    Rand::randomize();
    this->lorenzSolver= LorenzSolver();
    
    for (int i=0; i<NUM_POINTS; i++){
        Vec3f p= Vec3f(
                       Rand::randFloat(-50.0f,50.0f),
                       Rand::randFloat(-50.0f,50.0f),
                       Rand::randFloat(-10.0f,10.0f));

        this->oldPoints.push_back(p);
        this->points.push_back(p);
    }
}

void MainApp::keyDown(KeyEvent event){
    if (event.getChar()=='u')
        this->lorenzSolver.setSigma(-0.1f);
    else if (event.getChar()=='i')
        this->lorenzSolver.setSigma(0.1f);

    if (event.getChar()=='j')
        this->lorenzSolver.setBeta(-0.1f);
    else if (event.getChar()=='k')
        this->lorenzSolver.setBeta(0.1f);

    if (event.getChar()=='n')
        this->lorenzSolver.setRho(-0.1f);
    else if (event.getChar()=='m')
        this->lorenzSolver.setRho(0.1f);
    

    if (event.getChar()=='z')
        this->lineWidth-=0.1f;
    if (event.getChar()=='x')
        this->lineWidth+=0.1f;
}

void MainApp::mouseMove(MouseEvent event){
    this->dx+=(event.getPos().x-this->dx)*0.1;
    this->dy+=(event.getPos().y-this->dy)*0.1;
}

void MainApp::mouseDrag(MouseEvent event){
    this->xFrustrumOffset= event.getPos().x - getWindowSize().x/2;
    this->yFrustrumOffset= event.getPos().y - getWindowSize().y/2;
}

void MainApp::mouseWheel(MouseEvent event){
    this->zoomFactor+=event.getWheelIncrement()/10.f;
}

void MainApp::draw(){
    //compute new point coordinates
    this->points.clear();
	for( std::list<Vec3f>::iterator pointIter = this->oldPoints.begin(); pointIter != this->oldPoints.end(); ++pointIter ) {
        this->points.push_back(this->lorenzSolver.computePoint((*pointIter)));
    }
    

	gl::setMatricesWindow( getWindowSize() );
    
	gl::clear(Color(0.0f, 0.0f, 0.0f));
	//glColor3f(0.25f, 0.25f, 0.95f);
    //this->drawText();
    gl::translate(Vec2f((getWindowSize().x+this->xFrustrumOffset)/2, (getWindowSize().y+this->yFrustrumOffset)/2));
    gl::scale(Vec3f(this->zoomFactor,this->zoomFactor,0));

    float xAngle=(this->dx-getWindowSize().x/2)/2;
    float yAngle=(getWindowSize().y/2-this->dy)/2;
    
    
    gl::rotate(Vec3f(yAngle,xAngle, 0)); 
    glLineWidth(this->lineWidth);

	// iterate across our list of points, and pass each one to OpenGL
	std::list<Vec3f>::iterator oldPointIter = this->oldPoints.begin();

    for(std::list<Vec3f>::iterator pointIter = this->points.begin(); pointIter != this->points.end(); ++pointIter ) {

        glColor3f((*pointIter).x*Rand::randFloat(-0.1f,0.1f), 0.8f, 0.1f);
                  //(*pointIter).y*Rand::randFloat(-0.1f,0.1f),
                  //(*pointIter).z*Rand::randFloat(-0.1f,0.1f));
        glBegin( GL_LINE_STRIP );
		glVertex3f( *oldPointIter );
		glVertex3f( *pointIter );
        glEnd();

        ++oldPointIter;
	}
 
    
    //Points become old points
    this->oldPoints.swap(this->points);
}

void MainApp::drawText(){
    TextLayout simple;
	gl::Texture mSimpleTexture;
	
    //simple.setFont( customFont );
	simple.setColor( Color( 1, 1, 1 ) );
	//simple.addLine(this->lorenzSolver.getSigma());
	//simple.addLine(this->lorenzSolver.getBeta());
	//simple.addLine(this->lorenzSolver.getRho());
	mSimpleTexture = gl::Texture(simple.render(true));

    gl::draw(mSimpleTexture, Vec2f(0,0));

}