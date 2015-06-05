//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "ofApp.h"

//Patrons Singleton que gestionaran les Bullets, els Asteroides i  els Jugadors
BulletManager* BulletManager::_instance = NULL;
AsteroidManager* AsteroidManager::_instance = NULL;
PlayerManager* PlayerManager::_instance = NULL;

//Event que registra el canvi al joystic arduino
ofEvent<ofPoint> ofApp::ArdEvent = ofEvent<ofPoint>();
ofEvent<Missatge> ofApp::NetEvent = ofEvent<Missatge>();

//Variables globals que defineixen les vides i la puntuacio maxima
int MAX_SCORE = 2000;
int MAX_LIVES = 50;
int INITIAL_SCORE = 0;

//--------------------------------------------------------------
ofApp::ofApp(int cli, int SO, string host) {
	clientServidor = cli;
	sistemaOp = SO;
	Host = host;

	if (clientServidor == 0 || clientServidor == 1) {
		receiver.setup(PORT);
		sender.setup(Host, PORT);
		if (clientServidor == 0)
			s_clientServidor = "servidor";
		else
			s_clientServidor = "client";

		ofAddListener(SpaceShip::NetworkEvent, this, &ofApp::spaceshipEsMou);
	}
	else 
		s_clientServidor = "local";
	//setup();
}

void ofApp::setupArduino() {
	if (!serial.isInitialized()) {
		serial.listDevices();
		vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();

		// Diferents configuracions segons Mac Linux o Windows
		int baud = 9600;
		if (sistemaOp == 1)
			serial.setup("/dev/ttyACM0", baud);  //Linux powa!
		else if (sistemaOp == 2)
			serial.setup("COM4", baud); // Windows
		else if (sistemaOp == 3)
			serial.setup("/dev/tty.usbserial-A4001JEC", baud); //Mac
	}

	cyclesCounter = 0;
	cyclesJumped = 5;

	readAndSendMessage = false;
}

void ofApp::setup() {
	// Set framerate to 60 FPS
	ofSetFrameRate(60);

	//Posem Arduino a punt
	if (sistemaOp != 0)
		setupArduino();

	acaba_partida = false;
	// Load Asteroids from XML
	AsteroidManager::getInstance()->loadAsteroids();

	// Create Asteroids
	AsteroidManager::getInstance()->generateAsteroids(6);


	//Manera cutre d'afegir la forma (vertex) de les nostres naus (tenen la mateixa forma
	vector<ofPoint> shape = vector<ofPoint>();
	shape.push_back(ofPoint(-25, 25));
	shape.push_back(ofPoint(35,0));
	shape.push_back(ofPoint(-25,-25));
	shape.push_back(ofPoint(-25, 25));

	//Demanem al PlayerManager que ens creei un Players, amb la Spaceship que vulguem
	///els tipus poden ser Player (teclat), PlayerArd(arduino), PlayerRat(ratoli) i playerNet(Xarxa).
	//PlayerNet es especial ja que es controla a traves de missatges.

	SpaceShip* nau = new SpaceShip();

	nau->setup(shape, 40, 500, 50,
			ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));

	if (s_clientServidor == "client")
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(255,0,0), "Player", true);
	else if (s_clientServidor == "servidor")
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(255,0,0), "PlayerNet", false);
	else 
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(255,0,0), "Player", false);

	nau = new SpaceShip();

	nau->setup(shape, 40, 500, 50,
			ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));

	if (s_clientServidor == "servidor")
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,0,255),"Player",true);
	else if (s_clientServidor == "client")
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,0,255),"PlayerNet",false);
	else 
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,0,255), "Player", false);

	nau = new SpaceShip();

	nau->setup(shape, 40, 500, 50,
			ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));

	if (s_clientServidor == "client")
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,255,0), "PlayerRat",true);
	else if (s_clientServidor == "servidor")
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,255,0), "PlayerNet",false);
	else 
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,255,0), "PlayerRat",false);

	nau = new SpaceShip();

	nau->setup(shape, 40, 500, 50,
			ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));

	if (s_clientServidor == "servidor")
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(255,255,0),"PlayerArd",true);
	else if (s_clientServidor == "client")
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(255,255,0),"PlayerNet",false);
	else 
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(255,255,0), "PlayerArd", false);

	nau = new SpaceShip();

	nau->setup(shape, 40, 500, 50,
			ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));

	if (s_clientServidor == "client")
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,255,255), "Player",true);
	else if (s_clientServidor == "servidor")
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,255,255), "PlayerNet",false);
	else 
		PlayerManager::getInstance()->createPlayer(nau, INITIAL_SCORE, MAX_LIVES, ofColor(0,255,255), "Player", false);


	//Carreguem els sons d'explosions d'asteroides i de dispars
	//Comença SILENCIAT pel be de tota la humanitat!!
	explosion = new ofSoundPlayer();
	explosion->loadSound("sounds/explosion.mp3", false);
	AsteroidManager::getInstance()->setExplosionSound(NULL);

	pium = new ofSoundPlayer();
	pium->loadSound("sounds/lasergun.mp3", false);
	BulletManager::getInstance()->setBulletSound(NULL);

	// General logic
	ofBackground(0); // Set background to black

	// Debug
	debug = false;

	guanyador = NULL;
}

