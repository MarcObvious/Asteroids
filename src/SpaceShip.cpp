//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "SpaceShip.h"
ofEvent<Missatge> SpaceShip::NetworkEvent = ofEvent<Missatge>();

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
	_network = false;

	//Missatge per informar de l'estat de l'spaceship
	m.id = 0;
	m.posicio = ofPoint(0,0,0);
	m.thrust = false;
	m.dispara = false;
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
	destroyed = false;
	p.addVertices(shape);
	spaceShipThrust = vector<ofPoint>();
	spaceShipThrust.push_back(ofPoint(-25, 10));
	spaceShipThrust.push_back(ofPoint(-50,0));
	spaceShipThrust.push_back(ofPoint(-25,-10));
	return this->setup();

}

//Update,
void SpaceShip::update(float elapsedTime) {
	if (!destroyed) {
		if (thrust) {
			addThrust(5);
			p.addVertices(spaceShipThrust);
		}
		else {
			if (speed > 450)
				addThrust(-2);

			if (p.size() != 4) {
				p.clear();
				p.addVertices(spaceShipShape);
			}
		}

		//Rotem per girar i actualitzem la direcció, sempre tenint en compte elapsedTime
		if (gira_dreta) this->addRotation(0.7*elapsedTime);
		if (gira_esquerra) this->addRotation(-0.7*elapsedTime);
		this->setDirection(ofPoint(cos(rotation),sin(rotation)));

		//Demanem a bulletmanager una bala!
		if (isFiring) {
			BulletManager::getInstance()->createBullet(position,direction,speed*2, 4, _controlador);
		}

	}
	else //Destroyed?? Let's roll baby
		this->addRotation( 1.5*elapsedTime);


	//Actualtizem posició respecte direcció speed i elapsedTime (diferents maquines! s'ha de tenir en compte)
	position += direction * speed * elapsedTime;

	//Enviem l'estat complet de l'spaceship a travès d'un missatge
	if (_network) {
		m.posicio = ofPoint(position.x, position.y,rotation);
		m.thrust = thrust;
		m.dispara = isFiring;
		ofNotifyEvent(NetworkEvent, m, this);
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

void SpaceShip::shot(bool disp) {
	isFiring = disp;
}

void  SpaceShip::gira_d(bool dreta) {
	gira_dreta = dreta;
}

void  SpaceShip::gira_e(bool esquerra) {
	gira_esquerra = esquerra;
}

void SpaceShip::setControlador(int contr){
	_controlador = contr;
	m.id = contr;
}

bool SpaceShip::isDestroyed() const {
	return destroyed;
}

bool SpaceShip::isNetwork() const {
	return _network;
}

void SpaceShip::setNetwork(bool network) {
	_network = network;
}

void SpaceShip::setDestroyed(bool destroyed) {
	this->destroyed = destroyed;
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
