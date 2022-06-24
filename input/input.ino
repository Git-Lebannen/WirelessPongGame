  // writes commands to the serial port corresponding to IR inputs chosen by two players using remotes
#include <IRremote.h>

/*
  pinning for IR receiver:
  facing front:
  - left: 11
  - middle: GND
  - right: 5v
  pinning for RGB LED (common cathode)
  facing front(marker mark), left to right:
  - 1: 3 (R)
  - 2: 5 (G)
  - 3: GND
  - 4: 6 (B)
*/

// set pins and variables
const byte RECEIVER_PIN = 12;
const byte LED_R_PIN = 3;
const byte LED_G_PIN = 5;
const byte LED_B_PIN = 6;
int commands_P1[5];
int commands_P2[5];

/*
  mapping for inputs:
           P1    P2
  -------------------         
  up    |  11 |  21 |
  down  |  12 |  22 |
  left  |  13 |  23 |
  right |  14 |  24 |
  center|  15 |  25 |
*/

byte input;


void setup() {
  // set RGB_LED pins to outputs
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);

  // begin serial port and IR receiving
  Serial.begin(115200);
  IrReceiver.begin(RECEIVER_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR receiving has begun.");

  // set IR command storage arrays
  do {
    set(commands_P1, 1);
    set(commands_P2, 2);
  } while (!check());
  
  rgbProtocol("confirm");
  Serial.println("\nSetup complete, ready to take players' inputs");
}


void loop() {
  // get input and print corresponding commands to serial port
  input = 0;
    
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.command == commands_P1[0]) {
      input = 11;
    }
    else if (IrReceiver.decodedIRData.command == commands_P1[1]) {
      input = 12;
    }
    else if (IrReceiver.decodedIRData.command == commands_P1[2]) {
      input = 13;
    }
    else if (IrReceiver.decodedIRData.command == commands_P1[3]) {
      input = 14;
    }
    else if (IrReceiver.decodedIRData.command == commands_P1[4]) {
      input = 15;
    }
    else if (IrReceiver.decodedIRData.command == commands_P2[0]) {
      input = 21;
    }
    else if (IrReceiver.decodedIRData.command == commands_P2[1]) {
      input = 22;
    }
    else if (IrReceiver.decodedIRData.command == commands_P2[2]) {
      input = 23;
    }
    else if (IrReceiver.decodedIRData.command == commands_P2[3]) {
      input = 24;
    }
    else if (IrReceiver.decodedIRData.command == commands_P2[4]) {
      input = 25;
    }
    if (input != 0) {
      Serial.println(input);      
    }
    IrReceiver.resume();
  }
}


void set(int commands[], int p) {
  // returns an array with values from IR remote

  rgbProtocol("set");

  if (p == 1) {
    Serial.println("\nPlayer One:");
  } else {
    Serial.println("\nPlayer Two:");
  }

  Serial.println("Press the buttons you want to use as controls on your remote in this order: up, down, left, right, enter.");

  int i = 0;
  while (i < 5) {
    if (IrReceiver.decode()) {

      int command = IrReceiver.decodedIRData.command;
      if (i > 0 && commands[i - 1] == command) {
        i--;
      }
      commands[i] = command;

      i++;
      IrReceiver.resume();
    }
  }

  delay(2000);

  if (p == 1) {
    Serial.println("Setting complete, Player One's commands are: ");
  } else {
    Serial.println("Setting complete, Player Two's commands are: ");
  }

  for (int i = 0; i < 5; i++) {
    Serial.print(F("input "));
    Serial.print(i + 1);
    Serial.print(F(": "));
    Serial.println(commands[i]);
  }
}


bool check() {  
  for (int i = 0; i < 5; i++) {  
    if (i < 4 and (commands_P1[i] == commands_P1[i+1] or commands_P2[i] == commands_P2[i+1])) {
      printCommandError();
      return false;
    }
    else if (i == 4 and (commands_P1[i] == commands_P1[0] or commands_P2[i] == commands_P2[0])) {     
      printCommandError();
      return false;
    }
   
    for (int j = 0; j < 5; j++) {
      if (commands_P1[i] == commands_P2[j]) {
        printCommandError();
        return false;
      }
    } 
  }
  return true;
}


void printCommandError() {
  rgbProtocol("error");
  Serial.println("\nSome input values are not distinct, please check these values and try again: ");
  for (int i = 0; i < 5; i++) {
    Serial.print(F("input "));
    Serial.println(i + 1);
    Serial.print(F("Player One: "));
    Serial.print(commands_P1[i]);
    Serial.print(F(" - Player Two: "));
    Serial.println(commands_P2[i]);
  }
}


void rgbProtocol(String protocol) {
  if (protocol == "set") {
    for (int i = 0; i < 3; i++) {
      analogWrite(LED_B_PIN, 255);
      delay(500);
      analogWrite(LED_B_PIN, 0);  
      delay(500);
    }
  }
  
  else if (protocol == "error") {
    for (int i = 0; i < 3; i++) {
      analogWrite(LED_R_PIN, 255);
      delay(500);
      analogWrite(LED_R_PIN, 0);  
      delay(500);      
    }
  }

  else if (protocol == "confirm") {
    for (int i = 0; i < 3; i++) {
      analogWrite(LED_G_PIN, 255);
      delay(500);
      analogWrite(LED_G_PIN, 0);  
      delay(500);
    }
  }
}
