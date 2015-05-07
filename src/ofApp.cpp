//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "ofApp.h"

//Patrons Singleton que gestionaran les Bullets, els Asteroides i  els Jugadors
BulletManager* BulletManager::_instance = NULL;
AsteroidManager* AsteroidManager::_instance = NULL;
PlayerManager* PlayerManager::_instance = NULL;

//Variables globals que defineixen les vides i la puntuaci maxima
int MAX_SCORE = 1000;
int MAX_LIVES = 50;

//--------------------------------------------------------------


void ofApp::setup() {
	// Set framerate to 60 FPS
	ofSetFrameRate(60);

	// Load Asteroids from XML
	AsteroidManager::getInstance()->loadAsteroids();

	// Create Asteroids
	AsteroidManager::getInstance()->generateAsteroids(4);

	// TODO
	// Setup the following elements:
	// - players
	// - listeners? (depends on how you handle messages between entities)

	//Demanem al PlayerManager que ens creei un Player, amb la Spaceship que vulgueem
	nau1 = new SpaceShip();
	PlayerManager::getInstance()->createPlayer(nau1, 0, MAX_LIVES, ofColor(255,0,0));

	nau2 = new SpaceShip();
	PlayerManager::getInstance()->createPlayer(nau2, 0, MAX_LIVES, ofColor(0,0,255));

	//Carreguem els sons d'explosions d'asteroides i de dispars
	explosion = new ofSoundPlayer();
	explosion->loadSound("sounds/explosion.mp3", false);
	AsteroidManager::getInstance()->setExplosionSound(explosion);

	pium = new ofSoundPlayer();
	pium->loadSound("sounds/lasergun.mp3", false);
	BulletManager::getInstance()->setBulletSound(pium);




	//Manera cutre d'afegir la forma (vertex) de les nostres naus (tenen la mateixa forma
	vector<ofPoint> shape = vector<ofPoint>();
	shape.push_back(ofPoint(-25, 25));
	shape.push_back(ofPoint(35,0));
	shape.push_back(ofPoint(-25,-25));
	shape.push_back(ofPoint(-25, 25));


	nau1->setup(shape, 40, 500, 50,
			ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));
	nau2->setup(shape, 40, 500, 50,
			ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));



	// General logic
	ofBackground(0); // Set background to black

	// Debug
	debug = false;


}
//Destructor (teniem problemes amb eliminar l'audio)
ofApp::~ofApp(){

	free (nau1);
	free (nau2);

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

	//Escriu per terminal la data dels scores
	//	cout << PlayerManager::getInstance()->getAllScores();

	//Preguntem a PlayerManager si hi ha guanyador, si n'hi ha no updategem res.
	guanyador = PlayerManager::getInstance()->hihaguanyador(MAX_SCORE);
	if (guanyador == NULL){


		// We get the time that last frame lasted, and use it to update asteroids logic
		// so their behaviour is independent to the framerate
		float elapsedTime = ofGetLastFrameTime();

		// TODO
		// Implement calls for logic:
		// - players
		// - bullets
		// - collisions
		// - game conditions
		// [...]

		//Comprova colisions d'Asteroides (amb bullets i amb Players)
		AsteroidManager::getInstance()->comprova();

		//Fa els updates de tot
		BulletManager::getInstance()->update(elapsedTime);
		AsteroidManager::getInstance()->update(elapsedTime);
		//Hagues sigut mes elegant utilitzar Playermanager (que tambè te un punter a nau) per fer l'update. Mes endevant.
		nau1->update(elapsedTime);
		nau2->update(elapsedTime);

	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	//Si algu ha guanyat nomes dibuixem la pantalla de restart
	if ( guanyador ) {
		ofPushStyle();
		ofSetColor(guanyador->getColor());
		ofDrawBitmapString("A guanyat aquest color, press 'r' to restart.", 390, 450);
		ofPopStyle();
	}
	else {

		//Dibuixem els scores i les instruccions
		ofPushStyle();
			ofSetColor(255,255,255);
			ofDrawBitmapString(PlayerManager::getInstance()->getAllScores(), 5, 15);
			ofDrawBitmapString("Player 1 a w d s, Player 0 up, left, right, down .Press '1' to debug, '2' to mute", 5, 760);
		ofPopStyle();

		// TODO
		// Draw all game entities (bullets? players? effects?)

		//Dibuixem totes les bales i asteroides
		BulletManager::getInstance()->draw();
		AsteroidManager::getInstance()->draw(debug);

		//Altre cop hauria sigut mes elegant dibuixar desde PlayerManager. Obviament. Mes endevant.

			nau1->draw(debug);

			nau2->draw(debug);

		if (debug) {
			ofPushStyle();
			ofSetColor(255);
			ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 20);
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
	PlayerManager::getInstance()->reset();
	free(pium);
	free(explosion);
	setup();
	guanyador = NULL;
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




