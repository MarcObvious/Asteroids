//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "PlayerNet.h"

PlayerNet::PlayerNet(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color)
: Controlador(contr,  id,  score_inicial,  lives,  color) {

	//Listener dels upgrades a ArdEvent (event network a ofApp)
	ofAddListener(ofApp::NetEvent, this, &PlayerNet::moviment);
	_controlat = contr;
	_id = id;
	_controlat->setControlador(id);
	_score = score_inicial;
	_lives = lives;
	_color = color;
	_controlat->setColor(color);
	_tipus = 2;
}

//Es controla amb la x-Axis i y-Axis del joystic!
void PlayerNet::moviment(ofPoint& ordre) {
	if(ordre.y == 0 && ordre.z == 1)
		_controlat->setThrust(true);
	else
		_controlat->setThrust(false);

	if(ordre.y == 1 && ordre.z == 1)
		_controlat->shot(true);
	else
		_controlat->shot(false);

	if (ordre.y == 2 && ordre.z == 1) {
		_controlat->gira_d(true);
		_controlat->gira_e(false);
	}
	else if (ordre.y == 3 && ordre.z == 1) {
		_controlat->gira_e(true);
		_controlat->gira_d(false);
	}
//	else if (ordre.x == 0 && ordre.y == 0) {
//		_controlat->gira_e(false);
//		_controlat->gira_d(false);
//	}
	else {
		_controlat->gira_e(false);
		_controlat->gira_d(false);
	}

}
