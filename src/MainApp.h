//
//  MainApp.h
//
//  Created by Guillaume Ardaud on 7/7/11. guillaume@panafold.com
//  Copyright 2011 Panafold. All rights reserved.
//

#ifndef _MAIN_APP_H_
#define _MAIN_APP_H_

#include "cinder/app/AppBasic.h"
using namespace ci;
using namespace ci::app;
#include <list>
#include "LorenzSolver.h"

class MainApp : public AppBasic {

public:
    MainApp();
	void draw();
    void drawText();
    
    void keyDown(KeyEvent event);
    
protected:
    LorenzSolver lorenzSolver;
    
    std::list<Vec3f> oldPoints;
    std::list<Vec3f> points;
};


#endif