ofApp::~ofApp(){

}

//FUCK AUDIO!
void ofApp::killSound() {
	if (pium->isLoaded()){
		pium->stop();
		pium->unloadSound();
	}
	if (explosion->isLoaded()){
		explosion->stop();
		explosion->unloadSound();
	}
}

//AQUI ES REP I S'ENVIA A ARDUINO
void ofApp::arduinoUpdate() {
	if(readAndSendMessage || acaba_partida) {
		//Enviarem un byte,
		unsigned char enviar[1];
		//memset(enviar, 0, 4);
		enviar[0] = 'A';

		if (guanyador != NULL){
			switch (guanyador->getId()) {
			case 0:
				enviar[0] = 'Z';
				break;
			case 1:
				enviar[0] = 'U';
				break;
			case 2:
				enviar[0] = 'D';
				break;
			case 3:
				enviar[0] = 'T';
				break;
			case 4:
				enviar[0] = 'Q';
				break;
			case 5:
				enviar[0] = 'C';
				break;
			}
		}

		if(acaba_partida)
			enviar[0] = 'F';

		//Enviem el byte.
		serial.writeBytes(enviar,1);

		//Si hi ha alguna cosa per llegir,
		if(serial.available()) {

			int x; int y;
			//Llegim 4 bytes.
			unsigned char bytesRead[NUM_BYTES];
			memset(bytesRead, 0, NUM_BYTES);
			while(serial.readBytes(bytesRead, NUM_BYTES) > 0){ }
			//X-Axis
			x = bytesRead[0];
			x <<= 8;
			x += bytesRead[1];
			//Y-Axis
			y = bytesRead[2];
			y <<= 8;
			y += bytesRead[3];
			//cout << "X " << x << " Y " << y <<endl;
			if (x == 0 && y == 0) //Senyal de reset
				reset();
			else {
				//Fem una "filtre" cutre per no passar tonteries. Smooth.
				if (x > 0 && x < 770 && y > 0 && y < 770 ) {
					ofPoint pos = ofPoint(x,y);
					//Event que indica a les classes Ard quina posicio tene els Axis
					ofNotifyEvent(ArdEvent, pos, this);
				}
			}
		}
		readAndSendMessage = false;
	}

	cyclesCounter++;
	if(cyclesCounter >= cyclesJumped){
		readAndSendMessage = true;
		cyclesCounter = 0;
	}
}

//Informa de la info d'una spaceship (a través d'un event),
//Al seu corresponent controlador Net (a través de missages)
void ofApp::spaceshipEsMou(Missatge& dirs) {
	ofxOscMessage m;

	if (s_clientServidor == "client")
		m.setAddress("d_per_servidor");
	else
		m.setAddress("d_per_client");

	m.addIntArg(dirs.id);
	m.addFloatArg(dirs.posicio.x);
	m.addFloatArg(dirs.posicio.y);
	m.addFloatArg(dirs.posicio.z);
	if (dirs.dispara)
		m.addIntArg(1);
	else
		m.addIntArg(0);
	if (dirs.thrust)
		m.addIntArg(1);
	else
		m.addIntArg(0);

	sender.sendMessage(m);
}

