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
int MAX_SCORE = 300;
int MAX_LIVES = 50;
int INITIAL_SCORE = 0;

//--------------------------------------------------------------


void ofApp::setup() {
	// Set framerate to 60 FPS
	ofSetFrameRate(60);

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

	naus.push_back(nau);

	nau = new SpaceShip();

	nau->setup(shape, 40, 500, 50,
			ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));

	PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,0,255));

	naus.push_back(nau);

	nau = new SpaceShip();

	nau->setup(shape, 40, 500, 50,
			ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));

	PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,255,0));

	naus.push_back(nau);


	nau = new SpaceShip();

	nau->setup(shape, 40, 500, 50,
				ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));

	PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,255,255));

	naus.push_back(nau);

	nau = new SpaceShip();

		nau->setup(shape, 40, 500, 50,
				ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));

		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(255,255,0));

		naus.push_back(nau);

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

	cout << PlayerManager::getInstance()->getAllScores();

}
//Destructor (teniem problemes amb eliminar l'audio)
ofApp::~ofApp(){

	for(unsigned int i = 0; i < naus.size(); i++)
		free(naus[i]);
	naus.clear();

	if (pium->isLoaded()){
		pium->stop();
		pium->unloadSound();
	}
	free (pium);
	if (explosion->isLoaded()){
		explosion->stop();
		explosion->unloadSound();
	}
	free( explosion);
}

//--------------------------------------------------------------
void ofApp::update() {

	//Preguntem a PlayerManager si hi ha guanyador, si n'hi ha no updategem res.
	guanyador = PlayerManager::getInstance()->hihaguanyador(MAX_SCORE);
	if (guanyador == NULL){

		// We get the time that last frame lasted, and use it to update asteroids logic
		// so their behaviour is independent to the framerate
		float elapsedTime = ofGetLastFrameTime();

		//Comprova colisions d'Asteroides (amb bullets i amb Players)
		AsteroidManager::getInstance()->comprova();

		//Fa els updates de tot
		BulletManager::getInstance()->update(elapsedTime);
		AsteroidManager::getInstance()->update(elapsedTime);

		for(unsigned int i = 0; i < naus.size(); i++)
			naus[i]->update( elapsedTime );

	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	//Si algu ha guanyat nomes dibuixem la pantalla de restart
	if ( guanyador ) {
		ofPushStyle();
			ofSetColor(guanyador->getColor());
			stringstream id;
			id << "Press 'r' to restart. WINER JUGADOR ";
			id << guanyador->getId();
			id << " -> SCORE = ";
			id << guanyador->getScore();
			ofDrawBitmapString(id.str(), 390, 450);
		ofPopStyle();
	}
	else {

		//Dibuixem instruccions
		ofPushStyle();
			ofSetColor(255,255,255);
			ofDrawBitmapString("Player 1 a w d s, Player 0 up, left, right, down .Press '1' to debug, '2' to mute", 5, 760);
		ofPopStyle();


		//Draw Scores
		PlayerManager::getInstance()->drawScores();

		//Dibuixem totes les bales i asteroides
		BulletManager::getInstance()->draw();
		AsteroidManager::getInstance()->draw(debug);

		//Dibuixem totes les naus
		for(unsigned int i = 0; i < naus.size(); i++)
			naus[i]->draw( debug );

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
		reset();
		break;
		//----------------------------------------------------------------------
	}
}
//Reset del joc.
void ofApp::reset() {

	BulletManager::getInstance()->reset();
	AsteroidManager::getInstance()->reset();


	free(pium);
	free(explosion);

//	for(unsigned int i = 0; i < naus.size(); i++)
//		free(naus[i]);
	naus.clear();

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




