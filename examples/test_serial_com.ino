void setup(){
    Serial.begin(9600);
}

void loop(){
    if (Serial.available() ){
        byte empfangen = Serial.read();
        switch (empfangen)  {
        case 48:
            Serial.println("Empfangen 0");
            break;
        case 49:
            Serial.println("Empfangen 1");
            break;
        case 50:
            Serial.println("Empfangen 2");
            break;
        case 51:
            Serial.println("Empfangen 3");
            break;
        case 52:
            Serial.println("Empfangen 4");
            break;
        case 53:
            Serial.println("Empfangen 5");
            break;
        }
    }
}
