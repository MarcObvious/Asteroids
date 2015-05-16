//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//
//PLayer es un controlador (d'una nau) que utilitza el TECLAT!
#pragma once
#include "SpaceShip.h"
#include "Controlador.h"

class PlayerRat : public Controlador {
private:

public:
	PlayerRat(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color) ;

	~PlayerRat(){};
	//void update(double elapsed_time, const Uint8* keystate);

	/*void keyPressed(ofKeyEventArgs & args);
	void keyReleased(ofKeyEventArgs & args);*/
	
	void mouseMoved(ofMouseEventArgs & args);
		void mouseDragged(ofMouseEventArgs & args);
		void mousePressed(ofMouseEventArgs & args);
		void mouseReleased(ofMouseEventArgs & args);

};

