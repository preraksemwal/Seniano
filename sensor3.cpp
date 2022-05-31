const int triggerPin = 2;
const int echoPin    = 3;
const int buzzer     = 13;
const int led1       = 7;
const int led2       = 8;

int distance;


int length = 15; 

char notes[] = "ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

void setup(){
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(buzzer, OUTPUT);

    Serial.begin(9600);
}



void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(buzzer, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzer, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}


void loop(){

    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);  
    digitalWrite(triggerPin, LOW);
    distance = pulseIn(echoPin, HIGH) * 0.034 / 2;

    if(distance <= 2){
        for (int i = 0; i < length; i++) {
            if(i % 2 == 0){
                digitalWrite(led1, HIGH);
                digitalWrite(led2, LOW);
            }
            else{
                digitalWrite(led2, HIGH);
                digitalWrite(led1, LOW);
            }
            if (notes[i] == ' ') {
              delay(beats[i] * tempo); // rest
            } 
            else {
              playNote(notes[i], beats[i] * tempo);
            }
            delay(tempo / 2); 
            digitalWrite(led1, LOW);
            digitalWrite(led2, LOW);
        }
    }
    else if(distance <= 12) {
        digitalWrite(led2, HIGH);
        tone(buzzer, 576, 100);
        delay(100);
        digitalWrite(led2, LOW);
    }
    else if(distance <= 22){
        digitalWrite(led1, HIGH);
        tone(buzzer, 640, 100);
        delay(100);   
        digitalWrite(led1, LOW);
    }
}
