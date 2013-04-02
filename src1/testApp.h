#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "CarAccumulator.h"
#include "Car.h"   


class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	ofVideoPlayer movie;
	ofxCv::ContourFinder contourFinder;
	ofxCv::RectTrackerFollower<Car> tracker;
    
    ofImage thresholded;
    ofxCv::RunningBackground background;
    
    CarAccumulator accumulator;
};
