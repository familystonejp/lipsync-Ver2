#include "ofApp.h"

//プロジェクト→ソリューションの再ターゲットをする。

//--------------------------------------------------------------
void ofApp::setup(){	 
	
	ofSetVerticalSync(true);
	ofBackground(34);	 
	ofSetFrameRate(60);
	ofSetWindowTitle("BRIDGE");
	//soundStream.printDeviceList();
	int bufferSize = 256;

	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(512, 0.0);
	videoHistory.assign(512, 0.0);
	allvolHistory.assign(129, 0.0);
	allvideoHistory.assign(129, 0.0);
	x10volHistory.assign(111, 0.0);
	x10videoHistory.assign(111, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
	allscaledVol    = 0.0;
	x10scaledVol    = 0.0;
	brightness      = 0.0;
	allbrightness   = 0.0;
	x10brightness   = 0.0;

	ofSoundStreamSettings settings;

	// if you want to set the device id to be different than the default
	//auto devices = soundStream.getDeviceList();
	//settings.device = devices[4];

	// you can also get devices for an specific api
	// auto devices = soundStream.getDevicesByApi(ofSoundDevice::Api::PULSE);
	// settings.device = devices[0];

	// or get the default device for an specific api:
	// settings.api = ofSoundDevice::Api::PULSE;

	// or by name
	auto devices = soundStream.getMatchingDevices("default");
	
	if(!devices.empty()){
		settings.setInDevice(devices[0]);
	}
	settings.setApi(ofSoundDevice::Api::MS_DS);// = ofSoundDevice::Api::MS_DS;
	settings.setInListener(this);
	settings.sampleRate = 44100;
	settings.numOutputChannels = 2;
	settings.numInputChannels = 2;
	settings.bufferSize = bufferSize;
	soundStream.setup(settings);

	video.listDevices();
	video.setDeviceID(1);	
	video.setDesiredFrameRate(30);
	video.initGrabber(1280, 720);
	ofPixels pixels = video.getPixels();
	pixels.allocate(1280, 720 , OF_IMAGE_COLOR);
	ofSetVerticalSync(true);
	camWidth = 640;
	camHeight = 360;


	//pixels.allocate(camWidth, camHeight, GL_RGB);
	//ofSetVerticalSync(true);


}

//--------------------------------------------------------------
void ofApp::update() {

	video.update();
	/*if (video.isFrameNew()) {
		video.update();
	}*/

	ofPixels pixels = video.getPixels();
	

	if (video.isFrameNew()) {
		ofPixels& pixels = video.getPixels();
		for (size_t i = 0; i < pixels.size(); i+=10) {	
		
		}
	}
	
	float r = (float)pixels[(camWidth) * 3];
	float g = (float)pixels[(camWidth) * 3 + 1];
	float b = (float)pixels[(camWidth) * 3 + 2];

			float brightness = (r + g + b)/3;

			brightness = ofMap(brightness, 0.0, 255.0, 0.0, 1.0, true);

			videoHistory.push_back(brightness);

			//video if we are bigger the the size we want to record - lets drop the oldest value
			if (videoHistory.size() >= 512) {
				videoHistory.erase(videoHistory.begin(), videoHistory.begin() + 1);	
	}

			float allbrightness = (r + g + b) / 3;

			allbrightness = ofMap(allbrightness, 0.0, 255.0, 0.0, 10.0, true);

			allvideoHistory.push_back(allbrightness * 2);
			//video if we are bigger the the size we want to record - lets drop the oldest value
			if (allvideoHistory.size() >= 129) {
				allvideoHistory.erase(allvideoHistory.begin(), allvideoHistory.begin() + 1);
			}


			float x10brightness = (r + g + b) / 3;

			x10brightness = ofMap(x10brightness, 0.0, 255.0, 0.0, 10.0, true);

			x10videoHistory.push_back(x10brightness * 2);

			//video if we are bigger the the size we want to record - lets drop the oldest value
			if (x10videoHistory.size() >= 111) {
				x10videoHistory.erase(x10videoHistory.begin(), x10videoHistory.begin() + 1);
			}


	//lets scale the vol up to a 0-1 range 
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);

	//lets record the volume into an array
	volHistory.push_back(scaledVol);

	//sound if we are bigger the the size we want to record - lets drop the oldest value
	if (volHistory.size() >= 512) {
		volHistory.erase(volHistory.begin(), volHistory.begin() + 1);
	}

	//lets scale the vol up to a 0-1 range 
	allscaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 10.0, true);

	//lets record the volume into an array
	allvolHistory.push_back(allscaledVol*2);

	//sound if we are bigger the the size we want to record - lets drop the oldest value
	if (allvolHistory.size() >= 129
		) {
		allvolHistory.erase(allvolHistory.begin(), allvolHistory.begin() +1);
	}


	//lets scale the vol up to a 0-1 range 
	x10scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 10.0, true);

	//lets record the volume into an array
	x10volHistory.push_back(x10scaledVol * 2);

	//sound if we are bigger the the size we want to record - lets drop the oldest value
	if (x10volHistory.size() >= 111) {
		x10volHistory.erase(x10volHistory.begin(), x10volHistory.begin() + 1);
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(255);
	ofDrawBitmapString("LIP SYNC CHECKER", 82, 90
	);
	ofDrawBitmapString("BRIDGE", 82, 110);
	ofDrawBitmapString("Check the video ID at the command prompt and press the keyboard input number.", 82, 980);
	ofDrawBitmapString("If you make a mistake in the number, please restart it (it will be resolved in a future update).", 82,1000);
	ofNoFill();
//////////////////////////////////////////////////////////////////////////////////////////
// draw the video channel:
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(82, 120, 0);
	ofSetColor(225);

	ofPushStyle();
	ofFill();
	ofSetColor(54);
	ofDrawRectangle(0, 0, 512, 200);
	ofSetColor(0);
	ofDrawRectangle(384, 0, 128, 200);
	ofSetColor(255);
	ofDrawLine(384, 0, 384, 200);
	ofPopStyle();

	ofDrawBitmapString("video Channel", 4, 18);


	ofSetLineWidth(1);
	ofDrawRectangle(0, 0, 512, 200);

	ofSetColor(10, 245, 35);
	ofSetLineWidth(3);

	ofBeginShape();
	for (unsigned int i = 0; i < videoHistory.size(); i++) {
		if (i == 0) ofVertex(i, 200);

		ofVertex(i, 200 - videoHistory[i] * 180.0f);

		if (i == videoHistory.size() - 1) ofVertex(i, 200);
	}
	ofEndShape(false);

	ofPopMatrix();
	ofPopStyle();
///////////////////////////////////////////////////////////////////////////////////
// draw the sound channel:
ofPushStyle();
 ofPushMatrix();
	ofTranslate(82, 320, 0);
	ofSetColor(225);

	ofPushStyle();
	ofFill();
	ofSetColor(54);
	ofDrawRectangle(0, 0, 512, 200);
	ofSetColor(0);
	ofDrawRectangle(384, 0, 128, 200);
	ofSetColor(255);
	ofDrawLine(384, 0, 384, 200);
	ofPopStyle();

	ofDrawBitmapString("sound Channel", 4, 18);

	ofSetLineWidth(1);
	ofDrawRectangle(0, 0, 512, 200);

	ofSetColor(255, 68, 145);
	ofSetLineWidth(3);

	ofBeginShape();
	for (unsigned int i = 0; i < volHistory.size(); i++) {
		if (i == 0) ofVertex(i, 200);
		ofVertex(i, 200 - volHistory[i] * 200);
		if (i == volHistory.size() - 1) ofVertex(i, 200);
	}
	ofEndShape(false);

 ofPopMatrix();
ofPopStyle();
/////////////////////////////////////////////////////////////////////////////////////////
	// draw the average volume x4:
ofPushStyle();
 ofPushMatrix();
	ofTranslate(604, 120, 0);

	ofPushStyle();
	  ofFill();
	  ofSetColor(0);
	  ofDrawRectangle(0, 0, 512, 400);
	ofPopStyle();

	ofSetColor(255);
	ofDrawBitmapString("Sound  vol (0-100): " + ofToString(scaledVol * 100, 0), 4, 118);
	ofDrawBitmapString("x4", 490, 118);
	ofDrawLine(0, 100, 512, 100);
	ofSetColor(255, 68, 145);


	//lets draw the sound history as a graph
	ofBeginShape();
	for (unsigned int i = 0; i < allvolHistory.size(); i++) {
		if (i == 0) ofVertex(i*4 , 400);

		ofVertex(i*4 , 400 - allvolHistory[i] * 12.0f);

		if (i == allvolHistory.size() -1) ofVertex(i*4 , 400);
	}
	ofEndShape(false);

	ofPushStyle();
	ofSetColor(10, 245, 35);

	//lets draw the video history as a graph
	ofBeginShape();
	for (unsigned int i = 0; i < allvideoHistory.size(); i++) {
		if (i == 0) ofVertex(i*4 , 400);

		ofVertex(i*4 , 400 - allvideoHistory[i] * 12.0f);

		if (i == allvideoHistory.size() - 1) ofVertex(i*4 , 400);
	}
	ofEndShape(false);
	ofPopStyle();

	ofPushStyle();
	ofSetColor(54, 200, 255);
	ofSetLineWidth(5);

	//lets draw the right vol as a graph
	ofBeginShape();
	for (unsigned int i = 0; i < right.size(); i++) {
		ofVertex(i * 2, 50 - right[i] * 180.0f);
	}
	ofEndShape(false);
	ofPopStyle();


	ofSetColor(225);
	ofDrawRectangle(0, 0, 512, 400);	

 ofPopMatrix();
ofPopStyle();

////////////////////////////////////////////////////////////////////////////////
// draw the video in:
ofPushStyle();
ofPushMatrix();
ofTranslate(1126, 120, 0);

ofPushStyle();
ofNoFill();
ofSetColor(255);
ofDrawRectangle(0, 0, 712, 400.5);
ofPopStyle();

video.draw(0, 0, 712, 400.5);
ofDrawBitmapString("video in ", 4, 18);
ofSetColor(255, 10, 35);
ofFill();
ofDrawCircle(680, 30, scaledVol * 20.0f);

ofPopMatrix();
ofPopStyle();


/////////////////////////////////////////////////////////////////////////////////////////
	// draw the average volume x16:
ofPushStyle();
ofPushMatrix();
ofTranslate(82, 550, 0);

ofPushStyle();
ofFill();
ofSetColor(0);
ofDrawRectangle(0, 0, 1757, 400);
ofPopStyle();

ofSetColor(255);
//ofDrawBitmapString("Sound  vol (0-100): " + ofToString(scaledVol * 100, 0), 4, 118);
ofDrawBitmapString("x16", 1727, 20);
//ofDrawLine(0, 100, 512, 100);
ofSetColor(255, 68, 145);


//lets draw the sound history as a graph
ofBeginShape();
for (unsigned int i = 0; i < x10volHistory.size(); i++) {
	if (i == 0) ofVertex(i * 16, 400);

	ofVertex(i * 16, 400 - x10volHistory[i] * 18.0f);

	if (i == x10volHistory.size() - 1) ofVertex(i * 16, 400);
}
ofEndShape(false);

ofPushStyle();
ofSetColor(10, 245, 35);

//lets draw the video history as a graph
ofBeginShape();
for (unsigned int i = 0; i < x10videoHistory.size(); i++) {
	if (i == 0) ofVertex(i * 16, 400);

	ofVertex(i * 16, 400 - x10videoHistory[i] * 18.0f);

	if (i == x10videoHistory.size() - 1) ofVertex(i * 16, 400);
}
ofEndShape(false);
ofPopStyle();

ofSetColor(225);
ofDrawRectangle(0, 0, 1757, 400);

ofPopMatrix();
ofPopStyle();


////////////////////////////////////////////////////////////////////////////////

	drawCounter++;
	
	ofSetColor(225);
	string reportString = "buffers received: "+ofToString(bufferCounter)+"\ndraw routines called: "+ofToString(drawCounter)+"\nticks: " + ofToString(soundStream.getTickCount());
	ofDrawBitmapString(reportString, 86, 910);
		
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;	

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (size_t i = 0; i < input.getNumFrames(); i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;

		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :) 
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.2* curVol;
	
	bufferCounter++;
	
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	//switch (key){
	//	case '0':
	//		video.setDeviceID(0);
	//		video.update();
	//	    break;

	//	case '1':
	//		video.setDeviceID(1);
	//		video.update();
	//		break;
	//}
	
	if( key == '0' ){
		video.setDeviceID(0);
		video.update();

	}
	
	if( key == '1' ){
		video.setDeviceID(1);
		video.initGrabber( camWidth, camHeight);
		video.update();
	}
	

	if (key == '2') {
		video.setDeviceID(2);
		video.update();
	}
	

	if (key == '3') {
		video.setDeviceID(3);
		video.update();
	}

	if (key == '4') {
		video.setDeviceID(4);
		video.update();
	}

	if (key == '5') {
		video.setDeviceID(5);
		video.update();
	}

	if (key == '6') {
		video.setDeviceID(6);
		video.update();
	}


	video.setDesiredFrameRate(60);
	video.initGrabber(camWidth, camHeight);
	camWidth = 640;
	camHeight = 360;
	pixels.allocate(camWidth, camHeight, GL_RGB);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	//if (key == 'f') {
	//	ofToggleFullscreen();
	//}
	
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

