//
//  MainApp.cpp
//
//  Created by Guillaume Ardaud on 7/7/11. guillaume@panafold.com
//  Copyright 2011 Panafold. All rights reserved.
//

#define NUM_POINTS 2000

#include <iostream>
#include "MainApp.h"

#include "cinder/Rand.h"
using namespace ci;

MainApp::MainApp(){
    Rand::randomize();
    
    this->lorenzSolver= LorenzSolver();
    
    for (int i=0; i<NUM_POINTS; i++){
        Vec3f p= Vec3f(
                       Rand::randFloat(200.0f,400.0f),
                       Rand::randFloat(200.0f,400.0f),
                       Rand::randFloat(5.0f,10.0f));

        this->oldPoints.push_back(p);
        this->points.push_back(p);
    }
}

void MainApp::draw(){
    //compute new point coordinates
    this->points.clear();
	for( std::list<Vec3f>::iterator pointIter = this->oldPoints.begin(); pointIter != this->oldPoints.end(); ++pointIter ) {
        this->points.push_back(this->lorenzSolver.computePoint((*pointIter)));
    }
    

	gl::setMatricesWindow( getWindowSize() );
    
	gl::clear(Color(0.0f, 0.0f, 0.0f));
	glColor3f(0.25f, 0.25f, 0.75f);
	
	glBegin( GL_LINE_STRIP );

	// iterate across our list of points, and pass each one to OpenGL
	std::list<Vec3f>::iterator oldPointIter = this->oldPoints.begin();

    for(std::list<Vec3f>::iterator pointIter = this->points.begin(); pointIter != this->points.end(); ++pointIter ) {
		glVertex3f( *oldPointIter );
		glVertex3f( *pointIter );
        ++oldPointIter;
	}
 
    // tell OpenGL to actually draw the lines now
	glEnd();
    
    //Points become old points
    this->oldPoints.swap(this->points);
}