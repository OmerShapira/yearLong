#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "CarAccumulator.h"
#include "Car.h"
#include "ParkedCar.h"
#include "Path.h"
#include <deque>
//#include "ofxAutoControlPanel.h"


class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void mousePressed(int x, int y, int button);
	void keyPressed(int key);
	ofVideoPlayer movie;
	ofxCv::ContourFinder contourFinder;
	ofxCv::RectTrackerFollower<Car> tracker;
    
    ofImage thresholded;
    ofxCv::RunningBackground background;
    
    CarAccumulator accumulator;
   // cv::Rect accumRegion;
    ofPolyline bounds;

    ofImage img;
    vector<ParkedCar> parked;
    vector<ParkedCar> parked1;
    deque<Car> test;
    Path p;
    Path p1;
     
    Boolean pathEnabled;
   // ofxAutoControlPanel panel;
};
