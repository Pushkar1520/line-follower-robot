#include <Arduino.h>

const int S1=2,S2=3,S3=4,S4=5,S5=6;
const int ENA=10,IN1=11,IN2=12,ENB=9,IN3=A1,IN4=A5;

float Kp=180.0,Ki=0.01,Kd=100.0;
const int STRAIGHT_SPEED=255,BASE_SPEED=220,MAX_SPEED=255,MIN_SPEED=-255;
const float STRAIGHT_THRESHOLD=0.25;
const int BOOST_CONFIRM=6;
const int weight[5]={-2,-1,0,1,2};

float lastError=0,integral=0;
int boostCount=0;
bool isBoosting=false;

void setup(){
  int sensorPins[]={S1,S2,S3,S4,S5};
  int motorPins[]={IN1,IN2,IN3,IN4,ENA,ENB};
  for(int i=0;i<5;i++) pinMode(sensorPins[i],INPUT);
  for(int i=0;i<6;i++) pinMode(motorPins[i],OUTPUT);
  Serial.begin(9600);
}

void driveMotors(int L,int R){
  digitalWrite(IN1,L>=0?HIGH:LOW);
  digitalWrite(IN2,L>=0?LOW:HIGH);
  if(L<0)L=-L;
  digitalWrite(IN3,R>=0?HIGH:LOW);
  digitalWrite(IN4,R>=0?LOW:HIGH);
  if(R<0)R=-R;
  analogWrite(ENA,constrain(L,0,255));
  analogWrite(ENB,constrain(R,0,255));
}

void stopMotors(){
  digitalWrite(IN1,LOW);digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);digitalWrite(IN4,LOW);
  analogWrite(ENA,0);analogWrite(ENB,0);
}

float readError(bool &allOn,bool &noneOn){
  int count=0;
  float wSum=0;
  int v[5];
  v[0]=!digitalRead(S1);v[1]=!digitalRead(S2);v[2]=!digitalRead(S3);
  v[3]=!digitalRead(S4);v[4]=!digitalRead(S5);
  for(int i=0;i<5;i++){if(v[i]){wSum+=weight[i];count++;}}
  allOn=(count==5);
  noneOn=(count==0);
  return count==0?lastError:wSum/count;
}

void loop(){
  bool allOn,noneOn;
  float error=readError(allOn,noneOn);

  if(allOn){
    stopMotors();
    integral=0;boostCount=0;isBoosting=false;
    delay(50);return;
  }

  if(abs(error)<STRAIGHT_THRESHOLD){
    if(++boostCount>=BOOST_CONFIRM)isBoosting=true;
  }else{
    boostCount=0;isBoosting=false;
  }

  integral=constrain(integral+error,-100,100);
  float correction=Kp*error+Ki*integral+Kd*(error-lastError);
  lastError=error;

  int activeBase=isBoosting?STRAIGHT_SPEED:BASE_SPEED;
  driveMotors(
    constrain(activeBase+(int)correction,MIN_SPEED,MAX_SPEED),
    constrain(activeBase-(int)correction,MIN_SPEED,MAX_SPEED)
  );
}
