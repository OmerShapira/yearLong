//
//  ParkedCar.cpp
//  yearLong
//
//  Created by Surya on 31/03/13.
//
//

#include "ParkedCar.h"

ParkedCar::ParkedCar(){
    
}
//TODO: Initialist variables correctly
ParkedCar::ParkedCar(ofImage _img, ofVec2f _location){
    
    img = _img;
    acceleration = ofVec2f(0,0);
    velocity = ofVec2f(0,0);
    location = _location;
    maxSpeed =10;
    maxForce = 100;
    angle = 0;
    
    // TODO check if you need W,H if the image has fron through resize
    float fbo_x, fbo_y; // fbo_w, fbo_h;

}


void ParkedCar::update(){
    velocity += acceleration;
    velocity.limit(maxSpeed);
    location += velocity;
    acceleration *=0;
}

ofVec2f ParkedCar::seek(ofVec2f target){
    ofVec2f desired = target - location;

    if (desired.length()==0) {
        ;
    }
    else{
        desired = desired.normalized();
        desired *= 0.5;
//        ofVec2f steer = desired - velocity;
//        steer.limit(maxForce);
//        applyForce(steer);
        desired -=  velocity;
        desired.limit(maxForce);
       
    }
    return desired;
}

void ParkedCar::applyForce(ofVec2f force){
    acceleration += force;
    
}

//void ParkedCar::follow(Path p){
void ParkedCar::follow(Path p, vector<ParkedCar> c){
    float worldRecord = 1000000;
    ofVec2f target;
    ofVec2f predict = ofVec2f(velocity);
    predict =predict.normalized();
    predict *= 25;
    ofVec2f predictLoc = predict+location;
    
    for(int i=0;i<p.points.size()-1;i++){
        ofVec2f a = p.points[i];
        ofVec2f b = p.points[i+1];
        ofVec2f normalPoint = getNormalPoint(predictLoc, a, b);
        if(normalPoint.x<a.x||normalPoint.x>b.x){
            normalPoint.set(b);
        }

        
        float distance = normalPoint.distance(predictLoc);
        
        if(distance<worldRecord){
            worldRecord =distance;
            ofVec2f dir = b-a;
            dir=dir.normalized();
            dir *= 10;
            
            target = ofVec2f(normalPoint+dir);
        }
    }
//    ofVec2f a = p.start;
//    ofVec2f b = p.end;
//    ofVec2f normalPoint = getNormalPoint(predictLoc, a, b);
//    

    
    if(worldRecord>p.radius){
      //  seek(target);
        applyBehaviours(c, target);
    }
}

ofVec2f ParkedCar::getNormalPoint(ofVec2f p, ofVec2f a, ofVec2f b){
    ofVec2f ap = p-a;
    ofVec2f ab = b-a;

    ab = ab.normalized();
        ab *= ap.dot(ab);
    ofVec2f normalPoint = a +ab;
    
    return normalPoint;
}
//void ParkedCar::follow(FlowField flow){
//    ofVec2f desired = flow.lookUp(location);
//    desired.limit(maxSpeed);
//    
//    ofVec2f steer = desired - velocity;
//    steer.limit(maxForce);
//    applyForce(steer);
//    
//}
ofVec2f ParkedCar::seperate(vector<ParkedCar> cars){
    float desiredSeperation = width;
    ofVec2f sum = ofVec2f();
    int count =0;
    for(int i=0;i<cars.size();i++){
        float d = location.distance(cars[i].location);
        
        if(d>0&&d<desiredSeperation){
            ofVec2f diff = location - cars[i].location;
            diff = diff.normalized();
            sum += diff;
            count++;
        }

    }
    
    if(count>0){
        sum /= count;
        
        sum.scale(maxSpeed);//set(maxSpeed);
        sum -= velocity;
        //steer.limit(maxForce);
       // applyForce(steer);
    }
    return sum;
}

void ParkedCar::applyBehaviours(vector<ParkedCar> cars,ofVec2f target){
    ofVec2f sep = seperate(cars);
    ofVec2f seeks =  seek(target);
    sep *=2;
    applyForce(sep);
    applyForce(seeks);
    
}

void ParkedCar::draw(){
    ofPushMatrix();
    ofTranslate(location.x, location.y);
    //ofRotate(angle);
//    img.draw(location.x,location.y);
//    img.
    img.draw(0, 0);
    ofPopMatrix();
}