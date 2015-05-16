//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "PlayerArd.h"

PlayerArd::PlayerArd(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color)
: Controlador(contr,  id,  score_inicial,  lives,  color) {
//	ofRegisterKeyEvents(this);
//	ofAddListener(BaseButton::clickedInside, this, &o::buttonPressed);
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

void PlayerArd::moviment(ofPoint& pos) {

	if (pos.x > 650) {
		_controlat->gira_d(true);
		_controlat->gira_e(false);
	}
	else if (pos.x < 300) {
		_controlat->gira_e(true);
		_controlat->gira_d(false);
	}
	else if (pos.x == 0 and pos.y == 0) {
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
//	if (pos.x > pos.y)
//		_controlat->gira_d(true);
//	else  _controlat->gira_e(true);
  //_controlat->gira_e(true);
	//cout << pos.x << " "<< pos.y << endl;

}



