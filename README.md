# WirelessPongGame
Schul Arduino Projekt

Lebannen und Clyptos

Projektbeschreibung „Wireless Arduino Pong Game“

Funktionalitaet:

Wireless-Arduino-Pong-Game ist ein zwei Spieler Spiel das über beliebige IR Fernbedienungen läuft. 
Als Microkontroller wird das Arduino Uno verwendet. 
Das Spiel und die Inputs werden in verschiedenen Programmen gehandlet, Arduino ist zur Datenaufnahme zustaendig.
Der hauptsächliche Umsetzungspunkt ist die Datenübertrageung über den serial Port.

Programm Ablauf (arduino):

Der Arduino Teil des Projektes wurde von Lebannen erstellt. 
Es wird vorausgesetzt dass die Spieler (2 Stueck) jeweils eine Infrarotfernbedienung mit mindestens 5 verschieden Signalen bzw. Buttons hat.
Das Programm kommuniziert ueber den Seriellen Monitor mit den Spielern welche Arbeitsschritte sie abzuarbeiten haben.
Im Lauf des Programms werden zwei Arrays mit Integern gefuellt, welche die Infrarot Signale der Spielerinputs darstellen.
Wenn diese Arrays gefuellt sind und es keine Ueberschneidungen in den Werten gibt, werden die Infrarotsignale die der IRreceiver empfaengt,
mit den Werten in den Arrays verglichen und gegebenenfalls die korrespondierenden Inputs an den seriellen Port geschrieben.
