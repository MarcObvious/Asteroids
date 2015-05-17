//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "PlayerArd.h"

PlayerArd::PlayerArd(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color)
: Controlador(contr,  id,  score_inicial,  lives,  color) {

	//Listener dels upgrades a ArdEvent (event arduino a ofApp)
	ofAddListener(ofApp::ArdEvent, this, &PlayerArd::moviment);
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
void PlayerArd::moviment(ofPoint& pos) {

	if (pos.x > 650) {
		_controlat->gira_d(true);
		_controlat->gira_e(false);
	}
	else if (pos.x < 300) {
		_controlat->gira_e(true);
		_controlat->gira_d(false);
	}
	else if (pos.x == 0 && pos.y == 0) {
		_controlat->gira_e(false);
		_controlat->gira_d(false);
	}
	else {
		_controlat->gira_e(false);
		_controlat->gira_d(false);
	}
	if(pos.y > 650)
		_controlat->setThrust(true);
	else
		_controlat->setThrust(false);
	if(pos.y < 270)
		_controlat->shot(true);
	else
		_controlat->shot(false);

	//cout << pos.x << " "<< pos.y << endl;

}
