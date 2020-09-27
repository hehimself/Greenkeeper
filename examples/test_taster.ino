/*-----------------------------------------------
 * 
 *    Projekt: Arduino Greenkeeper - Taster Test
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
int Button_1_Status = 0;
int Button_2_Status = 0;
int Button_3_Status = 0;
int Button_4_Status = 0;


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
{
  Serial.begin(9600);
  pinMode(Button_1, INPUT);
  pinMode(Button_2, INPUT);
  pinMode(Button_3, INPUT);
  pinMode(Button_4, INPUT);
}

void loop()
{
  Button_1_Status = digitalRead(Button_1);
  if (Button_1_Status == HIGH)
  {
    Serial.println("Button 1 wurde gedrückt");
  }
  Button_2_Status = digitalRead(Button_2);
  if (Button_2_Status == HIGH)
  {
    Serial.println("Button 2 wurde gedrückt");
    delay(00);
  }
  Button_3_Status = digitalRead(Button_3);
  if (Button_3_Status == HIGH)
  {
    Serial.println("Button 3 wurde gedrückt");
  }
  Button_4_Status = digitalRead(Button_4);
  if (Button_4_Status == HIGH)
  {
    Serial.println("Button 4 wurde gedrückt");
  }
}
