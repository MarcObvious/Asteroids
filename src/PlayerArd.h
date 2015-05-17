//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//
//PLayerArd es un controlador (d'una nau) que utilitza el Events d'ARDUINO! pel moviment

#pragma once
#include "SpaceShip.h"
#include "Controlador.h"
#include "ofApp.h"

class PlayerArd : public Controlador {
private:

public:
	PlayerArd(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color) ;

	~PlayerArd(){};

	void moviment(ofPoint& pos);

};

