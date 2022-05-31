const int triggerPin = 2;
const int echoPin    = 3;
const int buzzer     = 13;
const int led1       = 7;
const int led2       = 8;

int distance;

#define  C     2100
#define  D     1870 
#define  E     1670
#define  f     1580    
#define  G     1400 
#define  R     0

int DEBUG = 1;

int melody[] = {E, E, E,R,
E, E, E,R,
E, G, C, D, E, R,
f, f, f,f, f, E, E,E, E, D ,D,E, D, R, G ,R,
E, E, E,R,
E, E, E,R,
E, G, C, D, E, R,
f, f, f,f, f, E, E, E,  G,G, f, D, C,R };


int MAX_COUNT  = sizeof(melody) / 2; 
long tempo     = 9000;
int pause      = 600;
int rest_count = 100; 
int tone_      = 0;
int beat       = 0;
long duration  = 0;


void setup(){
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(buzzer, OUTPUT);

    Serial.begin(9600);
}



void playTone(){
    long elapsed_time = 0;
    if (tone_ > 0) { 

        while (elapsed_time < duration) {
            digitalWrite(buzzer,HIGH);
            delayMicroseconds(tone_ / 2);

            digitalWrite(buzzer, LOW);
            delayMicroseconds(tone_ / 2);

            elapsed_time += (tone_);
        }
    }

    else{ 
        for (int j = 0; j < rest_count; j++) {
            delayMicroseconds(duration); 
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
        for (int i=0; i<MAX_COUNT; i++) {
            if(i % 2 == 0){
                digitalWrite(led1, HIGH);
                digitalWrite(led2, LOW);
            }
            else{
                digitalWrite(led2, HIGH);
                digitalWrite(led1, LOW);   
            }
            tone_ = melody[i];
            beat = 50;

            duration = beat * tempo; 

            playTone();

            delayMicroseconds(pause);
        }
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
    }
    else if(distance <= 12) {
        digitalWrite(led2, HIGH);
        tone(buzzer, 480, 100);
        delay(100);
        digitalWrite(led2, LOW);
    }
    else if(distance <= 22){
        digitalWrite(led1, HIGH);
        tone(buzzer, 512, 100);
        delay(100);   
        digitalWrite(led1, LOW);
    }
}
