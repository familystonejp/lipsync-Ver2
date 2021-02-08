#pragma once

#include "ofMain.h"

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
				
		void audioIn(ofSoundBuffer & input);
		//void audioOut(ofSoundBuffer& output);

		vector <float> left;
		vector <float> right;
		vector <float> volHistory;
		vector <float> videoHistory;
		vector <float> allvolHistory;
		vector <float> allvideoHistory;
		vector <float> x10volHistory;
		vector <float> x10videoHistory;
		
		int 	bufferCounter;
		int 	drawCounter;
		int     videobufferCounter;

		float smoothedVol;
		float scaledVol;
		float allscaledVol;
		float x10scaledVol;
		float brightness;
		float allbrightness;
		float x10brightness;

		float r;
		float g;
		float b;
		
		ofSoundStream soundStream;
	
		ofVideoGrabber video;
		float camWidth ;
		float camHeight ;
		ofPixels pixels;
		

};
