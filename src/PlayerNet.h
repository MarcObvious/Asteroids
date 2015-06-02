//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//
//PlayerNet es un controlador (d'una nau) que utilitza el Events d'ARDUINO! pel moviment

#pragma once
#include "SpaceShip.h"
#include "Controlador.h"
#include "ofApp.h"

class PlayerNet : public Controlador {
private:

public:
	PlayerNet(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color) ;

	~PlayerNet(){};

	void moviment(ofPoint& pos);

};

