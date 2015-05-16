//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//
//PLayer es un controlador (d'una nau) que utilitza el TECLAT!
#pragma once
#include "SpaceShip.h"
#include "Controlador.h"

class Player : public Controlador {
private:

public:
	Player(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color) ;

	~Player(){};

	void keyPressed(ofKeyEventArgs & args);
	void keyReleased(ofKeyEventArgs & args);

};

