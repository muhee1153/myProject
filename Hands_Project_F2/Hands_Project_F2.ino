#include <SoftwareSerial.h>

#define Trig 2
#define ECHO 3
#define LEFT_A1 9 //왼쪽 바퀴1
#define LEFT_B1 6 //왼쪽 바퀴2
#define RIGHT_A2 11 //오른쪽 바퀴1
#define RIGHT_B2 10 //오른쪽 바퀴2
#define BLUE_TX  4//블루투스 TX
#define BLUE_RX  5//블루투스 RX
SoftwareSerial BTSerial(BLUE_TX, BLUE_RX);  
char va;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello!");
  BTSerial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LEFT_A1, OUTPUT);
  pinMode(RIGHT_A2, OUTPUT);
  pinMode(LEFT_B1, OUTPUT);
  pinMode(RIGHT_B2, OUTPUT);  
  Serial.println("Arduino Bluetooth Car is ready to start");
}

void loop() {
  
  long duration, distance;
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duration = pulseIn (ECHO, HIGH);
  distance = duration * 17 / 1000;


  if(distance<10){
    digitalWrite(LEFT_A1, LOW);
    digitalWrite(LEFT_B1, HIGH);
    digitalWrite(RIGHT_A2, LOW);
    digitalWrite(RIGHT_B2, HIGH);
    Serial.println(distance);
    delay(500);
    digitalWrite(LEFT_A1, LOW);
    digitalWrite(LEFT_B1, LOW);
    digitalWrite(RIGHT_A2, LOW);
    digitalWrite(RIGHT_B2, LOW);
    delay(100);
  }
  else if(distance>=10){
     while(BTSerial.available()) {
     va = BTSerial.read();

     if(va == 'l'){            //좌회전(강)
       Serial.println("left");
       digitalWrite(LEFT_A1, LOW);
       digitalWrite(LEFT_B1, HIGH);
       digitalWrite(RIGHT_A2, HIGH);
       digitalWrite(RIGHT_B2, LOW);
     }
     else if(va == 'r'){      //우회전(강)
       Serial.println("right");
       digitalWrite(LEFT_A1, HIGH);
       digitalWrite(LEFT_B1, LOW);
       digitalWrite(RIGHT_A2, LOW);
       digitalWrite(RIGHT_B2, HIGH);

     }else if(va == 'f'){      //전진
       Serial.println("forward");
       digitalWrite(LEFT_A1, HIGH);
       digitalWrite(LEFT_B1, LOW);
       digitalWrite(RIGHT_A2, HIGH);
       digitalWrite(RIGHT_B2, LOW);

     }else if(va == 'b'){      //후진
       Serial.println("backward");
       digitalWrite(LEFT_A1, LOW);
       digitalWrite(LEFT_B1, HIGH);
       digitalWrite(RIGHT_A2, LOW);
       digitalWrite(RIGHT_B2, HIGH);

     }else if(va == 's'){      //정지
       Serial.println("stop");    
       digitalWrite(LEFT_A1, LOW);
       digitalWrite(LEFT_B1, LOW);
       digitalWrite(RIGHT_A2, LOW);
       digitalWrite(RIGHT_B2, LOW);
      }
     }
  }
}
