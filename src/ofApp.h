//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#pragma once

#include "ofMain.h"

#include "ofxXmlSettings.h"

#include "Asteroid.h"
#include "Bullet.h"
#include "SpaceShip.h"
#include "Player.h"
#include "AsteroidManager.h"
#include "PlayerManager.h"

#define NUM_BYTES 8

class ofApp: public ofBaseApp {

public:
	static ofEvent<ofPoint> ArdEvent;

	~ofApp();
	void setup();
	void setupArduino();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void reset();
	void killSound();


private:

	void normalizeOfPoint(ofPoint& point);
	void arduinoUpdate();

	ofSoundPlayer  * pium;
	ofSoundPlayer * explosion;

	//ARDUINO
	ofSerial	serial;
	int cyclesCounter;
	int cyclesJumped;
	bool readAndSendMessage;
	unsigned char receivedBytes[NUM_BYTES];
	int primer_cop;

	bool debug;
	Controlador* guanyador;


};
