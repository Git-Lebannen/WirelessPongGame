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
    gVv += 1
    serial.print(gVv)
    break;
       
   // down
   case 0x15:
    gvV -= 1
    serial.print(gVv)
    break;
       
   // left
   case 0x44:
    gVh -= 1
    serial.print(gVh)
    break;
       
   // right
   case 0x43:
    gVh += 1
    serial.print(gVh)
    break;
   }
  }
}
