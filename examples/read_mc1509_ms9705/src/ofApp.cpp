/* Implementation of read_snowboard_1610
Read and visualize data from Snowboard and 1610 sensor
Copyright (c) 2014-2016 Kitronyx http://www.kitronyx.com
contact@kitronyx.com
GPL V3.0
*/

#include "ofApp.h"
#include "klib.h"

KLib * klib;
Grid * grid;

//--------------------------------------------------------------
void ofApp::setup() {
	klib = new KLib();
	// update port number according to your system.
	klib->init("COM9", "MC1509", "MS9705");

	int sz_rect = 20;
	grid = new Grid(klib->nrow, klib->ncol, sz_rect);

	ofSetWindowShape(sz_rect*klib->ncol, sz_rect*klib->nrow);
	ofSetWindowTitle("Kitronyx Inc. read_mc1509_ms9705");

	klib->start();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	int scale = 5;
	if (klib->read() == true)
	{
		grid->draw(klib->frame, scale);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
