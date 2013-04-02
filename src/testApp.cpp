#include "testApp.h"

using namespace ofxCv;
using namespace cv;




void testApp::setup() {

//	app
    ofSetVerticalSync(true);
	ofBackground(0);

    //This is the test movie
	movie.loadMovie("/Users/Omer/Documents/Software\ Dev/Test/Surya/Road2.mov");
	movie.play();


//  background subtraction
    
    background.setDifferenceMode(RunningBackground::ABSDIFF);
    background.setLearningTime(15);
	background.setThresholdValue(20);
    
	contourFinder.setMinAreaRadius(15);
	contourFinder.setMaxAreaRadius(100);
	contourFinder.setThreshold(25);
    
    //how many frames before we give up on it
	tracker.setPersistence(3);
	// an object can move up to 50 pixels per frame
	tracker.setMaximumDistance(50);
    
    
    //TODO make it an up vector, not down vector
    accumulator.setUpVector(ofVec2f(0.0,-1.0));
    bounds.addVertex(161, 348);
    bounds.addVertex(384, 322);
    bounds.addVertex(485,448);
    bounds.addVertex(152,449);
    
    accumulator.setBounds(bounds);
    
    accumRegion.x = 150;
    accumRegion.y = 368;
    accumRegion.width = 300;
    accumRegion.height = 30;
    p = Path(900, 0, 900, 400);
}

void testApp::update() {
    //algorithm:
    
    //update movie
    // BIND FBO - Omer will provide handle
    // accumulate new cars
    // push to FBO, remove from list
    // UNBIND FBO
    
    //Calculate physics for particles
    // (in draw loop: bind FBO, draw)
    
    
    
	movie.update();
	if(movie.isFrameNew()) {
        
        background.update(movie, thresholded);
		thresholded.update();
        
		blur(thresholded, 10);
		contourFinder.findContours(thresholded);
		tracker.track(contourFinder.getBoundingRects());
        
	}
    
    for(int i =0; i<parked.size();i++){
        //parked[i].seek(ofVec2f(1200,400));
        parked[i].follow(p);
        parked[i].update();
    }

}

void testApp::draw() {	
	ofSetColor(255);
    movie.draw(0,0);
//	contourFinder.draw();
    p.display();
	vector<Car>& followers = tracker.getFollowers();

   
	for(int i = 0; i < followers.size(); i++) {

        if(accumulator.isInBounds(followers[i].boundingBox, 0.05, 4)){
            followers[i].draw();
            
            ofImage src = movie.getPixelsRef();
            img.cropFrom(src, followers[i].boundingBox.x, followers[i].boundingBox.y, followers[i].boundingBox.width, followers[i].boundingBox.height);
            img.resize(100, 200);
            ParkedCar c = ParkedCar(img, ofVec2f(700,0));
            parked.push_back(c);
            followers[i].kill();

        }
        
       //¨ ofSetColor(255, 0, 0);
        accumulator.bounds.draw();
        for(int i =0; i<parked.size();i++){
            parked[i].draw();
        }
        
        //TODO Remove debug line
      //  cout <<i<<" : "<<followers[i].getTangentAtPoint(5)<< endl;
	}
}

void testApp::mousePressed(int x, int y, int button){
    cout<<x<<","<<y<<endl;
}
