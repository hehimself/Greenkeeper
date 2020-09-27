/* ---------------------------------------------------------*
 *                                                          *
 *    Projekt: Arduino Greenkeeper - Bewässerungssystem     *
 *                                                          *
 *    Name: Marvin Schmid                                   *
 *                                                          *
 *    Version: 1.5                                          *
 *                                                          *
 * ---------------------------------------------------------*
*/
//Bibliotheken
#include <SPI.h>
#include <Wire.h>
//Bibliotheken für den betrieb des Displays
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

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
int LED_D9_Helligkeit = 0;
int LED_D11_Helligkeit = 0;
int LED_D12_Helligkeit = 0;
int LED_D13_Helligkeit = 0;
int LED_D14_Helligkeit = 0;

//Nachtmodus
int led_nachtmodus = 0;

//Arduino Schalter
const int Button_1 = 7;
const int Button_2 = 8;
const int Button_3 = 12;
const int Button_4 = 13;

//Pumpe und Pumpautomatik
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
unsigned long LED_D14_timeMillis = 0;
unsigned long LED_Transistor_timeMillis = 0;
unsigned long previousMillis1= 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;
unsigned long previousMillis5_unbenutzt = 0;
unsigned long previousMillis6_unbenutzt = 0;
unsigned long previousMillis7_unbenutzt = 0;
unsigned long previousMillis8_unbenutzt = 0;
const long interval1 = 10000;   //10 Sekunden
const long interval2 = 1000;    //1 Sekunde
const long interval3 = 25050;   //ca. 25 Sekunden
const long interval4 = 600000;  //10 Minuten
const long interval5_unbenutzt = 1000;
const long interval6_unbenutzt = 1000;
const long interval7_unbenutzt = 1000;
const long interval8_unbenutzt = 1000;

//Display Menu
int menu = 1;

