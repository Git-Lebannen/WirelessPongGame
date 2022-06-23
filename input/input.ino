// writes commands to the serial port corresponding to IR inputs chosen by two players using remotes
#include <IRremote.h>

/*
  pinning for IR receiver:
  facing front:
  - left: 5V
  - middle: GND
  - right: 11
  pinning for RGB LED
  facing front(marker mark), left to right:
  - 1: 3
  - 2: 5
  - 3: 6
  - 4: GND
*/

// set pins and variables
const byte RECEIVER_PIN = 11;
const byte LED_R_PIN = 3;
const byte LED_G_PIN = 5;
const byte LED_B_PIN = 6;
int commands_P1[5];
int commands_P2[5];
bool firstSet = true;


void setup() {
  // set RGB_LED pins to outputs
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);

  // begin serial port and IR receiving
  Serial.begin(115200);
  IrReceiver.begin(RECEIVER_PIN);
  Serial.println("IR receiving has begun.");

  // set IR command storage arrays
  do {
    set(commands_P1, 1);
    set(commands_P2, 2);
  } while (!check());
}


void loop() {
  // get input and print corresponding commands to serial port
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.command == commands_P1[0]) {
      Serial.write("P1UP");
    }
    else if (IrReceiver.decodedIRData.command == commands_P1[1]) {
      Serial.write("P1DOWN");
    }
    else if (IrReceiver.decodedIRData.command == commands_P1[2]) {
      Serial.write("P1LEFT");
    }
    else if (IrReceiver.decodedIRData.command == commands_P1[3]) {
      Serial.write("P1RIGHT");
    }
    else if (IrReceiver.decodedIRData.command == commands_P1[4]) {
      Serial.write("P1ENTER");
    }
    else if (IrReceiver.decodedIRData.command == commands_P2[0]) {
      Serial.write("P2UP");
    }
    else if (IrReceiver.decodedIRData.command == commands_P2[1]) {
      Serial.write("P2DOWN");
    }
    else if (IrReceiver.decodedIRData.command == commands_P2[2]) {
      Serial.write("P2LEFT");
    }
    else if (IrReceiver.decodedIRData.command == commands_P2[3]) {
      Serial.write("P2RIGHT");
    }
    else if (IrReceiver.decodedIRData.command == commands_P2[4]) {
      Serial.write("P2ENTER");
    }
  }
}


void set(int commands[], int p) {
  // returns an array with values from IR remote

  rgbProtocol("set");

  if (p == 1) {
    Serial.println("Player One:");
  } else {
    Serial.println("Player Two:");
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

  if (p == 1) {
    Serial.print("Setting complete, Player One's commands are: ");
  } else {
    Serial.print("Setting complete, Player Two's commands are: ");
  }

  for (int i = 0; i < 5; i++) {
    Serial.print(commands[i]);
  }
}


bool check() {
  if (!firstSet) {
    rgbProtocol("error");
    Serial.println("Some input values are not distinct, please check these values and try again: ");
    for (int i = 0; i < 5; i++) {
      Serial.println("input ");
      Serial.print(i + 1);
      Serial.println("Player One: ");
      Serial.print(commands_P1[i]);
      Serial.print(" - Player Two: ");
      Serial.print(commands_P2[i]);
    }
  }
  
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (commands_P1[i] == commands_P2[j]) {
        return false;
      }
    }
  }
  return true;
}


void rgbProtocol(String protocol) {
  if (protocol == "set") {
    for (int i = 0; i < 3; i++) {
      analogWrite(LED_B_PIN, 255);
      delay(10);
      analogWrite(LED_B_PIN, 0);  
    }
  }
  
  else if (protocol == "error") {
    for (int i = 0; i < 3; i++) {
      analogWrite(LED_R_PIN, 255);
      delay(10);
      analogWrite(LED_R_PIN, 0);  
    }
  }
}
