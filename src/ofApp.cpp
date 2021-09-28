#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    threshold.set("threshold", 0,0,100);
    
    panel.setup("calibrate", "settings.xml", 20, 20);
    panel.add(kinect.minDistance);
    panel.add(kinect.maxDistance);
    panel.add(threshold);
    panel.loadFromFile("settings.xml");
    
    grayKinect.allocate(1024, 768);
    
    scale = 1.0;
    scaleSetX = scaleSetY = 0;
    
    kinect.open();

}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
    if( kinect.isFrameNew() ){
        grayKinect.setFromPixels(kinect.getDepthPixels());
        grayKinect.threshold(threshold);
        contourFinder.findContours(grayKinect, 1000, 1024*768/4, 4, false);
    }
    
    numShadows = contourFinder.nBlobs;
    for (int j = 0; j < MAX_BLOBS; j++) {
        shadowLines[j].clear();
        if (j < numShadows) {
            for (int k = 0; k < contourFinder.blobs[j].pts.size(); k++)
                shadowLines[j].addVertex(contourFinder.blobs[j].pts[k]);
            shadowLines[j].close();
            shadowLines[j].simplify();
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(scaleSetX, scaleSetY);
    ofScale(scale, scale);
    
    ofSetLineWidth(3);
    ofSetColor(140, 140, 200);
    for (int j = 0; j < numShadows; j++)
        shadowLines[j].draw();
    
    if(cCalibrate) {
        grayKinect.draw(0, 0, 1024, 768);
        contourFinder.draw(0, 0, 1024, 768);
        panel.draw();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='c'){
        cCalibrate = !cCalibrate;
    }
    
    if (key == 'f') {
        ofToggleFullscreen();
        float w = ofGetWindowWidth(), h = ofGetWindowHeight();
        scale = MIN(w / 1024, h / 768);
        scaleSetX = (w - 1024 * scale) / 2;
        scaleSetY = (h - 768 * scale) / 2;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
