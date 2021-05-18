int LM1 = 5;      
int LM2 =  18;       
int RM1 =  19;       
int RM2 =  21;
int ENA = 34;
int ENB = 35;

//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
int mode1 = 0;
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  
  SerialBT.begin("D09 ESP32"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}
void go() { 

  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

void back() {

  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}

void right() {

  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);

}

void left() {

  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);

}

void stoper() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  
}

void loop() {
  if (mode1 == 1){
    go();
  }
  else if (mode1 == 2){
    right();
  }
  else if (mode1 == 3){
    left();
  }
  else if (mode1 == 4){
    back();
  }
  else if (mode1 == 5){
    stoper();
  }
  
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
    if(SerialBT.read() == 'g'){
      mode1=1;
      Serial.println("Let go!!!");
    }
    else if(SerialBT.read() == '6'){
      mode1=2;
      Serial.println("R!!!");
    }
     else if(SerialBT.read() == '4'){
      mode1=3;
      Serial.println("L!!!");
    }
     else if(SerialBT.read() == '2'){
      mode1=4;
      Serial.println("B!!!");
    }
    else if(SerialBT.read() == '5'){
      mode1=5;
      Serial.println("S!!!");
    }
    else
    stoper();
  }
  delay(20);
}
