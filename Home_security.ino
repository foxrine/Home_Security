#include <Wire.h> 
#include <LiquidCrystal.h>
#include <Keypad.h>
//Smart_home security

#define Password_Length 8 
#define Password_Length1 8 


#include <Servo.h>

Servo myservo; 


int servopos = 0;  
int count=0;

int x=0;
int RED = 30;
int GREEN = 28;

const int pir = 13;
int signalPin = 12;
int buzzer = 24;
int led = 26;
int pirtriiger=0;

char Data[Password_Length]; 
char Master[Password_Length] = "1234567"; 
char Master1[Password_Length1]= "2345678";
byte data_count = 0, master_count = 0;
byte data_count1 = 0;
bool Pass_is_good;
char customKey;


const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
int gsm=0;
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd (A0, A1, A2, A3, A4, A5); // pins of the LCD. (RS, E, D4, D5, D6, D7)


void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}

void clearData1(){
  while(data_count1 !=0){
    Data[data_count1--] = 0; 
  }
  return;
}

void red_on() {
    digitalWrite (RED, HIGH);
      digitalWrite (GREEN, LOW);
      Serial.println("Red");
      delay(1000);
}

void green_on() {
  digitalWrite (RED, LOW);
    digitalWrite (GREEN, HIGH);
    Serial.println("Green");
    delay(1000);
}

void alert_sms()
{
  if(Serial.available() >0)
 {
 Serial.println("AT+CMGF=1"); // set SMS mode to text
 delay(50);
 Serial.println("AT+CMGS=\"01739003528\"");//Change the receiver phone number
 delay(50);
 Serial.print("An intruder has been detected ");    //the message you want to send
 delay(50);
 Serial.write(26);
 delay(50);
}
}
void setup(){
  
  
  lcd.begin(20,4);

  
  pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
digitalWrite (RED, LOW);
digitalWrite (GREEN, LOW);
  pinMode(signalPin, OUTPUT);
  pinMode(pir, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  myservo.attach(11);
  Serial.begin(115200);
  Serial1.begin(9600);
  Serial2.begin(115200);
}

void loop(){
 
  lcd.setCursor(0, 0);
  lcd.print("     Welcome to    ");
  lcd.setCursor(0, 1);
  lcd.print("Home Security System");
  lcd.setCursor(0, 2);
  lcd.print("Enter Your Password");
  lcd.setCursor(0, 3);
  lcd.print("___________________");
  lcd.clear();

 Serial.println("Enter Password:");
    x = Serial1.read();
   // Serial1.println(x);

  customKey = customKeypad.getKey();


  
  if (customKey){
    Data[data_count] = customKey; 
  
    Serial.print(Data[data_count]); 
    data_count++; 
    }
    if(x ==136) //green
    {


      
      
      green_on();
     

lcd.setCursor(0, 0);
lcd.print ("Voice activation");
lcd.setCursor(0, 1);
lcd.print ("  Successful  ");
delay(5000);
lcd.clear();
lcd.setCursor(0, 1);
lcd.print (" System is active ");
delay(3000);
lcd.clear();
      
      while(1)
      {
              pirtriiger=digitalRead(pir);
              if(pirtriiger==HIGH)


{
  
             myservo.write(0);    
             digitalWrite(24, HIGH);
             digitalWrite(26, HIGH);
             lcd.setCursor(0, 1);
             lcd.print ("Intruder detected!");
             delay(5000); 
             lcd.clear();
             
             
             gsm=gsm+1;
              if (gsm==1)
             {
             alert_sms();
             }
             
 
}
  
    x = Serial1.read();  
  if(x ==241) 
   {
      red_on();

      lcd.setCursor(0, 1);
      lcd.print ("  System has been  ");
      lcd.setCursor(0, 2);
      lcd.print ("   deactivated  ");
      delay(2000);
      lcd.clear();
       myservo.write(80);
           digitalWrite(24, LOW);
           digitalWrite(26, LOW);
           gsm=0;
           break;
    }
      }
    }
  if(data_count == Password_Length-1){

   
    if(!strcmp(Data, Master)&&(count==0)){

lcd.setCursor(0, 1);
lcd.print ("Password is Correct!");
delay(2000);
lcd.clear();

       
     Serial.println("Correct");
      
      digitalWrite(signalPin, HIGH); 
      delay(5000);
      
      digitalWrite(signalPin, LOW);

      
      Serial.println("System activate");
      green_on();

      lcd.setCursor(0, 1);
      lcd.print (" System is active ");
      delay(5000);
      lcd.clear();
   
    

     
     while(1)
          {
              pirtriiger=digitalRead(pir);
              if(pirtriiger==HIGH)


{
  
             myservo.write(0);    
             digitalWrite(24, HIGH);
             digitalWrite(26, HIGH);

             lcd.setCursor(0, 1);
             lcd.print ("Intruder detected!");
             delay(10000); 
             lcd.clear();
             
             count=count+1;
             gsm=gsm+1;
             if (gsm==1)
             {
              alert_sms();
             }
             
             
 
}
  
   customKey = customKeypad.getKey();
   
    if (customKey){
    Data[data_count1] = customKey; 
        x = Serial1.read();

    Serial.print(Data[data_count1]); 
    data_count1++; 
  }
    
   
   if(data_count1 == Password_Length-1){
   if (!strcmp(Data, Master1) && (count==1))

          
          {

          
           
           myservo.write(80);
           digitalWrite(24, LOW);
           digitalWrite(26, LOW);

            lcd.setCursor(0, 1);
           lcd.print ("  System has been  ");
           lcd.setCursor(0, 2);
           lcd.print ("   deactivated  ");
           delay(5000);
          lcd.clear(); 
           count=0;
          
           red_on();
           clearData();
           clearData1();
           gsm=0;
           break;
          
          }
      
         }
       }
     }

    
  
     
  }
    
}




