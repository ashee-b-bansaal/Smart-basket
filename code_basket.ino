#include <SoftwareSerial.h>
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#include <stdlib.h>
#include <dht.h>
#define dht_dpin A0 
int mq135;
int mq9;
int i, j;
dht DHT;

char buf1[16];
char buf2[16];
char buf3[16];
char buf4[16];
char buf5[16];
String strmq135;
String strmq9;

String stri;
String strj;

// replace with your channel's thingspeak API key
String apiKey = "INYN3P915WIIDETA";


SoftwareSerial ser(5, 6); // RX, TX

// this runs once
void setup() {                
  // initialize the digital pin as an output.
   lcd.begin(16, 2);
lcd.setCursor(0, 0);
 lcd.print("IOT Sensor ");

 delay(2000);
 lcd.clear();
 
analogReference(DEFAULT);
  // enable debug serial
  Serial.begin(9600);
  // enable software serial
  ser.begin(115200);
// reset ESP8266
  ser.println("AT+RST");
   delay(500);
  ser.println("AT+CWMODE=3");
   delay(500);
  ser.println("AT+CWJAP=\"project\",\"12345678\"");
  delay(500);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
    pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(A2, INPUT);
    pinMode(A3, INPUT);
      pinMode(A4, INPUT);
      digitalWrite(A4, HIGH);
}


// the loop
void loop() {
   DHT.read11(dht_dpin);
      

 i=DHT.humidity;
      j =DHT.temperature;

mq9 = analogRead(A1); //mq9
mq135 = analogRead(A3); //mq135
if(i>70 || j>39 || mq9>800 || mq135>800)
{
  digitalWrite(2, HIGH);
}
else
{
   digitalWrite(2, LOW);
}

    lcd.setCursor(0, 0);
     lcd.print("mq9:");
 lcd.print(mq9);
 lcd.print(" ");
  
    lcd.setCursor(8, 0);
     lcd.print("m35:");
 lcd.print(mq135);
 lcd.print(" ");
  lcd.setCursor(0, 1);
     lcd.print("H:");
 lcd.print(i);
 lcd.print(" ");
  lcd.setCursor(8, 1);
   lcd.print("T:");
 lcd.print(j);
 lcd.print(" ");
  
// convert to string
  strmq135 = dtostrf(mq135, 4, 1, buf1);
 strmq9 = dtostrf(mq9, 4, 1, buf2);

  // convert to string

  stri = dtostrf(i, 4, 1, buf3);
strj = dtostrf(j, 4, 1, buf4);
  
  
   Serial.print(strmq135);
     Serial.print(" ");
   Serial.print(strmq9);
     Serial.print(" ");
    Serial.print(stri);
  Serial.print(" ");
   Serial.print(strj);
 
  Serial.println(" ");
String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);

  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }


 // prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field4=";
  getStr += String(strmq135);
  getStr += "\r\n\r\n";




// send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);


   if(ser.find(">")){
    ser.print(getStr);
  }
   else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
  delay(6000);
   DHT.read11(dht_dpin);
      

 i=DHT.humidity;
      j =DHT.temperature;

mq9 = analogRead(A1); //mq9
mq135 = analogRead(A3); //mq135
if(i>70 || j>39 || mq9>800 || mq135>800)
{
  digitalWrite(2, HIGH);
}
else
{
   digitalWrite(2, LOW);
}

    lcd.setCursor(0, 0);
     lcd.print("mq9:");
 lcd.print(mq9);
 lcd.print(" ");
  
    lcd.setCursor(8, 0);
     lcd.print("m35:");
 lcd.print(mq135);
 lcd.print(" ");
  lcd.setCursor(0, 1);
     lcd.print("H:");
 lcd.print(i);
 lcd.print(" ");
  lcd.setCursor(8, 1);
   lcd.print("T:");
 lcd.print(j);
 lcd.print(" ");
  
// convert to string
  strmq135 = dtostrf(mq135, 4, 1, buf1);
 strmq9 = dtostrf(mq9, 4, 1, buf2);

  // convert to string

  stri = dtostrf(i, 4, 1, buf3);
strj = dtostrf(j, 4, 1, buf4);
  
  
   Serial.print(strmq135);
     Serial.print(" ");
   Serial.print(strmq9);
     Serial.print(" ");
    Serial.print(stri);
  Serial.print(" ");
   Serial.print(strj);
 
  Serial.println(" ");
  
 
  String cmd1 = "AT+CIPSTART=\"TCP\",\"";
  cmd1 += "184.106.153.149"; // api.thingspeak.com
  cmd1 += "\",80";
  ser.println(cmd1);

  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }


 // prepare GET string
  String getStr1 = "GET /update?api_key=";
  getStr1 += apiKey;
  getStr1 +="&field1=";
  getStr1 += String(strmq9);
  getStr1 += "\r\n\r\n";




// send data length
  cmd1 = "AT+CIPSEND=";
  cmd1 += String(getStr1.length());
  ser.println(cmd1);


   if(ser.find(">")){
    ser.print(getStr1);
  }
   else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }

  // thingspeak needs 15 sec delay between updates
  delay(6000);
 DHT.read11(dht_dpin);
      

 i=DHT.humidity;
      j =DHT.temperature;

