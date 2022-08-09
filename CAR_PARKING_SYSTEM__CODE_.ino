
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <Servo.h>
Servo myservo1;
//int IR1 = 8; // IR Sensor 1
//int IR2 = 9; // IR Sensor 2
int Slot = 4;      //Enter Total number of parking Slots
int flag1 = 0;
int flag2 = 0;
#define echoPin 8 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 9 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin2 11 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin2 12 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
long  duration2; // variable for the duration of sound wave travel
int distance2; // variable for the distance measurement
void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT
   Serial.begin(9600);
  lcd.init();
  lcd.backlight();
 // pinMode(IR1, INPUT);
 // pinMode(IR2, INPUT);
  myservo1.attach(10);
  myservo1.write(0);
  lcd.setCursor (0, 0);
  lcd.print("     SMART     ");
  lcd.setCursor (0, 1);
  lcd.print(" PARKING SYSTEM ");
  delay (4000);
  lcd.clear();
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delay(600);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delay(500);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if ((distance > 3 &&distance < 12)&& flag1 == 0) {
    if (Slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo1.write(90);
        Slot = Slot - 1;
        lcd.setCursor (0, 0);
  lcd.print("  WELCOME!  ");
  lcd.setCursor (0, 1);
  lcd.print("Slot Left: ");
  lcd.print(Slot);
      }
    } else {
      lcd.setCursor (0, 0);
      lcd.print("      SORRY     ");
      lcd.setCursor (0, 1);
      lcd.print(" Parking Full ");
      delay (3000);
      lcd.clear();
    }
  }
  // Clears the trigPin condition
  digitalWrite(trigPin2, LOW);
  delay(600);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin2, HIGH);
  delay(500);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance2: ");
  Serial.print(distance2);
  Serial.println(" cm");
  
  if ((distance2 > 3 &&distance2 < 12) && flag2 == 0&& flag1 == 0&& Slot<4) {
    flag2 = 1;
    
      myservo1.write(90);
      Slot = Slot + 1;
      lcd.setCursor (0, 0);
  lcd.print("  Thanks!  ");
  lcd.setCursor (0, 1);
  lcd.print("Slot Left: ");
  lcd.print(Slot);
  delay(1500);
  flag2 = 0;
    if (flag2 == 0) {
      myservo1.write(0);
    }
    
  }
  if ((distance2 > 3 &&distance2 < 12) && flag2 == 0&& flag1 == 1) {
    flag1 = 0;
    if (flag1 == 0) {
      myservo1.write(0);
    }
  }
  if ((distance > 3 &&distance < 12) && flag1 == 0&& flag2 == 1) {
   
  }
//  if (flag1 == 1 && flag2 == 1) {
//    delay (1000);
//    myservo1.write(100);
//    flag1 = 0, flag2 = 0;
//  }
//  lcd.setCursor (0, 0);
//  lcd.print("  WELCOME!  ");
//  lcd.setCursor (0, 1);
//  lcd.print("Slot Left: ");
//  lcd.print(Slot);
}
