//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "ofApp.h"

//Patrons Singleton que gestionaran les Bullets, els Asteroides i  els Jugadors
BulletManager* BulletManager::_instance = NULL;
AsteroidManager* AsteroidManager::_instance = NULL;
PlayerManager* PlayerManager::_instance = NULL;

//Variables globals que defineixen les vides i la puntuacio maxima
int MAX_SCORE = 500;
int MAX_LIVES = 10;
int INITIAL_SCORE = 0;
ofEvent<ofPoint> ofApp::ArdEvent = ofEvent<ofPoint>();

//--------------------------------------------------------------

void ofApp::setupArduino() {
	if (!serial.isInitialized()) {
		serial.listDevices();
		vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();

		// Diferents configuracions segons Mac Linux o Windows
		int baud = 9600;
		serial.setup("COM4", baud); // Windows
		//serial.setup("/dev/tty.usbserial-A4001JEC", baud);  //Mac
		//serial.setup("/dev/ttyACM0", baud); //Linux powa!
	}

	cyclesCounter = 0;
	cyclesJumped = 5;

	readAndSendMessage = false;

	memset(receivedBytes, 0, NUM_BYTES);


}


void ofApp::setup() {
	// Set framerate to 60 FPS
	ofSetFrameRate(60);

	//Posem Arduino a punt
	setupArduino();

	// Load Asteroids from XML
	AsteroidManager::getInstance()->loadAsteroids();

	// Create Asteroids
	AsteroidManager::getInstance()->generateAsteroids(4);


	//Manera cutre d'afegir la forma (vertex) de les nostres naus (tenen la mateixa forma
	vector<ofPoint> shape = vector<ofPoint>();
	shape.push_back(ofPoint(-25, 25));
	shape.push_back(ofPoint(35,0));
	shape.push_back(ofPoint(-25,-25));
	shape.push_back(ofPoint(-25, 25));

	//Demanem al PlayerManager que ens creei un Player, amb la Spaceship que vulgueem
	//Setup Players amb les seves Naus

	///tot això ho hauria de fer un parser.
	SpaceShip* nau = new SpaceShip();

	nau->setup(shape, 40, 500, 50,
			ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));

	PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(255,0,0));

	nau = new SpaceShip();

	nau->setup(shape, 40, 500, 50,
			ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));

	PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,0,255));

	nau = new SpaceShip();

	nau->setup(shape, 40, 500, 50,
			ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));

	PlayerManager::getInstance()->createPlayerArd(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,255,0));


//	nau = new SpaceShip();
//
//	nau->setup(shape, 40, 500, 50,
//			ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));
//
//	PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,255,255));
//
//	nau = new SpaceShip();
//
//	nau->setup(shape, 40, 500, 50,
//			ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));
//
//	PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(255,255,0));


	//Carreguem els sons d'explosions d'asteroides i de dispars
	//ESTA SILENCIAT ARA MATEIX
	explosion = new ofSoundPlayer();
	explosion->loadSound("sounds/explosion.mp3", false);
	AsteroidManager::getInstance()->setExplosionSound(NULL);

	pium = new ofSoundPlayer();
	pium->loadSound("sounds/lasergun.mp3", false);
	BulletManager::getInstance()->setBulletSound(NULL);

	// General logic
	ofBackground(0); // Set background to black

	// Debug
	debug = false;


}

ofApp::~ofApp(){

}
//FUCK AUDIO!
void ofApp::killSound() {
	if (pium->isLoaded()){
		pium->stop();
		pium->unloadSound();
	}
	if (explosion->isLoaded()){
		explosion->stop();
		explosion->unloadSound();
	}
}



