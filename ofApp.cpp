#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	this->box2d.init();
	this->box2d.setGravity(0, 10);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();
}

//--------------------------------------------------------------
void ofApp::update(){

	if (ofGetKeyPressed()) {
		if (this->box2d.bCheckBounds) {
			float r = ofRandom(1.0, 20.0);
			this->circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
			this->circles.back().get()->setPhysics(3.0, 0.53, 0.1);
			this->circles.back().get()->setup(this->box2d.getWorld(), ofRandom(ofGetWidth()), 0, r);
		} else {
			this->box2d.createBounds();
			this->box2d.checkBounds(true);
		}

	} else {
		if (this->box2d.bCheckBounds) {
			this->box2d.createBounds(0, 0, 0, 0);
			this->box2d.checkBounds(false);
		}
	}

	ofColor circle_color;
	circle_color.setHsb(ofRandom(255), 255, 255);
	this->circles_color.push_back(circle_color);

	this->box2d.update();

	for (int i = this->circles.size() - 1; i > -1; i--) {
		if (this->circles[i].get()->getPosition().y > ofGetHeight() + 20) {
			this->circles[i].get()->destroy();
			this->circles.erase(this->circles.begin() + i);
			this->circles_color.erase(this->circles_color.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < this->circles.size(); i++) {
		ofNoFill();
		ofSetColor(this->circles_color[i]);
		this->circles[i].get()->draw();
	}

	this->box2d.drawGround();
}

//========================================================================
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
