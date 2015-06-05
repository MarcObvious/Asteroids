//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "Controlador.h"

Controlador::Controlador(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color) {
	_viu = true;
	_controlat = contr;
	_id = id;
	_controlat->setControlador(id);
	_score = score_inicial;
	_lives = lives;
	_color = color;
	_controlat->setColor(color);
	_tipus = 0;

}

int Controlador::getScore() const {
	return _score;
}

void Controlador::setScore(int score) {
	_score = score;
}

int Controlador::getLives() const {
	return _lives;
}

void Controlador::setLives(int lives) {
	_lives = lives;
	if (_lives <= 0) {
		_viu = false;
		_controlat->setDestroyed(true);
	}
}

ofColor Controlador::getColor() const {
	return _color;
}

int Controlador::getId() const {
	return _id;
}

bool Controlador::isViu() const {
	return _viu;
}

int Controlador::getTipus() const {
	return _tipus;
}

void Controlador::setTipus(int tipus) {
	_tipus = tipus;
}

void Controlador::setViu(bool viu) {
	_viu = viu;
}

void Controlador::setId(int id) {
	_id = id;
}

void Controlador::setControlat(SpaceShip* controlat) {
	_controlat = controlat;
}

void Controlador::setColor(ofColor color) {
	_color = color;
}

void Controlador::subLives(){
	--_lives;
	if (_lives <= 0) {
		_viu = false;
		_controlat->setDestroyed(true);
	}
}
void Controlador::addScore(int score) {
	_score += score;
}

SpaceShip* Controlador::getControlat() {
	return _controlat;
}