mq9 = analogRead(A1); //mq9
mq135 = analogRead(A3); //mq135
if(i>70 || j>39 || mq9>800 || mq135>800)
{
  digitalWrite(2, HIGH);
}
else
{
   digitalWrite(2, LOW);
}

    lcd.setCursor(0, 0);
     lcd.print("mq9:");
 lcd.print(mq9);
 lcd.print(" ");
  
    lcd.setCursor(8, 0);
     lcd.print("m35:");
 lcd.print(mq135);
 lcd.print(" ");
  lcd.setCursor(0, 1);
     lcd.print("H:");
 lcd.print(i);
 lcd.print(" ");
  lcd.setCursor(8, 1);
   lcd.print("T:");
 lcd.print(j);
 lcd.print(" ");
  
// convert to string
  strmq135 = dtostrf(mq135, 4, 1, buf1);
 strmq9 = dtostrf(mq9, 4, 1, buf2);

  // convert to string

  stri = dtostrf(i, 4, 1, buf3);
strj = dtostrf(j, 4, 1, buf4);
  
  
   Serial.print(strmq135);
     Serial.print(" ");
   Serial.print(strmq9);
     Serial.print(" ");
    Serial.print(stri);
  Serial.print(" ");
   Serial.print(strj);
 
  Serial.println(" ");
 
   // TCP connection
  String cmd2 = "AT+CIPSTART=\"TCP\",\"";
  cmd2 += "184.106.153.149"; // api.thingspeak.com
  cmd2 += "\",80";
  ser.println(cmd2);

  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }


 // prepare GET string
  String getStr2 = "GET /update?api_key=";
  getStr2 += apiKey;
  getStr2 +="&field2=";
  getStr2 += String(stri);
  getStr2 += "\r\n\r\n";




// send data length
  cmd2 = "AT+CIPSEND=";
  cmd2 += String(getStr2.length());
  ser.println(cmd2);


   if(ser.find(">")){
    ser.print(getStr2);
  }
   else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }



  // thingspeak needs 15 sec delay between updates
  delay(6000);

  DHT.read11(dht_dpin);
      

 i=DHT.humidity;
      j =DHT.temperature;

mq9 = analogRead(A1); //mq9
mq135 = analogRead(A3); //mq135
if(i>70 || j>39 || mq9>800 || mq135>800)
{
  digitalWrite(2, HIGH);
}
else
{
   digitalWrite(2, LOW);
}

    lcd.setCursor(0, 0);
     lcd.print("mq9:");
 lcd.print(mq9);
 lcd.print(" ");
  
    lcd.setCursor(8, 0);
     lcd.print("m35:");
 lcd.print(mq135);
 lcd.print(" ");
  lcd.setCursor(0, 1);
     lcd.print("H:");
 lcd.print(i);
 lcd.print(" ");
  lcd.setCursor(8, 1);
   lcd.print("T:");
 lcd.print(j);
 lcd.print(" ");
  
// convert to string
  strmq135 = dtostrf(mq135, 4, 1, buf1);
 strmq9 = dtostrf(mq9, 4, 1, buf2);

  // convert to string

  stri = dtostrf(i, 4, 1, buf3);
strj = dtostrf(j, 4, 1, buf4);
  
  
   Serial.print(strmq135);
     Serial.print(" ");
   Serial.print(strmq9);
     Serial.print(" ");
    Serial.print(stri);
  Serial.print(" ");
   Serial.print(strj);
 
  Serial.println(" ");
   // TCP connection
  String cmd3 = "AT+CIPSTART=\"TCP\",\"";
  cmd3 += "184.106.153.149"; // api.thingspeak.com
  cmd3 += "\",80";
  ser.println(cmd3);

  if(ser.find("Error")){
    return;
  }


 // prepare GET string
  String getStr3 = "GET /update?api_key=";
  getStr3 += apiKey;
  getStr3 +="&field3=";
  getStr3 += String(strj);
  getStr3 += "\r\n\r\n";




// send data length
  cmd3 = "AT+CIPSEND=";
  cmd3 += String(getStr3.length());
  ser.println(cmd3);


   if(ser.find(">")){
    ser.print(getStr3);
  }
   else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }


  // thingspeak needs 15 sec delay between updates
  delay(6000);
 DHT.read11(dht_dpin);
      

 i=DHT.humidity;
      j =DHT.temperature;

mq9 = analogRead(A1); //mq9
mq135 = analogRead(A3); //mq135
if(i>70 || j>39 || mq9>800 || mq135>800)
{
  digitalWrite(2, HIGH);
}
else
{
   digitalWrite(2, LOW);
}

    lcd.setCursor(0, 0);
     lcd.print("mq9:");
 lcd.print(mq9);
 lcd.print(" ");
  
    lcd.setCursor(8, 0);
     lcd.print("m35:");
 lcd.print(mq135);
 lcd.print(" ");
  lcd.setCursor(0, 1);
     lcd.print("H:");
 lcd.print(i);
 lcd.print(" ");
  lcd.setCursor(8, 1);
   lcd.print("T:");
 lcd.print(j);
 lcd.print(" ");
  
// convert to string
  strmq135 = dtostrf(mq135, 4, 1, buf1);
 strmq9 = dtostrf(mq9, 4, 1, buf2);

  // convert to string

  stri = dtostrf(i, 4, 1, buf3);
strj = dtostrf(j, 4, 1, buf4);
  
  
   Serial.print(strmq135);
     Serial.print(" ");
   Serial.print(strmq9);
     Serial.print(" ");
    Serial.print(stri);
  Serial.print(" ");
   Serial.print(strj);
 
  Serial.println(" ");
}
