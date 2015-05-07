//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//
 
#pragma once
#include <string>
#include <cassert>

#include "Player.h"

//Altre patro per gestionar els jugadors.
//Esta fet així pk sigui facil posar mes modes de joc (ratoli,mando teclat etc)

class PlayerManager {

private:

	int _pos;

	static PlayerManager* _instance; //1 instancia! only

	vector<Player*> _players; //vector de players

	PlayerManager();

	~PlayerManager();

public:

	static PlayerManager * getInstance();

	void createPlayer(SpaceShip* contr ,int score_inicial, int lives, ofColor color); //crea player...

	Player* getPlayer(int i);

	string getAllScores();

	string hihaguanyador(int maxScore);

	bool comprova(Entity* ent);

	void reset();

};

