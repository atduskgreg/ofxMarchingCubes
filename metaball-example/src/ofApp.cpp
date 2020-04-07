#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(250,250,250);
	ofSetVerticalSync(true);
	glm::vec3 iniPos(0,0,0); //the position is refering to the center of the grid
	glm::vec3 gridSize(1000, 1000, 1000);
	int gridResX = 30;
	int gridResY = 30;
	int gridResZ = 30;
	marchingCubes.init(iniPos, gridSize, gridResX, gridResY, gridResZ);
	glEnable(GL_DEPTH_TEST);
	metaBalls.resize(NUM_META_BALLS);
	for(int i=0; i<metaBalls.size(); i++){
		metaBalls[i].init(iniPos);
	}
    
    
    ofEnableLighting();
    light.enable();    
    light.setup();
    

	ofSetLogLevel(OF_LOG_VERBOSE);
	bSaveModel = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	float counter = ((float)ofGetFrameNum()) * 0.01f;
	float threshold = ((float)mouseX / ofGetWidth());
	marchingCubes.resetIsoValues();
	glm::vec3 force;
	glm::vec3 gridCenter = marchingCubes.getGridPos();
	float randomStep = 10;
	for(int i=0; i<metaBalls.size(); i++){
		force.x = ofRandom(-randomStep, randomStep);
		force.y = ofRandom(-randomStep, randomStep);
		force.z = ofRandom(-randomStep, randomStep);
		force += (gridCenter - metaBalls[i]) * 0.003f;
		metaBalls[i].update(force, 0.9);
		marchingCubes.addMetaBall(metaBalls[i], metaBalls[i].size);
	}
	
	marchingCubes.update(threshold, true);
	
	if(bSaveModel){
		bSaveModel = false;
		marchingCubes.saveModel("testBin.stl");
		marchingCubes.saveModel("testASCII.stl", true);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    
	glm::vec3 center(ofGetWidth()*0.5f, ofGetHeight()*0.5f, -1000);
	glm::vec3 gridSize = marchingCubes.getGridSize();
	float counter = (float)ofGetFrameNum();
    
	ofPushMatrix();
	ofTranslate(center.x, center.y, center.z);
	ofRotateDeg(counter*0.05f, 1.0f, 0.0f, 0.0f);
	ofRotateDeg(counter*0.1f, 0.0f, 1.0f, 0.0f);
    
	ofSetColor(0.0f, 0.0f, 0.0f);    
	marchingCubes.debugDraw();
	ofPopMatrix();
	
    ofSetColor(0, 0, 0);
	string info = "fps:" + ofToString(ofGetFrameRate()) + 
	+ "\nnum triangles:" + ofToString(marchingCubes.getNumTriangles(), 0)
	+ "\nthreshold:" + ofToString(marchingCubes.getThreshold());
	ofDrawBitmapString(info, 20, 20);
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if(key == ' ')bSaveModel = true;
}

void ofApp::keyPressed(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){ }
