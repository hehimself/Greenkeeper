
/*-----------------------------------------------
 * 
 *    Projekt: Arduino Greenkeeper - Test LM35
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
const int BUTTON_1 = 7;
const int BUTTON_2 = 8;
const int BUTTON_3 = 12;
const int BUTTON_4 = 13;

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
  Serial.begin(9600); //Im Setup beginnt die serielle Kommunikation, damit die Temperatur an den serial monitor übertragen wird. Über die serielle Kommunikation sendet das Board die Messwerte an den Computer. In der Arduino-Software kann man unter „Werkzeuge“ den „Seriellen Monitor“ starten um die Messwerte zu sehen.
}

void loop() 
{
  Temperatursensor_Messwert = analogRead(Temperatursensor); //Auslesen des Sensorwertes.
  Temperatur = map(Temperatursensor_Messwert, 0, 307, 0, 150); //Umwandeln des Sensorwertes mit Hilfe des "map" Befehls.
  delay(1000); // Nach jeder Messung ist je eine kleine Pause mit der Dauer „t“ in Millisekunden.
  Serial.print(Temperatur); //Nun wird der Wert „temperatur“ über die serielle Kommunikation an den PC gesendet. Durch öffnen des seriellen Monitors in der Arduino-Software kann die Temperatur abgelesen werden.
  Serial.println(" Grad Celsius"); // Im seriellen Monitor wird hinter der Temperatur die Einheit eingeblendet.
}
