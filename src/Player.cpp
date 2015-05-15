//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "Player.h"

Player::Player(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color)
: Controlador(contr,  id,  score_inicial,  lives,  color) {
	ofRegisterKeyEvents(this);
	_controlat = contr;
	_id = id;
	_controlat->setControlador(id);
	_score = score_inicial;
	_lives = lives;
	_color = color;
	_controlat->setColor(color);
	_tipus = 1;
}


void Player::keyPressed(ofKeyEventArgs & args) {

	if (_id == 0) {
		switch (args.key) {
		case OF_KEY_UP:
			_controlat->setThrust(true);
			break;
		case OF_KEY_DOWN:
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
		case 'w':
			_controlat->setThrust(true);
			break;
		case 's':
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
		case OF_KEY_UP:
			_controlat->setThrust(false);
			break;
		case OF_KEY_LEFT:
			_controlat->gira_e(false);
			break;
		case OF_KEY_DOWN:
			_controlat->shot(false);
			break;
		case OF_KEY_RIGHT:
			_controlat->gira_d(false);
			break;
		}
	}
	else if(_id == 1) {
		switch (args.key) {
		case 'w':
			_controlat->setThrust(false);
			break;
		case 'a':
			_controlat->gira_e(false);
			break;
		case 's':
			_controlat->shot(false);
			break;
		case 'd':
			_controlat->gira_d(false);
			break;
		}


	}

}

