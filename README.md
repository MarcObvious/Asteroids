
Marc Mateu Sagues        Nia:146756
Ignasi Larroca Barcelo   Nia:158633

Projecte d'un joc interactiu d'Asteroids amb Arduino UNO per a la classe Sistemes interactius. UPF-2015

Està programant, compilant i provant en un Linux de 64 bits.
Tambè està testejat amb VisualStudio 2012 64 bits 

Les comunicacions amb arduino no funcionen gaire bè en Linux. En Windows tot perfecte
L'unic addon Openframeworks es el de Xml.

Tot el codi es nostre, els patrons i manera de gestionar events ens els hem inventat o tret
l'assignatura de Jocs Electronics.

Encara hi ha coses a millorar però n'estem bastant orgullosos. 
S'ha intentat seguir la nostra propi patró d'estil, però a vegades es xoca amb l'estil del framework i queda una mica desordenat.

Per a compilar i executar:

Clonar Repositori, git@github.com:MarcObvious/Asteroids.git
Crear projecte Openframeworks amb AddOn xMlSettings

Si es vol utilitzar Arduino: 
Carregar la llibreria LCD (Arduino/SerialLCD.rar) a on estigui instalat Arduino.
Compilar i executar el fitxer arduino_stars al Arduino UNO(veure esquema a doc/Arduino)

En linux:
Descomentar la linea serial.setup("/dev/ttyACM0", baud) a ofApp (amb el port corresponent). 
Comentar la de Windows.

make clean | make -sj4 
make run

En Windows:
Descomentar la linea serial.setup("COM4", baud); a ofApp (amb el port corresponent).
Comentar la de Linux.
Compilar i executar VisualStudio en Release.

Per jugar:
2 players amb el teclat (però està preparat per a que puguin ser mes players, 
i diferents tipus de controladors Player separat de spaceship).


src/ conté:
Entity.cpp .h -> Base de cada objecte amb representació visual
Asteroid.cpp .h   -> Entitat amb forma i logica dels asteroides.
AsteroidManager.cpp .h   -> Gestiona tots els Asteroides que hi han al mapa (dibuixa. fa upgrades)
SpaceShip.cpp .h -> Entitat amb forma i logica de spaceShip
Bullet.cpp .h -> Entitat amb forma i logica de bala.
bulletManager.cpp .h -> Gestiona totes les Bales que hi han al mapa (dibuixa, fa upgrades)
main.cpp -> Obvi no?
ofApp.cpp .h -> Base
Controlador.cpp .h -> Base de cada tipus de controlador. "Representa a cada entitat que jugui"
Player.cpp .h -> Controlador que utilitza teclat
PlayerArd.cpp .h -> Controlador que utilitza controls arduino
PlayerRat.cpp .h -> Controlador que utilitza el ratolí 
Enemic.cpp .h -> Controlador que utilitza certa IA (no està implementat)
PlayerManager.cpp .h -> Gestiona tots els Controladors, els dibuixa, fa updates i informa dels resultats.


bin/ conté
data/asteroids.xml
data/sounds/explosion.mp3
data/sounds/lasergun.mp3

Arduino/
arduino_stars/arduino_stars.io -> Logica que carreguem a la placa Arduino UNO
SerialLCD.rar -> LLibreries per utilitzar SerialLCD.s


