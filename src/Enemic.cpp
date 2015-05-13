//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "Enemic.h"

Enemic::Enemic(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color)
	: Controlador(contr,  id,  score_inicial,  lives,  color) {
	
	_controlat = contr;
	_id = id;
	_controlat->setControlador(id);
	_score = score_inicial;
	_lives = lives;
	_color = color;
	_controlat->setColor(color);
}



