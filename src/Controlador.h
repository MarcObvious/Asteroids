//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#pragma once
#include "SpaceShip.h"

class Controlador {
protected:
	SpaceShip* _controlat;
	int _id;
	int _score;
	int _lives;
	ofColor _color;
	bool _viu;
public:
	Controlador(SpaceShip* contr, int id, int score_inicial, int lives, ofColor color);

	~Controlador(){};
	//void update(double elapsed_time, const Uint8* keystate);

	SpaceShip* getControlat();
	int getScore() const;
	void setScore(int score);
	void addScore(int score);
	int getLives() const;
	void setLives(int lives);
	void subLives();
	ofColor getColor() const;
	void setColor(ofColor color);
	void setControlat(SpaceShip* controlat);
	int getId() const;
	void setId(int id);
	bool isViu() const;
	void setViu(bool viu);
};