void setup() {
  digitalWrite(Pumpe, HIGH);
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
  
  //Display Konfigurationen
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();

  //Startsequenz
  Startsequenz();
  
  //Iniziere das Menu
  updateMenu();
  
  //Zeit für blinkende LED
  LED_D10_timeMillis = millis();
  
  //Dafault für Automatik
  Pumpe_Auto = 1;
  led_nachtmodus = 0;
  digitalWrite(LED_Transistor, LOW);
  digitalWrite(Pumpe, HIGH);
}
void loop() {
  SERIAL_COMMUNICATION();
  LED_Steuerung();
  BUTTON_Steuerung();
  updateMenu();
  //Tropfensensor jede Stunde lesen
  unsigned long currentMillis4 = millis();
  if (currentMillis4 - previousMillis4 >= interval4) {
    previousMillis4 = currentMillis4;
    //Tropfensensor();
  }
  //Lichtmessung alle 15 Minuten aufrufen
  unsigned long currentMillis3 = millis();
  if (currentMillis3 - previousMillis3 >= interval3) {
    previousMillis3 = currentMillis3;
    Temperaturmessung();
  }
  //Lichtmessung alle 1 Sekunde aufrufen
  unsigned long currentMillis2 = millis();
  if (currentMillis2 - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis2;
    Lichtmessung();
  }
  //Bewaesserungssystem alle 15 Minuten aufrufen
  unsigned long currentMillis1 = millis();
  if (currentMillis1 - previousMillis1 >= interval1) {
    previousMillis1= currentMillis1;
    Bewaesserungssystem();
  }
}
void Lichtmessung() {
  //Lichtmessung mit Hilfe der Photozelle wird durchgeführt
  Lichtsensor_Messwert = analogRead(Lichtsensor);
}
void Temperaturmessung() {
  //Temperaturmessung mit LM35
  Temperatursensor_Messwert = analogRead(Temperatursensor); 
  Temperatur = map(Temperatursensor_Messwert, 0, 307, 0, 150); 
}
void Bewaesserungssystem() {
  //Als erstes wird eine Bodenmessung durchgeführt
  Bodenmessung();

  //Falls der Boden zu trocken ist wird die Pumpe eingeschalten
  if (Bodensensor_Messwert >= 450) {
    if (Pumpe_Auto == 1) {
      LED_D12_Status = 1;
      LED_Steuerung();
      digitalWrite(Pumpe, LOW);
      Pumpe_counter ++;
      delay(1000);
      digitalWrite(Pumpe, HIGH);
      LED_D12_Status = 0;
    } else {
      LED_D11_Status = 1;
    }  
  } else {
    LED_D11_Status = 1;
  }
}
void Bodenmessung() {
  Bodensensor_Messwert = analogRead(Bodensensor); 
  Serial.println(Bodensensor_Messwert);
}
void Tropfensensor() {
  Wasserstand_1_Messwert = analogRead(Wasserstand_1);
  Wasserstand_2_Messwert = analogRead(Wasserstand_2);
}
void Startsequenz() {
  //Dieser Code wird nach dem Einschalten ausgeführt
  //LED Startsequenz
  digitalWrite(LED_Transistor, HIGH);
  delay(500);
  digitalWrite(LED_Transistor, LOW);
  for (int helligkeit =1; helligkeit <= 255; helligkeit = helligkeit +1){
    analogWrite(LED_D9, helligkeit);
    delay(1);
  }
  for (int helligkeit =255; helligkeit >= 0; helligkeit = helligkeit -1){
    analogWrite(LED_D9, helligkeit);
    delay(1);
  }
  for (int helligkeit =1; helligkeit <= 255; helligkeit = helligkeit +1){
    analogWrite(LED_D10, helligkeit);
    delay(1);
  }
  for (int helligkeit =255; helligkeit >= 0; helligkeit = helligkeit -1){
    analogWrite(LED_D10, helligkeit);
    delay(1);
  }
  for (int helligkeit =1; helligkeit <= 255; helligkeit = helligkeit +1){
    analogWrite(LED_D11, helligkeit);
    delay(1);
  }
  for (int helligkeit =255; helligkeit >= 0; helligkeit = helligkeit -1){
    analogWrite(LED_D11, helligkeit);
    delay(1);
  }
  for (int helligkeit =1; helligkeit <= 255; helligkeit = helligkeit +1){
    analogWrite(LED_D12, helligkeit);
    delay(1);
  }
  for (int helligkeit =255; helligkeit >= 0; helligkeit = helligkeit -1){
    analogWrite(LED_D12, helligkeit);
    delay(1);
  }
  for (int helligkeit =1; helligkeit <= 255; helligkeit = helligkeit +1){
    analogWrite(LED_D13, helligkeit);
    delay(1);
  }
  for (int helligkeit =255; helligkeit >= 0; helligkeit = helligkeit -1){
    analogWrite(LED_D13, helligkeit);
    delay(1);
  }
  for (int helligkeit =1; helligkeit <= 255; helligkeit = helligkeit +1){
    analogWrite(LED_D14, helligkeit);
    delay(1);
  }
  for (int helligkeit =255; helligkeit >= 0; helligkeit = helligkeit -1){
    analogWrite(LED_D14, helligkeit);
    delay(1);
  }
  for (int helligkeit =1; helligkeit <= 255; helligkeit = helligkeit +1){
    analogWrite(LED_D14, helligkeit);
    analogWrite(LED_D13, helligkeit);
    analogWrite(LED_D12, helligkeit);
    analogWrite(LED_D11, helligkeit);
    analogWrite(LED_D10, helligkeit);
    analogWrite(LED_D9, helligkeit);
    delay(3);
  }
  for (int helligkeit =255; helligkeit >= 0; helligkeit = helligkeit -1){
    analogWrite(LED_D14, helligkeit);
    analogWrite(LED_D13, helligkeit);
    analogWrite(LED_D12, helligkeit);
    analogWrite(LED_D11, helligkeit);
    analogWrite(LED_D10, helligkeit);
    analogWrite(LED_D9, helligkeit);
    delay(3);
  }
  for (int i = 1; i <= 2; i = i+1) {
    digitalWrite(LED_D9, HIGH);
    delay(50);
    digitalWrite(LED_D10, HIGH);
    delay(50);
    digitalWrite(LED_D11, HIGH);
    delay(50);
    digitalWrite(LED_D12, HIGH);
    delay(50);
    digitalWrite(LED_D13, HIGH);
    delay(50);
    digitalWrite(LED_D14, HIGH);
    delay(200);
    digitalWrite(LED_D9, LOW);
    delay(50);
    digitalWrite(LED_D10, LOW);
    delay(50);
    digitalWrite(LED_D11, LOW);
    delay(50);
    digitalWrite(LED_D12, LOW);
    delay(50);
    digitalWrite(LED_D13, LOW);
    delay(50);
    digitalWrite(LED_D14, LOW);
    delay(200);
    digitalWrite(LED_D14, HIGH);
    delay(50);
    digitalWrite(LED_D13, HIGH);
    delay(50);
    digitalWrite(LED_D12, HIGH);
    delay(50);
    digitalWrite(LED_D11, HIGH);
    delay(50);
    digitalWrite(LED_D10, HIGH);
    delay(50);
    digitalWrite(LED_D9, HIGH);
    delay(200);
    digitalWrite(LED_D14, LOW);
    delay(50);
    digitalWrite(LED_D13, LOW);
    delay(50);
    digitalWrite(LED_D12, LOW);
    delay(50);
    digitalWrite(LED_D11, LOW);
    delay(50);
    digitalWrite(LED_D10, LOW);
    delay(50);
    digitalWrite(LED_D9, LOW);
    delay(200);
  }
  for (int i = 0; i <= 2; i = i+1) {
    delay(100);
    for (int helligkeit =1; helligkeit <= 255; helligkeit = helligkeit +1){
      analogWrite(LED_D14, helligkeit);
      analogWrite(LED_D13, helligkeit);
      analogWrite(LED_D12, helligkeit);
      analogWrite(LED_D11, helligkeit);
      analogWrite(LED_D10, helligkeit);
      analogWrite(LED_D9, helligkeit);
      delay(1);
    }
    for (int helligkeit =255; helligkeit >= 0; helligkeit = helligkeit -1){
      analogWrite(LED_D14, helligkeit);
      analogWrite(LED_D13, helligkeit);
      analogWrite(LED_D12, helligkeit);
      analogWrite(LED_D11, helligkeit);
      analogWrite(LED_D10, helligkeit);
      analogWrite(LED_D9, helligkeit);
      delay(1);
    }
  }
  menu = 10;
  //POWER LED an
  LED_D9_Status = 1;
}
void BUTTON_Steuerung() {
  if (digitalRead(Button_1) == HIGH){
    menu = 1;
    updateMenu();
    delay(500);
  }
  if (digitalRead(Button_2) == HIGH){
    delay(500);
  }
  if (digitalRead(Button_3) == HIGH){
    menu++;
    updateMenu();
    delay(500);
  }
  if (digitalRead(Button_4) == HIGH){
    excecuteAction();
    updateMenu();
    delay(500);
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
    display.println("  Transistor");
    display.setCursor(0,24);
    display.println("  Wasserstand");
    display.display();
    break;
  case 2:
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("  Pumpe");
    display.setCursor(0,8);
    display.println("> LEDs");
    display.setCursor(0,16);
    display.println("  Transistor");
    display.setCursor(0,24);
    display.println("  Wasserstand");
    display.display();
    break;
  case 3:
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("  Pumpe");
    display.setCursor(0,8);
    display.println("  LEDs");
    display.setCursor(0,16);
    display.println("> Transistor");
    display.setCursor(0,24);
    display.println("  Wasserstand");
    display.display();
    break;
  case 4:
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("  Pumpe");
    display.setCursor(0,8);
    display.println("  LEDs");
    display.setCursor(0,16);
    display.println("  Transistor");
    display.setCursor(0,24);
    display.println("> Wasserstand");
    display.display();
    break;
  case 5:
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(">  Display");
    display.setCursor(0,8);
    display.println("   Dashboard");
    display.setCursor(0,16);
    display.println("----------------");
    display.display();
    break;
  case 6:
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("   Display");
    display.setCursor(0,8);
    display.println(">  Dashboard");
    display.setCursor(0,16);
    display.println("----------------");
    display.display();
    break;
  case 7:
    menu = 1;
    break;
  case 8:
    display.clearDisplay();
    display.display();
    break;
  case 10:
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print("Licht: ");
    display.print(Lichtsensor_Messwert);
    display.setCursor(90,0);
    display.print("T: ");
    display.println(Temperatur);
    display.setCursor(0,8);
    display.println("---------------------");
    display.setTextSize(2);
    display.setCursor(0,16);
    display.print("Boden: ");
    display.println(Bodensensor_Messwert);
    display.display();
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
    case 6:
      action6();
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
    display.setCursor(0,8);
    display.println("ausgeschalten");
    display.display();
    Pumpe_Auto = 0;
    updateMenu();
  } else {
    if (Pumpe_Auto == 0) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Pumpautomatik wird");
      display.setCursor(0,8);
      display.println("angeschalten");
      display.display();
      Pumpe_Auto = 1;
      updateMenu();
    }
  }
  delay(3000);
}
void action2() {
  if (led_nachtmodus == 0) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Nachtmodus wird");
    display.setCursor(0,8);
    display.println("angeschalten");
    display.display();
    led_nachtmodus = 1;
    menu = 10;
    updateMenu();
  } else {
    if (led_nachtmodus == 1) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Nachtmodus wird");
      display.setCursor(0,8);
      display.println("ausgeschalten");
      display.display();
      led_nachtmodus = 0;
      menu = 10;
      updateMenu();
    }
  }
  delay(3000);
}
void action3() {
  digitalWrite(LED_Transistor, !digitalRead(LED_Transistor));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Transistor wird");
  display.setCursor(0,8);
  display.println("an/ausgeschalten");
  display.display();
  delay(3000);
  menu = 10;
  updateMenu();
}
void action4() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Wasserstand 1:");
  display.print(Wasserstand_1_Messwert);
  display.setCursor(0,8);
  display.print("Wasserstand 2:");
  display.print(Wasserstand_2_Messwert);
  display.display();
  delay(3000);
  menu = 10;
  updateMenu();
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
  menu = 8;
  updateMenu();
}
void action6() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("_________");
  display.setCursor(0,16);
  display.print("Dashboard");
  display.display();
  delay(1000);
  menu = 10;
  updateMenu();
}
void LED_Steuerung() {
  //Check ob der Nachtmodus an oder ausgeschalten ist
  if (led_nachtmodus == 0) {
    //Check LED D9
    if (LED_D9_Status == 1) {
      LED_D9_Helligkeit = map(Lichtsensor_Messwert, 0, 1023, 1, 5);
      LED_D9_Helligkeit = map(LED_D9_Helligkeit, 1, 5, 5, 220);
      analogWrite(LED_D9, LED_D9_Helligkeit);
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
      LED_D11_Helligkeit = Lichtsensor_Messwert;
      if (LED_D11_Helligkeit <= 200)  {
        analogWrite(LED_D11, 100);
      } 
      else {
        digitalWrite(LED_D11, HIGH);
      }
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
      LED_D13_Helligkeit = map(Lichtsensor_Messwert, 0, 1023, 1, 5);
      LED_D13_Helligkeit = map(LED_D13_Helligkeit, 1, 5, 5, 255);
      analogWrite(LED_D13, LED_D13_Helligkeit);
    } else {
      digitalWrite(LED_D13, LOW);
    }
    //Check LED_D14
    if (LED_D14_Status == 1) {
      if ((millis() - LED_D14_timeMillis) >= 500) {
      digitalWrite(LED_D14, !digitalRead(LED_D14));
      LED_D14_timeMillis = millis();
    }
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
void SERIAL_COMMUNICATION() {
  //Serielle Kommunation mit dem Raspberry Pi über eine USB Verbindung
  //so können Befehle direkt an den Greenkeeper gesendet werden
  if (Serial.available() ){
    byte empfangen = Serial.read();
    switch (empfangen)  {
      case 48:      //ASCII = 0
        action1();  //Pumpautomatik wird aus- oder eingeschalten
        break;
      case 49:      //ASCII = 1
        action2();  //Nachtmodus wird aus- oder eingeschalten
        break;
      case 50:      //ASCII = 2
        action3();  //Transistor wird aus- oder eingeschalten
        break;
      case 51:      //ASCII = 3
        action5();  //Display wird ausgeschalten
        break;
      case 52:      //ASCII = 4
        LED_D10_Status = 1;
        LED_Steuerung();
        break;
      case 53:      //ASCII = 5
        LED_D10_Status = 0;
        LED_Steuerung();
        break;
      case 54:      //ASCII = 6
        LED_D14_Status = 1;
        LED_Steuerung();
        break;
      case 55:      //ASCII = 7
        LED_D14_Status = 0;
        LED_Steuerung();
        break;
      case 56:      //ASCII = 8
        delay(1);   //NOCH OHNE FUNKTION
        break;
      case 57:      //ASCII = 9
        delay(1);   //NOCH OHNE FUNKTION
        break;
      }
    }
}
