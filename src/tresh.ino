//Aymen Ezzayer - Ei2i2
//Tresh - A Battery informations displayer on Arduino
//V1.0 11/06/2021

/* 
Spécifications : 
Écran OLED 128x64 : - SDA (Port A4, Pin 4)- ; - SCL (Port A5, Pin 5) - ; - GND -> GND - ; - VCC -> 5V - .
*/

//Bibliothéque 
#include <Adafruit_SSD1306.h> //Lib pour l'écran
#include <Adafruit_INA219.h> //Lib pour l'INA 219
#include <Wire.h> //Lib pour pointer les pins qu'utilise l'INA219

//Paramétres
Adafruit_SSD1306 display(4); //On met 4 car le pin SDA est sur A4
Adafruit_INA219 ina219; //On initialise le paramétre de l'INA219

//Prototypes
void InitMenu(); //Prototype de InitMeny

//Variables Globales
float pourcentage_batterie = 0; //On initialise le pourcentage de batterie
bool test = true; //On crée une var test qui va permettre d'alterner entre le mode de test du code et le vrai code.

//Objets

//Fonctions
/* 
Nom        : InitMenu
Fonction   : Initialise le Menu Principal
Paramétres : NONE
*/
void InitMenu()
{
 display.clearDisplay(); //On efface l'écran
 
 //Scrutation des Var
 digitalWrite(2,HIGH);
 float shuntvoltage = ina219.getShuntVoltage_mV(); //Voltage qui passe dans la résistance de l'INA219 en milli Volt
 float busvoltage = ina219.getBusVoltage_V(); //Voltage du bus physique
 float current_mA = ina219.getCurrent_mA(); //Courrant actuel en milli-Ampére
 float loadvoltage = busvoltage + (shuntvoltage / 1000); //Combien il reste dans la batterie
 float power = current_mA * loadvoltage; //Puissance du courrant
 if (test == false) { float pourcentage_batterie = (busvoltage - 3.2) / 0.6; } //On calcule le pourcentage de la batterie sachant que la batterie agit entre 3,2V et 3,6V
 
 //Titre du Menu
 display.setTextColor(WHITE); //On met la couleur du texte en blanc
 display.setCursor(50,0); //On set le curseur en X = 50; Y = 0
 display.println("Tresh"); //On écrit le nom de notre produit au milieu de l'écran
 
 //Batterie
 display.setCursor(0,0); //On set la position à X = 0 ; Y = 0
 display.drawRect(14, 12, 12, 4, WHITE); //Embout de la Batterie
 display.drawRect(10, 15, 20, 13, WHITE); //Squelette de la Batterie
 float barre_batterie = 0.00; //Variable qui compte les barres de batterie
 for (barre_batterie ; barre_batterie < (pourcentage_batterie/10)+0.5 ; barre_batterie ++) { display.fillRect(12, 26-barre_batterie, 16, 1, WHITE); }
 /*Pour chaque barre de batterie (Minimum 1; Maximum 10) on affiche une barre dans le squelette de la batterie. On rajoute 0,5 pour arrondir au supérieur. 
 Exemple : Pourcentage_batterie = 67%; Barre = (67/10)+0,5 = 6,7+0,5 = 7,2 ; ainsi on affiche 7 barre et on simplifie ainsi l'affichage. */
 display.setCursor(2,2);
 display.println(pourcentage_batterie); //On affiche le pourcentage de batterie à côté de l'indicateur visuel
 if (pourcentage_batterie >= 100) { display.setCursor(40,2); } //Si on est à 100% on décale l'affichage du '%'
 else { display.setCursor(33,2); }
 display.println("%");

 //Informations Analogique
 /*On détérmine le nombre d'heure que ça prends pour tout vider à 100% avec le rapport [mAh_de_la_batterie/consommation_du_circuit].
 On multiplie ça par le rapport [pourcentage_batterie/100], ainsi à 100% on aura un coef de 1, si on est à 50% on aura un coef de 0,5 et ainsi de suite.*/
 float heures_restantes = (1800.0/331.0)*(pourcentage_batterie/100); //On calcule le nombre d'heures restantes
 int nombre_heures = (int)heures_restantes; //On calcule le nombre d'heures ENTIERES restantes, EX: Si on a 5.33 heures alors on a 5h et 0,33*60 minutes.
 float minutes_restantes = (heures_restantes-nombre_heures)*60; //On calcule le nombre de minutes restantes EX: Si on a 5.33 heures alors on a (5,33-5)*60 minutes.
 int nombre_minutes = (int)minutes_restantes; //On calcule le nombre de minutes ENTIERES restantes
 float secondes_restantes = (minutes_restantes-nombre_minutes)*60; //On calcule le nombre de secondes restantes EX: Si on a 43.57 minutes alors on a (48,57-48)*60 secondes.
 int nombre_secondes = (int)secondes_restantes; //On calcule le nombre de secondes ENTIERES restantes
 
 //HEURES
 if(nombre_heures < 10) { display.setCursor(74,20); } //Si on a qu'une seule unité on décale l'écriture pour ne pas laisser de blanc
 else { display.setCursor(68,20); }
 display.println(nombre_heures); //On affiche le nombre d'heures restantes
 display.setCursor(80,20);
 display.println("h");
 //MINUTES
 if(nombre_minutes < 10) { display.setCursor(96,20); } //Si on a qu'une seule unité on décale l'écriture pour ne pas laisser de blanc
 else { display.setCursor(90,20); }
 display.println(nombre_minutes); //On affiche le nombre de minutes restantes
 display.setCursor(102,20);
 display.println("m");
 //SECONDES
 if(nombre_secondes < 10) { display.setCursor(116,20); } //Si on a qu'une seule unité on décale l'écriture pour ne pas laisser de blanc
 else { display.setCursor(110,20); }
 display.println(nombre_secondes); //On affiche le nombre de secondes restantes
 display.setCursor(122,20);
 display.println("s");

 //Display
 display.display();
}

/* 
Nom        : Setup
Fonction   : Initialise la boucle d'éxécution
Paramétres : NONE
*/
void setup()
{
  //Init Serial USB
  Serial.begin(9600); //On régle la vitesse à 9600Bauds
  Serial.println(F("Lancement de Tresh")); //On écrit dans le moniteur série afin de s'avoir quand le programme commence
  
  //Init OLED screen
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Le premier paramétre correspond à l'écran et le deuxiéme correspond à l'adresse du port I2C : 0x3C :
  display.clearDisplay();
  ina219.begin();
  pinMode(2,OUTPUT);  //ON met le pin mode en OUTPUT
}

/* 
Nom        : Loop
Fonction   : Boucle d'éxécution
Paramétres : NONE
*/
void loop()
{
 if (test == true) //On lance la boucle de test
 {
  if (pourcentage_batterie <= 0) {pourcentage_batterie = random(30,100);}
  while (pourcentage_batterie > 0)
  {
   delay(1); //On gére le taux de rafraichissement
   float perte_batterie = random(1,10);
   perte_batterie = perte_batterie/100;
   pourcentage_batterie = pourcentage_batterie - perte_batterie; //Décrémentation de test
   InitMenu(); //On affiche le menu
  }
 }
 else
 {
  delay(1); //On gére le taux de rafraichissement
  InitMenu(); //On affiche le menu
 }
} 
