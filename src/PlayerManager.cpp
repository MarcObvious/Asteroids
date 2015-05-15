//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "PlayerManager.h"


PlayerManager::PlayerManager() {
	assert(_instance == NULL); //Si no es cumpleix PETA nomes 1 Instancia!
	_instance = this;
	_pos = 0;

}

void PlayerManager::reset() {
	_players.clear();
	_pos = 0;
}
PlayerManager::~PlayerManager() {
	free(_instance);
	_players.clear();
}

PlayerManager * PlayerManager::getInstance() {
	if (_instance == NULL)
		_instance = new PlayerManager();
	return _instance;
}

void PlayerManager::createPlayer(SpaceShip* contr ,int score_inicial, int lives, ofColor color) {
	Player* p = new Player(contr, _pos, score_inicial, lives, color);
	_players.push_back(p);
	++_pos;
}
void PlayerManager::createPlayerArd(SpaceShip* contr ,int score_inicial, int lives, ofColor color) {
	PlayerArd* p = new PlayerArd(contr, _pos, score_inicial, lives, color);
	_players.push_back(p);
	++_pos;
}

Controlador* PlayerManager::getPlayer(int i){
	return _players[i];
}

//Retorna tots els scores de tots els players
string PlayerManager::getAllScores(){
	stringstream ss;
	for(unsigned int i = 0; i < _players.size(); i++)
		ss << "Player " << i << ": Score " << _players[i]->getScore() << " Lives " << _players[i]->getLives() << endl;

	return ss.str();
}

void PlayerManager::drawScores() {
	int posicio_y = 20;
	int posicio_x = 15;
	for(unsigned int i = 0; i < _players.size(); i++) {
		stringstream score_line;
		score_line << "Player " << i;
		if (_players[i]->isViu())
			score_line << ": Score " << _players[i]->getScore() << " Lives " << _players[i]->getLives() << endl;
		else
			score_line << " -> DEAAAAAAAAAAAAAAAD!!!!!" << endl;

		ofPushStyle();
		ofSetColor(ofColor(_players[i]->getColor()));
		ofDrawBitmapString(score_line.str(), posicio_x, posicio_y);
		ofPopStyle();
		posicio_y += 15;
	}
}

//Retorna NO si no hi ha guanyador, el guanyador en cas contrari (o perdedor si algu simplement s'ha matat)
Controlador* PlayerManager::hihaguanyador(int maxScore) {
	int jugadors_vius = _players.size();
	for(unsigned int i = 0; i < _players.size(); i++){
		if (_players[i]->getScore() >= maxScore)
			return _players[i];

		if(!_players[i]->isViu())
			--jugadors_vius;
	}
	if (jugadors_vius == 1) {
		for(unsigned int i = 0; i < _players.size(); i++){
			if(_players[i]->isViu())
				return _players[i];
		}
	}

	return NULL;
}

//Comprobacions Entity Entity (per als asteriodes), resta vida a player si hi ha colisio
bool PlayerManager::comprova(Entity* ent){
	for(unsigned int i = 0; i < _players.size(); i++) {
		if (ent->getCollision(_players[i]->getControlat())) {
			_players[i]->subLives();
			return true;
		}
	}
	return false;
}

void PlayerManager::draw(bool debug){
	drawScores();
	for(unsigned int i = 0; i < _players.size(); i++)
		_players[i]->getControlat()->draw(debug);

}
void PlayerManager::update(float elapsed_time) {
	for(unsigned int i = 0; i < _players.size(); i++) {
		//if (_players[i]->getTipus() == 1)
		_players[i]->getControlat()->update(elapsed_time);
	}
}
//void PlayerManager::update(float elapsed_time, unsigned char receivedBytes){
//	for(unsigned int i = 0; i < _players.size(); i++) {
//			if (_players[i]->getTipus() == 2) {
////				_players[i]->setOrders
//				_players[i]->getControlat()->update(elapsed_time);
//			}
//		}
//
//}

