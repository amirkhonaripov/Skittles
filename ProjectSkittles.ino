/* This code works with GY-31 TCS3200 TCS230 color sensor module
 * It select a photodiode set and read its value (Red Set/Blue set/Green set) and displays it on the Serial monitor
 */

#define s0 2       //Module pins wiring
#define s1 3
#define s2 4
#define s3 5
#define out 6
#include <Servo.h>
Servo colorSorter;   //define your servo name

int b = 0;
int g = 0;
int r = 0;
int data=0;        //This is where we're going to stock our values

void setup() 
{
   pinMode(s0,OUTPUT);    //pin modes
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);
   colorSorter.attach(8);  //connect servo

   Serial.begin(9600);   //intialize the serial monitor baud rate
   
   digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100% (recommended)
   digitalWrite(s1,HIGH); //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
   
}

void loop()                  //Every 2s we select a photodiodes set and read its data
{
   colorSorter.write(1);
   delay(1000);
   colorSorter.write(50);
   delay(2000);
   digitalWrite(s2,LOW);        //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
   digitalWrite(s3,LOW);
   Serial.print("Red value= "); 
   r = GetData();

   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   Serial.print("Blue value= ");
   b = GetData();

   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   Serial.print("Green value= ");
   g = GetData();
   
   Serial.println();
   
   if(r >=30 && r <=60 && b >= 70 && b <= 100 && g >= 100 && g <= 130){
    Serial.println("The color is pink");
   }
   else if(r >=25 && r <=55 && b >= 65 && b <= 95 && g >= 65 && g <= 95){
    Serial.println("The color is orange");
   }
   else if(r >=10 && r <=40 && b >= 50 && b <= 80 && g >= 25 && g <= 60){
    Serial.println("The color is yellow");
   }
   else if(r >=55 && r <=80 && b >= 80 && b <= 110 && g >= 50 && g <= 80){
    Serial.println("The color is green");
   }
   else if(r >=80 && r <=110 && b >= 90 && b <= 120 && g >= 120 && g <= 150){
    Serial.println("The color is purple");
   }
   else{
    Serial.println("The color was not identified!");
   }
   delay(2000);
   colorSorter.write(106);
   delay(2000);
}

int GetData(){
   data=pulseIn(out,LOW);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
   Serial.print(data);          //it's a time duration measured, which is related to frequency as the sensor gives a frequency depending on the color
   Serial.print("\t");          //The higher the frequency the lower the duration
   delay(20);
   return data;
}
