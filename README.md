
Marc Mateu Sagues        Nia: 146756
Ignasi Larroca Barcelo   Nia: 158633
https://github.com/MarcObvious/Asteroids

------------------------------------------------------------------------------------------------------------
Projecte d'un joc interactiu Asteroids amb Arduino UNO per a la classe Sistemes interactius. UPF-2015.

EL JOC ES CAÒTIC. Molts Asteroides i moltes Naus. Ho sabem, i ens agrada.

Tot el codi es nostre o està acreditat, els patrons i manera de gestionar events ens els hem 
inventat o tret l'assignatura de Jocs Electronics.

Està programat, compilat i provat en un Linux de 64 bits.
També està testejat amb VisualStudio 2012 64 bits 

Es MULTI-PLATAFORMA. Una instancia pot estar en Linux, l'altre en Windows, i tot funcionarà
correctament.

------------------------------------------------------------------------------------------------------------
Les comunicacions amb Arduino no funcionen gaire bé en Linux. En Windows tot perfecte.
Les comunicacions per la xarxa funcionen perfecte. En condicions normals el servidor envia 
uns 35 KiB/s i el client uns 24 KiB/s (Molt optimitzable. We know it). 
Els addons OpenFrameworks son el de Xml i el de OSC.

Si no funciona, desbloquejar el port 12345! (Iptables rules, permetre firewall en Windows)

La lògica amb Arduino es simple, Un joystic per controlar un player, un button o touchButton per
a reiniciar el joc, una pantalla LCD que informa de diferents events i un led i buzzer que 
ens reservem dir quan i que fan ;).
Es pregunta al usuari si vol jugar sense-Arduino(0), Arduino-Linux(1), Arduino-Windows(2), 
Arduino-Mac(3).

------------------------------------------------------------------------------------------------------------
Hi han diversos modes de joc, en solitari(3), fent de client(1) o fent de servidor(0).
Es pregunta a l'usuari a l'inici sobre com es vol jugar. Si s'escull (0) o (1) es demanarà
també la IP de l'altre ordinador.
(0) Controlarà Player 1 (teclat), Player 3 (Arduino).
(1) Controlarà Player 0 (teclat), Player 2 (Ratolí), Player 4 (Arduino). 
(3) Els controla tots.
(veure controls a doc/Controls)

------------------------------------------------------------------------------------------------------------
Per a compilar i executar:
Crear projecte Openframeworks amb AddOn xMlSettings i OSC.
Clonar Repositori dins, git@github.com:MarcObvious/Asteroids.git

Si es vol utilitzar Arduino: 
Carregar la llibreria LCD (Arduino/SerialLCD.rar) a on estigui instal·lat Arduino.


Compilar i executar el fitxer arduino_stars al Arduino UNO(veure esquema a doc/Arduino)

En Linux:
make clean
make -sj4 
make run


En Windows:
Compilar i executar VisualStudio en Release.

------------------------------------------------------------------------------------------------------------
Notes:
El joc es COMPLETAMENT dinàmic. Si es vol fer mes players nomes s'han de demanar al PlayerManager i tota la 
resta seguirà funcionant (Scores, updates, representació per pantalla, etc), està fet aixi ja que seria fàcil 
implementar "rivals" controlats per IA (classe enemic, no acabada).

Amb Arduino es possible que s'hagi de canviar el PORT a ofApp manualment.

Nomes es selecciona Arduino a la instancia on estigui connectat. (O en les 2 alhora)

Els controls son els mateixos independentment si estas en client o servidor

El joc comença SILENCIAT.

------------------------------------------------------------------------------------------------------------
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
ofApp.cpp .h -> Aquí passa tota la màgia.
Controlador.cpp .h -> Base de cada tipus de controlador. "Representa a cada entitat que jugui"
Player.cpp .h -> Controlador que utilitza teclat
PlayerArd.cpp .h -> Controlador que utilitza controls Arduino
PlayerRat.cpp .h -> Controlador que utilitza el ratolí 
PlayerNet.cpp .h -> Controlador que utilitza missatges rebuts per la Xarxa
Enemic.cpp .h -> Controlador que utilitza certa IA (no està implementat)
PlayerManager.cpp .h -> Gestiona tots els Controladors, els dibuixa, fa upgrades i informa dels resultats.


bin/ conté
data/asteroids.xml
data/sounds/explosion.mp3
data/sounds/lasergun.mp3


Arduino/
arduino_stars/arduino_stars.io -> Lògica que carreguem a la placa Arduino UNO
SerialLCD.rar -> Llibreries per utilitzar SerialLCD

------------------------------------------------------------------------------------------------------------
![ScreenShot](https://github.com/MarcObvious/Asteroids/blob/master/screenshots/screenshot1.png)



