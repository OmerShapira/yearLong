#include "testApp.h"

using namespace ofxCv;
using namespace cv;




void testApp::setup() {

//	app
    ofSetVerticalSync(true);
	ofBackground(0);

    //This is the test movie
	movie.loadMovie("/Users/Omer/Documents/Software Dev/Test/Surya/Road2.mov");
	movie.play();
	    
    
//  background subtraction
    
    background.setDifferenceMode(RunningBackground::ABSDIFF);
    background.setLearningTime(15);
//    background.setLearningRate(.001);
	background.setThresholdValue(30);
    
	contourFinder.setMinAreaRadius(15);
	contourFinder.setMaxAreaRadius(100);
	contourFinder.setThreshold(15);
    
    //how many frames before we give up on it
	tracker.setPersistence(3);
	// an object can move up to 50 pixels per frame
	tracker.setMaximumDistance(50);
    
    
    //TODO make it an up vector, not down vector
    accumulator.setUpVector(ofVec2f(0.0,-1.0));
}

void testApp::update() {
	movie.update();
	if(movie.isFrameNew()) {
        
        background.update(movie, thresholded);
		thresholded.update();
        
		blur(thresholded, 10);
		contourFinder.findContours(thresholded);
		tracker.track(contourFinder.getBoundingRects());
        
	}

}

void testApp::draw() {	
	ofSetColor(255);
    movie.draw(0,0);
	thresholded.draw(640, 0);
	contourFinder.draw();
	vector<Car>& followers = tracker.getFollowers();
	for(int i = 0; i < followers.size(); i++) {
		followers[i].draw();
        //TODO Remove debug line
        cout <<i<<" : "<<followers[i].getTangentAtPoint(5)<< endl;
	}
}
