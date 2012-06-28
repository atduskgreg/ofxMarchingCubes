#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(250,250,250);
	ofSetVerticalSync(true);
	ofPoint iniPos(0,0,0); //the position is refering to the center of the grid
	ofPoint gridSize(480, 480, 480);
	int gridResX = 70;
	int gridResY = 70;
	int gridResZ = 70;
	marchingCubes.init(iniPos, gridSize, gridResX, gridResY, gridResZ);
    	
    // populate mesh from image with alpha values
    ofImage img;
	img.loadImage("linzer.png");
	mesh.setMode(OF_PRIMITIVE_POINTS);
	for(int y = 0; y < img.getHeight(); y+=2) {
		for(int x = 0; x < img.getWidth(); x+=2) {
			ofColor cur = img.getColor(x, y);
			if(cur.a > 0) {
				// the alpha value encodes depth, let's remap it to a good depth range
				float z = ofMap(cur.a, 0, 255, -480, 480);
				cur.a = 255;
				mesh.addColor(cur);
				ofVec3f pos(x - img.getWidth() / 2, y - img.getHeight() / 2, z);
				mesh.addVertex(pos);
			}
		}
	}

    
    
    ofEnableLighting();
    light.enable();    
    light.setup();

    bModelRendered = false;
    bSaveModel = false;
    bShowCubes = false;
    
    ofSetLogLevel(OF_LOG_VERBOSE);

}

//--------------------------------------------------------------
void testApp::update(){

    if(bShowCubes && !bModelRendered){
    
        marchingCubes.resetIsoValues();
    
        vector<ofVec3f> vertices = mesh.getVertices();
    
        for(int i=0; i<mesh.getNumVertices(); i+=20){
            ofVec3f vertex = vertices.at(i);
            ofPoint p = ofPoint(vertex.x, vertex.y, vertex.z );
            marchingCubes.addMetaBall(p, 0.2);
        }
	
        marchingCubes.update(1.7, true);
        bModelRendered = true;
        
    }
    
    if(bModelRendered && bSaveModel){
        bSaveModel = false;
        cout << "saving: linzer.stl" << endl;
		marchingCubes.saveModel("linzer.stl");
        cout << "saving: ASCIIlinzer.stl" << endl;

		marchingCubes.saveModel("ASCIIlinzer.stl", true);

    }
    
	
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(125, 125, 125);
    

    cam.begin();
    ofSetColor(255, 255, 255);
    
    if(bShowCubes){
        marchingCubes.drawFilled();

    } else {
        mesh.draw();
    }

    cam.end();
    
	
	string info = "fps:" + ofToString(ofGetFrameRate()) + 
	+ "\nnum triangles:" + ofToString(marchingCubes.getNumTriangles(), 0)
	+ "\nthreshold:" + ofToString(marchingCubes.getThreshold())
    + "\nmaxIsoValue: " + ofToString(marchingCubes.getMaxIsoValue())
    + "\nminIsoValue: " + ofToString(marchingCubes.getMinIsoValue());
	ofDrawBitmapString(info, 20, 20);
}


//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(key == ' '){
        bShowCubes = !bShowCubes;
    }
    
    if( key == 's'){
        bSaveModel = true;
    }
}
void testApp::keyPressed(int key){}
void testApp::mouseMoved(int x, int y){}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){}
void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){ }
