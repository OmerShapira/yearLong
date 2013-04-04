//
//  Path.cpp
//  yearLong
//
//  Created by Surya on 01/04/13.
//
//

#include "Path.h"


Path::Path(){
    radius = 10;
   // points.resize(5);
}

Path::Path(int x, int y, int x1 ,int y1){
    radius = 5;
    start = ofVec2f(x,y);
    end = ofVec2f(x1,y1);

    //end.he
}


void Path::display(){
    
    ofSetColor(255);
    //ofLine(start.x, start.y, end.x, end.y);
   // ofSetPolyMode(OF_POLY_WINDING_POSITIVE);
    
    ofBeginShape();
    for(int i=0; i<points.size();i++){
        ofVertex(points[i].x, points[i].y);
    }
    ofEndShape();
}

void Path::addPoint(float x, float y){
    points.push_back(ofVec2f(x,y));
}