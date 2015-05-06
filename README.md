
Marc Mateu Sagues        Nia:146756
Ignasi Larroca Barcelo   Nia:158633

Projecte d'un joc interactiu d'Asteroids per a la classe Sistemes interactius. UPF-2015

S'està programant, compilant i provant en un Linux de 64 bits però hauria de funcionar 
tot correcte en Windows. L'unic addon es el de Xml.

Tot el codi es nostre, els patrons i manera de gestionar les coses l'hem tret de
l'assignatura de Jocs Electronics.
Encara hi ha coses a millorar però n'estem bastant orgullosos. 
S'ha intentat seguir la nostra propi patró d'estil, però a vegades es xoca amb l'estil del framework i queda una mica desordenat.

Per a compilar i executar:

make clean
make
make run

Per jugar:
2 players amb el teclat (però està preparat per a que puguin ser mes players, 
i diferents tipus de controladors Player separat de spaceship).

Player 0
Direcció -> a w d
Disparar -> s

Player 1
Direcció -> esquerra dreta amunt
Disparar -> abaix

Debug 1
Treure el so 2  (millor jugar sense so ja que es bastant molest, ho hem posat per
demostrar que ho sabiem fer..).


/src conté:
Asteroid.cpp .h
AsteroidManager.cpp .h
Bullet.cpp .h
bulletManager.cpp .h
Entity.cpp .h
main.cpp
ofApp.cpp .h
Player.cpp .h
PlayerManager.cpp .h
SpaceShip.cpp .h

/bin conté
/data/asteroids.xml
/data/sounds/explosion.mp3
/data/sounds/lasergun.mp3
