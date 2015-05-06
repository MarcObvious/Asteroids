//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "Bullet.h"

Bullet::Bullet() {
	position.x = 0;
	position.y = 0;

	lastPosition.x = 0;
	lastPosition.y = 0;

	direction = ofPoint(0, 0);

	rotation = 0;

	speed = 100;
}

Bullet::~Bullet(void) {

}

bool Bullet::setup() {
	return false;
}

bool Bullet::setup(ofPoint shipPosition, ofPoint shipDirection, float size,
		float speed, float lifeTime, int author) {
	position.x = shipPosition.x;
	position.y = shipPosition.y;

	lastPosition.x = shipPosition.x;
	lastPosition.y = shipPosition.x;

	direction.x = shipDirection.x;
	direction.y = shipDirection.y;

	this->speed += speed;
	this->lifeTime = lifeTime;
	_author= author;

	return true;
}

void Bullet::update(float elapsedTime) {
	// TODO
	// Bullet's logic
	lastPosition = position;
	position += direction * speed * elapsedTime;
	lifeTime -= elapsedTime;
}

int Bullet::getAuthor(){
	return _author;
}


bool Bullet::viva() {
	if ( lifeTime <= 0 ) return false;
	return true;
}