//Enviem ordres bidireccionalment!!! reset? finish? whatever!
void ofApp::enviaBi(string ordre) {
	ofxOscMessage m;
	if (s_clientServidor == "client")
		m.setAddress("o_per_servidor");
	else
		m.setAddress("o_per_client");

	m.addStringArg(ordre);

	//Si a mes l'ordre es que hi ha un guanyador, l'enviem també.
	if (ordre == "guanyador")
		m.addIntArg(guanyador->getId());

	sender.sendMessage(m);

}

//Envia i rep de toooot a cada Update. Pk ens la pela el framerate i ample de banda
void ofApp::enviairep(){

	//Si som el servidor enviem els asteroides i les puntuacions dels players
	if (s_clientServidor == "servidor") {
		ofxOscMessage surt;
		surt = AsteroidManager::getInstance()->generaMissatgeAsteroids();
		surt.setAddress("a_per_client");
		sender.sendMessage(surt);

		surt.clear();
		surt = PlayerManager::getInstance()->generaMissatgePlayers();
		surt.setAddress("p_per_client");
		sender.sendMessage(surt);
	}

	//Independenment de qui som rebem missatges
	while(receiver.hasWaitingMessages()){
		ofxOscMessage entra;
		receiver.getNextMessage(&entra);

		//Si hi han ordres tan per a client com per a servidor les executem
		if(entra.getAddress() == "o_per_"+s_clientServidor){
			Missatge ordre;
			string ord = entra.getArgAsString(0);
			if (ord == "reset")
				reset();
			else if (ord == "guanyador")
				guanyador = PlayerManager::getInstance()->getPlayer(entra.getArgAsInt32(1));
			else if (ord == "finish")
				finish();

		}

		//Si hi han direccions tan per a client com per a servidor (per a algun controlador Net)
		else if (entra.getAddress() == "d_per_"+s_clientServidor ){
			Missatge dirs;
			dirs.id =  entra.getArgAsInt32(0); //id del controlador
			dirs.posicio = ofPoint(entra.getArgAsFloat(1),entra.getArgAsFloat(2),entra.getArgAsFloat(3));
			if (entra.getArgAsInt32(4) == 0)
				dirs.dispara = false;
			else
				dirs.dispara = true;

			if (entra.getArgAsInt32(5) == 0)
				dirs.thrust = false;
			else
				dirs.thrust = true;

			//Event que indica a les classes Net la posicio i estat de les seves spaceships
			ofNotifyEvent(NetEvent, dirs, this);
		}

		//Rebem els Asteroids (del servidor al client)
		else if (entra.getAddress() == "a_per_"+s_clientServidor )
			AsteroidManager::getInstance()->acceptaMissatgeAsteroids(entra);
		//Rebem els scores i vides (del servidor al client) Però podria ser a l'inversa! faacilment
		else if (entra.getAddress() == "p_per_"+s_clientServidor )
			PlayerManager::getInstance()->acceptaMissatgePlayers(entra);
	}
}
//--------------------------------------------------------------
void ofApp::update() {

	if (!acaba_partida) { 
		// We get the time that last frame lasted, and use it to update asteroids logic
		// so their behaviour is independent to the framerate
		float elapsedTime = ofGetLastFrameTime();

		//Preguntem a PlayerManager si hi ha guanyador, si n'hi ha no updategem res.
		if (s_clientServidor == "servidor" || s_clientServidor == "local") {

			guanyador = PlayerManager::getInstance()->hihaguanyador(MAX_SCORE);
			if (guanyador == NULL){
				//Comprova colisions d'Asteroides amb spaceShips NOMES HO FA SERVIDOR!!! (i local)
				AsteroidManager::getInstance()->comprova();

				//Fa els updates de tot
				BulletManager::getInstance()->update(elapsedTime);
				AsteroidManager::getInstance()->update(elapsedTime);
				PlayerManager::getInstance()->update(elapsedTime);
			}
			else
				//We've got a winner! ding ding ding
				if (s_clientServidor != "local")
					enviaBi("guanyador");
		}
		//Updates de client
		else {
			if (guanyador == NULL){
				BulletManager::getInstance()->update(elapsedTime);
				PlayerManager::getInstance()->update(elapsedTime);
			}
		}
	}
	//Update dels controladors arduino
	if (sistemaOp != 0)
		if (serial.isInitialized())
			arduinoUpdate();

	//Enviem i rebem de tot
	if (s_clientServidor != "local")
		enviairep();
}	

