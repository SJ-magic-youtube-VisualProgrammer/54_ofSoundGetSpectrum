#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	ofSetBackgroundAuto(true);
	
	ofSetWindowTitle("DaicingCloud");
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	ofEnableAlphaBlending();
	// ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	// ofEnableSmoothing();
	
	/********************
	********************/
	sound.load( "audioblocks-awesome-tropical-house_r6SxbK4-U.mp3" );	
	sound.setLoop( true );
	sound.play();

	for (int i=0; i<N; i++) {
		spectrum[i] = 0.0f;
	}

	for ( int j=0; j<NUM_CLOUD_POINTS; j++ ) {
		t_noise[j].x = ofRandom( 0, 1000 );
		t_noise[j].y = ofRandom( 0, 1000 );
	}
	
	/********************
	********************/
	img.load("img.png");

}

//--------------------------------------------------------------
void ofApp::update(){
	/********************
	********************/
	ofSoundUpdate();

	/********************
	Get current spectrum with N bands
	We should not release memory of val,
	because it is managed by sound engine
	********************/
	float *val = ofSoundGetSpectrum( N );

	/********************
	smoothing
	********************/
	for ( int i=0; i<N; i++ ) {
		spectrum[i] *= 0.97;
		spectrum[i] = max( spectrum[i], val[i] );
	}

	/********************
	********************/
	float now = ofGetElapsedTimef();
	float dt = now - t_Last;
	dt = ofClamp( dt, 0.0, 0.1 );	
	t_Last = now;

	Rad = ofMap( spectrum[ bandRad ], 1, 3, 400, 800, true );
	Vel = ofMap( spectrum[ bandVel ], 0, 0.1, 0.05, 0.5 );
	
	add_color = ofMap( spectrum[ bandRad ], 1, 3, 0, 255, true );
	
	for (int j = 0; j < NUM_CLOUD_POINTS; j++) {
		t_noise[j].x += Vel * dt;
		t_noise[j].y += Vel * dt;
		
		p_cloud[j].x = ofSignedNoise( t_noise[j].x ) * Rad;		
		p_cloud[j].y = ofSignedNoise( t_noise[j].y ) * Rad;	
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	/********************
	********************/
	ofBackground(0, 0, 0);

	/********************
	********************/
	ofSetColor(255, 255, 255, 100);
	img.draw(0, 0);
	
	/********************
	********************/
	//Draw background rect for spectrum
	ofSetColor(255, 255, 255, 10);
	ofFill();
	ofDrawRectangle( 0, 700, N * 5, -100 );

	// spectrum
	for (int i = 0; i < N; i++) {
		if ( i == bandRad || i == bandVel )	ofSetColor( 0, 255, 0 , 150);
		else								ofSetColor( 0, 100, 255, 150 );
		
		ofDrawRectangle( i * 5, 700, 3, -spectrum[i] * 100 );
	}

	/********************
	Dancing cloud
	********************/
	ofPushMatrix();
		ofTranslate( ofGetWidth() / 2, ofGetHeight() / 2 );
	
		//Draw points
		ofColor base(10, 100, 255);
		ofSetColor( min(base.r + (int)add_color, 255), min(base.g + (int)add_color, 255), min(base.b + (int)add_color, 255), 150);
		
		ofFill();
		for (int i=0; i<NUM_CLOUD_POINTS; i++) {
			ofDrawCircle( p_cloud[i], 2 );
		}
	
		//Draw lines between near points
		glLineWidth(1);
		float thresh_dist = 40;
		for (int j=0; j<NUM_CLOUD_POINTS; j++) {
			for (int k=j+1; k<NUM_CLOUD_POINTS; k++) {
				if ( ofDist( p_cloud[j].x, p_cloud[j].y, p_cloud[k].x, p_cloud[k].y ) < thresh_dist ) {
					ofDrawLine( p_cloud[j], p_cloud[k] );
				}
			}
		}
	
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
