# Greenkeeper
Der Arduino Greenkeeper ist ein vollautomatisiertes Bewässerungssystem für eine Zimmerpflanze.
Zu Beginn habe ich eine Platine mithilfe von KiCAD erstellt. Auf der Platine können alle wichtigen Teile direkt verlötet werden. Die SMD LEDs helfen, den Status des Bewässerungssystems zu erkennen. Auf dem OLED Display werden die Messwerte wie Bodenfeuchtigkeit, Temperatur, Lichtstärke usw dargestellt. Zudem gibt es ein Menü, welches sich durch die Buttons steuern lässt.

## Funktionsweise
### 1. Die Bewässerung
Die Bewässerungsanlage ist recht simple aufgebaut. Es wird mithilfe des Sensor die Bodenfeuchtigkeit gemessen. Wenn der Messwert einen gewissen Wert überschreitet wird die Pumpe mithilfe des Relais für eine Sekunde aktiviert. Alle 10 Sekunden wird die Bodenfeuchtigkeit gemessen. Somit wird sichergestellt, das die Pflanze immer genügend Wasser zur Verfügung hat.

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
