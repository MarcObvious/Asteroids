//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//
//PLayer es un controlador (d'una nau) que utilitza el MOUSE!
#include "PlayerRat.h"

PlayerRat::PlayerRat(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color)
: Controlador(contr,  id,  score_inicial,  lives,  color) {
	 ofRegisterMouseEvents(this);
	_controlat = contr;
	_id = id;
	_controlat->setControlador(id);
	_score = score_inicial;
	_lives = lives;
	_color = color;
	_controlat->setColor(color);
	_tipus = 1;
}

void PlayerRat::mouseMoved(ofMouseEventArgs & args){

}
void PlayerRat::mouseDragged(ofMouseEventArgs & args){
	switch (args.button) {
	case 1:
		_controlat->setThrust(true);
		_controlat->shot(false);
		break;
	}
}
void PlayerRat::mousePressed(ofMouseEventArgs & args){
	switch (args.button) {
	case 0:
		_controlat->gira_e(true);	
		break;
	case 1:
		_controlat->shot(true);
		break;
	case 2:
		_controlat->gira_d(true);	
		break;
	}
	
}
void PlayerRat::mouseReleased(ofMouseEventArgs & args){
	switch (args.button) {
	case 0:
		_controlat->gira_e(false);	
		break;
	case 1:
		_controlat->shot(false);
		_controlat->setThrust(false);
		break;
	case 2:
		_controlat->gira_d(false);	
		break;
	}
}


