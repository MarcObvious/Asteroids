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

//Crea Player de tipus tipus si està activat "networ" aquesta spaceshipe enviara la seva info a travès d'events
bool PlayerManager::createPlayer(SpaceShip* contr ,int score_inicial, int lives, ofColor color, string tipus, bool network) {
	if (tipus == "Player") {
		Player* p = new Player(contr, _pos, score_inicial, lives, color);
		if(network)
			p->getControlat()->setNetwork(true);
		_players.push_back(p);
		++_pos;
		return true;
	}
	else if (tipus == "PlayerArd") {
		PlayerArd* p = new PlayerArd(contr, _pos, score_inicial, lives, color);
		if(network)
			p->getControlat()->setNetwork(true);
		_players.push_back(p);
		++_pos;
		return true;
	}
	else if (tipus == "PlayerRat") {
		PlayerRat* p = new PlayerRat(contr, _pos, score_inicial, lives, color);
		if(network)
			p->getControlat()->setNetwork(true);
		_players.push_back(p);
		++_pos;
		return true;
	}
	else if (tipus == "PlayerNet") {
		PlayerNet* p = new PlayerNet(contr, _pos, score_inicial, lives, color);
		_players.push_back(p);
		++_pos;
		return true;
	}
	return false;
}

int PlayerManager::getNumPlayers() {
	return _players.size();
}

//Retorna un Player concret
Controlador* PlayerManager::getPlayer(int i){
	return _players[i];
}

//Retorna tots els scores de tots els players en un string
string PlayerManager::getAllScores(){
	stringstream ss;
	for(unsigned int i = 0; i < _players.size(); i++)
		ss << "Player " << i << ": Score " << _players[i]->getScore() << " Lives " << _players[i]->getLives() << endl;
	return ss.str();
}

//Dibuixem Scores per pantalla
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

//Dibuixa tots els Players, independenment del tipus.
void PlayerManager::draw(bool debug){
	drawScores();
	for(unsigned int i = 0; i < _players.size(); i++)
		_players[i]->getControlat()->draw(debug);

}

//Fa Update de tots els players
void PlayerManager::update(float elapsed_time) {
	for(unsigned int i = 0; i < _players.size(); i++) {
		_players[i]->getControlat()->update(elapsed_time);
	}
}

//Retorna el missatge amb la info de lives i scores de tot els players
ofxOscMessage PlayerManager::generaMissatgePlayers(){
	ofxOscMessage surt;
	int midaP = _players.size();
	if (midaP != 0) {
		surt.addIntArg(midaP);
		for(int i = 0; i < midaP; i++) {
			surt.addIntArg(_players[i]->getLives());
			surt.addInt64Arg(_players[i]->getScore());
		}
	}
	return surt;
}

//Fa un set d'un missatge amb els scores i lives de tots els players
void PlayerManager::acceptaMissatgePlayers(ofxOscMessage entra){
	int mida = entra.getArgAsInt32(0);
	int j = 0;
	for(int i = 0; i < mida; i++) {
		_players[i]->setLives(entra.getArgAsInt32(j+1));
		_players[i]->setScore(entra.getArgAsInt64(j+2));
		j += 2;
	}
}

