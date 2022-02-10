#include "DHT.h" 
#include <Wire.h> 
#define DHTPIN 2     // what pin we're connected to 
#define DHTTYPE DHT22   // DHT 22  (AM2302) 
#define fan 4 
#define relay 3 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 
  
int maxTemp = 35; 
int minTemp = 30; 
int maxHum = 70; 
int minHum = 60; 
  
  
DHT dht(DHTPIN, DHTTYPE); 
  
void setup() { 
  pinMode(relay, OUTPUT); 
    pinMode(fan, OUTPUT); 
  Serial.begin(9600); 
    dht.begin(); 
    lcd.begin(16,2); 
    lcd.init(); 
  lcd.backlight(); 
} 
  
void loop() { 
  // Wait a few seconds between measurements. 
  delay(2000); 
  
  // Reading temperature or humidity takes about 250 milliseconds! 
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor) 
  float h = dht.readHumidity(); 
  // Read temperature as Celsius 
  float t = dht.readTemperature(); 
  
  // Check if any reads failed and exit early (to try again). 
  if (isnan(h) || isnan(t)) { 
    Serial.println("Failed to read from DHT sensor!"); 
    return; 
  } 
  
      if( t < minTemp) { // if temp is lower than minimum temp 
      // Heater on 
      digitalWrite(relay, 255); 
   } 
    if( t > maxTemp ) { // if temp is higher than maximum temp 
      // Heater off 
     analogWrite(relay, LOW); 
   } 
     if( h > maxHum) { // if hum is higher than maximum hum 
      // fan is spinning 
      analogWrite(fan, 255); 
   } 
    if( h < minHum ) { // if hum is lower than minimum hum 
      // fan is not spinning 
      digitalWrite(fan, LOW); 
   } 
  
  Serial.print("Humidity: "); 
  Serial.print(h); 
  Serial.print(" %\t"); 
  Serial.print("Temperature: "); 
  Serial.print(t); 
  Serial.println(" *C "); 
    
    lcd.clear(); 
    lcd.setCursor(0,0); 
    lcd.print("Temp: "); 
    lcd.print(t); 
    lcd.print(" "); 
    lcd.print((char)223); 
    lcd.print("C"); 
     lcd.setCursor(0,1); 
    lcd.print("Hum: "); 
     lcd.print(h); 
    lcd.print(" %"); 
    delay(1000); //Delay 1 sec. 
} 