//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#pragma once
#include "SpaceShip.h"
#include "Controlador.h"

class Player : public Controlador {
private:

public:
	Player(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color) ;

	~Player(){};
	//void update(double elapsed_time, const Uint8* keystate);

	void keyPressed(ofKeyEventArgs & args);
	void keyReleased(ofKeyEventArgs & args);

};

