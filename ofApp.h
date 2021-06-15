/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

/************************************************************
************************************************************/

class ofApp : public ofBaseApp{
private:
	enum{
		WINDOW_WIDTH	= 1280,
		WINDOW_HEIGHT	= 720,
	};
	
	enum{
		N					= 256, //Number of bands in spectrum
		NUM_CLOUD_POINTS	= 400,
	};

	
	ofSoundPlayer sound;
	
	float spectrum[ N ];	//Smoothed spectrum values
	float Rad = 500;		//Cloud raduis parameter
	float Vel = 0.1;		//Cloud points velocity parameter
	int bandRad = 2;		//Band index in spectrum, affecting Rad value
	int bandVel = 100;		//Band index in spectrum, affecting Vel value
	
	ofVec2f t_noise[NUM_CLOUD_POINTS];
	ofPoint p_cloud[NUM_CLOUD_POINTS];
	float add_color = 0;
	
	float t_Last = 0;
	
	ofImage img;
	

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
	
};
