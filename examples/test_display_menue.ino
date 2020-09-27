/*-----------------------------------------------
 * 
 *    Projekt: Arduino Greenkeeper - Bewässerungssystem
 * 
 *    Name: Marvin Schmid
 * 
 *    Version: 0.2
 * 
 * -----------------------------------------------
*/
//Bibliotheken
#include <SPI.h>
#include <Wire.h>
//Bibliotheken für den betrieb des Displays
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

const unsigned char Greenkeeper_IMAGE [] = {
0x80, 0x00, 0x20, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40, 0x02, 0x22, 0x22, 0x20, 0x02, 0x22, 0x22, 0x22, 0x00,
0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x42, 0x02, 0x02, 0x22, 0x42, 0x00, 0x00, 0x02, 0x02, 0x00,
0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x02, 0x02, 0x02, 0x22, 0x42, 0x00, 0x00, 0x02, 0x02, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0x00, 0x02, 0x22, 0x02, 0x00, 0x00, 0x02, 0x02, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x02, 0x02, 0x02, 0x22, 0x22, 0x02, 0x02, 0x22, 0x02, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x01, 0x02, 0x22, 0x00, 0x01, 0x02, 0x41, 0x02, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//Arduino LEDs
const int LED_D9 = 3;
const int LED_D10 = 9;
const int LED_D11 = 5;
const int LED_D12 = 6;
const int LED_D13 = 10;
const int LED_D14 = 11;
const int LED_Transistor = 4;
int LED_D9_Status = 0;
int LED_D10_Status = 0;
int LED_D11_Status = 0;
int LED_D12_Status = 0;
int LED_D13_Status = 0;
int LED_D14_Status = 0;
int led_nachtmodus = 0;

//Arduino Schalter
const int Button_1 = 7;
const int Button_2 = 8;
const int Button_3 = 12;
const int Button_4 = 13;

//Arduino Aktoren
const int Pumpe = 2;
int Pumpe_Auto = 0;
int Pumpe_counter = 0;

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

//Wichtig statt Delay
unsigned long LED_D10_timeMillis = 0;
unsigned long lastMillis2 = 0;
unsigned long previousMillis1= 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;
const long interval1 = 900000; //15 Minuten
const long interval2 = 900000;
const long interval3 = 900000;
const long interval4 = 3600000;

//Display Menu
int menu = 1;

void setup() {
  //Kommunikation
  Serial.begin(9600);

  //Sensoren und Aktoren
  pinMode(Pumpe, OUTPUT);
  pinMode(Button_1, INPUT);
  pinMode(Button_2, INPUT);
  pinMode(Button_3, INPUT);
  pinMode(Button_4, INPUT);
  pinMode(LED_D9, OUTPUT);
  pinMode(LED_D10, OUTPUT);
  pinMode(LED_D11, OUTPUT);
  pinMode(LED_D12, OUTPUT);
  pinMode(LED_D13, OUTPUT);
  pinMode(LED_D14, OUTPUT);
  pinMode(LED_Transistor, OUTPUT);
  
  //Startsequenz
  //Startsequenz();
  
  //Display Konfigurationen
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.drawBitmap(0, 0, Greenkeeper_IMAGE, 128, 32, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(3000);
  
  //Iniziere das Menu
  updateMenu();
  
  //Zeit für blinkende LED
  LED_D10_timeMillis = millis();
  lastMillis2 = millis();
  
  //Dafault für Automatik
  Pumpe_Auto = 1;
  led_nachtmodus = 0;
}
void loop() {
  updateMenu();
}
void Lichtmessung() {
  Lichtsensor_Messwert = analogRead(Lichtsensor);
  Serial.print("Sensorwert = " );
  Serial.println(Lichtsensor_Messwert);
}
void Temperaturmessung() {
  Temperatursensor_Messwert = analogRead(Temperatursensor); 
  Temperatur = map(Temperatursensor_Messwert, 0, 307, 0, 150); 
  Serial.print(Temperatur); 
  Serial.println(" Grad Celsius");
}
void Bewaesserungssystem() {
  //Als erstes wird eine Bodenmessung durchgeführt
  Bodenmessung();
  //Falls der Boden zu trocken ist wird die Pumpe eingeschalten
  if (Bodensensor_Messwert < 50) {
    if (Pumpe_Auto == 1) {
      digitalWrite(Pumpe, HIGH);
      Pumpe_counter ++;
      delay(1000);
      digitalWrite(Pumpe, LOW);
    } else {
      Serial.print("Boden ist Troken Pumpautomatik ist ausgeschalten");
    }  
  } else {
    Serial.print("Boden ist nass genug Sensorwert bei: "+ Bodensensor_Messwert);
  }
}
void Bodenmessung() {
  Bodensensor_Messwert = analogRead(Bodensensor); 
  Serial.print("Feuchtigkeits-Messwert:");
  Serial.println(Bodensensor_Messwert);
  delay(1000);
}
void Tropfensensor() {
  Wasserstand_1_Messwert = analogRead(Wasserstand_1);
  Serial.print("Feuchtigkeits-Messwert Wasserstand 1:");
  Serial.println(Wasserstand_1_Messwert);
  delay(1000);
  Wasserstand_2_Messwert = analogRead(Wasserstand_2);
  Serial.print("Feuchtigkeits-Messwert Wasserstand 2:");
  Serial.println(Wasserstand_2_Messwert);
  delay(1000);
}
void Startsequenz() {
  //Dieser Code wird nach dem Einschalten ausgeführt
  //LED Startsequenz
  Serial.println("|--------------------------------------------|");
  Serial.println("|     Programm: Greenkeeper                  |");
  Serial.println("|                                            |");
  Serial.println("|     Name: Marvin Schmid                    |");
  Serial.println("|                                            |");
  Serial.println("|--------------------------------------------|");
  Serial.print("\t");
  Serial.println("...wird gestartet.");
  Serial.print("\t");
  digitalWrite(LED_Transistor, HIGH);
  delay(2000);
  digitalWrite(LED_Transistor, LOW);
  delay(500);
  digitalWrite(LED_D9, HIGH);
  digitalWrite(LED_D10, HIGH);
  digitalWrite(LED_D11, HIGH);
  digitalWrite(LED_D12, HIGH);
  digitalWrite(LED_D13, HIGH);
  digitalWrite(LED_D14, HIGH);
  delay(1000);
  digitalWrite(LED_D9, LOW);
  digitalWrite(LED_D10, LOW);
  digitalWrite(LED_D11, LOW);
  digitalWrite(LED_D12, LOW);
  digitalWrite(LED_D13, LOW);
  digitalWrite(LED_D14, LOW);
}
void BUTTON_Steuerung() {
  if (!digitalRead(Button_1)){
    updateMenu();
    delay(100);
    while (!digitalRead(Button_1));
  }
  if (!digitalRead(Button_2)){
    menu++;
    updateMenu();
    delay(100);
    while (!digitalRead(Button_2));
  }
  if (!digitalRead(Button_3)){
    menu--;
    updateMenu();
    delay(100);
    while(!digitalRead(Button_3));
  }
  if (!digitalRead(Button_4)){
    excecuteAction();
    updateMenu();
    delay(100);
    while (!digitalRead(Button_4));
  }
}
void updateMenu() {
  switch (menu)
  {
  case 0:
    menu = 1;
    break;
  case 1:
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("> Pumpe");
    display.setCursor(0,8);
    display.println("  LEDs");
    display.setCursor(0,16);
    display.println("  Temperatur");
    display.setCursor(0,24);
    display.println("  Lichtsensor");
    display.display();
    break;
  case 2:
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("  Pumpe");
    display.setCursor(1,0);
    display.println("> LEDs");
    display.display();
    break;
  case 3:
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("> Temperatur");
    display.setCursor(1,0);
    display.println("  Lichtsensor");
    display.display();
    break;
  case 4:
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("  Temperatur");
    display.setCursor(1,0);
    display.println("> Lichtsensor");
    display.display();
    break;
  case 5:
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(">  Display");
    display.setCursor(1,0);
    display.println("-------------");
    display.display();
  case 6:
    menu = 5;
    break;
  }
}
void excecuteAction() {
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
    case 5:
      action5();
      break;
  }
}
void action1() {
  if (Pumpe_Auto == 1) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Pumpautomatik wird");
    display.setCursor(1,0);
    display.println("ausgeschalten");
    display.display();
    Pumpe_Auto = 0;
  } else {
    if (Pumpe_Auto == 0) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Pumpautomatik wird");
      display.setCursor(1,0);
      display.println("angeschalten");
      display.display();
      Pumpe_Auto = 1;
    }
  }
}
void action2() {
  if (led_nachtmodus == 0) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Nachtmodus wird");
    display.setCursor(1,0);
    display.println("angeschalten");
    display.display();
    led_nachtmodus = 1;
  } else {
    if (led_nachtmodus == 1) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Nachtmodus wird");
      display.setCursor(1,0);
      display.println("ausgeschalten");
      display.display();
      led_nachtmodus = 0;
    }
  }
}
void action3() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Temperatur: ");
  display.println(Temperatur);
  display.display();
  delay(3000);
}
void action4() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Lichtsensor: ");
  display.println(Lichtsensor_Messwert);
  display.display();
  delay(3000);
}
void action5() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Display aus");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
}
void LED_Steuerung() {
  if (led_nachtmodus == 0) {
    //Check LED D9
    if (LED_D9_Status == 1) {
      digitalWrite(LED_D9, HIGH);
    } else {
      digitalWrite(LED_D9, LOW);
    }
    //Check LED_D10
    if (LED_D10_Status == 1) {
      if ((millis() - LED_D10_timeMillis) >= 500) {
      digitalWrite(LED_D10, !digitalRead(LED_D10));
      LED_D10_timeMillis = millis();
    }
    } else {
      digitalWrite(LED_D10, LOW);
    }
    //Check LED_D11
    if (LED_D11_Status == 1) {
      digitalWrite(LED_D11, HIGH);
    } else {
      digitalWrite(LED_D11, LOW);
    }
    //Check LED_D12
    if (LED_D12_Status == 1) {
      digitalWrite(LED_D12, HIGH);
    } else {
      digitalWrite(LED_D12, LOW);
    }
    //Check LED_D13
    if (LED_D13_Status == 1) {
      digitalWrite(LED_D13, HIGH);
    } else {
      digitalWrite(LED_D13, LOW);
    }
    //Check LED_D14
    if (LED_D14_Status == 1) {
      digitalWrite(LED_D14, HIGH);
    } else {
      digitalWrite(LED_D14, LOW);
    }
  } else {
    digitalWrite(LED_D9, LOW);
    digitalWrite(LED_D10, LOW);
    digitalWrite(LED_D11, LOW);
    digitalWrite(LED_D12, LOW);
    digitalWrite(LED_D13, LOW);
    digitalWrite(LED_D14, LOW);
    digitalWrite(LED_Transistor, LOW);
  }
}
