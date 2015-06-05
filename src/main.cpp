//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	//Salvatjada al main. Pur i net que estava..
	cout << "Benvinguts a Asteriods, contesteu un parell de preguntes"<< endl;

	int clientServidor;
	cout << "Aquesta instancia sera 0 servidor, 1 client o 3 sol?" << endl;
	cin >> clientServidor;

	string Host = "localhost";
	if (clientServidor == 0 || clientServidor == 1) {
		cout << "Introdueix la IP de l'altra maquina" << endl;
		cin >> Host;
	}

	int sistemaOp;
	cout << "Arduino no connectat 0, Ardunio en linux 1, Arduino en Windows 2, Arduino en MAC 3" << endl;
	cin >> sistemaOp;

	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp(clientServidor, sistemaOp, Host));

}