//--------------------------------------------------------------
void ofApp::draw() {
	if (!acaba_partida) {
		//Si algu ha guanyat nomes dibuixem la pantalla de restart
		if ( guanyador != NULL ) {
			ofPushStyle();
				ofSetColor(guanyador->getColor());
				stringstream id;
				id << "WINER JUGADOR " << guanyador->getId();
				id << " -> SCORE = " << guanyador->getScore();
				ofDrawBitmapString(id.str(), 390, 450);
			ofPopStyle();
			ofDrawBitmapString("Press 'r' to restart, 'f' to finish", 390, 470);
		}
		else {
			//Dibuixem instruccions
			ofPushStyle();
				ofSetColor(255,255,255);
				ofDrawBitmapString("Press '1' to debug/help, '2' to unmute/mute, 'r' to restart, 'f' to finish, 'ESC' to get out", 5, 760);
			ofPopStyle();


			//Dibuixem totes les bales i asteroides
			BulletManager::getInstance()->draw();
			AsteroidManager::getInstance()->draw(debug);
			PlayerManager::getInstance()->draw(debug);

			if (debug) {
				ofPushStyle();
					ofSetColor(255);
					ofDrawBitmapString(ofToString(ofGetFrameRate()), 900, 20);
					ofDrawBitmapString("Player 1 a w d s, Player 0 up, left, right, down, Player 2 mouse, Player 3 joystic i 4 sols per Vacilar.", 5, 745);
				ofPopStyle();
			}
		}
	}
	else {
		//Pantalla de finalització del joc.
		ofPushStyle();
			ofSetColor(0,255,0);
			ofDrawBitmapString("MOLTES GRACIES PER JUGAR!", 240, 364);
			ofDrawBitmapString("Joc creat per Marc Mateu i Ignasi Larroca", 240, 384);
		ofPopStyle();
		ofPushStyle();
			ofSetColor(255,0,0);
			ofDrawBitmapString("No, la musica infernal no s'acaba mai.", 240, 404);
		ofPopStyle();
		ofPushStyle();
			ofDrawBitmapString("'ESC' per sortir, 'r' per reiniciar la partida amb la musiqueta dels ******", 240, 464);
		ofPopStyle();
	}
}


void ofApp::keyPressed(int key) {
	switch (key) {
	// If pressed 1 change debug/help mode
	case '1':
		debug = !debug;
		break;
		// Apretem 2 silenciem, no silenciem
	case '2':
		if (explosion->isLoaded()) {
			explosion->unloadSound();
			AsteroidManager::getInstance()->setExplosionSound(NULL);
		}
		else {
			explosion->loadSound("sounds/explosion.mp3", false);
			AsteroidManager::getInstance()->setExplosionSound(explosion);
		}
		if (pium->isLoaded()) {
			pium->unloadSound();
			BulletManager::getInstance()->setBulletSound(NULL);
		}
		else {
			pium->loadSound("sounds/explosion.mp3", false);
			BulletManager::getInstance()->setBulletSound(pium);
		}
		break;
		//r, ressetegem el joc
	case 'r':
		reset();
		break;
		//f, "Finalitzem" el joc el joc
	case 'f':
		finish();
		break;
		//----------------------------------------------------------------------
	}

}

//Obvi no?
void ofApp::finish() {
	//enviem a tothom la comanda "reset"
	if (s_clientServidor != "local")
		enviaBi("finish"); //enviem a tothom la comanda "finish"
	
	acaba_partida = true;
	cout << "MENTIDAAAAAAAAAAAAAAAAAAA, musicaaaa i mes musicaaaaa Muahahahahhah!" << endl;
}

//Reset del joc.
void ofApp::reset() {
	if (s_clientServidor != "local")
		enviaBi("reset");

	cout << "Reset at:" << endl;
	cout << PlayerManager::getInstance()->getAllScores();

	BulletManager::getInstance()->reset();
	AsteroidManager::getInstance()->reset();

	killSound();

	guanyador = NULL;

	PlayerManager::getInstance()->reset();

	setup();

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}




