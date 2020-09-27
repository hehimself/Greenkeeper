/*-----------------------------------------------
 * 
 *    Projekt: Arduino Greenkeeper
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

void setup() {
  pinMode(LED_D9, OUTPUT);
  pinMode(LED_D10, OUTPUT);
  pinMode(LED_D11, OUTPUT);
  pinMode(LED_D12, OUTPUT);
  pinMode(LED_D13, OUTPUT);
  pinMode(LED_D14, OUTPUT);
  pinMode(LED_Transistor, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  analogWrite(LED_D9, 70);
  analogWrite(LED_D10, 0);
  analogWrite(LED_D11, 255);
  analogWrite(LED_D12, 255);
  analogWrite(LED_D13, 0);
  analogWrite(LED_D14, 0);
  delay(4000);
  digitalWrite(LED_D9, LOW);
  digitalWrite(LED_D10, LOW);
  digitalWrite(LED_D11, LOW);
  digitalWrite(LED_D12, LOW);
  digitalWrite(LED_D13, LOW);
  digitalWrite(LED_D14, LOW);
  //digitalWrite(LED_Transistor, HIGH);
  delay(4000);
  digitalWrite(LED_Transistor, LOW);
  Serial.print("LED Transistor aus");
}
