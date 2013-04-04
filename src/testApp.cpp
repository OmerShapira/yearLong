#include "testApp.h"

using namespace ofxCv;
using namespace cv;




void testApp::setup() {
    
    //	app
    ofSetVerticalSync(true);
	ofBackground(0);
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    pathEnabled = false;
    //This is the test movie
	movie.loadMovie("CarCounterMovie.mov");
	movie.play();
    
    //  background subtraction
    
    background.setDifferenceMode(RunningBackground::ABSDIFF);
    //    background.setLearningTime(15);
    background.setLearningTime(60);
    //    background.setLearningRate(.001);
	background.setThresholdValue(50);
    
	contourFinder.setMinAreaRadius(15);
	//contourFinder.setMaxAreaRadius(100);
    contourFinder.setMaxAreaRadius(150);
	contourFinder.setThreshold(50);
    
    //how many frames before we give up on it
	tracker.setPersistence(3);
	// an object can move up to 50 pixels per frame
	tracker.setMaximumDistance(50);
    
    
    //TODO make it an up vector, not down vector
    accumulator.setUpVector(ofVec2f(0.0,-1.0));
    //    bounds.addVertex(322, 370);
    //    bounds.addVertex(416, 359);
    //    bounds.addVertex(482,448);
    //    bounds.addVertex(351,449);
    
    bounds.addVertex(527,200);
    bounds.addVertex(463,408);
    bounds.addVertex(0,392);
    bounds.addVertex(0,200);
    accumulator.setBounds(bounds);
   // p = Path( 417,229,92,586);
    p = Path();
    p1 = Path();
    p.addPoint(319, 327);
    p.addPoint(14, 795);
    p1.addPoint(432,403);
    p1.addPoint(379,900);
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
    for(int i =0; i<parked1.size();i++){
        if(pathEnabled){
            parked1[i].follow(p1,parked1);
        }
        parked1[i].update();
        
    }
    for(int i =0; i<parked.size();i++){
        //parked[i].seek(ofVec2f(1200,400));
        if(pathEnabled){
        parked[i].follow(p,parked);

        }
       // parked[i].seek(ofVec2f(14,795));
        parked[i].update();
      //  cout<<i<<": "<<parked[i].acceleration<<endl;
    }
    
}

void testApp::draw() {
	ofSetColor(255);
    movie.draw(0,0);
	thresholded.draw(640, 0);
	//contourFinder.draw();
    accumulator.bounds.draw();
    p.display();
    
	vector<Car>& followers = tracker.getFollowers();
    
    //tracker.
    //test.push_back( tracker.getFollowers());
    
	for(int i = 0; i < followers.size(); i++) {
        
        if(accumulator.isInBounds(followers[i].boundingBox, 0.4, 6)){
            followers[i].draw();
            
            if(followers[i].getLifeTime()>20){
                if (!followers[i].getDead()) {
                    ofImage src = movie.getPixelsRef();
                    img.cropFrom(src, followers[i].boundingBox.x, followers[i].boundingBox.y, followers[i].boundingBox.width, followers[i].boundingBox.height);
                    
                    img.resize(followers[i].boundingBox.width, followers[i].boundingBox.height);
                    //img.resize(50, 100);
                    ParkedCar c = ParkedCar(img, ofVec2f(followers[i].boundingBox.x,followers[i].boundingBox.y));
                    c.velocity = followers[i].getVelocity();
                    c.width=followers[i].boundingBox.width;
                    c.height=followers[i].boundingBox.height;
                    if(c.location.x>341){
                        parked1.push_back(c);
                    }
                    else{
                    parked.push_back(c);    
                    }

                    followers[i].kill();
                }
                
            }
            
        }
	}
             //   cout<<followers.size()<<endl;
    for(int i =0; i<parked.size();i++){
        parked[i].draw();
    }
    for(int i =0; i<parked1.size();i++){
        parked1[i].draw();
    }
}

void testApp::mousePressed(int x, int y, int button){
    cout<<x<<","<<y<<endl;
    if(!pathEnabled){
        p1.addPoint(x, y);
    }
}

void testApp::keyPressed(int key){
    cout<<key<<endl;
    if (key == 112) {
        pathEnabled =  !pathEnabled;
    }
    if(key=='f'){
        ofToggleFullscreen();
    }
}