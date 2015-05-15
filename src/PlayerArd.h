//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#pragma once
#include "SpaceShip.h"
#include "Controlador.h"
#include "ofApp.h"

class PlayerArd : public Controlador {
private:
//	SpaceShip* _controlat;
//	int _id;
//	int _score;
//	int _lives;
//	ofColor _color;
public:
	PlayerArd(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color) ;

	~PlayerArd(){};
	//void update(double elapsed_time, const Uint8* keystate);

//	void keyPressed(ofKeyEventArgs & args);
//	void keyReleased(ofKeyEventArgs & args);
	void moviment(ofPoint& pos);

};

