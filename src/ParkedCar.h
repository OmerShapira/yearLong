//
//  ParkedCar.h
//  yearLong
//
//  Created by Surya on 31/03/13.
//
//

#ifndef __yearLong__ParkedCar__
#define __yearLong__ParkedCar__

#include <iostream>
#include "ofMain.h"
#include "Path.h"
class ParkedCar{
    
    
public:
    ParkedCar();
    ParkedCar(ofImage _img,ofVec2f _location);
    
    void update();
    void draw();
    void applyForce(ofVec2f force);
    ofVec2f seek(ofVec2f target);
    void follow(Path p, vector<ParkedCar> c);
    ofVec2f seperate(vector<ParkedCar> cars);
    ofVec2f getNormalPoint(ofVec2f p ,ofVec2f a, ofVec2f b);
    void applyBehaviours(vector<ParkedCar> cars,ofVec2f target);

    ofVec2f location;
    ofVec2f velocity;
    ofVec2f acceleration;
    float maxSpeed;
    float maxForce;
    ofImage img;
    float angle;
    float width;
    float height;
    
};
#endif /* defined(__yearLong__ParkedCar__) */
