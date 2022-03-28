#include <IRremote.h>

int receiver = 11;
int commands[5] = {0, 3, 0, 0, 0};

void setup()
{
   Serial.begin(115200);
   Serial.println("Beginn IR receiving.");
   IrReceiver.begin(receiver, ENABLE_LED_FEEDBACK);
   Serial.println("Press the buttons you want to use as controls on your remote in this order: up, down, left, right, enter.");
   set();
}

void loop()
{
  for (int i = 0; i == 5; i++)
  {
    Serial.println(commands[i]);
  }  
  read();
}

void read()
{
   if (IrReceiver.decode())
   {
      Serial.println(IrReceiver.decodedIRData.command, HEX);
      IrReceiver.resume();
   }
}

void set()
{
  for (int i = 0; i == 5; i++)
  {
    commands[i] = IrReceiver.decodedIRData.command;
    i ++;
    Serial.println(i);
  }
}

/*
# include <IRremote.h>
int reader = 4;
gVv = 0
gVh = 0

void setup()
{
  Serial.begin(9600);
  
  // setup IR receiver
  IrReceiver.begin(reader);
}

void loop()
{
  // read inputs ()
  if (IrReceiver.decode())
  {
   switch (IrReceiver.decodedIRData.command)
   {
       
   // up
   case 0x46:
    gVv = 1
    serial.write(gVv)
    break;
       
   // down
   case 0x15:
    gvV = -1
    serial.write(gVv)
    break;
       
   // left
   case 0x44:
    gVh = -1
    serial.write(gVh)
    break;
       
   // right
   case 0x43:
    gVh = 1
    serial.write(gVh)
    break;
   }
  }
}
*/
