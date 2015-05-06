//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#pragma once
#include "SpaceShip.h"

class Player {
private:
	SpaceShip* _controlat;
	int _controlador;
	int _score;
	int _lives;
public:
	Player(SpaceShip* contr, int controlador,int score_inicial, int lives);

	~Player(){};
	//void update(double elapsed_time, const Uint8* keystate);

	void keyPressed(ofKeyEventArgs & args);
	void keyReleased(ofKeyEventArgs & args);

	SpaceShip* getControlat();
	int getScore() const;
	void setScore(int score);
	void addScore(int score);
	int getLives() const;
	void setLives(int lives);
	void subLives();
};

