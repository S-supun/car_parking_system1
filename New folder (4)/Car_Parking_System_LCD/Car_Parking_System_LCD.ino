#include <LiquidCrystal_I2C.h>

#include <Servo.h>  //includes the servo library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR 0x27   // I2C address of the LCD
#define LCD_COLUMNS 16  // Number of columns in your LCD
#define LCD_ROWS 4      // Number of rows in your LCD
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

Servo myservo;

#define ir_enter 2
#define ir_back 4

#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8

unsigned long startTime1 = 0;
unsigned long parkingDuration1 = 0;
bool parked1 = false;
unsigned long startTime2 = 0;
unsigned long parkingDuration2 = 0;
bool parked2 = false;
unsigned long startTime3 = 0;
unsigned long parkingDuration3 = 0;
bool parked3 = false;
unsigned long startTime4 = 0;
unsigned long parkingDuration4 = 0;
bool parked4 = false;

int S1 = 0, S2 = 0, S3 = 0, S4 = 0;
int flag1 = 0, flag2 = 0;
int slot = 4;
void setup() {
  Serial.begin(9600);

  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);


  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);

  myservo.attach(3);
  myservo.write(90);

  lcd.begin(16,4);
  lcd.setCursor(0, 1);
  lcd.print(" Car parking  ");
  lcd.setCursor(4, 2);
  lcd.print("    System     ");
  lcd.backlight();
  delay(2000);
  lcd.clear();
  Read_Sensor();

  int total = S1 + S2 + S3 + S4;
  slot = slot - total;
}

void loop() {

  Read_Sensor();

  lcd.setCursor(0, 0);
  lcd.print(" Have Slot: ");
  lcd.print(slot);
  lcd.print("    ");

  lcd.setCursor(0, 1);
  if (S1 == 1) {
    lcd.print("S1:Fill ");
    if (!parked1) {
      startTime1 = millis();  // Record the start time when the car is parked
      parked1 = true;
    }
  }

  else {
    lcd.print("S1:Emp");
    if (parked1) {
      lcd.clear();
      parkingDuration1 = millis() - startTime1;  // Calculate parking duration
      lcd.setCursor(0, 1);
      lcd.print("S1 Parking time: ");
      lcd.setCursor(0, 2);
      lcd.print(parkingDuration1 / 1000);  // Convert milliseconds to seconds
      lcd.setCursor(2, 2);
      lcd.println(" seconds");
      parked1 = false;
      delay(2000);
      lcd.clear();
    }
  }
  
  lcd.setCursor(8, 1);
  if (S2 == 1) {
    lcd.print("S2:Fill ");
    if (!parked2) {
      startTime2 = millis();  // Record the start time when the car is parked
      parked2 = true;
    }
  } else {
    lcd.print("S2:Emp");
    if (parked2) {
      lcd.clear();
      parkingDuration2 = millis() - startTime2;  // Calculate parking duration
      lcd.setCursor(0, 1);
      lcd.print("S2 Parking time: ");
      lcd.setCursor(0, 2);
      lcd.print(parkingDuration2 / 1000);  // Convert milliseconds to seconds
      lcd.setCursor(2, 2);
      lcd.println(" seconds");
      parked2 = false;
      delay(2000);
      lcd.clear();
    }
  }

  lcd.setCursor(0, 2);
  if (S3 == 1) {
    lcd.print("S3:Fill ");
    if (!parked3) {
      startTime3 = millis();  // Record the start time when the car is parked
      parked3 = true;
    }
  }

  else {
    lcd.print("S3:Emp");
    if (parked3) {
      lcd.clear();
      parkingDuration3 = millis() - startTime3;  // Calculate parking duration
      lcd.setCursor(0, 1);
      lcd.print("S3 Parking time: ");
      lcd.setCursor(0, 2);
      lcd.print(parkingDuration3 / 1000);  // Convert milliseconds to seconds
      lcd.setCursor(2, 2);
      lcd.println(" seconds");
      parked3 = false;
      delay(2000);
      lcd.clear();
    }
  }

  lcd.setCursor(0, 3);
  if (S4 == 1) {
    lcd.print("S4:Fill ");
    if (!parked4) {
      startTime4 = millis();  // Record the start time when the car is parked
      parked4 = true;
    }
  } else {
    lcd.print("S4:Emp");
    if (parked4) {
      lcd.clear();
      parkingDuration4 = millis() - startTime4;  // Calculate parking duration
      lcd.setCursor(0, 1);
      lcd.print("S4 Parking tme: ");
      lcd.setCursor(0, 2);
      lcd.print(parkingDuration4 / 1000);  // Convert milliseconds to seconds
      lcd.setCursor(2, 2);
      lcd.println(" seconds");
      parked4 = false;
      delay(2000);
      lcd.clear();
    }
  }


  if (digitalRead(ir_enter) == 0 && flag1 == 0) {
    if (slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo.write(180);
        slot = slot - 1;
      }
    } else {

      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(" Sorry ");
      lcd.setCursor(1, 2);
      lcd.print("Parking full");
      delay(1500);
      lcd.clear();
    }
  }

  if (digitalRead(ir_back) == 0 && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo.write(180);
      slot = slot + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    myservo.write(90);
    flag1 = 0, flag2 = 0;
  }

  delay(1);
}


void Read_Sensor() {
  S1 = 0, S2 = 0, S3 = 0, S4 = 0;

  if (digitalRead(ir_car1) == 0) { S1 = 1; }
  if (digitalRead(ir_car2) == 0) { S2 = 1; }
  if (digitalRead(ir_car3) == 0) { S3 = 1; }
  if (digitalRead(ir_car4) == 0) { S4 = 1; }
}