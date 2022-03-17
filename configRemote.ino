# include <IRremote.h>
int EmpfaengerPin = 11;

void setup()
{
 Serial.begin(9600);
 // Empfänger starten
 IrSender.begin(EmpfaengerPin);.
}

void loop()
{
 // Daten lesen
 if (IrReceiver.decode())
 {
 /*
 printIRResultMinimal zeigt die verwendete Taste
 P = Protokoll
 C = Kommando in Hex
 */

 Serial.print(F("P = Protokoll C = Taste hexadezimal: "));
 IrReceiver.printIRResultMinimal(&Serial);
 Serial.print(F(" Dezimal: "));
 Serial.println(IrReceiver.decodedIRData.command);

 delay(200);

 // nächsten Wert lesen
 IrReceiver.resume();
 }
}
