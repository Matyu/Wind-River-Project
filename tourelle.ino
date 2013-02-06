// Le code source d'origine est celui de XAVIER Hinault, voir le site http://mon-club-elec.fr/
// Il y a un ajout de code qui sera indiqué dans le programme 

// ------- Licence du code de ce programme ----- 

//  This program is free software: you can redistribute it and/or modify

//  it under the terms of the GNU General Public License as published by

//  the Free Software Foundation, either version 3 of the License,

//  or any later version.

//  This program is distributed in the hope that it will be useful,

//  but WITHOUT ANY WARRANTY; without even the implied warranty of

//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the

//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License

//  along with this program.  If not, see <http://www.gnu.org/licenses/>.



// ////////////////////  PRESENTATION DU PROGRAMME //////////////////// 



// -------- Que fait ce programme ? ---------

 /* Un servomoteur connectÃ© Ã  la carte Arduino est contrÃ´lÃ©

Ã  l'aide d'un shield Joystick (DFRobot). 

L'appui sur un bouton poussoir permet la rÃ©initialisation 

de la position du servomoteur.  */ 



// --- FonctionnalitÃ©s utilisÃ©es --- 



// Utilise la conversion analogique numÃ©rique 10 bits 

// Utilise la carte d'extension Arduino (shield) Joystick + BP x 2

// Utilise un servomoteur



// -------- Circuit Ã  rÃ©aliser --------- 



// ******* ATTENTION : il est possible de connecter directement 2 ou 3 servomoteurs sur la carte Arduino

// Connecter un servomoteur sur la broche 8

// Connecter un servomoteur dur la brche 9

// Enficher la carte d'extension Arduino (shield) Joystick + BP x 2 broche Ã  broche sur la carte EasyCard

// Enficher la carte EasyCard broche Ã  broche sur la carte Arduino

// les connexions sont rÃ©alisÃ©es broche Ã  broche entre le module et la carte Arduino





// /////////////////////////////// 1. EntÃªte dÃ©clarative /////////////////////// 

// A ce niveau sont dÃ©clarÃ©es les librairies incluses, les constantes, les variables, les objets utiles...



// --- DÃ©claration des constantes ---



// --- Inclusion des librairies ---



#include <Servo.h> // librairie pour servomoteur 



// --- DÃ©claration des constantes utiles ---

const int APPUI=LOW; // constante pour tester Ã©tat BP



//--- Constantes utilisÃ©es avec le servomoteur 

const int ANGLE_MIN_TILT=0; // angle position MIN en degrÃ©s

const int POS_MIN_TILT=550; // largeur impulsion pour position ANGLE_MIN degrÃ©s du servomoteur

const int ANGLE_MIN_PAN= 0;
const int POS_MIN_PAN= 550;

                  // par exemple POS_MIN=600 pour ANGLE_MIN=10Â° avec un futaba S3003 

                  // ou POS_MIN=550 pour ANGLE_MIN=0 avec un futaba S3003


const int ANGLE_MAX_PAN = 180;
const int POS_MAX_PAN = 2450;

// Ajout de nouvelles constantes par rapport au code d'origine
const int ANGLE_MAX_TILT=180; // angle position MAX en degrÃ©s

int POS_MAX_TILT=2450;  // largeur impulsion pour position ANGLE_MAX degrÃ©s du servomoteur

                  // POS_MAS=2300 pour ANGLE_MIN=170Â° pour futaba s3003

                  // ou POS_MAX=2400 pour ANGLE_MAX=172 pour futaba S3003



// pour Ã©talonner un servomoteur, voir la page : 

//http://www.mon-club-elec.fr/pmwiki_mon_club_elec/pmwiki.php?n=MAIN.ArduinoExpertSerieDepuisPCPositionServomoteur



// --- DÃ©claration des constantes des broches E/S numÃ©riques ---



const int bpRouge=3; // Constante pour la broche 3

const int bpBleu=4; // Constante pour la broche 4

const int bpJoystick=5; // Constante pour la broche 5



const int broche_servoPan=8; // Constante pour la broche 8

const int broche_servoTilt=9; // Constante pour la broche 8



// --- DÃ©claration des constantes des broches analogiques ---



const int axe1Joystick=0; // Constante pour la broche analogique 0

const int axe2Joystick=1; // Constante pour la broche analogique 1



// --- DÃ©claration des variables globales ---



int mesure_brute=0;// Variable pour acquisition rÃ©sultat brut de conversion analogique numÃ©rique

float mesuref=0.0;// Variable pour calcul rÃ©sultat dÃ©cimal de conversion analogique numÃ©rique



int positionAxe1=0; // Variable pour acquisition rÃ©sultat brut de conversion analogique numÃ©rique axe 1 Joystick

