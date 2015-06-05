//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "PlayerNet.h"

PlayerNet::PlayerNet(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color)
: Controlador(contr,  id,  score_inicial,  lives,  color) {

	//Listener dels upgrades a NetEvent (event network a ofApp)
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

//Es controla en forma de missatges (struct a spaceship)
void PlayerNet::moviment(Missatge& ordre) {
	if (ordre.id == _id) {
	//	cout << _id << "_id vs id" << ordre.id << endl;
		if(ordre.thrust)
			_controlat->setThrust(true);
		else
			_controlat->setThrust(false);

		if(ordre.dispara)
			_controlat->shot(true);
		else
			_controlat->shot(false);

		_controlat->setPosition(ofPoint(ordre.posicio.x,ordre.posicio.y));
		_controlat->setRotation(ordre.posicio.z); //YEAH Z ES LA ROTACIO
		_controlat->setDirection(ofPoint(cos(ordre.posicio.z),sin(ordre.posicio.z)));
	}

}
