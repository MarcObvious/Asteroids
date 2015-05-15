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


class ofApp: public ofBaseApp {

public:
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

	ofSoundPlayer  * pium;
	ofSoundPlayer * explosion;

	ofSerial	serial;

	bool debug;
	Player* guanyador;


};
