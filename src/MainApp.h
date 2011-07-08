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
    
    void prepareSettings(Settings* settings);
    void keyDown(KeyEvent event);
    void mouseMove(MouseEvent event);
    void mouseDrag(MouseEvent event);
    void mouseWheel(MouseEvent event);
    
protected:
    LorenzSolver lorenzSolver;
    
    std::list<Vec3f> oldPoints;
    std::list<Vec3f> points;

    int dx, dy;
    int xFrustrumOffset, yFrustrumOffset;
    float zoomFactor;
    float lineWidth;
};


#endif
