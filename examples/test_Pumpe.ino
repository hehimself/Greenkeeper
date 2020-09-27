/*-----------------------------------------------
 * 
 *    Projekt: Arduino Greenkeeper - Test Pumpe
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
const int Pumpe = 4;

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

int transistor = 2;
void setup() {
  pinMode(Pumpe, OUTPUT);
  pinMode(transistor, OUTPUT);
  delay(5000);
  digitalWrite(transistor, HIGH);
  delay(1000);
  digitalWrite(Pumpe, HIGH);
  delay(1000);
  digitalWrite(Pumpe, LOW);
  delay(1000);
}

void loop() {
  delay(10000);
  digitalWrite(transistor, HIGH);
  delay(1000);
  digitalWrite(Pumpe, HIGH);
  delay(1000);
  digitalWrite(Pumpe, LOW);
  delay(1000);
  digitalWrite(transistor, LOW);
}
