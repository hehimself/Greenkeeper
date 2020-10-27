# Greenkeeper
[![GPLv3 license](https://img.shields.io/badge/License-GPLv3-blue.svg)](http://perso.crans.org/besson/LICENSE.html)
[![Generic badge](https://img.shields.io/badge/build-sucess-sucess.svg)](https://shields.io/)
[![GitHub pull-requests](https://img.shields.io/github/issues-pr/Naereen/StrapDown.js.svg)](https://GitHub.com/Naereen/StrapDown.js/pull/)
[![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://GitHub.com/Naereen/StrapDown.js/graphs/commit-activity)

![Platine](/images/Greenkeeper.png)
Der Arduino Greenkeeper ist ein vollautomatisiertes Bewässerungssystem für eine Zimmerpflanze.
Zu Beginn habe ich eine Platine mithilfe von KiCAD erstellt. Auf der Platine können alle wichtigen Teile direkt verlötet werden. Die SMD LEDs helfen, den Status des Bewässerungssystems zu erkennen. Auf dem OLED Display werden die Messwerte wie Bodenfeuchtigkeit, Temperatur, Lichtstärke usw dargestellt. Zudem gibt es ein Menü, welches sich durch die Buttons steuern lässt.
(Schaltplan unter: schema.pdf)

## Funktionsweise
### 1. Die Bewässerung
Die Bewässerungsanlage ist recht simple aufgebaut. Es wird mithilfe des Sensor die Bodenfeuchtigkeit gemessen. Wenn der Messwert einen gewissen Wert überschreitet wird die Pumpe mithilfe des Relais für eine Sekunde aktiviert. Alle 10 Sekunden wird die Bodenfeuchtigkeit gemessen. Somit wird sichergestellt, das die Pflanze immer genügend Wasser zur Verfügung hat.

```C++
void Bewaesserungssystem() {
  //Als erstes wird eine Bodenmessung durchgeführt
  Bodenmessung();
//Falls der Boden zu trocken ist wird die Pumpe eingeschalten
  if (Bodensensor_Messwert >= 450) {        //Dieser Wert ist natürlich abhängig von Pflanze und Sensor
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
```

### 2. Die Status LEDs
Die Status LEDs die am meisten angeschalten sind werden, je nach Helligkeit automatisch gedimmt. Diese sind am Arduino an den PWM (Pulse Width Modulation) fähigen Pins angeschlossen.

POWER Diese LED zeigt, ob die Platine mit Strom versorgt wird
STATUS (gelb) Diese blinkt wenn etwas mit der Bewässerung nicht stimmt
STATUS (grün) Diese LED leuchtet wenn die Pflanze genügend Wasser hat
PUMPE Diese LED leuchtet wenn die Pumpe läuft
W-Tank Diese LED leuchtet, wenn der Wassertank leer ist.
FEHLER (noch ohne funktion)

### 3. Die Tasten
Taster von links nach rechts:

Menü Button
"Down" Button
"UP" Button
"ENTER" Button

### 4. Das Display
Auf dem Dashboard wird der Messwert der Bodenmessung, die Temperatur und der Messwert des Lichtsensor dargestellt. Wenn man zum Menü kommen will muss man nur den "Menü" Button betätigen (1. Button von links). Um wieder zurück zum Dashboard zu kommen wählt man im Menü den Punk "Dashboard" aus.

Das Menü hat folgende weitere Funktionen:

PUMP Automatik Hierbei lässt sich die Bewässerung ausschalten um sicher zu gehen das die Pumpe nicht läuft, obwohl der Sensor beispielsweise aus der Pflanze genommen wurde.
Nachtmodus Der Nachtmodus lässt sich über das Menü aktivieren/deaktivieren. Während der Nachtmodus aktiviert ist gehen alle Status LEDs aus.
Display Mit diesem Menü Punkt lässt sich das Display ausschalten, sodass alles Dunkel ist. Wenn man das Display wieder anschalten möchte muss man einfach den "Menü" Button (Button_S1) drücken.
Transistor Mithilfe dieser Funktion, lassen sich die Grünen LEDs unten manuell anschalten. Diese sind jedoch zurzeit nur für ein schönes aussehen und noch komplett ohne eine sinnvolle Funktion

## Die Platine
![Platine](/images/Platine_final.PNG)

## Übersicht zu Widerständen und Leds
![Platine](/images/übersicht.PNG)

# Bauanleitung
Die Gesamte Anleitung gibts hier: [hackster.io](https://www.hackster.io/ms2002maerz14/arduino-greenkeeper-687363)
WARNUNG: Man sollte bereits Erfahrung im löten von SMD Komponenten der Größe 0805 besitzen, da sonst die Komponenten oder die Platine beschädigt werden können.

### Platine löten

Ich rate aus eigener Erfahrung mehrere Platinen und mehr Komponenten als angegeben sich zu kaufen, da es sehr schnell gehen kann eine SMD Komponente zu zerstören. Am Besten nimmt man sich die Übersicht zu Widerständen uns LEDs zur Hilfe während des löten, um zu wissen, welches Bauteil, wo gelötet werden muss.

### Platine testen

![Platine](/images/Bauanleitung_1.jpg)

Zum testen aller Funktionen und zum Einstellen der Parameter der Sensoren habe ich die Platine per USB mit dem Computer verbunden und nacheinander alle Sensoren, Schalter und Display getestet.

### Inbetriebnahme

Am Besten befestigt man den Schlauch mit ein bisschen Tesafilm an dem Topf, damit dieser während der Bewässerung nicht verrutscht. Zudem ist es nun Zeit den Sensor für die Bodenfeuchtigkeit in die Erde zu stecken.

![Platine](/images/Bauanleitung_2.jpg)

Nun ist es Zeit sich um den Wassertank zu kümmer. Hierbei empfehle ich die Pumpe am Boden des Behälters oder des Tanks festzukleben. Das Relais habe ich in meinem Fall einfach an die Seite des Wasserbehälter geklebt (siehe Abbildung unten)

![Platine](/images/Bauanleitung_3.jpg)

Die Platine habe ich mithilfe von Platinen Abstandshalter an der Wand befestigt und im Anschluss alle Anschlüsse verkabelt. Die Stromversorgung erfolgt über ein Netzteil (9V). Eine Versorgung über USB ist zwar möglich jedoch wenn alle LEDs angeschalten sind und die Pumpe läuft, ist man an der Spitze der Leistung des Arduino. Das Bewässerungssystem ist nun einsatzbereit. Eventuell muss man im Code den Wert, ab wann die Pumpe pumpt noch für seine Pflanze anpassen.


![Platine](/images/Bauanleitung_4.jpg)

Fertig...
