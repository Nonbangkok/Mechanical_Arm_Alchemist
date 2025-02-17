#include <Servo.h>

// Declare the Constant
const int Rotate1_Pin = 9;
const int Rotate2_Pin = 10;
const int LeftHand_Pin = 11;
const int RightHand_Pin = 12;

int Rotate1_Angle = 90;
int Rotate2_Angle = 40;

// Initial the Servo 
Servo Rotate1,Rotate2,LeftHand,RightHand;

void setup(){
  // Set up Servo Pin
  Rotate1.attach(Rotate1_Pin);
  Rotate2.attach(Rotate2_Pin);
  LeftHand.attach(LeftHand_Pin);
  RightHand.attach(RightHand_Pin);

  // Set up Serial
  Serial.begin(9600);
}

// Test the Servo by Rotating the servo back and forth
void Test_the_Servo(Servo servo,int MaxAngle){
  // Rotate Forward
  for(int i=0;i<=MaxAngle;i+=5){
    servo.write(i);
    delay(100);
    Serial.println(i);
  }
  delay(300);

  // Rotate Backward
  for(int i=MaxAngle;i>=0;i-=5){
    servo.write(i);
    delay(100);
    Serial.println(i);
  }
  delay(300);
}

// Gently rotate the servo 1
void Rotate1_write(int End_Angle){
  if(Rotate1_Angle < End_Angle){
    for(int i=Rotate1_Angle;i<=End_Angle;i+=5){
      Rotate1.write(i);
      delay(200);
    }
  }else if(Rotate1_Angle > End_Angle){
    for(int i=Rotate1_Angle;i>=End_Angle;i-=5){
      Rotate1.write(i);
      delay(200);
    }
  }
  Rotate1_Angle = End_Angle;
}

// Gently rotate the servo 2
void Rotate2_write(int End_Angle){
  if(Rotate2_Angle < End_Angle){
    for(int i=Rotate2_Angle;i<=End_Angle;i+=5){
      Rotate2.write(i);
      delay(200);
    }
  }else if(Rotate2_Angle > End_Angle){
    for(int i=Rotate2_Angle;i>=End_Angle;i-=5){
      Rotate2.write(i);
      delay(200);
    }
  }
  Rotate2_Angle = End_Angle;
}

// Catch the object by rotate the servo 
void Catch(){
  LeftHand.write(180);
  RightHand.write(60);
}

// Uncatch the object by rotate the servo
void Uncatch(){
  LeftHand.write(120);
  RightHand.write(120);
}

// Stand by state before and after the misison
void Stand_by(){
  Rotate1.write(90);
  Rotate2_write(0);
  Uncatch();
}

// Rotate the mechanical arm to start point
void Move_to_start_point(){
  Rotate1.write(150);
  Rotate2_write(70);
}

// Rotate the mechanical arm to end point
void Move_to_end_point(){
  Rotate1.write(30);
  Rotate2_write(70);
}

// Go up the mechanical arm.
void Go_up(){
  Rotate2_write(0);
}

// Go down the mechanical arm.
void Go_down(){
  Rotate2_write(70);
}

// Do mission
void Do_Mission(int wait){
  Rotate1_Angle = 90;
  Rotate2_Angle = 40;

  Stand_by();
  delay(wait);

  Move_to_start_point();
  delay(wait);

  Catch();
  delay(wait);

  Go_up();
  delay(wait);

  Move_to_end_point();
  delay(wait);

  Uncatch();
  delay(wait);

  Go_up();
  delay(wait);

  Stand_by();
  delay(wait);
}

void loop(){
  Do_Mission(1000);
}