int positionAxe2=0; // Variable pour acquisition rÃ©sultat brut de conversion analogique numÃ©rique axe 2 Joystick



int angleServoPan=90; // variable de position du servo  Pan en degrÃ©s

int angleServoTilt=90; // variable de position du servo  Tilt en degrÃ©s



int angleServoPan0=90; // variable de la derniÃ¨re position du servo  Pan en degrÃ©s

int angleServoTilt0=90; // variable de la derniÃ¨re position du servo  Tilt en degrÃ©s



// --- DÃ©claration des objets utiles pour les fonctionnalitÃ©s utilisÃ©es ---



//--- CrÃ©ation objet servomoteur 

Servo mon_servoPan;  // crÃ©e un objet servo pour contrÃ´ler le servomoteur 1

Servo mon_servoTilt;  // crÃ©e un objet servo pour contrÃ´ler le servomoteur 2





// ////////////////////////// 2. FONCTION SETUP = Code d'initialisation ////////////////////////// 

// La fonction setup() est exÃ©cutÃ©e en premier et 1 seule fois, au dÃ©marrage du programme



void setup()   { // debut de la fonction setup()


// Ajout de la fonction de Serial
Serial.begin(115200);


// --- ici instructions Ã  exÃ©cuter 1 seule fois au dÃ©marrage du programme --- 



// ------- Initialisation fonctionnalitÃ©s utilisÃ©es -------  



//--- Initialisation Servomoteur 

mon_servoPan.attach(broche_servoPan);  // attache l'objet servo Ã  la broche de commande du servomoteur Pan

mon_servoTilt.attach(broche_servoTilt);  // attache l'objet servo Ã  la broche de commande du servomoteur Tilt





// ------- Broches en sorties numÃ©riques -------  

 pinMode (broche_servoPan,OUTPUT); // Broche broche_servoPan configurÃ©e en sortie

 pinMode (broche_servoTilt,OUTPUT); // Broche broche_servoPan configurÃ©e en sortie



// ------- Broches en entrÃ©es numÃ©riques -------  

 pinMode (bpRouge,INPUT); // Broche bpRouge configurÃ©e en entrÃ©e

 pinMode (bpBleu,INPUT); // Broche bpBleu configurÃ©e en entrÃ©e

 pinMode (bpJoystick,INPUT); // Broche bpJoystick configurÃ©e en entrÃ©e



// ------- Activation si besoin du rappel au + (pullup) des broches en entrÃ©es numÃ©riques -------  



// Les BP du shield Joystick + BPx2 dispose d'un rappel au plus sur le shield





// ------- Initialisation des variables utilisÃ©es -------  



// ------- Codes d'initialisation utile -------  



mon_servoPan.writeMicroseconds(anglePan(angleServoPan)); // crÃ©e impulsion Ã  partir valeur angle - plus prÃ©cis que write()

mon_servoTilt.writeMicroseconds(angleTilt(angleServoTilt)); // crÃ©e impulsion Ã  partir valeur angle - plus prÃ©cis que write()







} // fin de la fonction setup()

// ********************************************************************************

// Création d'une nouvelle fonction de conversion, ajout par rapport au code source

int convert(String str) {
 
 int nbre = 0; 
 int tm = 1;
 
 for(int i = str.length() - 1; i >= 0; i--) {
   int e;
   
         switch(str[i]) {
              case '0':
                  e = 0;
                break;
              case '1':
                  e = 1;
                break;
              case '2':
                  e = 2;
                break;
              case '3':
                  e = 3;
                break;
              case '4':
                  e = 4;
                break;
              case '5':
                  e = 5;
                break;
              case '6':
                  e = 6;
                break;
              case '7':
                  e = 7;
                break;
              case '8':
                  e = 8;
                break;
              case '9':
                  e = 9;
                break;
              default:
                break;
         } 
   
     nbre += (e * tm);
     tm *= 10;
   } 
   
 return nbre;
}

//Ajout 

boolean isNumberorSemi_colon(char carac) {
 switch(carac) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case ';':
      return true;
    default:
      return false;
 } 
 
 return false;
 
}


////////////////////////////////// 3. FONCTION LOOP = Boucle sans fin = coeur du programme //////////////////

// la fonction loop() s'exÃ©cute sans fin en boucle aussi longtemps que l'Arduino est sous tension

