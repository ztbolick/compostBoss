  #include <dht.h>
  #include <elapsedMillis.h>
  #include <LiquidCrystal.h>
  #define DHT11_Internal 7
  #define DHT11_External 6
  
  
  // Temp Sensor
  dht DHT;
  
  // Timer
  elapsedMillis timeElapsed;
  int minuitesElapsed;
  int secondsElapsed;
  LiquidCrystal lcd(13,12,2,3,4,5);
  
  void setup(){
    lcd.begin(16,2);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(24, OUTPUT);
    pinMode(26, OUTPUT);
    Serial.begin(9600);
  }
  
  void printTime() {
    minuitesElapsed = (int) (timeElapsed * 0.001) / 60;
    secondsElapsed = (int) (timeElapsed * 0.001);
    Serial.print("Time = ");
    Serial.print(minuitesElapsed);
    Serial.print("m - ");
    Serial.print(secondsElapsed % 60);
    Serial.print("s");
    Serial.println();
  }
  
  void printInternalTemp() {
    Serial.println("=============================================");
    int chk = DHT.read11(DHT11_Internal);
    
    // Temp
    Serial.print("Internal Temp = ");
    double temp = DHT.temperature * 1.8 + 32;
    int hui = DHT.humidity;
    if(temp > 90 || hui > 75){
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
    }
    else if(temp < 60 || hui < 40){
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
    }
    else{
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
      digitalWrite(11,LOW);
    }
    String tempStr = String((temp), 1);
    Serial.print(tempStr);
    Serial.println(" °F");
    
    
    // Humidity
    Serial.print("Internal Humi = ");
    Serial.print(hui);
    Serial.println(" %");
  
    // prints on the lcd
    lcd.setCursor(0,0);
    lcd.print("Sen1: ");
    lcd.print(tempStr);
    lcd.print("F ");
    lcd.print(hui);
    lcd.print("%");
  
    if (timeElapsed % 60000 == 0) {
      
    }
  
    
    if (timeElapsed >= 3600000) {
      timeElapsed = 0;
    }
  }
  
  void printExternalTemp() {
    int chk = DHT.read11(DHT11_External);
    int chui = DHT.humidity;
    // Temp
    Serial.print("External Temp = ");
    double temp = DHT.temperature * 1.8 + 32;
    if(temp > 90 || chui > 75){
      digitalWrite(22,HIGH);
      digitalWrite(24,LOW);
      digitalWrite(26,LOW);
    }
    else if(temp < 60 || chui < 40){
      digitalWrite(22,LOW);
      digitalWrite(24,LOW);
      digitalWrite(26,HIGH);
    }
    else{
      digitalWrite(22,LOW);
      digitalWrite(24,HIGH);
      digitalWrite(26,LOW);
    }
    String tempStr = String((temp), 1);
    Serial.print(tempStr);
    Serial.println(" °F");
    
    
    // Humidity
    Serial.print("External Humi = ");
    Serial.print(chui);
    Serial.println(" %");
    
    Serial.println("=============================================");
    Serial.println();
  
    // prints on the lcd
    lcd.setCursor(0,1);
    lcd.print("Sen2: ");
    lcd.print(tempStr);
    lcd.print("F ");
    lcd.print(chui);
    lcd.print("%");
  
    if (timeElapsed % 60000 == 0) {
      
    }
  
    
    if (timeElapsed >= 3600000) {
      timeElapsed = 0;
    }
  }
  
  void loop()
  {
    printTime();
    printInternalTemp();
    printExternalTemp();
    delay(1000);
    
  }
  

