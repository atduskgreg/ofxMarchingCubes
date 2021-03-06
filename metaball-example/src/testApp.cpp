#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(250,250,250);
	ofSetVerticalSync(true);
	ofPoint iniPos(0,0,0); //the position is refering to the center of the grid
	ofPoint gridSize(1000, 1000, 1000);
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
void testApp::update(){
	float counter = ((float)ofGetFrameNum()) * 0.01f;
	float threshold = ((float)mouseX / ofGetWidth());
	marchingCubes.resetIsoValues();
	ofPoint force;
	ofPoint gridCenter = marchingCubes.getGridPos();
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
void testApp::draw(){
    
	ofPoint center(ofGetWidth()*0.5f, ofGetHeight()*0.5f, -1000);
	ofPoint gridSize = marchingCubes.getGridSize();
	float counter = (float)ofGetFrameNum();
    
	ofPushMatrix();
	ofTranslate(center.x, center.y, center.z);
	ofRotate(counter*0.05f, 1.0f, 0.0f, 0.0f);
	ofRotate(counter*0.1f, 0.0f, 1.0f, 0.0f);
    
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
void testApp::keyReleased(int key){
	if(key == ' ')bSaveModel = true;
}

void testApp::keyPressed(int key){}
void testApp::mouseMoved(int x, int y){}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){}
void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){ }
