// writes commands to the serial port corresponding to IR inputs chosen by two players using remotes

/* 
   
   pinning for IR receiver:

   facing front: 
   - left: 5V
   - middle: GND
   - right: 11

   pinning for RGB-LED:

*/

#include <IRremote.h>

// set pins 
int receiver = 11;

// initialize int arrays to hold set commands
int commands1[5];
int commands2[5];
bool setStatus = false;

// start Serial printing and IR receiving. Then set inputs 
void setup()
{
  Serial.begin(115200);
  Serial.println("Beginn IR receiving.");
  IrReceiver.begin(receiver, ENABLE_LED_FEEDBACK);

  set();
  
  if (!setStatus) {
    do {
      Serial.println("The commands weren't all distinct, see this list to make the appropriate changes:");
      set();
    } while (!setStatus);
  }
    
  for (int i = 0; i < 5; i++)
  {
    Serial.println(commands1[i]);
    Serial.println(commands2[i]);
  }   
}

// continuosly get input and print the corresponding commands to the serial port
void loop()
{ 
  input();
}

// input function which checks IR commands and maps them to users inputs
void input()
{
  if (IrReceiver.decode()) {
    switch (IrReceiver.decodedIRData.command)
    {       
      // P1 up
      case commands1[0]:
        serial.write("P1UP");
        break;

      // P1 down
      case commands1[1]:
        serial.write("P1DOWN");
        break;
      
      // P1 left
      case commands1[2]:
        serial.write("P1LEFT");
        break;

      // P1 right
      case commands1[3]:
        serial.write("P1RIGHT");
        break;

      // P1 enter
      case commands1[4]:
        serial.write("P1ENTER");
        break;

      // P2 up
      case commands2[0]:
        serial.write("P2UP");
        break;

      // P2 down
      case commands2[1]:
        serial.write("P2DOWN");
        break;
      
      // P2 left
      case commands2[2]:
        serial.write("P2LEFT");
        break;

      // P2 right
      case commands2[3]:
        serial.write("P2RIGHT");
        break;

      // P2 enter
      case commands2[4]:
        serial.write("P2ENTER");
        break;
    }
  }
}

void set() {
  Serial.println("Press the buttons you want to use as controls on your remote in this order: up, down, left, right, enter.");
  Serial.println("First Player One, then Player Two");
  
  // get inputs from both users
  for (int i = 1; i < 3; i++) {
    int j = 0;
    while ( j < 5) {
    
      if (IrReceiver.decode()) {
        
        int command = IrReceiver.decodedIRData.command;
        String commands = commands + i;
        Serial.println(commands);
        
        if (j > 0 && commands[j-1] == command) {
          j--;
        }
  
        commands[j] = command;
  
        IrReceiver.resume();

        i++;
      }
      
    }
  }

  // check both users arrays for same inputs
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {

      if (commands1[i] = commands2[j]) return;
    }
  }  

  // if there are no doubled values, set setStatus to true
  setStatus = true;
}


///////////////////////////////////////////////////////////////////////////////////////////// new code 

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

// set pins
const byte RECEIVER_PIN = 11;
const byte LED_R_PIN = 3;
const byte LED_G_PIN = 5;
const byte LED_B_PIN = 6;

// set IR command storage arrays
const byte NUM_INPUTS = 5;
int commands_P1[NUM_INPUTS];
int commands_P2[NUM_INPUTS];


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
  set(commands_P1, 1);
  set(commands_P2, 2);
  for (int i = 0; i < NUM_INPUTS; i++) {
    Serial.print(commands_P1[i]);
    Serial.print(commands_P2[i]);
  }
}


void loop() {
  // get input and print corresponding commands to serial port
  if (IrReceiver.decode()) {
    switch (IrReceiver.decodedIRData.command)
    {       
      // P1 up
      case commands_P1[0]:
        serial.write("P1UP");
        break;

      // P1 down
      case commands_P1[1]:
        serial.write("P1DOWN");
        break;
      
      // P1 left
      case commands_P1[2]:
        serial.write("P1LEFT");
        break;

      // P1 right
      case commands_P1[3]:
        serial.write("P1RIGHT");
        break;

      // P1 enter
      case commands_P1[4]:
        serial.write("P1ENTER");
        break;

      // P2 up
      case commands_P2[0]:
        serial.write("P2UP");
        break;

      // P2 down
      case commands_P2[1]:
        serial.write("P2DOWN");
        break;
      
      // P2 left
      case commands_P2[2]:
        serial.write("P2LEFT");
        break;

      // P2 right
      case commands_P2[3]:
        serial.write("P2RIGHT");
        break;

      // P2 enter
      case commands_P2[4]:
        serial.write("P2ENTER");
        break;
    }
  }
}


void set(int commands[], int p) {
  // returns an array with values from IR remote

  if (p == 1) {
    Serial.println("Player One:");
  } else {
    Serial.println("Player Two:");
  }

  Serial.println("Press the buttons you want to use as controls on your remote in this order: up, down, left, right, enter.");
  
  int i = 0;
  while (i < NUM_INPUTS) {
    if (IrReceiver.decode()) {

        int command = IrReceiver.decodedIRData.command;
        if (i > 0 && commands[i-1] == command) {
          i--;
        }  
        commands[i] = command;
        
        i++;  
        IrReceiver.resume();
    }
  }
}


void RGB_protocol(int type) {
  switch (type) {
    
    // receiving new values
    case 1:
      while (true) {
        if (IrReceiver.decode()) {
          analogWrite(LED_B_PIN, 255);
          delay(5);
          analogWrite(LED_B_PIN, 0);
        }
      }
            
    // getting input
    case 2:
      while (true) {
        if (IrReceiver.decode()) {
          analogWrite(LED_G_PIN, 255);
          delay(5);
          analogWrite(LED_G_PIN, 0);
        }
      }
      
    // error
    case 3:
      while (true) {
        if (IrReceiver.decode()) {
          analogWrite(LED_R_PIN, 255);
          delay(10);
          analogWrite(LED_R_PIN, 0);
        }
      }

    // clear RGB protocol
    case 4: 
      analogWrite(LED_R_PIN, 0);
      analogWrite(LED_G_PIN, 0);
      analogWrite(LED_B_PIN, 0);
      break;
  }
}

