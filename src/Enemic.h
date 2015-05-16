//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//
//Enemic es un controlador (d'una nau) que es mou SOL!
//Faltaria fer el tema IA i tal xD

#pragma once
#include "SpaceShip.h"
#include "Controlador.h"

class Enemic : public Controlador {
private:

public:
	Enemic(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color) ;

	~Enemic(){};
	//void update(double elapsed_time, const Uint8* keystate);

};