void ofApp::arduinoUpdate() {
	if(readAndSendMessage) {
		
		unsigned char enviar[1];
		//memset(enviar, 0, 4);
		enviar[0] = 'A';
	/*	enviar[1] = 'A';
		enviar[2] = 'A';
		enviar[3] = '\n';*/
		if (guanyador != NULL){
			switch (guanyador->getId()) {
			case 0:
				enviar[0] = 'Z';
			/*	enviar[1] = 'Z';
				enviar[2] = 'Z';
				enviar[3] = '\0';*/
				//cout << "GUANYADOR z" <<endl;
			break;
			case 1:
				enviar[0] = 'U';
			/*	enviar[1] = 'U';
				enviar[2] = 'U';
				enviar[3] = '\0';*/
			//	cout << "GUANYADOR U" <<endl;
			break;
			case 2:
				enviar[0] = 'D';
			/*	enviar[1] = 'D';
				enviar[2] = 'D';
				enviar[3] = '\0';*/
			//	cout << "GUANYADOR T" <<endl;
			break;
			case 3:
				enviar[0] = 'T';
			/*	enviar[1] = 'T';
				enviar[2] = 'T';
				enviar[3] = '\0';*/
			//	cout << "GUANYADOR D" <<endl;
			break;
			case 4:
				enviar[0] = 'Q';
				/*enviar[1] = 'Q';
				enviar[2] = 'Q';
				enviar[3] = '\0';*/
				//cout << "GUANYADOR Q" <<endl;
			break;
			
		
		}
		
		}
		serial.writeBytes(enviar,1);
		
		if(serial.available()) {
			int x; int y;
			//const int NUM_BYTES = 4;
			unsigned char bytesReturned[4];
			memset(bytesReturned, 0, 4); //Set 0 for NUM_BYTES in bytesReturned
			while(serial.readBytes(bytesReturned, 4) > 0){ }
			//X-Axis 
			x = bytesReturned[0];
			x <<= 8;
			x += bytesReturned[1];
			//Y-Axis
			y = bytesReturned[2];
			y <<= 8;
			y += bytesReturned[3];
			cout << "X " << x << " Y " << y <<endl;
			if (x == 0 && y == 0)
				reset();
			
			else {
				if (x > 0 && x < 770) {
					if (y > 0 && y < 770) {
						//cout << "X " << pos_x << " Y " << pos_y << endl;
						ofPoint pos = ofPoint(x,y);
						ofNotifyEvent(ArdEvent, pos, this);

					}
				}
			}
		}
		readAndSendMessage = false;
	}

	cyclesCounter++;
	if(cyclesCounter >= cyclesJumped){
		readAndSendMessage = true;
		cyclesCounter = 0;
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	// We get the time that last frame lasted, and use it to update asteroids logic
	// so their behaviour is independent to the framerate
	float elapsedTime = ofGetLastFrameTime();

	//Preguntem a PlayerManager si hi ha guanyador, si n'hi ha no updategem res.
	guanyador = PlayerManager::getInstance()->hihaguanyador(MAX_SCORE);
	if (guanyador == NULL){

		//Comprova colisions d'Asteroides (amb bullets i amb Players)
		AsteroidManager::getInstance()->comprova();

		//Fa els updates de tot
		BulletManager::getInstance()->update(elapsedTime);
		AsteroidManager::getInstance()->update(elapsedTime);
		PlayerManager::getInstance()->update(elapsedTime);


	}
	//AQUI ES REP I S'ENVIA A ARDUINO
	arduinoUpdate();
}	

//--------------------------------------------------------------
void ofApp::draw() {
	//Si algu ha guanyat nomes dibuixem la pantalla de restart
	if ( guanyador ) {
		ofPushStyle();
		ofSetColor(guanyador->getColor());
		stringstream id;
		id << "WINER JUGADOR ";
		id << guanyador->getId();
		id << " -> SCORE = ";
		id << guanyador->getScore();
		ofDrawBitmapString(id.str(), 390, 450);
		ofPopStyle();
		ofDrawBitmapString("Press 'r' to restart.", 390, 470);
	}
	else {

		//Dibuixem instruccions
		ofPushStyle();
		ofSetColor(255,255,255);
		ofDrawBitmapString("Player 1 a w d s, Player 0 up, left, right, down .Press '1' to debug, '2' to mute", 5, 760);
		ofPopStyle();


		//Draw Scores
		//PlayerManager::getInstance()->drawScores();

		//Dibuixem totes les bales i asteroides
		BulletManager::getInstance()->draw();
		AsteroidManager::getInstance()->draw(debug);
		PlayerManager::getInstance()->draw(debug);


		if (debug) {
			ofPushStyle();
			ofSetColor(255);
			ofDrawBitmapString(ofToString(ofGetFrameRate()), 900, 20);
			ofPopStyle();
		}
	}
}


void ofApp::keyPressed(int key) {
	switch (key) {
	// If pressed 1 change debug mode
	case '1':
		debug = !debug;
		break;
		// Apretem 2 silenciem, no silenciem
	case '2':
		if (explosion->isLoaded()) {
			explosion->unloadSound();
			AsteroidManager::getInstance()->setExplosionSound(NULL);
		}
		else {
			explosion->loadSound("sounds/explosion.mp3", false);
			AsteroidManager::getInstance()->setExplosionSound(explosion);
		}
		if (pium->isLoaded()) {
			pium->unloadSound();
			BulletManager::getInstance()->setBulletSound(NULL);
		}
		else {
			pium->loadSound("sounds/explosion.mp3", false);
			BulletManager::getInstance()->setBulletSound(pium);
		}
		break;
		//r, ressetegem el joc
	case 'r':
		cout << "Reset at:" << endl;
		cout << PlayerManager::getInstance()->getAllScores();
		reset();
		break;
		//----------------------------------------------------------------------
	}
}
//Reset del joc.
void ofApp::reset() {

	BulletManager::getInstance()->reset();
	AsteroidManager::getInstance()->reset();

	killSound();

	guanyador = NULL;

	PlayerManager::getInstance()->reset();

	setup();

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	//	for (int i = 0; i < asteroids.size(); i++) {
	//		if (asteroids[i]->getCollision(ofPoint(x, y))) {
	//			cout << "Mouse hit Asteroid " << i << endl;
	//			splitAsteroid(i);
	//
	//		}
	//	}
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}




