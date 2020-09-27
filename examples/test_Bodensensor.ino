/*-----------------------------------------------
 * 
 *    Projekt: Arduino Greenkeeper - Test Bodensensor
 * 
 *    Name: Marvin Schmid
 * 
 *    Version: 0.1
 * 
 * -----------------------------------------------
*/
//Arduino LEDs
const int LED_D9 = 3;
const int LED_D10 = 9;
const int LED_D11 = 5;
const int LED_D12 = 6;
const int LED_D13 = 10;
const int LED_D14 = 11;
const int LED_Transistor = 4;

//Arduino Schalter
const int Button_1 = 7;
const int Button_2 = 8;
const int Button_3 = 12;
const int Button_4 = 13;

//Arduino Aktoren
const int Pumpe = 2;

//Arduino Sensoren
const int Bodensensor = A3;
const int Wasserstand_1 = A1;
const int Wasserstand_2 = A2;
const int Lichtsensor = A6;
const int Temperatursensor = A7;
int Bodensensor_Messwert = 0;
int Wasserstand_1_Messwert = 0;
int Wasserstand_2_Messwert = 0;
int Lichtsensor_Messwert = 0;
int Temperatursensor_Messwert = 0;
int Temperatur = 0;

void setup() 

{ ////Hier beginnt das Setup.

  Serial.begin(9600); //Die Kommunikation mit dem seriellen Port wird gestartet. Das benötigt man, um sich den ausgelesenen Wert im serial monitor anzeigen zu lassen.

}

void loop()

{ //Hier beginnt der Hauptteil  

  Bodensensor_Messwert = analogRead(Bodensensor); //Die Spannung an dem Sensor wird ausgelesen und unter der Variable „messwert“ gespeichert.

  Serial.print("Feuchtigkeits-Messwert:"); //Ausgabe am Serial-Monitor: Das Wort „Feuchtigkeits-Messwert:"

  Serial.println(Bodesensor_Messwert); //und im Anschluss der eigentliche Messwert.

  delay(1000); //Zum Schluss noch eine kleine Pause, damit nicht zu viele Zahlenwerte über den Serial-Monitor rauschen.

}
