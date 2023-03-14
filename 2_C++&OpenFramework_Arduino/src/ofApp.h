#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofTrueTypeFont font;
    ofSerial serial;
    
    string sensorValue;
    int byteData;
    string msg;
    char sendData = 1;
    
    bool byteDataReceived = false;
    bool whiteScreen = false;
};
