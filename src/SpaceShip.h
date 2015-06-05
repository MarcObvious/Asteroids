//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#pragma once
#include "ofMain.h"
#include "bulletManager.h"
#include "Entity.h"

// Possible SpaceShip implementation

//Spaceship es la "forma" que dona voltes pel mapa. Ha de ser controlada per un player

//Struct per enviar l'estat d'una spaceship
typedef struct{
	int id;
	ofPoint posicio;
	bool dispara;
	bool thrust;
}Missatge;

class SpaceShip: public Entity {

private:
	// SpaceShip's behaviour control variables
	bool thrust, isFiring, gira_dreta, gira_esquerra;
	bool _network;
	int _controlador;
	ofColor _color;

	vector<ofPoint> spaceShipShape;
	vector<ofPoint> spaceShipThrust;
	ofPolyline p;
	bool destroyed;
	bool out;
	Missatge m;

public:
	SpaceShip();
	~SpaceShip();
	//Event que informa dels moviments d'una spaceship per enviarho!
	static ofEvent<Missatge> NetworkEvent;

	virtual bool setup();
	virtual bool setup(vector<ofPoint> & shape, float size, float speed,
			float rotation, ofPoint position);

	virtual void update(float deltaTime);
	virtual void draw(bool debug);

	void addThrust(float thrust);

	void setThrust(bool trust);
	void gira_d(bool dreta);
	void gira_e(bool esquerra);

	void  gir(float angle_in_rad, ofPoint axis);
	void shot(bool disp);
	void setControlador(int contr);
	int getControlador();

	ofColor getColor() const;
	void setColor(ofColor color);
	bool isDestroyed() const;
	void setDestroyed(bool destroyed);
	bool isNetwork() const;
	void setNetwork(bool network);
};
