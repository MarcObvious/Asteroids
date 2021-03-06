//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#pragma once

#include "ofMain.h"

#include "ofxXmlSettings.h"
#include "ofxOsc.h"

#include "Asteroid.h"
#include "Bullet.h"
#include "SpaceShip.h"
#include "Player.h"
#include "AsteroidManager.h"
#include "PlayerManager.h"

//defs per sender/receiver
#define PORT 12345
#define NUM_PTS 800

//Bytes per arduino
#define NUM_BYTES 4

class ofApp: public ofBaseApp {

public:
	static ofEvent<ofPoint> ArdEvent;
	static ofEvent<Missatge> NetEvent;
	
	ofApp(int cli, int SO, string Host);
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
	void finish();
	void killSound();
	void enviairep();
	void spaceshipEsMou(Missatge& ordre);
	void enviaBi(string ordre);


private:

	void normalizeOfPoint(ofPoint& point);
	void arduinoUpdate();

	ofSoundPlayer  * pium;
	ofSoundPlayer * explosion;

	int sistemaOp;
	//SenderReceiver
	int clientServidor;
	string s_clientServidor;

	ofxOscSender sender;
	ofxOscReceiver receiver;

	//ARDUINO
	ofSerial	serial;
	int cyclesCounter;
	int cyclesJumped;
	bool readAndSendMessage;
	
	string Host;

	bool acaba_partida;

	bool debug;
	Controlador* guanyador;

};
