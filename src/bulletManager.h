//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//
 
#pragma once
#include <string>
#include <cassert>

#include "Bullet.h"

//Manager en forma de singleton que gestiona les bales, sempre n'hi hauran com a molt 1000

class BulletManager {

private:

	static BulletManager* _instance;

	std::vector<Bullet*>* _bullets; //Vector punters totes les bales

	ofSoundPlayer* _bullet_sound;

	int _pos; //posicio al vector de bales max 1000

	bool _init;

	BulletManager();

	~BulletManager();


public:

	static BulletManager * getInstance(); 		//Retorna el Bulletmanager

	void createBullet(ofPoint position, ofPoint direction, float speed ,float lifeTime, int author_id);

	void draw();

	void update( float elapsed_time);

	int comprova(Entity* ent);

	void reset();

	void setBulletSound (ofSoundPlayer *pium);


};

