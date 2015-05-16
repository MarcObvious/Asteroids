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

/*
void Player::keyPressed(ofKeyEventArgs & args) {

	if (_id == 0) {
		switch (args.key) {
		case OF_KEY_DOWN:
			_controlat->setThrust(true);
			break;
		case OF_KEY_UP:
			_controlat->shot(true);
			break;
		case OF_KEY_LEFT:
			_controlat->gira_e(true);

			break;
		case OF_KEY_RIGHT:
			_controlat->gira_d(true);

			break;
		}
	}
	else if (_id == 1){
		switch (args.key) {
		case 's':
			_controlat->setThrust(true);
			break;
		case 'w':
			_controlat->shot(true);
			break;
		case 'a':
			_controlat->gira_e(true);
			break;
		case 'd':
			_controlat->gira_d(true);
			break;

		}
	}

}


void Player::keyReleased(ofKeyEventArgs & args) {
	if (_id == 0) {
		switch (args.key) {
		case OF_KEY_DOWN:
			_controlat->setThrust(false);
			break;
		case OF_KEY_LEFT:
			_controlat->gira_e(false);
			break;
		case OF_KEY_UP:
			_controlat->shot(false);
			break;
		case OF_KEY_RIGHT:
			_controlat->gira_d(false);
			break;
		}
	}
	else if(_id == 1) {
		switch (args.key) {
		case 's':
			_controlat->setThrust(false);
			break;
		case 'a':
			_controlat->gira_e(false);
			break;
		case 'w':
			_controlat->shot(false);
			break;
		case 'd':
			_controlat->gira_d(false);
			break;
		}


	}

}*/

