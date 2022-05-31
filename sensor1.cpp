const int triggerPin = 2;
const int echoPin    = 3;
const int buzzer     = 13;
const int led1       = 7;
const int led2       = 8;

int distance;

void setup(){
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(buzzer, OUTPUT);

    Serial.begin(9600);
}


void playTone(int tone, int duration) {

    for (long i=0; i<duration*1000L; i+=tone*2) {

        digitalWrite(buzzer, HIGH);
        delayMicroseconds(tone);
        digitalWrite(buzzer, LOW);
        delayMicroseconds(tone);

    }

}

void playNote(char note, int duration) {

    char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',           
                   'c', 'd', 'e', 'f', 'g', 'a', 'b',
                   'x', 'y' };

    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,
                   956,  834,  765,  593,  468,  346,  224,
                   655 , 715 };

    int SPEE = 5;
    for (int i=0; i<16; i++) {

        if (names[i] == note) {
            int newduration = duration/SPEE;
            playTone(tones[i], newduration);
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
        int length     = 28; 

        char notes[]   = "GGAGcB GGAGdc GGxecBA yyecdc";
        int beats[]    = { 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8,8, 16, 1, 2,2,8,8,8,8,16, 1,2,2,8,8,8,16 };
        int tempo      = 150;

        for (int i=0; i<length; i++){

            if(i % 2 == 0){
                digitalWrite(led2, HIGH);
                digitalWrite(led1, LOW);    
            }
            else{
                digitalWrite(led1, HIGH);
                digitalWrite(led2, LOW);       
            }
            

            if(notes[i] == ' '){
                delay(beats[i] * tempo); 
            } 
            else{
                playNote(notes[i], beats[i] * tempo);
            }
            delay(tempo);
        }

        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
    }
    else if(distance <= 12) {
        digitalWrite(led2, HIGH);
        tone(buzzer, 384, 100);
        delay(100);
        digitalWrite(led2, LOW);
    }
    else if(distance <= 22){
        digitalWrite(led1, HIGH);
        tone(buzzer, 432, 100);
        delay(100);   
        digitalWrite(led1, LOW);
    }
}
