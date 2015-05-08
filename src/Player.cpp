//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "Player.h"

Player::Player(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color) {
	ofRegisterKeyEvents(this);
	_controlat = contr;
	_id = id;
	_controlat->setControlador(id);
	_score = score_inicial;
	_lives = lives;
	_color = color;
	_controlat->setColor(color);
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

ofColor Player::getColor() const {
	return _color;
}

int Player::getId() const {
	return _id;
}

void Player::setId(int id) {
	_id = id;
}

void Player::setControlat(SpaceShip* controlat) {
	_controlat = controlat;
}

void Player::setColor(ofColor color) {
	_color = color;
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
		if (_controlat != NULL) {
			cout << _controlat << endl;
			cout << _controlat->getControlador() << "i hauria de ser"<< _id<< endl;
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
		else cout << _id << "COLLONS QUE NO EXISTEIX" << endl;
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
		if (_controlat != NULL) {
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
			cout << "HAAAAAAAAAAAAAAAAAAAAAAAa" << endl;
		}
		else cout << _id << "COLLONS QUE NO EXISTEIX" << endl;

	}

}

