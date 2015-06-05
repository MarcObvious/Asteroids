//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//
 
#pragma once
#include <string>
#include <cassert>

#include "Asteroid.h"
#include "ofxXmlSettings.h"
#include "bulletManager.h"

//Forma molt mes elegant de gestionar els asteroides. Si algu en vol un, li demana al manager!

class AsteroidManager {

private:

	static AsteroidManager* _instance;

	ofSoundPlayer* _explosion_sound;

	vector<Asteroid*> _asteroids; //Vector d'asteroides

	ofxXmlSettings XML;

	vector<vector<ofPoint> > asteroidsDefinitions;

	AsteroidManager();

	~AsteroidManager();

public:

	static AsteroidManager * getInstance();  //Retorna la instancia a Asteroidmanager

	void draw(bool debug);

	void update(float elapsed_time);

	void comprova(); //colisions

	void loadAsteroids();

	void generateAsteroids(int numAsteroids);

	void splitAsteroid(int asteroidID);

	void setExplosionSound (ofSoundPlayer *explosion); //Obvi

	void reset();

	vector<Asteroid*> getAsteroids() const;

	void setAsteroids(vector<Asteroid*> asteroids);

	vector<vector<ofPoint> > getAsteroidsDefinitions() const;

	void enviaAsteroids(ofxOscSender sender, string desti);

	void setAsteroidsDefinitions(vector<vector<ofPoint> > asteroidsDefinitions);
};

