//****************************************************************************//
//                   Marc Mateu Sagues,       Nia:146756                      //
//                   Ignasi Larroca Barcelo   Nia:158633                      //
//****************************************************************************//

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	cout << "Benvinguts a Asteriods, contesteu un parell de preguntes"<< endl;
	int clientServidor;
	cout << "Aquesta instancia sera 0 servidor o 1 client?" << endl;
	cin >> clientServidor;
	int sistemaOp;
	cout << "Arduino no connectat 0, Ardunio en linux 1, Arduino en Windows 2" << endl;
	cin >> sistemaOp;

	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp(clientServidor, sistemaOp));

}
