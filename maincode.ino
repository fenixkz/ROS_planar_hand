
#include <ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int64.h>
#include <robot_control/coord.h>
#include <robot_control/accelerometr.h>
#include <dynamixel_msgs/JointState.h>
#include <Wire.h>
#include <LSM303.h>
const int Xpin = 0;
const int motorPin = 12;
const int buttonPin = 13;
const int butPin = 3;
double X;
int a = 8;
int b = 9;
int c = 2;
int d = 11;
int e = 4;
int f = 6;
int g = 7; 
int button = 0;
LSM303 compass;
char report[80];
int buttonState = 0;
ros::NodeHandle nh;
  double pos1;
  double goalpos1;
  double prevPos1 = 5;
  double diff = 0;
  double prevdiff = 5;
  int pos2;
  int pos3;
  int pos4;
  int pos5;
  int isMoving;
  int N;
  int j[5] = { 0 , 0 , 0, 0, 0 };
  int l = 0;
  int k = 0;
std_msgs::Int64 pos;

void numberCb(const std_msgs::Int64& msgN) {
  N = msgN.data;

}

void isMovingCb(const std_msgs::Int64& msg) {
     k = msg.data;
  

}




robot_control::coord coordinates;
robot_control::coord coo;
robot_control::accelerometr acceler;
ros::Publisher coord("coord", &coordinates);
ros::Publisher accel("accel", &acceler);
ros::Publisher but("isPressed", &pos);

ros::Subscriber<std_msgs::Int64> number("/motorN", numberCb);
ros::Subscriber<std_msgs::Int64> moving("/isStuck", isMovingCb);






void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Xpin, INPUT);  
  pinMode(buttonPin, INPUT);
  pinMode(butPin, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  digitalWrite(a, LOW); 
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);

  
  Wire.begin();
  compass.init();
  compass.enableDefault();



 nh.initNode();
 
 nh.subscribe(number);
 nh.subscribe(moving);
 
 nh.advertise(accel);
 nh.advertise(coord);
 nh.advertise(but);

}

void loop() {
  // put your main code here, to run repeatedly:
  j[l] = k;
  l++;
  if (l>4){
    l = 0;
  }
  button = digitalRead(butPin);
  analogWrite(motorPin, 0);
  X = analogRead(Xpin);
  
  
  buttonState = digitalRead(buttonPin);
    
  if (j[0] == 1 && j[1] == 1 && j[2] == 1 && j[3] == 1 && j[4] == 1){
    analogWrite(motorPin, 180);
  }
  
    
  
  compass.read();
  snprintf(report, sizeof(report), "A: %6d %6d %6d",
    compass.a.x, compass.a.y, compass.a.z);
  

  coordinates.x = X;
  coordinates.y = buttonState;
  pos.data = button;
  acceler.y = compass.a.y;
  acceler.x = compass.a.z;
  coo.x = j[0];
  coo.y = j[1];
  coo.vert = j[2];
  accel.publish( &acceler);
  but.publish( &pos);
  coord.publish( &coordinates);



  
  nh.spinOnce();
if (N == 0){
    led1();
  }else if(N == 1){
    
    led2();
  }else if(N == 2){
    
    led3();
  }else if(N == 3){
    
    led4();
  }else if(N == 4){
    
    led5();
  }
  delay(1);
}

void led0(){
digitalWrite(a, HIGH);
digitalWrite(b, HIGH);
digitalWrite(c, HIGH);
digitalWrite(d, HIGH);
digitalWrite(e, HIGH);
digitalWrite(f, HIGH);
digitalWrite(g, LOW);
}

void led1(){
digitalWrite(a, LOW);
digitalWrite(b, HIGH);
digitalWrite(c, HIGH); 
digitalWrite(d, LOW);
digitalWrite(e, LOW);
digitalWrite(f, LOW);
digitalWrite(g, LOW);
}

void led2(){
digitalWrite(a, HIGH);
digitalWrite(b, HIGH);
digitalWrite(c, LOW);
digitalWrite(d, HIGH);
digitalWrite(e, HIGH);
digitalWrite(f, LOW);
digitalWrite(g, HIGH);
} 

void led3(){
digitalWrite(a, HIGH);
digitalWrite(b, HIGH);
digitalWrite(c, HIGH);
digitalWrite(d, HIGH);
digitalWrite(e, LOW);
digitalWrite(f, LOW);
digitalWrite(g, HIGH);
}

void led4(){
digitalWrite(a, LOW);
digitalWrite(b, HIGH);
digitalWrite(c, HIGH);
digitalWrite(d, LOW);
digitalWrite(e, LOW);
digitalWrite(f, HIGH);
digitalWrite(g, HIGH);
}

void led5(){
digitalWrite(a, HIGH);
digitalWrite(b, LOW);
digitalWrite(c, HIGH);
digitalWrite(d, HIGH);
digitalWrite(e, LOW);
digitalWrite(f, HIGH);
digitalWrite(g, HIGH);
}

