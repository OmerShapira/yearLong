#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "CarAccumulator.h"
#include "Car.h"
#include "ParkedCar.h"
#include "Path.h"
//#include "ofxA"


class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void mousePressed(int x, int y, int button);
	
	ofVideoPlayer movie;
	ofxCv::ContourFinder contourFinder;
	ofxCv::RectTrackerFollower<Car> tracker;
    
    ofImage thresholded;
    ofxCv::RunningBackground background;
    
    CarAccumulator accumulator;
    cv::Rect accumRegion;
    ofPolyline bounds;

    ofImage img;
    vector<ParkedCar> parked;
    
    Path p;
};
