//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "Player.h"

Player::Player(SpaceShip* contr, int controlador,int score_inicial, int lives) {
	ofRegisterKeyEvents(this);
	_controlat = contr;
	_controlador = controlador;
	_controlat->setControlador(controlador);
	_score = score_inicial;
	_lives = lives;
}

int Player::getScore() const {
	return _score;
}

void Player::setScore(int score) {
	_score = score;
}

int Player::getLives() const {
	return _lives;
}

void Player::setLives(int lives) {
	_lives = lives;
}

void Player::subLives(){
	--_lives;
}
void Player::addScore(int score) {
	_score += score;
}

SpaceShip* Player::getControlat() {
	return _controlat;
}

void Player::keyPressed(ofKeyEventArgs & args) {

	if (_controlador == 0) {
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
	else {
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
	if (_controlador == 0) {
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
	else {
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

