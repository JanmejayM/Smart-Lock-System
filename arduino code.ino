//Arduino code

#include <Keypad.h>
#include <Wire.h>
#include<LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(3,2);

#define Password_Length 5
#define relay 11
#define buzzer A3

LiquidCrystal_I2C lcd(0x27,16,2);
const byte rows = 4; //four rows
const byte cols = 3; //three columns
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[rows] = {10, 9, 8, 7}; //connect to the row pinouts of the keypad
byte colPins[cols] = {6,5,4}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );
byte data_count;
char Password[5]="1234";
char Data[5];

void setup()
{
  
  pinMode(relay,OUTPUT);
  Serial.begin(9600);
  
  ArduinoUno.begin(4800);
  // put your setup code here, to run once:
    lcd.init();                      // initialize the lcd
    lcd.backlight();
    digitalWrite(relay,HIGH);
   
}
void loop(){
  int door=0;
  // put your main code here, to run repeatedly:
 lcd.setCursor(0,0);
 lcd.print(" 4 Digit Pin:");
 char key=keypad.getKey();
 delay(20);
     




if(key)
{
  Data[data_count]=key;
  lcd.setCursor(data_count+6,1);
  lcd.print("*");
  data_count++;
  delay(100);
 

}

  
  if(!strcmp(Data,Password))//0 when equal
{
 
  lcd.setCursor(0,0);
  lcd.print("Correct Pin");
  digitalWrite(relay,LOW);
  door=0; 
 

  delay(200);
  lcd.clear();
  lcd.print("Door is Open");
  delay(10000);
  digitalWrite(relay,HIGH);
    while(data_count){
    Data[data_count--]=0;
  }
  lcd.clear();
 
  delay(500);
}
else if(data_count>=4 || !strcmp(Data,Password)  ){
  lcd.clear();
 
  door=door+1;
  digitalWrite(relay,HIGH);
    tone(buzzer,3500,4000);

  lcd.clear();
    lcd.setCursor(2,0);
  lcd.print("Unauthorized");
  lcd.setCursor(5,1);
  lcd.print("Access");
  delay(5000);
      noTone(buzzer);

  lcd.clear();
  
  
    while(data_count){
    Data[data_count--]=0;
  }
 
  delay(500);
 
}

   
else{
  
}

  
ArduinoUno.print(door);
   ArduinoUno.println("\n");
  delay(20);
}
![image](https://user-images.githubusercontent.com/89799094/145670659-7704e6c6-c733-4ad4-b13b-0a9ceefecd58.png)
