//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "Controlador.h"

Controlador::Controlador(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color) {
	_controlat = contr;
	_id = id;
	_controlat->setControlador(id);
	_score = score_inicial;
	_lives = lives;
	_color = color;
	_controlat->setColor(color);
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
}

ofColor Controlador::getColor() const {
	return _color;
}

int Controlador::getId() const {
	return _id;
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
}
void Controlador::addScore(int score) {
	_score += score;
}

SpaceShip* Controlador::getControlat() {
	return _controlat;
}



