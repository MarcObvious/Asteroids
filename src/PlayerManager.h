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
#include "PlayerRat.h"

//Altre patro per gestionar els jugadors.
//Esta fet així pk sigui facil posar mes modes de joc (ratoli,mando teclat etc)

class PlayerManager {

private:

	int _pos;

	static PlayerManager* _instance; //1 instancia! only

	vector<Controlador*> _players; //vector de players

	PlayerManager();

	~PlayerManager();

public:

	static PlayerManager * getInstance();

	bool createPlayer(SpaceShip* contr ,int score_inicial, int lives, ofColor color, string tipus, bool network); //crea player...

	Controlador* getPlayer(int i);

	string getAllScores();

	void drawScores();

	Controlador* hihaguanyador(int maxScore);

	bool comprova(Entity* ent);

	void reset();

	void draw(bool debug);

	void update(float elapsed_time);
};

