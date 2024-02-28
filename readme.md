
# Motors Control

Project developped for Ersatz by kalinarm (kalinarm@gmail.com)

Permet le controle d'une grille de servo moteur par 2 drivers sur I2C
et le controle d'un moteur pas à pas
Le tout est controlable en DMX ou en port série (sur USB) : 
Pas les deux en meme temps, en mode DEBUG le port série est activé, et sinon c'est le port DMX

## Setup

Utiliser l'environnement arduino (Arduino IDE v 1.8 ou supérieur) pour uploader ce programme.
Dans Arduino, allez dans Croquis/Inclure Bibliothèque/Gérér les bibliothèques
Installer les bibliothèques : 
- Adafruit Motor Shield library
- Adafruit PWM Servo Driver library
- AccelStepper
 
Brancher votre carte Arduino sur le port USB
Configurer le bon port COM dans Outils
Cliquer sur Upload

## Configuration

Pour enlever le mode debug et passer par un controle DMX, 
il faut commenter le #define DEBUG au début de constants.h

La plupart de la configuration se fait dans l'onglet constants.h
notamment,
- la position de la grille, pour gérer le multi grille GRID_X
- la vitesse du port série : SERIAL_SPEED
- le nombre de moteur X_COUNT et Y_COUNT

L'adresse DMX peut etre changé pour les différentes cartes
DMX_SLAVE_CHANNELS représente la première addresse DMX et DMX_COMMANDS_COUNT le nombre de canaux reservés.
Il faut qu'une autre carte soit configuré en DMX_SLAVE_CHANNELS dans une autre plage que DMX_SLAVE_CHANNELS -> DMX_SLAVE_CHANNELS + DMX_COMMANDS_COUNT de la première carte.

MOTOR_MIN, MOTOR_MAX et MOTOR_RANGE, correspondent à des calculs internes, ne pas modifier sans savoir ce que l'ont fait.

## Fonctionnement

Pour controller la carte : 
nous pouvons controller le moteur pas à pas, 
ou l'ensemble des servos moteurs pour leur faire faire des mouvements syncronisés.

### En mode port série (DEBUG activé)

Le moteur pas à pas se controle avec cette commande :

**300 [moveDirection] [speed]**

avec

- [moveDirection] : 0->20=stop, 20->60=clockwise, 60->100= anticlockwise
- [speed] : vitesse entre 0 et 100 de rotation


Les servos moteurs sont controllables en choisissant des modes de fonctionnement

**[mode] [intensity] [speed] [offset]**

Ceci se règle à travers 4 paramètres

- [mode] choix du mode
- [intensity] Amplitude du mouvement [0 - 100]
- [speed] Vitesse du mouvement [0 - 100]
- [offset] reférence du mouvement [0 - 100] (la valeur par défault est 0)

### En mode DMX (DEBUG desactivé)

La carte est configuré comme un périphérique DMX esclave.
Chaque canaux correspond à une commande
Il faut ajouter DMX_SLAVE_CHANNELS à chaque canal cité ici pour avoir le bon canal DMX

- [0] Stepper direction : 0->20=stop, 20->60=clockwise, 60->100= anticlockwise
- [1] Stepper speed [0 - 100]


- [2] Mode selection [0 - 100]
- [3] Mode intensity [0 - 100]
- [4] Mode speed [0 - 100]
- [5] Mode offset [0 - 100]

## Les modes

Voici les différents mode, le chiffre au début représente le range de la commande [mode] à envoyer pour selectionner le mode.

------------------------------
| Min  | Max | Mode | Description  |
| ------------ | ------------| ------------| ------------ |
| 0 | 10 | zero | Remet tout les servos moteurs à zero |
| 10 | 20 | zero | Remet tout les servos moteurs à zero |
| 20 | 30 | uniform | Tout les servos moteurs sont mis à **offset** |
| 30 | 40 | WaveY | simule une vague en Y |
| 40 | 50 | WaveX | simule une vague en X |
| 50 | 60 | IcePack | simule une banquise, faire varier **offset** de 0 à 100 pour simuler l'effondrement |
| 60 | 70 | Random | les moteurs bougent de facon aléatoire|
| 70 | 80 | Sea | simule la mer dont l'état est reglable avec **intensity** et **speed** |
| 80 | 90 | SinusY | simule un sinus en Y |
| 90 | 100 | SinusX | simule un sinus en X |


## documentation
problem with stepper motor : [https://community.element14.com/members-area/personalblogs/b/blog/posts/arduino-controlling-stepper-motor-28byj-48-with-accelstepper-library]