void loop(){ // debut de la fonction loop()

// Les premières lignes de codes sont ajoutées
int bt = 0;
String tmp = "";

boolean inkeyboard = false;

if (Serial.available() > 0) {
  
  while(1){
    bt = Serial.read();
    if(isNumberorSemi_colon(char(bt)))
      tmp = tmp + char(bt);
    if(char(bt) == '\n')
      break;
    
  }
    
    String str_axe_1 = tmp.substring(0, tmp.indexOf(';'));
    String str_axe_2 = tmp.substring(tmp.indexOf(';') + 1, tmp.length());
    
    if(str_axe_1 != "")
      positionAxe1 = convert(str_axe_1);
    else
      positionAxe1 = mon_servoTilt.read();
    if(str_axe_2 != "")
      positionAxe2 = convert(str_axe_2);
    else
      positionAxe2 = mon_servoPan.read();
    inkeyboard = true;
}

else {
  
    positionAxe1=analogRead(axe1Joystick); // acquisition conversion analogique numÃ©rique sur broche analogique axe 1

    positionAxe2=analogRead(axe2Joystick); // acquisition conversion analogique numÃ©rique sur broche analogique axe 2
    //----- lecture position Joytstick
    inkeyboard = false;

  


if (positionAxe2>700) {

   if (angleServoPan <= ANGLE_MAX_PAN)
     angleServoPan=angleServoPan+1; 

   constrain(angleServoPan,ANGLE_MIN_PAN,ANGLE_MAX_PAN); 

}



if (positionAxe2<300) {

   if (angleServoPan > 0)
     angleServoPan=angleServoPan-1; 

   constrain(angleServoPan,ANGLE_MIN_PAN,ANGLE_MAX_PAN); 

}



if (positionAxe1>700) { 

   if (angleServoTilt <= ANGLE_MAX_TILT)
       angleServoTilt=angleServoTilt+1; 

   constrain(angleServoTilt,ANGLE_MIN_TILT,ANGLE_MAX_TILT); 

}



if (positionAxe1<300) {
   if (angleServoTilt > 0)
      angleServoTilt=angleServoTilt-1;

  constrain(angleServoTilt,ANGLE_MIN_TILT,ANGLE_MAX_TILT);  

}

}

//---- lecture Ã©tat des BP du shield Joystick

if (digitalRead(bpRouge)==APPUI) { // si appui BP rouge



    angleServoTilt=90; // rÃ©initialise angle Tilt



}



if (digitalRead(bpBleu)==APPUI) { // si appui BP 



    angleServoPan=90; // rÃ©initialise angle PAN 

}



if (digitalRead(bpJoystick)==APPUI) { // si appui BP joystick



}



//------------- mise Ã  jour de la position du servomoteur --- 

// Ajout

if(!inkeyboard) {


    if (angleServoPan!=angleServoPan0) {

      mon_servoPan.writeMicroseconds(anglePan(angleServoPan)); // crÃ©e impulsion Ã  partir valeur angle - plus prÃ©cis que write()

      angleServoPan0=angleServoPan; // mÃ©morise derniÃ¨re valeur angle prise en compte

    }





    if (angleServoTilt!=angleServoTilt0) { // si angleServoTilt a changÃ©

      mon_servoTilt.writeMicroseconds(angleTilt(angleServoTilt)); // crÃ©e impulsion Ã  partir valeur angle - plus prÃ©cis que write()

      angleServoTilt0=angleServoTilt; // mÃ©morise derniÃ¨re valeur angle prise en compte

    }


  delay(6);



    // fixe la vitesse de mouvement du servo - entre 2 lecture analogique

 } else {
   if(positionAxe1 < 0)
     positionAxe1 = 0;
   if(positionAxe1 > 180)
     positionAxe1 = 180;
   if(positionAxe2 < 0)
     positionAxe2 = 0;
   if(positionAxe2 > 180)
     positionAxe2 = 180;
  
   mon_servoTilt.writeMicroseconds(angleTilt(positionAxe1));
   mon_servoPan.writeMicroseconds(anglePan(positionAxe2));
   
  
 }
// Fin ajout


//while(1); // stop loop


} // fin de la fonction loop() - le programme recommence au dÃ©but de la fonction loop sans fin

// ********************************************************************************





// ////////////////////////// FONCTIONS DE GESTION DES INTERRUPTIONS //////////////////// 





// ////////////////////////// AUTRES FONCTIONS DU PROGRAMME //////////////////// 



//------------- fonction calibrage impulsion servomoteur Ã  partir valeur angle en degrÃ©s

//Modification de la fonction angle et ajout de la nouvelle fonction angleTilt

int anglePan(int val) {
     int impuls = 0;
     impuls= map(val, ANGLE_MIN_PAN, ANGLE_MAX_PAN, POS_MIN_PAN, POS_MAX_PAN);
     return impuls; 
  
}

int angleTilt(int valeur_angle) { 



  int impuls=0;

	impuls=map(valeur_angle,ANGLE_MIN_TILT,ANGLE_MAX_TILT,POS_MIN_TILT, POS_MAX_TILT);

	return impuls;   



} // fin fonction impulsion servomoteur



// ////////////////////////// Fin du programme //////////////////// 

