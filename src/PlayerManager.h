//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//
 
#pragma once
#include <string>
#include <cassert>

#include "Controlador.h"
#include "Player.h"
#include "PlayerArd.h"

//Altre patro per gestionar els jugadors.
//Esta fet així pk sigui facil posar mes modes de joc (ratoli,mando teclat etc)

class PlayerManager {

private:

	int _pos;
	int _posArd;

	static PlayerManager* _instance; //1 instancia! only

	vector<Controlador*> _players; //vector de players


	PlayerManager();

	~PlayerManager();

public:

	static PlayerManager * getInstance();

	void createPlayer(SpaceShip* contr ,int score_inicial, int lives, ofColor color); //crea player...

	void createPlayerArd(SpaceShip* contr ,int score_inicial, int lives, ofColor color); //crea player controlat per Ard...

	Controlador* getPlayer(int i);

	string getAllScores();

	void drawScores();

	Controlador* hihaguanyador(int maxScore);

	bool comprova(Entity* ent);

	void reset();

	void draw(bool debug);

	void update(float elapsed_time);

//	void update(float elapsed_time, unsigned char receivedBytes[8]);
};

