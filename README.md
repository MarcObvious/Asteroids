
Marc Mateu Sagues        Nia: 146756
Ignasi Larroca Barcelo   Nia: 158633

Projecte d'un joc interactiu d'Asteroids amb Arduino UNO per a la classe Sistemes interactius. UPF-2015

Està programant, compilant i provant en un Linux de 64 bits.
També està testejat amb VisualStudio 2012 64 bits 

Les comunicacions amb Arduino no funcionen gaire bé en Linux. En Windows tot perfecte.
L'únic addon OpenFrameworks es el de Xml.

Tot el codi es nostre o està acrediat, els patrons i manera de gestionar events ens els hem 
inventat o tret l'assignatura de Jocs Electronics.

La lògica amb Arduino es simple, Un joystic per controlar un player, un button o touchButton per
a reiniciar el joc, una pantalla LCD que informa de diferents events i un led i buzzer que 
ens reservem dir quan i que fan ;).

Per a compilar i executar:

Crear projecte Openframeworks amb AddOn xMlSettings.
Clonar Repositori dins, git@github.com:MarcObvious/Asteroids.git

Si es vol utilitzar Arduino: 
Carregar la llibreria LCD (Arduino/SerialLCD.rar) a on estigui instalat Arduino.

Compilar i executar el fitxer arduino_stars al Arduino UNO(veure esquema a doc/Arduino)

En Linux:
Descomentar la linea serial.setup("/dev/ttyACM0", baud) a ofApp (amb el port corresponent). 
Comentar la de Windows.

make clean | make -sj4 
make run

En Windows:
Descomentar la linea serial.setup("COM4", baud); a ofApp (amb el port corresponent).
Comentar la de Linux.

Compilar i executar VisualStudio en Release.

ES POT JUGAR SENSE ARDUINO. El joc comença SILENCIAT.

doc /conté:
Controls.txt -> Explicació sobre com es controla el joc.
Esquema Arduino.txt -> Explicació de a quin port ha d'anar cada sensor

src/ conté:
Entity.cpp .h -> Base de cada objecte amb representació visual
Asteroid.cpp .h   -> Entitat amb forma i lògica dels asteroides.
AsteroidManager.cpp .h   -> Gestiona tots els Asteroides que hi han al mapa (dibuixa. fa upgrades)
SpaceShip.cpp .h -> Entitat amb forma i lògica de spaceShip
Bullet.cpp .h -> Entitat amb forma i lògica de bala.
bulletManager.cpp .h -> Gestiona totes les Bales que hi han al mapa (dibuixa, fa upgrades)
main.cpp -> Obvi no?
ofApp.cpp .h -> Aquí passa tota la magia.
Controlador.cpp .h -> Base de cada tipus de controlador. "Representa a cada entitat que jugui"
Player.cpp .h -> Controlador que utilitza teclat
PlayerArd.cpp .h -> Controlador que utilitza controls Arduino
PlayerRat.cpp .h -> Controlador que utilitza el ratolí 
Enemic.cpp .h -> Controlador que utilitza certa IA (no està implementat)
PlayerManager.cpp .h -> Gestiona tots els Controladors, els dibuixa, fa updates i informa dels resultats.


bin/ conté
data/asteroids.xml
data/sounds/explosion.mp3
data/sounds/lasergun.mp3

Arduino/
arduino_stars/arduino_stars.io -> Lògica que carreguem a la placa Arduino UNO
SerialLCD.rar -> Llibreries per utilitzar SerialLCD


