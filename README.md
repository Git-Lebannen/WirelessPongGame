# WirelessPongGame
school Arduino project

Lebannen und Clyptos

Projektbeschreibung „Wireless Arduino Pong Game“

Funktionalitaet:

Wireless-Arduino-Pong-Game ist ein zwei Spieler Spiel das über selbst hergestellte und designte wireless-Controller läuft. Als Microkontroller wird das NodeMCU mit integriertem ESP 32 WROOM 32 verwendet. Die hauptsächlichen Umsetzunspunkte sind die Verbindung der Controller mit der NodeMCU über Wlan, die Herstellung der Controller (Case und Motherboard) und die Verbindung des über den NodeMCU eingehenden Inputs mit einem Pong-Game.
Die Controller werden über einen Knopf, der zum Spielstart, pausieren und Selektieren verwendet wird, und einen Encoder (Endlosdrehregler), der die jeweilige Pong-Platte reguliert, verfügen. Zum Spielstart müssen beide Spieler ihren Knopf gedrückt halten, genauso wie fürs Pausieren. Das Selektieren läuft über den Hauptcontroller. Der Encoder bewirkt bei Rechtsdrehen eine Steigung der Pong-Platte und bei Linksdrehen eine Senkung der Platte. Im Pausenmenü kann der Hauptcontroller sich mit Hilfe des Encoders über verschiedene selektierbare Optionen bewegen und mit dem Knopf auswählen. Auswählbare Optionen werden Sound, (Vibration), movementspeed und ballspeed (fürs Erste). 

Code-Verständniss:

Input.ino code liest die übertragenen Informationen in den Serial port. Das C# programm nimmt die Informationen wieder aus dem Serial port raus und übersetzt sie in das Spiel. 
