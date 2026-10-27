const byte leds[]={2,3,4,5,6,7,8};
const byte buttons[]={10,11,12,13,A0};
bool pothole=false,closure=false,peak=false,ambulance=false;
bool prev[5]={HIGH,HIGH,HIGH,HIGH,HIGH};
unsigned long lastPress[5]={0},lastReport=0;
void setup(){Serial.begin(9600);for(byte p:leds)pinMode(p,OUTPUT);pinMode(9,OUTPUT);for(byte p:buttons)pinMode(p,INPUT_PULLUP);}
void loop(){
 for(int i=0;i<5;i++){bool current=digitalRead(buttons[i]);if(prev[i]==HIGH && current==LOW && millis()-lastPress[i]>180){lastPress[i]=millis();switch(i){case 0:pothole=!pothole;break;case 1:closure=!closure;break;case 2:ambulance=!ambulance;break;case 3:peak=!peak;break;case 4:pothole=closure=peak=ambulance=false;break;}}prev[i]=current;}
 int score=(peak?2:0)+(pothole?2:0)+(closure?3:0);
 const char* risk=score>=2?"HIGH":score==1?"MEDIUM":"LOW";
 for(byte p:leds)digitalWrite(p,LOW);noTone(9);
 if(ambulance){digitalWrite(5,HIGH);digitalWrite(8,HIGH);tone(9,1200);}else if(score>=2){digitalWrite(2,HIGH);digitalWrite(7,HIGH);}else if(score==1){digitalWrite(3,HIGH);digitalWrite(7,HIGH);}else{digitalWrite(4,HIGH);digitalWrite(7,HIGH);}
 if(millis()-lastReport>=500){lastReport=millis();Serial.print("RISK=");Serial.print(risk);Serial.print(",SCORE=");Serial.print(score);Serial.print(",POTHOLE=");Serial.print(pothole?"YES":"NO");Serial.print(",CLOSURE=");Serial.print(closure?"YES":"NO");Serial.print(",PEAK=");Serial.print(peak?"YES":"NO");Serial.print(",AMBULANCE=");Serial.println(ambulance?"ACTIVE":"OFF");}
 delay(20);
}
