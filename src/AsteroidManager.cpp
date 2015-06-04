//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "PlayerManager.h"
#include "AsteroidManager.h"


AsteroidManager::AsteroidManager() {
	assert(_instance == NULL); //Si no es cumpleix PETA
	_instance = this;
}

vector<Asteroid*> AsteroidManager::getAsteroids() const {
	return _asteroids;
}

vector<vector<ofPoint> > AsteroidManager::getAsteroidsDefinitions() const {
	return asteroidsDefinitions;
}

void AsteroidManager::setAsteroidsDefinitions(
		vector<vector<ofPoint> > asteroidsDefinitions) {
	this->asteroidsDefinitions = asteroidsDefinitions;
}

void AsteroidManager::setAsteroids(vector<Asteroid*> asteroids) {
	_asteroids = asteroids;
}

void AsteroidManager::reset(){
	_asteroids.clear();
}
AsteroidManager::~AsteroidManager() {
	free(_instance);
	_asteroids.clear();
}

//ES UN SINGLETON, NOMES POT HAVERHI UNA INSTANCIA ACTIVA
AsteroidManager * AsteroidManager::getInstance() {
	if (_instance == NULL)
		_instance = new AsteroidManager();
	return _instance;
}
//Draw de tots
void AsteroidManager::draw(bool debug) {
	for (unsigned int i = 0; i < _asteroids.size(); i++)
		_asteroids[i]->draw(debug);

}
//Update de tots
void AsteroidManager::update(float elapsed_time ){
	for(unsigned int i = 0; i < _asteroids.size(); i++)
		_asteroids[i]->update( elapsed_time );
}

void AsteroidManager::comprova() {
	//PER CADA ASTEROIDE comprovem
	for (unsigned int i = 0; i < _asteroids.size(); i++) {
		//Retorna l'autor de la bala que ha matat l'asteroide
		int autor = BulletManager::getInstance()->comprova(_asteroids[i]);
		if ( autor != -1){
			splitAsteroid(i);
			//Actualitzem scores
			PlayerManager::getInstance()->getPlayer(autor)->addScore(10);
			i = _asteroids.size(); //Evitar seg faults en windows. Pk a linux no passa? I dunno.
		}
		//Comprova si algun player ha xocat amb algun asteroide
		else if (PlayerManager::getInstance()->comprova(_asteroids[i])) {
			splitAsteroid(i);
			i = _asteroids.size();
		}
	}
}
//-------------------------------------------------------------
void AsteroidManager::loadAsteroids() {
	// Load the file where asteroids definitions are saved
	if (XML.loadFile("asteroids.xml")) {
		cout << "Load Asteroids definition xml" << endl;
	} else {
		cout << "unable to load asteroids.xml check data/ folder" << endl;
	}

	// Check if there is the main xml tag defined or not (as an entry point)
	int areAsteroids = XML.getNumTags("asteroids");
	if (areAsteroids > 0) {
		cout << "Found asteroids defined" << endl;
		XML.pushTag("asteroids");

		// Parse all the asteroid definitions
		int numAsteroids = XML.getNumTags("asteroid");
		if (numAsteroids > 0) {
			cout << "There are " << numAsteroids << " asteroids defined"
					<< endl;

			for (int i = 0; i < numAsteroids; i++) {
				XML.pushTag("asteroid", i);
				vector<ofPoint> tempDefinition;

				int numPoints = XML.getNumTags("point");
				cout << " defined by " << numPoints << " points" << endl;

				// Create a vector for each asteroid definition with the points that define its shape
				for (int i = 0; i < numPoints; i++) {
					cout << "  " << XML.getAttribute("point", "x", 0, i) << "x"
							<< XML.getAttribute("point", "y", 0, i) << endl;

					tempDefinition.push_back(
							ofPoint(XML.getAttribute("point", "x", 0, i),
									XML.getAttribute("point", "y", 0, i)));
				}

				asteroidsDefinitions.push_back(tempDefinition);
				XML.popTag();
			}
		}
		XML.popTag();
	}
}

//-------------------------------------------------------------
void AsteroidManager::generateAsteroids(int numAsteroids) {
	float randSize = 0.0f;

	for (int i = 0; i < numAsteroids; i++) {
		// Logic to generate the Asteroids in different sizes
		// these are right now 120, 80, 40 and 20 (minimum)
		int randValue = ofRandom(0, 3);
		if (randValue == 2) {
			randSize = 120;
		} else {
			if (randValue == 1) {
				randSize = 80;
			} else {
				randSize = 40;
			}
		}

		int asteroidShape = ofRandom(asteroidsDefinitions.size());

		Asteroid* temp = new Asteroid();
		temp->setup(asteroidsDefinitions.at(asteroidShape), randSize,
				ofRandom(100, 250), ofRandom(-PI, PI),
				ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())),
				ofPoint(ofRandom(-1, 1), ofRandom(-1, 1)).normalize());
		_asteroids.push_back(temp);
	}
}

//-TOT IGUAL QUE ABANS, ARA AMB SO. Yuhuu
void AsteroidManager::splitAsteroid(int which) {
	int asteroidShape = 0;

	if (_asteroids[which]->getSize() > 20) {
		if (_explosion_sound != NULL) {
			if (_explosion_sound->isLoaded())
				_explosion_sound->play();
		}
		for (int i = 0; i < (_asteroids[which]->getSize() / 40) + 1; i++) {
			asteroidShape = ofRandom(asteroidsDefinitions.size());

			Asteroid* newAsteroid = new Asteroid();
			newAsteroid->setup(asteroidsDefinitions.at(asteroidShape),
					_asteroids[which]->getSize() / 2,
					_asteroids[which]->getSpeed(),
					_asteroids[which]->getRotation(),
					_asteroids[which]->getPosition(),
					ofPoint(-(ofRandom(-1, 1)), ofRandom(-1, 1)));
			_asteroids.push_back(newAsteroid);
		}
	}

	_asteroids.erase(_asteroids.begin() + which);

	if (_asteroids.size() == 0) {
		generateAsteroids(ofRandom(4, 6));
	}
}

void AsteroidManager::setExplosionSound (ofSoundPlayer *explosion){
	_explosion_sound = explosion;
}
