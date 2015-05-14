//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "SpaceShip.h"

SpaceShip::SpaceShip() {
	position.x = 0;
	position.y = 0;

	direction = ofPoint(0, 0);

	rotation = 0;
	thrust = false;
	isFiring = false;
	gira_dreta=false;
	gira_esquerra=false;
	_color = ofColor(0,0,0);

}

SpaceShip::~SpaceShip() {

}

bool SpaceShip::setup() {

	return true;
}

bool SpaceShip::setup(vector<ofPoint> & shape, float size, float speed,
		float rotation, ofPoint position) {

	this->spaceShipShape = shape;
	this->size = size;
	this->speed = speed;
	this->rotation = rotation;
	this->position = position;
	this->setDirection(ofPoint(cos(rotation),sin(rotation)));
	p.addVertices(shape);
	spaceShipThrust = vector<ofPoint>();
	spaceShipThrust.push_back(ofPoint(-25, 10));
	spaceShipThrust.push_back(ofPoint(-50,0));
	spaceShipThrust.push_back(ofPoint(-25,-10));
	return this->setup();

}

//Update,
void SpaceShip::update(float elapsedTime) {
	// Example on how to accelerate SpaceShip
	if (thrust) {
		addThrust(5);
		p.addVertices(spaceShipThrust);
	} else {
		if (speed > 450)
			addThrust(-2);
		if (p.size() != 4) {
			p.clear();
			p.addVertices(spaceShipShape);
		}

	}

	// TODO
	// - add spaceship state update
	// - control spacehsip and window boundaries (i.e. marginSwap)

	//Rotem per girar i actualitzem la direcció, sempre tenint en compte elapsedTime
	if (gira_dreta) this->addRotation(0.7*elapsedTime);
	if (gira_esquerra) this->addRotation(-0.7*elapsedTime);
	this->setDirection(ofPoint(cos(rotation),sin(rotation)));

	//Actualtizem posició respecte direcció speed i elapsedTime (diferents maquines! s'ha de tenir en compte)
	position += direction * speed * elapsedTime;

	//Demanem a bulletmanager una bala!
	if (isFiring) {
		BulletManager::getInstance()->createBullet(position,direction,speed*2, 4, _controlador);
	}
	marginsWrap();
}
//Draw quasi igual que Asteroides, no gaire coasa a dir Rotacio->Traslacio
void SpaceShip::draw(bool debug) {

	//Shape que hem carregat prevament


	ofPushStyle();
	ofPushMatrix();
		ofSetColor(_color);
		glTranslatef(position.x, position.y, 0);
		//S'ha de passar a radians!
		glRotatef(rotation  / PI * 180, 0, 0, 1);

		if (debug) {
			ofPushStyle();
			ofNoFill();
			ofCircle(0, 0, size);
			ofPopStyle();
		}

		p.draw();
	ofPopMatrix();
	ofPopStyle();

}

//Funcions de control

void SpaceShip::addThrust(float thrust) {
	speed += thrust;
}

void  SpaceShip::setThrust(bool trust) {
	thrust = trust;
}
void  SpaceShip::gira_d(bool dreta) {
	gira_dreta = dreta;
}
void  SpaceShip::gira_e(bool esquerra) {
	gira_esquerra = esquerra;
}
void SpaceShip::shot(bool disp) {
	isFiring = disp;
}
void SpaceShip::setControlador(int contr){
	_controlador = contr;
}
int SpaceShip::getControlador() {
	return _controlador;
}

ofColor SpaceShip::getColor() const {
	return _color;
}

void SpaceShip::setColor(ofColor color) {
	_color = color;
}
