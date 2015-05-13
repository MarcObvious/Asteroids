//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "bulletManager.h"
#include "PlayerManager.h"

BulletManager::BulletManager() {
	assert(_instance == NULL); //Si no es cumpleix PETA
	_instance = this;
	_bullets = new vector<Bullet*>();
	_bullets->reserve(5000); //Nomes 5000!
	_pos = 0;
	_init = true;

}

void BulletManager::reset() {
//	for(unsigned int i = 0; i < _bullets->size(); i++)
//		free ( _bullets->at(i));

	_bullets = new vector<Bullet*>();
	_bullets->reserve(5000);
	_pos = 0;
	_init = true;
}

BulletManager::~BulletManager() {
	// _bullets->clear();
	free(_instance);
	for(unsigned int i = 0; i < _bullets->size(); i++)
		free ( _bullets->at(i));
}

BulletManager * BulletManager::getInstance() {
	if (_instance == NULL)
		_instance = new BulletManager();
	return _instance;
}

void BulletManager::draw() {
	glPointSize(5);
	glBegin(GL_POINTS);
		//Dibuixem punts de colors macos per les bales
		for(unsigned int i = 0; i < _bullets->size(); i++) {
			if ( _bullets->at(i)->viva() ) {//Dibuixa nomes les que el temps de vida sigui positiu
				glColor3f(0,5,20);
				glVertex3f(_bullets->at(i)->getPosition().x,_bullets->at(i)->getPosition().y,_bullets->at(i)->getPosition().z);
				glColor3f(1.0, 1.0, 1.0);
			}
		}
	glEnd();

}

void BulletManager::update( float elapsed_time ){

	for(unsigned int i = 0; i < _bullets->size(); i++) {
		if ( _bullets->at(i)->viva() ) {//Update nomes les que el temps de vida sigui positiu
			_bullets->at(i)->update( elapsed_time );

		}
	}
}

void BulletManager::createBullet(ofPoint position, ofPoint direction, float speed ,float lifeTime, int author_id) {
	if (!_init) { //Si el vector ja ha arribat a 1000, sobreescrivim bullets
		_bullets->at(_pos)->setup(position,  direction, 10, speed , lifeTime, author_id);
		++_pos;
	}
	//Creem nova bullet fins a 5000
	if (_pos < 5000 && _init) {
		Bullet* b = new Bullet();
		b->setup(position,  direction, 10 , speed , lifeTime, author_id);
		_bullets->push_back(b);
		++_pos;
	}
	//Si arribem a 5000 tornem a començar el compte
	if (_pos == 5000) {
		_pos = 0;
		_init = false;
	}
	//SO
	if (_bullet_sound != NULL) {
		if (_bullet_sound->isLoaded())
			_bullet_sound->play();
	}


}
//Comprobació bullet entity
int BulletManager::comprova(Entity* ent) {
	for (unsigned int i = 0; i < _bullets->size(); i++) {
		if ( _bullets->at(i)->viva() )
			if (ent->getCollision(_bullets->at(i)->getPosition())){
				return _bullets->at(i)->getAuthor();
			}
	}
	return -1;
}
//PIUM PIUM PIUM
void BulletManager::setBulletSound(ofSoundPlayer *pium){
	_bullet_sound = pium;
}
