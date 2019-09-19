#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library


#define LeftMotorForward 4    //right motor
#define LeftMotorBackward 5

#define RightMotorForward 6    //left motor
#define RightMotorBackward 7

#define Speedr 3     //it's common for motor1 & motor2
#define Speedl 11


//sensor pins
#define trig_pin1 8 //analog input 1
#define echo_pin1 9   //analog input 2

#define trig_pin2 A1 //analog input 1
#define echo_pin2 A2   //analog input 2

#define trig_pin3 A3 //analog input 1
#define echo_pin3 A4   //analog input 2
#define maximum_distance 175 

boolean goesForward = false;
int distance = 100;

float sr=58 ,sl=63;
NewPing sonarF(trig_pin1, echo_pin1, maximum_distance); //sensor function
NewPing sonarR(trig_pin2, echo_pin2, maximum_distance); //sensor function
NewPing sonarL(trig_pin3, echo_pin3, maximum_distance); //sensor function


void GoBack()
{
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);  
    analogWrite(Speedr,sr);         //change speed here 
    analogWrite(Speedl,sl);         //change speed here 

}
void GoForward()
{          
  
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  analogWrite(Speedr,sr);         //change speed here 
  analogWrite(Speedl,sl);         //change speed here 
  
}
void GoLeft()
{
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  
  analogWrite(Speedr,sr);         //change speed here 
  analogWrite(Speedl,sl);         //change speed here 
}
void GoRight()
{
 digitalWrite(LeftMotorForward, HIGH);
 digitalWrite(RightMotorBackward, HIGH); 
 digitalWrite(LeftMotorBackward, LOW);
 digitalWrite(RightMotorForward, LOW);
 
 analogWrite(Speedr,sr);         //change speed here 
 analogWrite(Speedl,sl);         //change speed here
 
}
void StopCar()
{  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  analogWrite(Speedr,0);         //change speed here 
  analogWrite(Speedl,0);         //change speed here 
}

void setup() 
{
pinMode(LeftMotorForward,OUTPUT);
pinMode(LeftMotorBackward,OUTPUT);
pinMode(RightMotorForward,OUTPUT);
pinMode(RightMotorBackward,OUTPUT);
pinMode(Speedr,OUTPUT);
pinMode(Speedl,OUTPUT);
Serial.begin(9600);
}

void loop() 
{
  
char reading;

if(Serial.available())
{
reading=Serial.read();
switch (reading)
 {
case 'F':
   {
   GoForward();
   break;
   }
case 'B':
   {
   GoBack();
   break;
   }
case 'R':
   {
   GoRight();
   break;
   }
case 'L':
   {
   GoLeft();
   break;
   }
case '3':
   {
    sr=58 ,sl=63;
    break;
   }
case '5':
   {
    sr=88 ,sl=93;
   break;
   }
case '8':
   {
    sr=108 ,sl=113;
   break;
   }
case '9':
   {
 sr=128 ,sl=133;
   break;
   }
case 'V':
   {  
  delay(8000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100); 
  sr=58 ,sl=63;
  
   while(1)
       {
         moveForward();
         int distanceRight = 0;
         int distanceLeft = 0;
         delay(50);
         if (distance <= 15)
           {
             moveStop();
             delay(150);
             moveBackward();
             delay(250);
             moveStop();
             delay(250);
             distanceRight = lookRight();
             delay(150);
             distanceLeft = lookLeft();
             delay(150);

             if (distanceRight > distanceLeft)
                 {
                   turnRight();
                   moveStop();
                 }
            else
                 {
                  turnLeft();
                  moveStop();
                 }
           }
      else
        {
          if(lookRight()<=5)
             AdjustLeft();
     else if(lookLeft()<=5)
             AdjustRight();
    
          moveForward(); 
        }
   distance = readPing();
    }
   break;
   }
default :
  {
   StopCar();
   break;
  }
 }
}

}


int lookRight()
{  
  int x=sonarR.ping_cm();
  if(x==0)
     x=250;
  return x;
}

int lookLeft()
{
  
  int x=sonarL.ping_cm();
  if(x==0)
     x=250;
  return x;
}

int readPing()
{
  
  int x=sonarF.ping_cm();
  if(x==0)
     x=250;
  return x; 
}

void moveStop()
{  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  
  analogWrite(Speedr,0);   
  analogWrite(Speedl,0);        //change speed here 
}

void moveForward()
{

  if(!goesForward)
  {
    goesForward=true;

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
    
  analogWrite(Speedr,sr);   
  analogWrite(Speedl,sl);        //change speed here 
  }

}

void moveBackward()
{

  goesForward=false;
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);  
  analogWrite(Speedr,sr);   
  analogWrite(Speedl,sl);        //change speed here 
}

void turnRight()
{
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  analogWrite(Speedr,sr);   
  analogWrite(Speedl,sl);        //change speed here 
  delay(420);
  
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);

  
  analogWrite(Speedr,sr);   
  analogWrite(Speedl,sl);        //change speed here 
}

void turnLeft()
{

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  
  analogWrite(Speedr,sr);   
  analogWrite(Speedl,sl);        //change speed here 
  
  delay(420);
  
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  analogWrite(Speedr,sr);   
  analogWrite(Speedl,sl);        //change speed here 
}


void AdjustLeft()
{

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  
  analogWrite(Speedr,sr);   
  analogWrite(Speedl,sl);        //change speed here 
  
  delay(40);
  
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  analogWrite(Speedr,sr);   
  analogWrite(Speedl,sl);        //change speed here 
}

void AdjustRight()
{
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  analogWrite(Speedr,sr);   
  analogWrite(Speedl,sl);        //change speed here 
  
  delay(40);
  
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);

  
  analogWrite(Speedr,sr);   
  analogWrite(Speedl,sl);        //change speed here   
}
 
