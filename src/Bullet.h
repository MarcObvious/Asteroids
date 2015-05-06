//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#pragma once
#include "ofMain.h"

#include "Entity.h"

//Bullet basicament copiada del que ja teniem

class Bullet: public Entity {
public:
	Bullet();

	~Bullet();

	virtual bool setup();

	bool setup(ofPoint spaceShipPosition, ofPoint spaceShipDirection,
			float size, float speed, float lifeTime, int author);

	virtual void update(float deltaTime);

	virtual void draw(bool debug){};

	bool viva(); //Pos eso

	int getAuthor(); //torna autor de la bala

private:
	// Possible bullet's life control variables
	ofPoint lastPosition; //No ho fem servir ara mateix


	float fireDistance;

	float lifeTime;

	int _author;
};
