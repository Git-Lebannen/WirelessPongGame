#include <IRremote.h>

int receiver = 11;
int commands1[5] = {0, 0, 0, 0, 0};
int commands2 = commands1;

void setup()
{
  Serial.begin(115200);
  Serial.println("Beginn IR receiving.");
  IrReceiver.begin(receiver, ENABLE_LED_FEEDBACK);
  Serial.println("Press the buttons you want to use as controls on your remote in this order: up, down, left, right, enter. Firsts Player One, then Player Two");
  set();
  for (int i = 0; i < 5; i++)
  {
    Serial.println(commands1[i]);
    Serial.println(commands2[i]);
  } 
}

void loop()
{ 
  input();
}

void input()
{
   if (IrReceiver.decode())
   {
      Serial.println(IrReceiver.decodedIRData.command);
      IrReceiver.resume();
   }
}

void set()
{
  int i = 0;
  while (i < sizeof(commands1)/sizeof(int) * 2)
  {
    if (IrReceiver.decode())
    {
      int command = IrReceiver.decodedIRData.command;
      if (i > 0 && commands1[i-1] == command)
      {
        i --;
      }
      if i == 0 or i % 2 == 0:
        commands1[i] = command;
      else:
        commands2[i - 1] = command;
      i ++;
      IrReceiver.resume();
    }
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
