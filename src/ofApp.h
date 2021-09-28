#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

#define MAX_BLOBS 4

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofxPanel panel;
    ofParameter<int> threshold;
    ofxSlider <int> minDistance;
    ofxSlider <int> maxDistance;
    
    ofxKinectV2 kinect;
    ofxCvGrayscaleImage grayKinect;
    ofxCvContourFinder contourFinder;
    
    int numShadows;
    ofPolyline shadowLines[MAX_BLOBS];
    bool cCalibrate;
    
    float scale, scaleSetX, scaleSetY;
};
